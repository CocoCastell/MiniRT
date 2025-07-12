/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int     my_close(t_miniRt *minirt)
{
        free_mlx(minirt);
        exit(0);
}

int	key_pressed(int keycode, t_miniRt *minirt)
{
	if (keycode == ESC)
		my_close(minirt);
        if (keycode == A_KEY || keycode == D_KEY)
                camera_side_mouvement(keycode, minirt);
	return 0;
}

void	event_manager(t_miniRt *minirt)
{
	mlx_hook(minirt->win, ClientMessage, StructureNotifyMask, my_close, minirt);
        mlx_hook(minirt->win, KeyPress, KeyPressMask, key_pressed, minirt);
        // mlx_hook(minirt->win, ButtonPress, ButtonPressMask, mouse_pressed, minirt);
        // mlx_hook(minirt->win, ButtonRelease, ButtonReleaseMask, mouse_released, minirt);
        // mlx_hook(minirt->win, MotionNotify, PointerMotionMask, mouse_move, minirt);
}
