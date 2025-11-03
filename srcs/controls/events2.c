/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/03 20:46:30 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	mirror_control(int keycode, t_scene *scene)
{
	float	*reflctivity;

	if (scene->selection.sel_type == SPHERE)
		reflctivity = &scene->sphere.reflectivity[scene->selection.sel_index];
	else if (scene->selection.sel_type == PLANE)
		reflctivity = &scene->plane.reflectivity[scene->selection.sel_index];
	else if (scene->selection.sel_type == CYLINDER || \
		scene->selection.sel_type == CYLINDER_CAP)
		reflctivity = &scene->cylinder.reflectivity[scene->selection.sel_index];
	else
		return ;
	if (keycode == MINUS_KEY)
		*reflctivity -= 0.05;
	else
		*reflctivity += 0.05;
	if (*reflctivity > 1.0f)
		*reflctivity = 1.0f;
	else if (*reflctivity < 0.0f)
		*reflctivity = 0.0f;
}

void	settings(int keycode, t_scene *scene)
{
	if (keycode == K_1)
		set_opposite_bool(&scene->settings.scene_creation_on);
	if (keycode == K_2)
		set_opposite_bool(&scene->settings.checkered_on);
	if (keycode == K_3)
		set_opposite_bool(&scene->settings.gamma_on);
	if (keycode == K_4)
		set_opposite_bool(&scene->settings.mirror_on);
	if (keycode == K_5)
		set_opposite_bool(&scene->settings.plane_on);
	if (keycode == K_6)
		set_opposite_bool(&scene->settings.antialias_on);
	if (keycode == I_KEY)
		print_menu(scene->settings);
}

int	get_viewport_coord(t_vec3 position, t_scene *scene)
{
	t_vec3	cam_to_obj;
	float	x;
	float	z;

	cam_to_obj = vector_from_to(scene->camera.pos, position);
	x = dot(cam_to_obj, scene->camera.right);
	z = dot(cam_to_obj, scene->camera.forward);
	return ((int)((x / (z * to_radian(scene->camera.fov))) * (WIN_WIDTH / 2) \
				+ WIN_WIDTH / 2));
}

void	select_light(int light_count, t_selection *selection)
{
	static int	prev_index;

	if (selection->sel_type == LIGHT)
	{
		if (selection->sel_index < light_count - 1)
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
	print_selection(LIGHT);
}

void	select_object(int x, int y, t_selection *selection)
{
	t_ent_type	type;
	int			index;

	type = selection->type_grid[y][x];
	index = selection->index_grid[y][x];
	if (type != selection->sel_type || index != selection->sel_index)
	{
		selection->sel_index = index;
		if (selection->sel_type == CYLINDER_CAP)
			selection->sel_type = CYLINDER;
		else
			selection->sel_type = type;
	}
	else
	{
		selection->sel_type = CAMERA;
		selection->sel_index = 0;
	}
	print_selection(selection->sel_type);
}
