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
        put_data_in_file(minirt->scene);
        free_mlx(minirt);
        exit(0);
}

void    settings(int keycode, t_scene *scene)
{
        if (keycode == K_1)
                set_opposite_bool(&scene->settings.mirror_on);
        if (keycode == K_2)
                set_opposite_bool(&scene->settings.gamma_on);
        if (keycode == K_3)
                set_opposite_bool(&scene->settings.plane_on);
        if (keycode == K_4)
                set_opposite_bool(&scene->settings.sphere_on);
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
        else if (is_setting_key(keycode))
                settings(keycode, minirt->scene);
        else if (keycode == PLUS_KEY || keycode == MINUS_KEY)
                mirror_control(keycode, minirt->scene);
        raytracing(minirt);
	return (0);
}

int     mouse_pressed(int button, int x, int y, t_miniRt *minirt)
{
        t_selection     s;
        t_scene         *scene;

        scene = minirt->scene;
        if (button == LEFT_CLICK)
        {
                s = scene->selection_grid[y][x];
                if (s.type != scene->entity_selected.type || s.index != scene->entity_selected.index)
                        scene->entity_selected = s;
                else
                {
                        scene->entity_selected.type = CAMERA;
                        scene->entity_selected.index = 0;
                }
        }
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
