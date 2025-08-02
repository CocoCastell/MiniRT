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

#include "../../includes/miniRT.h"

int     my_close(t_miniRt *minirt)
{
        free_mlx(minirt);
        exit(0);
}

void    light_models(int keycode, t_scene *scene)
{
        if (keycode == R_KEY)
        {
                if (scene->mirror_on == true)
                        scene->mirror_on = false;
                else
                        scene->mirror_on = true;
        }
}

void    mirror_control(int keycode, t_scene *scene)
{
        float   reflectivity;

        reflectivity = 0.05;
        if (keycode == MINUS_KEY)
                reflectivity = -0.05;
        if (scene->entity_selected.type == SPHERE)
                scene->sphere.reflectivity[scene->entity_selected.index] += reflectivity;
        if (scene->entity_selected.type == PLANE)
                scene->plane.reflectivity[scene->entity_selected.index] += reflectivity;
        if (scene->entity_selected.type == CYLINDER)
                scene->cylinder.reflectivity[scene->entity_selected.index] += reflectivity;
}

int	key_pressed(int keycode, t_miniRt *minirt)
{
	if (keycode == ESC)
		my_close(minirt);
        else if (is_movement_key(keycode))
                side_movement(keycode, minirt->scene);
        else if (is_rotation_key(keycode))
                rotation(keycode, minirt->scene);
        else if (keycode == R_KEY)
                light_models(keycode, minirt->scene);
        else if (keycode == PLUS_KEY || keycode == MINUS_KEY)
                mirror_control(keycode, minirt->scene);
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
