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

bool    is_mouvement_key(int keycode)
{
        return (keycode == A || keycode == D || keycode == W || keycode == S || keycode == SPACE || keycode == SHIFT);
}

bool    is_rotation_key(int keycode)
{
        return (keycode == UP_K || keycode == DOWN_K || keycode == LEFT_K || keycode == RIGHT_K || keycode == Q || keycode == E);
}

int	key_pressed(int keycode, t_miniRt *minirt)
{
	if (keycode == ESC)
		my_close(minirt);
        else if (is_mouvement_key(keycode))
                side_mouvement(keycode, minirt);
        else if (is_rotation_key(keycode))
                rotation(keycode, minirt);
        raytracing(minirt);
	return (0);
}

int     mouse_pressed(int button, int x, int y, t_miniRt *minirt)
{
        if (button == LEFT_CLICK)
                minirt->scene->entity_selected = minirt->scene->selection_grid[y][x];
        else if (button == SCROLL_UP || button == SCROLL_DOWN)
                scale_entity(minirt->scene, button);
        raytracing(minirt);
        return (0);
}

void	event_manager(t_miniRt *minirt)
{
	mlx_hook(minirt->win, ClientMessage, StructureNotifyMask, my_close, minirt);
        mlx_hook(minirt->win, KeyPress, KeyPressMask, key_pressed, minirt);
        mlx_hook(minirt->win, ButtonPress, ButtonPressMask, mouse_pressed, minirt);
        // mlx_hook(minirt->win, ButtonRelease, ButtonReleaseMask, mouse_released, minirt);
        // mlx_hook(minirt->win, MotionNotify, PointerMotionMask, mouse_move, minirt);
}
