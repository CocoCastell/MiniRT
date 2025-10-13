/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 11:06:06 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	get_shininess(t_scene *scene, t_hit_info *hit)
{
	if (hit->type == SPHERE)
		return (scene->sphere.shininess[hit->ent_index]);
	else if (hit->type == PLANE)
		return (scene->plane.shininess[hit->ent_index]);
	else if (hit->type == CYLINDER)
		return (scene->cylinder.shininess[hit->ent_index]);
	return (0.0f);
}

float	get_spec_force(t_scene *scene, t_hit_info *hit)
{
	if (hit->type == SPHERE)
		return (scene->sphere.spec_force[hit->ent_index]);
	else if (hit->type == PLANE)
		return (scene->plane.spec_force[hit->ent_index]);
	else if (hit->type == CYLINDER)
		return (scene->cylinder.spec_force[hit->ent_index]);
	return (0.0f);
}

float	get_reflectivity(t_hit_info *hit, t_scene *scene)
{
	if (hit->type == SPHERE)
		return (scene->sphere.reflectivity[hit->ent_index]);
	else if (hit->type == PLANE)
		return (scene->plane.reflectivity[hit->ent_index]);
	else if (hit->type == CYLINDER)
		return (scene->cylinder.reflectivity[hit->ent_index]);
	return (0.0f);
}

/* t_vec3 get_reflected_vec(t_vec3 incident_vec, t_vec3 normal)
{
    float dot_prod = dot(incident_vec, normal);
    t_vec3 scaled_normal = scale_vector(normal, 2.0f * dot_prod);
    return (vector_from_to(scaled_normal, incident_vec));
} */
t_vec3	get_reflected_vec(t_vec3 incident_vec, t_vec3 normal)
{
	t_vec3	scaled_normal;

	scaled_normal = scale_vector(normal, 2.0f * dot(incident_vec, normal));
	return (vector_from_to(incident_vec, scaled_normal));
}
