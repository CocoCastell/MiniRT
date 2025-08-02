/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color parse_color(char *str, t_miniRt *minirt)
{
  int     c[3];
  char    **components;

  components = ft_split(str, ',');
  if (ft_str_array_len(components) != 3)
    free_error(minirt, "Color: invalid format.\n", 1);
  // if (!ft_is_only_digit(components[0]) || !ft_is_only_digit(components[1]) || !ft_is_only_digit(components[3]))
  // {
    // ft_free_string_array(components);
    // free_error(minirt, "Color: invalid format.\n", 1);
  // }
  c[0] = ft_atoi(components[0]);
  c[1] = ft_atoi(components[1]);
  c[2] = ft_atoi(components[2]);
  ft_free_string_array(components);
  if (c[0] < 0 || c[0] > 255 || c[1] < 0 || c[1] > 255 || c[2] < 0 || c[2] > 255)
    free_error(minirt, "Color: value out of range [0, 255].\n", 1);
  return (create_color(c[0] / 255.0f, c[1] / 255.0f, c[2] / 255.0f));
}

t_vec3  parse_coordinates(char *str, t_miniRt *minirt)
{
  t_vec3  coord;
  char    **components;

  components = ft_split(str, ',');
  if (ft_str_array_len(components) != 3)
    free_error(minirt, "Coordinates: invalid format.\n", 1);
  // if (!ft_is_only_digit(components[0]) || !ft_is_only_digit(components[1]) || !ft_is_only_digit(components[3]))
  // {
    // ft_free_string_array(components);
    // free_error(minirt, "Coordinates: invalid format.\n", 1);
  // }
  coord.x = ft_atoi(components[0]);
  coord.y = ft_atoi(components[1]);
  coord.z = ft_atoi(components[2]);
  ft_free_string_array(components);
  return (coord);
}

t_vec3  parse_normal_vec(char *str, t_miniRt *minirt)
{
  char    **components;
  float   c[3];

  components = ft_split(str, ',');
  if (ft_str_array_len(components) != 3)
    free_error(minirt, "Normal: invalid format.\n", 1);
  // if (!ft_is_only_digit(components[0]) || !ft_is_only_digit(components[1]) || !ft_is_only_digit(components[0]))
  // {
    // ft_free_string_array(components);
    // free_error(minirt, "Normal: invalid format.\n", 1);
  // }
  c[0] = ft_atof(components[0]);
  c[1] = ft_atof(components[1]);
  c[2] = ft_atof(components[2]);
  ft_free_string_array(components);
  if (c[0] < -1.0f || c[0] > 1.0f || c[1] < -1.0f || c[1] > 1.0f || c[2] < -1.0f || c[2] > 1.0f)
    free_error(minirt, "Normal vector: value out of range [-0.0, 1.0].\n", 1);
  return (vec3(c[0], c[1], c[2]));
}

void parse_ambient(t_miniRt *minirt, char **data)
{
  t_color color;
  float   ratio;

  if (ft_str_array_len(data) != 3)
      free_error(minirt, "Ambient: invalid number of arguments.\n", 1);
  ratio = ft_atof(data[1]);
  if (ratio < 0.0f || ratio > 1.0f)
      free_error(minirt, "Ambient: ratio out of range [0.0, 1.0].\n", 1);
  color = parse_color(data[2], minirt);
  minirt->scene->amb_ratio = ratio;
  minirt->scene->amb_color = color;
}

void parse_camera(t_miniRt *minirt, char **data)
{
  t_vec3    forward;
  t_vec3    position;
  t_camera  camera;
  int       fov;

  if (ft_str_array_len(data) != 4)
      free_error(minirt, "Camera: invalid number of arguments.\n", 1);
  position = parse_coordinates(data[1], minirt);
  forward = parse_normal_vec(data[2], minirt);
  fov = ft_atoi(data[3]);
  if (fov < 0 || fov > 180)
      free_error(minirt, "Camera: fov out of range [0, 180].\n", 1);
  camera = minirt->scene->camera;
  camera.pos = position;
	camera.forward = forward; 
	camera.world_up = vec3(0, 1, 0);
	camera.right = normalize(cross(camera.forward, camera.world_up));
	camera.up = normalize(cross(camera.right, camera.forward));
	camera.fov = fov;
  minirt->scene->camera = camera;
}

void  parse_material_properties(int nb_of_data, t_parse_data *values, char **data, t_miniRt *minirt)
{
  int i;

  i = nb_of_data - MATERIAL_PROPERTIES;
  if (i == 0)
    return ;
  if (i >= 1)
  {
    values->shininess = ft_atof(data[nb_of_data - i + 1]);
    if (values->shininess < 0.0f || values->shininess > 200.0f)
       free_error(minirt, "Material: shininess out of range [0.0, 200.0].\n", 1);
  }
  if (i >= 2)
  {
    values->spec_force = ft_atof(data[nb_of_data - i + 2]);
    if (values->spec_force < 0.0f || values->spec_force > 1.0f)
      free_error(minirt, "Material: specular force out of range [0.0, 1.0].\n", 1);
  }
  if (i >= 3)
  {
    values->reflectivity = ft_atof(data[nb_of_data - i + 3]);
    if (values->reflectivity < 0.0f || values->reflectivity > 1.0f)
     free_error(minirt, "Material: reflectivity out of range [0.0, 1.0].\n", 1);
  }
}

void  parse_sphere(t_miniRt *minirt, char **data)
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

void  parse_plane(t_miniRt *minirt, char **data)
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

void  parse_cylinder(t_miniRt *minirt, char **data)
{
  int           nb_of_data;
  t_parse_data  values;
  static int    cylinder_index;

  nb_of_data = ft_str_array_len(data) - 1;
  if (nb_of_data < 3 || nb_of_data > 6)
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

void  parse_light(t_miniRt *minirt, char **data)
{
  static int    light_index;
  t_vec3        pos;
  float         intensity;
  t_color       color;

  if (ft_str_array_len(data) != 4)
      free_error(minirt, "Light: invalid number of arguments.\n", 1);
  pos = parse_coordinates(data[1], minirt);
  intensity = ft_atof(data[2]) / 2;
  if (intensity < 0.0f || intensity > 1000.0f)
     free_error(minirt, "Sphere: intensity out of range [0.0, 1.0].\n", 1);
  color = parse_color(data[3], minirt);
  minirt->scene->light.pos[light_index] = pos;
  minirt->scene->light.intensity[light_index] = intensity;
  minirt->scene->light.color[light_index] = color;
  light_index++;
}

int  put_object_in_structure(char *line, t_miniRt *minirt)
{
    char          **obj_data;

    if (!line || *line == '\n')
        return (0);
    obj_data = ft_split_whitespace(line);
    minirt->array1 = obj_data;
    if (!obj_data || !obj_data[0])
        return (ft_free_string_array(obj_data), 1);
    else if (obj_data[0][0] == 'C')
        parse_camera(minirt, obj_data);
		if (obj_data[0][0] == 'A')
        parse_ambient(minirt, obj_data);
	  else if (obj_data[0][0] == 'L')
        parse_light(minirt, obj_data);
    else if (ft_strncmp(obj_data[0], "sp", 3) == 0)
        parse_sphere(minirt, obj_data);
    else if (ft_strncmp(obj_data[0], "pl", 3) == 0)
        parse_plane(minirt, obj_data);
    // else if (ft_strncmp(obj_data[0], "cy", 3) == 0)
    //     parse_cylinder(minirt, obj_data);
    ft_free_string_array(obj_data);
    return (0);
}