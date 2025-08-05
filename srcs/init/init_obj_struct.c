/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	init_sphere(t_scene *scene, int sphere_nb)
{
	t_sphere		sphere;
	
	sphere.count = sphere_nb;
	if (sphere_nb == 0)
		return ;
	sphere.radius = malloc(sizeof(float) * sphere_nb);
	sphere.color = malloc(sizeof(t_color) * sphere_nb);
	sphere.center = malloc(sizeof(t_vec3) * sphere_nb);
	sphere.shininess = malloc(sizeof(float) * sphere_nb);
	sphere.spec_force = malloc(sizeof(float) * sphere_nb);
	sphere.reflectivity = malloc(sizeof(float) * sphere_nb);
	scene->sphere = sphere;
}

void	init_plane(t_scene *scene, int plane_nb)
{
	t_plane		plane;
	
	plane.count = plane_nb;
	if (plane_nb == 0)
		return ;
	plane.color = malloc(sizeof(t_color) * plane_nb);
	plane.point = malloc(sizeof(t_vec3) * plane_nb);
	plane.normal = malloc(sizeof(t_vec3) * plane_nb);
	plane.shininess = malloc(sizeof(float) * plane_nb);
	plane.spec_force = malloc(sizeof(float) * plane_nb);
	plane.reflectivity = malloc(sizeof(float) * plane_nb);
	scene->plane = plane;
}

void	init_cylinder(t_scene *scene, int cylinder_nb)
{
	t_cylinder		cylinder;
	
	cylinder.count = cylinder_nb;
	if (cylinder_nb == 0)
		return ;
	cylinder.radius = malloc(sizeof(float) * cylinder_nb);
	cylinder.color = malloc(sizeof(t_color) * cylinder_nb);
	cylinder.center = malloc(sizeof(t_vec3) * cylinder_nb);
	cylinder.shininess = malloc(sizeof(float) * cylinder_nb);
	cylinder.spec_force = malloc(sizeof(float) * cylinder_nb);
	cylinder.reflectivity = malloc(sizeof(float) * cylinder_nb);
	scene->cylinder = cylinder;
}

void	init_triangle(t_scene *scene, int triangle_nb)
{
	t_triangle		triangle;
	
	triangle.count = triangle_nb;
	if (triangle_nb == 0)
		return ;
	triangle.pointA = malloc(sizeof(t_vec3) * triangle_nb);
	triangle.pointB = malloc(sizeof(t_vec3) * triangle_nb);
	triangle.pointC = malloc(sizeof(t_vec3) * triangle_nb);
	triangle.color = malloc(sizeof(t_color) * triangle_nb);
	triangle.shininess = malloc(sizeof(float) * triangle_nb);
	triangle.spec_force = malloc(sizeof(float) * triangle_nb);
	triangle.reflectivity = malloc(sizeof(float) * triangle_nb);
	scene->triangle = triangle;
}

void  init_light(t_scene *scene, int light_nb)
{
  t_light light;

  light.count = light_nb;
	if (light_nb == 0)
		return ;
	light.color = malloc(sizeof(t_color) * light_nb);
	light.pos = malloc(sizeof(t_vec3) * light_nb);
	light.intensity = malloc(sizeof(float) * light_nb);
  scene->light = light;
}