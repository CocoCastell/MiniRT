/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/07 17:41:39 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	parse_color(char *str, t_minirt *minirt)
{
	int		c[3];
	char	**components;

	components = ft_split(str, ',');
	if (ft_str_array_len(components) != 3)
		free_error(minirt, "Color: invalid format.\n", 1);
	printf("goingthere\n");
	ft_is_only_digit(components[0]);
	/* if (!ft_is_only_digit(components[0]) || !ft_is_only_digit(components[1]) || !ft_is_only_digit(components[3])) */
	/* { */
		/* printf("%s, %s, %s \n", components[0], components[1], components[2]); */
		/* ft_free_string_array(components); */
		/* free_error(minirt, "Color: invalid format.\n", 1); */
	/* } */
	printf("color: \n");
	printf("%s\n", components[0]);
	printf("%s\n", components[1]);
	printf("%s\n", components[2]);
	printf("\n");
	c[0] = ft_atoi(components[0]);
	c[1] = ft_atoi(components[1]);
	c[2] = ft_atoi(components[2]);
	ft_free_string_array(components);
	if (c[0] < 0 || c[0] > 255 || c[1] < 0 || c[1] > 255 || \
		c[2] < 0 || c[2] > 255)
		free_error(minirt, "Color: value out of range [0, 255].\n", 1);
	return (create_color(c[0] / 255.0f, c[1] / 255.0f, c[2] / 255.0f));
}

t_vec3	parse_coordinates(char *str, t_minirt *minirt)
{
	t_vec3	coord;
	char	**components;

	components = ft_split(str, ',');
	if (ft_str_array_len(components) != 3)
		free_error(minirt, "Coordinates: invalid format.\n", 1);
	coord.x = ft_atof(components[0]);
	coord.y = ft_atof(components[1]);
	coord.z = ft_atof(components[2]);
	ft_free_string_array(components);
	return (coord);
}

t_vec3	parse_normal_vec(char *str, t_minirt *minirt)
{
	char	**components;
	float	c[3];

	components = ft_split(str, ',');
	if (ft_str_array_len(components) != 3)
		free_error(minirt, "Normal: invalid format.\n", 1);
	c[0] = ft_atof(components[0]);
	c[1] = ft_atof(components[1]);
	c[2] = ft_atof(components[2]);
	ft_free_string_array(components);
	if (c[0] < -1.0f || c[0] > 1.0f || c[1] < -1.0f || c[1] > 1.0f || \
		c[2] < -1.0f || c[2] > 1.0f)
		free_error(minirt, "Normal vec: value out of range [-0.0, 1.0].\n", 1);
	return (vec3(c[0], c[1], c[2]));
}

void	parse_properties(t_parse_data *values, char **data, t_minirt *minirt)
{
	values->shininess = 0.0f;
	values->spec_force = 0.0f;
	values->reflectivity = 0.0f;
	if (*data == NULL)
		return ;
	values->shininess = ft_atof(*data);
	if (values->shininess < 0.0f || values->shininess > 999.99f)
		free_error(minirt, "Shininess out of range [0.0, 200.0].\n", 1);
	if (*(++data) == NULL)
		return ;
	values->spec_force = ft_atof(*data);
	if (values->spec_force < 0.0f || values->spec_force > 1.0f)
		free_error(minirt, "Specular force out of range [0.0, 1.0].\n", 1);
	if (*(++data) == NULL)
		return ;
	values->reflectivity = ft_atof(*data);
	if (values->reflectivity < 0.0f || values->reflectivity > 1.0f)
		free_error(minirt, "Reflectivity out of range [0.0, 1.0].\n", 1);
}
