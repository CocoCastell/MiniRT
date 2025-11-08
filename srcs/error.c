/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/08 14:13:38 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	free_gnl(int fd)
{
	int		is_eof;
	char	*line;

	if (fd != -1)
	{
		while (true)
		{
			line = get_next_line(fd, &is_eof);
			if (line == NULL)
				break ;
			free(line);
		}
		close(fd);
	}
}

void	free_triangle(t_scene *scene)
{
	free(scene->triangle.point_a);
	free(scene->triangle.point_b);
	free(scene->triangle.point_c);
	free(scene->triangle.color);
	free(scene->triangle.shininess);
	free(scene->triangle.spec_force);
	free(scene->triangle.reflectivity);
	free(scene);
}

void	free_scene(t_scene *scene)
{
	free(scene->sphere.center);
	free(scene->sphere.radius);
	free(scene->sphere.color);
	free(scene->sphere.shininess);
	free(scene->sphere.spec_force);
	free(scene->sphere.reflectivity);
	free(scene->plane.color);
	free(scene->plane.normal);
	free(scene->plane.point);
	free(scene->plane.shininess);
	free(scene->plane.spec_force);
	free(scene->plane.reflectivity);
	free(scene->cylinder.radius);
	free(scene->cylinder.height);
	free(scene->cylinder.axis);
	free(scene->cylinder.center);
	free(scene->cylinder.color);
	free(scene->cylinder.shininess);
	free(scene->cylinder.spec_force);
	free(scene->cylinder.reflectivity);
	free(scene->light.pos);
	free(scene->light.color);
	free(scene->light.intensity);
	free_triangle(scene);
}

void	free_mlx(t_minirt *minirt)
{
	free_scene(minirt->scene);
	if (minirt->fd != -1)
		free_gnl(minirt->fd);
	if (minirt->array1 != NULL)
		ft_free_string_array(minirt->array1);
	if (minirt->line != NULL)
		free(minirt->line);
	if (minirt->fd != -1)
		close(minirt->fd);
	if (minirt->img.img != NULL)
		mlx_destroy_image(minirt->mlx, minirt->img.img);
	if (minirt->win != NULL)
		mlx_destroy_window(minirt->mlx, minirt->win);
	if (minirt->mlx != NULL)
	{
		mlx_destroy_display(minirt->mlx);
		free(minirt->mlx);
	}
}

void	free_error(t_minirt *minirt, char *msg, int error)
{
	free_mlx(minirt);
	exit_error(msg, error);
}
