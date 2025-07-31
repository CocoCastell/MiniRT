/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color ambient_reflection(t_scene *scene, t_color color)
{
  t_color tmp_color;
	t_color	new_color;

  tmp_color = scale_color(color_mult(color, scene->amb_color), scene->amb_ratio);
  new_color = tmp_color;
	return (new_color);
}

void  lambert_diffuse_reflection(t_hit_info *hit, t_light light, int i)
{
  float   angle;
  float   intensity;
  t_color diffuse_color;

  angle = max(0, dot(hit->normal, hit->light_dir));
  intensity = light.intensity[i];
  diffuse_color = scale_color(color_mult(hit->color, light.color[i]), intensity);
  diffuse_color = scale_color(diffuse_color, hit->dist_attenuation);
  hit->color = add_color(hit->color, scale_color(diffuse_color, angle));
}

void  specular_reflection(t_hit_info *hit, t_light light, int i, t_scene *scene)
{
  t_color spec_color;
  t_vec3  reflect_ray;
  t_vec3	ray_dir;
  float   spec_factor;

  ray_dir = normalize(vector_from_to(hit->point, scene->camera.pos));  
  reflect_ray = normalize(vector_from_to(light.pos[i], hit->point));
  reflect_ray = normalize(get_reflected_vec(reflect_ray, hit->normal));
  spec_factor = pow(max(0, dot(reflect_ray, ray_dir)), get_shininess(scene, hit));
  spec_color = scale_color(light.color[i], light.intensity[i]);
  spec_color = scale_color(spec_color, spec_factor * get_spec_force(scene, hit));
  spec_color = scale_color(spec_color, hit->dist_attenuation);
  hit->color = add_color(hit->color, spec_color);
}

void  idk_reflection(t_hit_info *hit, t_scene *scene, unsigned int depth)
{
  t_ray       reflect_ray;
  t_vec3      reflect_dir;
  t_hit_info  reflect_hit;
	t_vec3      bias_pos;

  if (depth == 0)
    return ;
	bias_pos = add_vector(hit->point, scale_vec(hit->normal, 0.1f));
  reflect_dir = normalize(get_reflected_vec(vector_from_to(scene->camera.pos, hit->point), hit->normal));
  reflect_ray = make_ray(bias_pos, reflect_dir);
  reflect_hit = scene_intersect(reflect_ray, scene, vec3(100, 100, 100)); // const
  if (reflect_hit.has_hit == false)
    return ;
  apply_reflections(scene, &reflect_hit, --depth);
  hit->color = add_color(scale_color(hit->color, 0.6), scale_color(reflect_hit.color, 0.4));
}

void	apply_reflections(t_scene *scene, t_hit_info *hit, unsigned int depth)
{
  int  i;

	hit->color = scene->sphere.color[hit->ent_index];
	hit->color = ambient_reflection(scene, hit->color);
	if (scene->light.count == 0 || depth == 0)
    return ;
  i = -1;
  fill_hit_normal(hit, scene);
  while (++i < scene->light.count)
  {
    fill_light_data(hit, scene, i);
	  if (hit->in_shadow)
      continue ;
    lambert_diffuse_reflection(hit, scene->light, i);
    specular_reflection(hit, scene->light, i, scene);
  }
  idk_reflection(hit, scene, depth); // Execute even in shadow I think 
}