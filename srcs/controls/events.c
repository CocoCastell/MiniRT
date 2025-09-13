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

int     my_close(t_minirt *minirt)
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
                set_opposite_bool(&scene->settings.antialias_on);
}

void    mirror_control(int keycode, t_scene *scene)
{
        float   *reflectivity;

        if (scene->selection.sel_type == SPHERE)
                reflectivity = &scene->sphere.reflectivity[scene->selection.sel_index];
        else if (scene->selection.sel_type == PLANE)
                reflectivity = &scene->plane.reflectivity[scene->selection.sel_index];
        else if (scene->selection.sel_type == CYLINDER)
                reflectivity = &scene->cylinder.reflectivity[scene->selection.sel_index];
        else
                return ;
        if (keycode == MINUS_KEY)
                *reflectivity -= 0.05;
        else
                *reflectivity += 0.05;
        if (*reflectivity > 1.0f)
                *reflectivity = 1.0f;
        else if (*reflectivity < 0.0f)
                *reflectivity = 0.0f;
}

void    select_light(int light_count, t_selection *selection)
{
        static int      prev_index;

        if (selection->sel_type == LIGHT)
        {
                if (selection->sel_index < light_count)
                        selection->sel_index++;
                else
                        selection->sel_index = 0;
                prev_index = selection->sel_index;
        }
        else
        {
                selection->sel_index = prev_index;
                selection->sel_type = LIGHT;
        }
}

int	key_pressed(int keycode, t_minirt *minirt)
{
        // printf("Key: %d\n", keycode);
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

void    select_object(int x, int y, t_selection *selection)
{
        t_ent_type      type;
        int             index;

        type = selection->type_grid[y][x];
        index = selection->index_grid[y][x];
        if (type != selection->sel_type || index != selection->sel_index)
        {
                selection->sel_type = type;
                selection->sel_index = index;
        }
        else
        { 
                selection->sel_type = CAMERA;
                selection->sel_index = 0;
        }
}

int     get_viewport_coord(t_vec3 position, t_scene *scene)
{
        t_vec3  cam_to_obj;

        cam_to_obj = vector_from_to(scene->camera.pos, position);
        float x = dot(cam_to_obj, scene->camera.right);
        float z = dot(cam_to_obj, scene->camera.forward);
        return ((int)((x / (z * to_radian(scene->camera.fov))) * (WIN_WIDTH / 2) + WIN_WIDTH / 2));
}

int     mouse_pressed(int button, int x, int y, t_minirt *minirt)
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
        // mlx_hook(minirt->win, ButtonRelease, ButtonReleaseMask, mouse_released, minirt);
        // mlx_hook(minirt->win, MotionNotify, PointerMotionMask, mouse_move, minirt);
}
