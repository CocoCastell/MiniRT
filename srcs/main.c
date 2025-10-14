/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 12:14:58 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(int argc, char *argv[])
{
	t_minirt	minirt;

	if (argc != 2)
		return (printf("Wrong number of arguments\n"));
	srand(time(NULL));
	init_minirt(&minirt, argv[1]);
	event_manager(&minirt);
	printf("Starting raytracing ...\n");
	print_menu(minirt.scene->settings);
	raytracing(&minirt);
	mlx_loop(minirt.mlx);
	return (0);
}
