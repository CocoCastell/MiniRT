/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void  parse_sphere(t_minirt *minirt, char **data)
{
  int           nb_of_data;
  t_parse_data  values;
  static int    sphere_index;

  nb_of_data = ft_str_array_len(data) - 1;
  if (nb_of_data < 3 || nb_of_data > 6)
      free_error(minirt, "Sphere: invalid number of arguments.\n", 1);
  values.center = parse_coordinates(data[1], minirt);
  values.radius = ft_atof(data[2]) / 2;
  if (values.radius < 0.0f || values.radius > 500.0f)
     free_error(minirt, "Sphere: diameter out of range [0.0, 1000.0].\n", 1);
  values.color = parse_color(data[3], minirt);
  values.shininess = 0.0f;
  values.spec_force = 0.0f;
  values.reflectivity = 0.0f;
  parse_material_properties(nb_of_data, &values, data, minirt);
  add_sphere(values, minirt->scene->sphere, sphere_index);
  sphere_index++;
}

void  parse_plane(t_minirt *minirt, char **data)
{
  int           nb_of_data;
  t_parse_data  values;
  static int    plane_index;

  nb_of_data = ft_str_array_len(data) - 1;
  if (nb_of_data < 3 || nb_of_data > 6)
      free_error(minirt, "Plane: invalid number of arguments.\n", 1);
  values.point = parse_coordinates(data[1], minirt);
  values.normal = parse_normal_vec(data[2], minirt);
  values.color = parse_color(data[3], minirt);
  values.shininess = 0.0f;
  values.spec_force = 0.0f;
  values.reflectivity = 0.0f;
  parse_material_properties(nb_of_data, &values, data, minirt);
  add_plane(values, minirt->scene->plane, plane_index);
  plane_index++;
}

void  parse_cylinder(t_minirt *minirt, char **data)
{
  int           nb_of_data;
  t_parse_data  values;
  static int    cylinder_index;

  nb_of_data = ft_str_array_len(data) - 1;
  if (nb_of_data < 5 || nb_of_data > 8)
      free_error(minirt, "Cylinder: invalid number of arguments.\n", 1);
  values.center = parse_coordinates(data[1], minirt);
  values.normal = parse_normal_vec(data[2], minirt);
  values.radius = ft_atof(data[2]) / 2;
  if (values.radius < 0.0f || values.radius > 500.0f)
     free_error(minirt, "Cylinder: diameter out of range [0.0, 1000.0].\n", 1);
  values.height = ft_atof(data[4]);
  values.color = parse_color(data[5], minirt);
  values.shininess = 0.0f;
  values.spec_force = 0.0f;
  values.reflectivity = 0.0f;
  parse_material_properties(nb_of_data, &values, data, minirt);
  add_cylinder(values, minirt->scene->cylinder, cylinder_index);
  cylinder_index++;
}

void  parse_triangle(t_minirt *minirt, char **data)
{
  int           nb_of_data;
  t_parse_data  values;
  static int    triangle_index;

  nb_of_data = ft_str_array_len(data) - 1;
  if (nb_of_data < 4 || nb_of_data > 7)
      free_error(minirt, "Triangle: invalid number of arguments.\n", 1);
  values.point = parse_coordinates(data[1], minirt);
  values.point2 = parse_coordinates(data[1], minirt);
  values.point3 = parse_coordinates(data[1], minirt);
  values.color = parse_color(data[5], minirt);
  values.shininess = 0.0f;
  values.spec_force = 0.0f;
  values.reflectivity = 0.0f;
  parse_material_properties(nb_of_data, &values, data, minirt);
  add_triangle(values, minirt->scene->triangle, triangle_index);
  triangle_index++;
}