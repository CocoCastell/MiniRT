/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 11:44:29 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_hit_normal(t_hit_info *hit, t_scene *scene)
{
	if (hit->type == SPHERE)
		hit->normal = normalize(vector_from_to(\
					scene->sphere.center[hit->ent_index], hit->point));
	if (hit->type == PLANE)
		hit->normal = scene->plane.normal[hit->ent_index];
	if (hit->type == CYLINDER)
	{
    t_vec3 axis = normalize(scene->cylinder.axis[hit->ent_index]);
    t_vec3 center = scene->cylinder.center[hit->ent_index];
		t_vec3 center_to_hit = vector_from_to(center, hit->point);
    t_vec3 projection = scale_vector(axis, dot(center_to_hit, axis));
    t_vec3 point_on_axis = add_vector(center, projection);
    t_vec3 normal = vector_from_to(point_on_axis, hit->point);
    hit->normal = normalize(normal);
  }
	if (hit->type == CYLINDER_CAP)
	{

	}
}

/* 	if (hit->type == CYLINDER)
	{
		t_vec3 axis = normalize(scene->cylinder.axis[hit->ent_index]);
		t_vec3 center = scene->cylinder.center[hit->ent_index];
		t_vec3 pc = vector_from_to(center, hit->point);
		t_vec3 proj_vec = scale_vector(axis, dot(pc, axis)); // projection de pc sur l'axe
		t_vec3 normal = vector_from_to(proj_vec, pc);      // soustraction pour obtenir la composante perpendiculaire
		hit->normal = normalize(normal);
	}*/

		// t_vec3 center_on_plane = vec3(scene->cylinder.center[hit->ent_index].x, hit->point.y, scene->cylinder.center[hit->ent_index].z);
		// hit->normal = normalize(vector_from_to(center_on_plane, hit->point));
	// if (hit->type == CYLINDER)
	// {
    // t_vec3 axis = normalize(scene->cylinder.axis[hit->ent_index]);
    // t_vec3 center_to_hit = vector_from_to(scene->cylinder.center[hit->ent_index], hit->point);
    // float proj_length = dot(center_to_hit, axis);
    // t_vec3 projection = scale_vector(axis, proj_length);
    // t_vec3 point_on_axis = add_vector(scene->cylinder.center[hit->ent_index], projection);
    // hit->normal = normalize(vector_from_to(point_on_axis, hit->point));
  //   printf("Normal cylindre: (%f, %f, %f)\n", hit->normal.x, hit->normal.y, hit->normal.z);
	// }	

void	set_hit_color(t_hit_info *hit, t_scene *scene)
{
	hit->color = create_color(0.0f, 0.0f, 0.0f);
	if (hit->type == SPHERE)
		hit->material_color = scene->sphere.color[hit->ent_index];
	if (hit->type == PLANE)
		hit->material_color = scene->plane.color[hit->ent_index];
	if (hit->type == CYLINDER || hit->type == CYLINDER_CAP)
		hit->material_color = scene->cylinder.color[hit->ent_index];
}

void	set_light_data(t_hit_info *hit, t_scene *scene, int i)
{
	t_ray	light_ray;
	t_vec3	light_vec;
	t_vec3	shadow_bias_pos;

	light_vec = vector_from_to(hit->point, scene->light.pos[i]);
	hit->light_dir = normalize(light_vec);
	shadow_bias_pos = add_vector(hit->point, scale_vector(hit->normal, 1e-4f));
	light_ray = make_ray(shadow_bias_pos, hit->light_dir);
	hit->in_shadow = true;
	if (pre_shadow_calcul(hit, light_ray))
		return ;
	if (is_in_shadow(light_ray, scene, vector_sq_length(light_vec)))
		return ;
	hit->in_shadow = false;
	hit->dist_attenuation = distance_attenuation(light_vec);
}
