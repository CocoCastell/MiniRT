/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

#define WIN_WIDTH 1500
#define WIN_HEIGHT 900

void	exit_error(char *msg, int error)
{
	if (msg != NULL)
		ft_printf("%s", msg);
	exit(error);
}

void	free_mlx(t_miniRt *minirt)
{
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

void	free_error(t_miniRt *minirt, char *msg, int error)
{
	free_mlx(minirt);
	exit_error(msg, error);
}

void	ft_mlx_init(t_miniRt *minirt)
{
	minirt->mlx = mlx_init();
	if (minirt->mlx == NULL)
		exit_error("Mlx init error\n", 1);
	minirt->win = mlx_new_window(minirt->mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Raytracer");
	if (minirt->win == NULL)
		free_error(minirt, "Win init error\n", 1);
	minirt->img.img = mlx_new_image(minirt->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (minirt->img.img == NULL)
		free_error(minirt, "Img init error\n", 1);
	minirt->img.addr = mlx_get_data_addr(minirt->img.img, &minirt->img.bpp, \
			&minirt->img.line_length, &minirt->img.endian);
	if (minirt->img.addr == NULL)
		free_error(minirt, "Img addr init error\n", 1);
}

int main()
{
	t_miniRt minirt;

	ft_mlx_init(&minirt);
	mlx_loop(minirt.mlx);

	return (0);
}
