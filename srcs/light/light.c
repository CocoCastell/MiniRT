/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 11:54:27 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ambient_reflection(t_scene *scene, t_hit_info *hit)
{
	t_color	tmp_color;

	tmp_color = color_mult(hit->material_color, scene->amb_color);
	if (scene->settings.scene_creation_on)
		tmp_color = scale_color(tmp_color, 0.8f);
	else
		tmp_color = scale_color(tmp_color, scene->amb_ratio);
	hit->color = add_color(hit->color, tmp_color);
}

/**
 * @brief Applies Lambertian diffuse reflection to a hit point.
 *
 * Computes the diffuse light contribution from a single light source at
 * index `i`, based on the surface normal, light direction, and light color.
 * Updates the hit color in-place by adding the scaled diffuse component.
 *
 * @param hit Pointer to the hit information containing surface and light data.
 * @param light Light source structure containing intensity and color arrays.
 * @param i Index of the light source to use for the diffuse calculation.
 */
void	lambert_diffuse_reflection(t_hit_info *hit, t_light light, int i)
{
	float	angle;
	float	intensity;
	t_color	diffuse_color;

	angle = max(0, dot(hit->normal, hit->light_dir));
	intensity = light.intensity[i];
	diffuse_color = color_mult(hit->material_color, light.color[i]);
	diffuse_color = scale_color(diffuse_color, angle);
	diffuse_color = scale_color(diffuse_color, intensity);
	diffuse_color = scale_color(diffuse_color, hit->dist_attenuation);
	hit->color = add_color(hit->color, diffuse_color);
}

/**
 * @brief Computes and applies the specular reflection component to the
 * hit color.
 *
 * Uses the Phong reflection model to calculate the specular highlight based
 * on the angle between the reflected light direction and the viewer direction.
 * Modulates by shininess, specular force, and distance attenuation.
 *
 * @param hit Pointer to the hit information (includes position, normal, color).
 * @param light Light source data (position, color, intensity).
 * @param i Index of the light source being considered.
 * @param scene Pointer to the scene for accessing camera position and material
 * parameters.
 */

t_vec3 sub_vector(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return (result);
}

void	specular_reflection(t_hit_info *hit, t_light light, int i, t_scene *s)
{
	t_color	spec_color;
	t_vec3	reflect_ray;
	t_vec3	view_dir;
	float	spec_factor;

    view_dir = normalize(hit->point);
		reflect_ray = normalize(get_reflected_vec(hit->light_dir, hit->normal));
    spec_factor = powf(max(0, dot(reflect_ray, view_dir)), get_shininess(s, hit));
    spec_color = scale_color(light.color[i], light.intensity[i]);
    spec_color = scale_color(spec_color, spec_factor * get_spec_force(s, hit));
    spec_color = scale_color(spec_color, hit->dist_attenuation);
    hit->color = add_color(hit->color, spec_color);
}

/**
 * @brief Applies mirror-like reflection recursively to simulate reflective
 * surfaces.
 *
 * Casts a secondary ray in the reflected direction based on the surface normal
 * and incident ray. Blends the reflected color with the original hit color based
 * on reflectivity. Stops recursion when depth reaches zero or no intersection
 * is found.
 *
 * @param hit Pointer to the current hit information.
 * @param scene Pointer to the scene for intersection testing.
 * @param depth Remaining recursion depth for reflections.
 */
void	mirror_reflection(t_hit_info *hit, t_scene *scene, unsigned int depth)
{
	t_ray		reflect_ray;
	t_vec3		reflect_dir;
	t_vec3		bias_pos;
	t_hit_info	reflect_hit;

	if (depth == 0)
		return ;
	reflect_dir = normalize(get_reflected_vec(hit->incident_ray, hit->normal));
	bias_pos = add_vector(hit->point, scale_vector(hit->normal, 1e-4f));
	reflect_ray = make_ray(bias_pos, reflect_dir);
	init_ray(&reflect_hit, vec3(999, 999, 999), false); // const
	scene_intersect(&reflect_hit, reflect_ray, scene);
	reflect_hit.incident_ray = reflect_ray.direction;
	reflect_hit.point = add_vector(reflect_ray.origin, \
		scale_vector(reflect_ray.direction, reflect_hit.distance));
	if (reflect_hit.has_hit == false)
		reflect_hit.color = scene->background;
	else
		apply_reflections(scene, &reflect_hit, --depth);
	hit->color = add_color(scale_color(hit->color, 1 - get_reflectivity(hit, \
		scene)), scale_color(reflect_hit.color, get_reflectivity(hit, scene)));
}

/**
 * @brief Applies all reflection and lighting models to a surface hit.
 *
 * Computes ambient, diffuse, and specular reflections for each light source,
 * applies shadow checks, and handles optional mirror reflection if enabled.
 * Modifies the final hit color accordingly.
 *
 * @param scene Pointer to the scene containing lights, camera, and settings.
 * @param hit Pointer to hit information structure (position, normal, color,etc)
 * @param depth Recursion depth allowed for mirror reflections.
 */
void	apply_reflections(t_scene *scene, t_hit_info *hit, unsigned int depth)
{
	int	i;

	set_hit_color(hit, scene);
	if (scene->settings.checkered_on)
		checkered_pattern(hit, scene);
	ambient_reflection(scene, hit);
	if (scene->light.count == 0 || scene->settings.scene_creation_on)
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
	if (scene->settings.mirror_on)
		mirror_reflection(hit, scene, depth);
}