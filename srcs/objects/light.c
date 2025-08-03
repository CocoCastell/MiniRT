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

#include "../../includes/miniRT.h"

/**
 * @brief Computes the ambient reflection component for a given base color.
 *
 * Applies the global ambient light of the scene to the input color using
 * the ambient color and ambient ratio defined in the scene.
 *
 * @param scene Pointer to the scene containing ambient light parameters.
 * @param color The base surface color.
 * @return The resulting ambient-reflected color.
 */
t_color ambient_reflection(t_scene *scene, t_color color)
{
  t_color tmp_color;
	t_color	new_color;

  tmp_color = scale_color(color_mult(color, scene->amb_color), scene->amb_ratio);
  new_color = tmp_color;
	return (new_color);
}

/**
 * @brief Applies Lambertian diffuse reflection to a hit point.
 *
 * Computes the diffuse light contribution from a single light source at index `i`,
 * based on the surface normal, light direction, and light color. Updates the hit
 * color in-place by adding the scaled diffuse component.
 *
 * @param hit Pointer to the hit information containing surface and light data.
 * @param light Light source structure containing intensity and color arrays.
 * @param i Index of the light source to use for the diffuse calculation.
 */
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

/**
 * @brief Computes and applies the specular reflection component to the hit color.
 *
 * Uses the Phong reflection model to calculate the specular highlight based on the
 * angle between the reflected light direction and the viewer direction. Modulates
 * by shininess, specular force, and distance attenuation.
 *
 * @param hit Pointer to the hit information (includes position, normal, color).
 * @param light Light source data (position, color, intensity).
 * @param i Index of the light source being considered.
 * @param scene Pointer to the scene for accessing camera position and material parameters.
 */
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

/**
 * @brief Applies mirror-like reflection recursively to simulate reflective surfaces.
 *
 * Casts a secondary ray in the reflected direction based on the surface normal and
 * incident ray. Blends the reflected color with the original hit color based on
 * reflectivity. Stops recursion when depth reaches zero or no intersection is found.
 *
 * @param hit Pointer to the current hit information.
 * @param scene Pointer to the scene for intersection testing.
 * @param depth Remaining recursion depth for reflections.
 */
void  mirror_reflection(t_hit_info *hit, t_scene *scene, unsigned int depth)
{
  t_ray       reflect_ray;
  t_vec3      reflect_dir;
  t_hit_info  reflect_hit;
	t_vec3      bias_pos;

  if (depth == 0)
    return ;
  reflect_dir = normalize(get_reflected_vec(hit->incident_ray, hit->normal));
	bias_pos = add_vector(hit->point, scale_vec(hit->normal, 1e-4f));
  reflect_ray = make_ray(bias_pos, reflect_dir);
  reflect_hit = scene_intersect(reflect_ray, scene, vec3(100, 100, 100)); // cont
  reflect_hit.incident_ray = reflect_ray.direction; 
  reflect_hit.point = add_vector(reflect_ray.origin, scale_vec(reflect_ray.direction, reflect_hit.distance));
  if (reflect_hit.has_hit == false)
    return ;
  apply_reflections(scene, &reflect_hit, --depth);
  hit->color = add_color(scale_color(hit->color, 1 - get_reflectivity(hit, scene)), scale_color(reflect_hit.color, get_reflectivity(hit, scene)));
}

/**
 * @brief Applies all reflection and lighting models to a surface hit.
 *
 * Computes ambient, diffuse, and specular reflections for each light source,
 * applies shadow checks, and handles optional mirror reflection if enabled.
 * Modifies the final hit color accordingly.
 *
 * @param scene Pointer to the scene containing lights, camera, and settings.
 * @param hit Pointer to hit information structure (position, normal, color, etc.).
 * @param depth Recursion depth allowed for mirror reflections.
 */
void	apply_reflections(t_scene *scene, t_hit_info *hit, unsigned int depth)
{
  int  i;

  set_hit_color(hit, scene);
	hit->color = ambient_reflection(scene, hit->color);
	if (scene->light.count == 0)
    return ;
  i = -1;
  set_hit_normal(hit, scene);
  while (++i < scene->light.count)
  {
    set_light_data(hit, scene, i);
	  if (hit->in_shadow)
      continue ;
    lambert_diffuse_reflection(hit, scene->light, i);
    specular_reflection(hit, scene->light, i, scene);
  }
  if (scene->settings.mirror_on == true)
    mirror_reflection(hit, scene, depth);
}