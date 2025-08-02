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

#include "../includes/miniRT.h"

t_color parse_color(char *str)
{
  t_color color;
  char    **components;

    components = ft_split(str, ',');
    if (str_array_len(components) != 3)
        free_error(NULL, "Color: invalid format", 1);
    int r = ft_atoi(components[0]);
    int g = ft_atoi(components[1]);
    int b = ft_atoi(components[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        free_error(NULL, "Color: value out of range", 1);
    free_split(components);
    color = {r, g, b};
    return (color);
}

void parse_ambient(t_scene *scene, char **data)
{
  t_color color;
  float   ratio;

  if (str_array_len(data) != 3)
      free_error(scene, "Ambient: invalid number of arguments", 1);
  ratio = ft_atof(data[1]);
  if (ratio < 0.0f || ratio > 1.0f)
      free_error(scene, "Ambient: ratio out of range [0.0, 1.0]", 1);
  color = parse_color(data[2]);
  scene->amb_ratio = ratio;
  scene->amb_color = color;
}

void  init_counter(t_obj_counter *counter)
{
  counter->sphere = 0;
  counter->plane = 0;
  counter->cylinder = 0;
  counter->light = 0;
  counter->camera = 0;
  counter->ambient = 0;
}

void  compute_count(char *token, t_obj_counter *counter)
{
  if (ft_strcmp(tokens, "sp", 3) == 0)
    counter->sphere++;
  else if (ft_strcmp(tokens, "pl", 3) == 0)
    counter->plane++;
  else if (ft_strcmp(tokens, "cy", 3) == 0)
    counter->cylinder++;
  else if (ft_strcmp(tokens, "L", 2) == 0)
    counter->light++;
  else if (ft_strcmp(tokens, "C", 2) == 0)
    counter->camera++;
  else if (ft_strcmp(tokens, "A", 2) == 0)
    counter->ambient++;
}       

t_obj_counter count_objects(int fd)
{
    t_obj_counter counter;
    char          *line;
    int           is_eof;
    char          **tokens;

    init_counter(&counter);
    while (1)
    {
        line = get_next_line(fd, &is_eof);
        if (line == NULL && is_eof == -1)
            exit_error("Get_next_line error");
        if (line == NULL)
            break;
        tokens = ft_split(line, " ");
        if (tokens && tokens[0])
          compute_count(token[0], &counter);
        ft_free_string_array(tokens);
        free(line);
    }
    if (c.camera != 1)
        free_error(scene, "Camera is defined twice\n", 1);
    if (c.ambient != 1)
        free_error(scene, "Ambient light is defined twice\n", 1); //change
    return (counter);
}

int	put_object_in_structure(char *line, t_obj_lists *lists, t_scene *scene)
{
    char          **obj_data;
    t_obj_counter counter;
    t_obj_counter obj_count;

    if (!line || *line == '\n')
        return ;
    obj_data = ft_split(line, " ");
    if (!obj_data || !obj_data[0])
        return (free_split(obj_data), 1);
    counter = count_object(fd);
		if (obj_data[0][0] == 'A')
		{
        if (scene->amb_set)
            free_error(scene, "Ambient light is defined twice\n", 1);
        parse_ambient(scene, obj_data);
        scene->amb_set = true;
    }
		else if (obj_data[0][0] == 'C')
		{
        if (scene->camera_set)
            free_error(scene, "Camera is defined twice\n", 1);
        parse_camera(scene, obj_data);
        scene->camera_set = true;
    }
		else if (obj_data[0][0] == 'L')
		{
        t_light_node *new = malloc(sizeof(t_light_node));
        new->data = parse_light(obj_data);
        new->next = lists->lights;
        lists->lights = new;
        lists->light_count++;
    }
/*     else if (ft_strcmp(obj_data[0], "sp") == 0)
		{
        t_sphere_node *new = malloc(sizeof(t_sphere_node));
        new->data = parse_sphere(obj_data);
        new->next = lists->spheres;
        lists->spheres = new;
        lists->sphere_count++;
    }
    else if (ft_strcmp(obj_data[0], "pl") == 0)
		{
        t_plane_node *new = malloc(sizeof(t_plane_node));
        new->data = parse_plane(obj_data);
        new->next = lists->planes;
        lists->planes = new;
        lists->plane_count++;
    }
    else if (ft_strcmp(obj_data[0], "cy") == 0)
		{
        t_cylinder_node *new = malloc(sizeof(t_cylinder_node));
        new->data = parse_cylinder(obj_data);
        new->next = lists->cylinders;
        lists->cylinders = new;
        lists->cylinder_count++;
     */}
    else
        free_error(scene, "Unknown object type", 1);
    free_split(obj_data);
}