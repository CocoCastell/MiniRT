/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/08 14:14:27 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	exit_error(char *msg, int error)
{
	if (msg != NULL)
		ft_printf(RED"ERROR: "DEF "%s", msg);
	exit(error);
}

int	main(int argc, char *argv[])
{
	t_minirt	minirt;

	if (argc != 2)
		return (printf("Wrong number of arguments\n"));
	srand(time(NULL));
	init_minirt(&minirt, argv[1]);
	event_manager(&minirt);
	print_menu(minirt.scene->settings);
	raytracing(&minirt);
	mlx_loop(minirt.mlx);
	return (0);
}
