/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/08 12:32:24 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//put_data_in_file(minirt->scene);
int	my_close(t_minirt *minirt)
{
	free_mlx(minirt);
	exit(0);
}

int	key_pressed(int keycode, t_minirt *minirt)
{
	if (keycode == ESC)
		my_close(minirt);
	else if (is_movement_key(keycode))
		side_movement(keycode, minirt->scene);
	else if (is_rotation_key(keycode))
		rotation(keycode, minirt->scene);
	else if (is_setting_key(keycode))
		settings(keycode, minirt->scene);
	else if (keycode == PLUS_KEY || keycode == MINUS_KEY)
		mirror_control(keycode, minirt->scene);
	else if (keycode == L_KEY)
		select_light(minirt->scene->light.count, &minirt->scene->selection);
	raytracing(minirt);
	return (0);
}

int	mouse_pressed(int button, int x, int y, t_minirt *minirt)
{
	if (button == LEFT_CLICK)
		select_object(x, y, &minirt->scene->selection);
	if (button == RIGHT_CLICK)
		click_move_object(x, y, minirt->scene);
	else if (button == SCROLL_UP || button == SCROLL_DOWN)
		scale_entity(minirt->scene, button);
	raytracing(minirt);
	return (0);
}

void	event_manager(t_minirt *minirt)
{
	mlx_hook(minirt->win, ClientMessage, StructureNotifyMask, my_close, minirt);
	mlx_hook(minirt->win, KeyPress, KeyPressMask, key_pressed, minirt);
	mlx_hook(minirt->win, ButtonPress, ButtonPressMask, mouse_pressed, minirt);
}
