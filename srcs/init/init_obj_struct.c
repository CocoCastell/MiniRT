/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/03 20:15:09 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	init_sphere(t_scene *scene, int sphere_nb)
{
	t_sphere		sphere;

	sphere.count = sphere_nb;
	if (sphere_nb == 0)
		return (0);
	sphere.radius = malloc(sizeof(float) * sphere_nb);
	sphere.color = malloc(sizeof(t_color) * sphere_nb);
	sphere.center = malloc(sizeof(t_vec3) * sphere_nb);
	sphere.shininess = malloc(sizeof(float) * sphere_nb);
	sphere.spec_force = malloc(sizeof(float) * sphere_nb);
	sphere.reflectivity = malloc(sizeof(float) * sphere_nb);
	if (!sphere.radius
		|| !sphere.color
		|| !sphere.center
		|| !sphere.shininess
		|| !sphere.spec_force
		|| !sphere.reflectivity)
		return (1);
	scene->sphere = sphere;
	return (0);
}

int	init_plane(t_scene *scene, int plane_nb)
{
	t_plane		plane;

	plane.count = plane_nb;
	if (plane_nb == 0)
		return (0);
	plane.color = malloc(sizeof(t_color) * plane_nb);
	plane.point = malloc(sizeof(t_vec3) * plane_nb);
	plane.normal = malloc(sizeof(t_vec3) * plane_nb);
	plane.shininess = malloc(sizeof(float) * plane_nb);
	plane.spec_force = malloc(sizeof(float) * plane_nb);
	plane.reflectivity = malloc(sizeof(float) * plane_nb);
	if (!plane.color
		|| !plane.point
		|| !plane.normal
		|| !plane.shininess
		|| !plane.spec_force
		|| !plane.reflectivity)
		return (1);
	scene->plane = plane;
	return (0);
}

int	init_cylinder(t_scene *scene, int cylinder_nb)
{
	t_cylinder		cylinder;

	cylinder.count = cylinder_nb;
	if (cylinder_nb == 0)
		return (0);
	cylinder.radius = malloc(sizeof(float) * cylinder_nb);
	cylinder.color = malloc(sizeof(t_color) * cylinder_nb);
	cylinder.center = malloc(sizeof(t_vec3) * cylinder_nb);
	cylinder.axis = malloc(sizeof(t_vec3) * cylinder_nb);
	cylinder.height = malloc(sizeof(float) * cylinder_nb);
	cylinder.shininess = malloc(sizeof(float) * cylinder_nb);
	cylinder.spec_force = malloc(sizeof(float) * cylinder_nb);
	cylinder.reflectivity = malloc(sizeof(float) * cylinder_nb);
	if (!cylinder.radius
		|| !cylinder.color
		|| !cylinder.center
		|| !cylinder.axis
		|| !cylinder.height
		|| !cylinder.shininess
		|| !cylinder.spec_force
		|| !cylinder.reflectivity)
		return (1);
	scene->cylinder = cylinder;
	return (0);
}

int	init_triangle(t_scene *scene, int triangle_nb)
{
	t_triangle		triangle;

	triangle.count = triangle_nb;
	if (triangle_nb == 0)
		return (0);
	triangle.point_a = malloc(sizeof(t_vec3) * triangle_nb);
	triangle.point_b = malloc(sizeof(t_vec3) * triangle_nb);
	triangle.point_c = malloc(sizeof(t_vec3) * triangle_nb);
	triangle.color = malloc(sizeof(t_color) * triangle_nb);
	triangle.shininess = malloc(sizeof(float) * triangle_nb);
	triangle.spec_force = malloc(sizeof(float) * triangle_nb);
	triangle.reflectivity = malloc(sizeof(float) * triangle_nb);
	if (!triangle.point_a
		|| !triangle.point_b
		|| !triangle.point_c
		|| !triangle.color
		|| !triangle.shininess
		|| !triangle.spec_force
		|| !triangle.reflectivity)
		return (1);
	scene->triangle = triangle;
	return (0);
}

int	init_light(t_scene *scene, int light_nb)
{
	t_light	light;

	light.count = light_nb;
	if (light_nb == 0)
		return (0);
	light.color = malloc(sizeof(t_color) * light_nb);
	light.pos = malloc(sizeof(t_vec3) * light_nb);
	light.intensity = malloc(sizeof(float) * light_nb);
	if (!light.color || !light.pos || !light.intensity)
		return (1);
	scene->light = light;
	return (0);
}
