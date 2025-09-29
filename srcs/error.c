/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 14:02:29 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	exit_error(char *msg, int error)
{
	if (msg != NULL)
		ft_printf(RED"ERROR: "DEF "%s", msg);
	exit(error);
}

void	free_mlx(t_minirt *minirt)
{
	if (minirt->array1 != NULL)
		ft_free_string_array(minirt->array1);
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
