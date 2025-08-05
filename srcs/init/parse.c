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
    if (obj_data[0][0] == 'C')
        parse_camera(minirt, obj_data);
	else if (obj_data[0][0] == 'A')
        parse_ambient(minirt, obj_data);
	else if (obj_data[0][0] == 'L')
        parse_light(minirt, obj_data);
    else if (ft_strncmp(obj_data[0], "sp", 3) == 0)
        parse_sphere(minirt, obj_data);
    else if (ft_strncmp(obj_data[0], "pl", 3) == 0)
        parse_plane(minirt, obj_data);
    // else if (ft_strncmp(obj_data[0], "tr", 3) == 0)
    //     parse_triangle(minirt, obj_data);
    // else if (ft_strncmp(obj_data[0], "cy", 3) == 0)
    //     parse_cylinder(minirt, obj_data);
    ft_free_string_array(obj_data);
    minirt->array1 = NULL;
    return (0);
}