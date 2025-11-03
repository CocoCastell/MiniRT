/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/10/25 11:30:02 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	click_move_object(int x, int y, t_scene *scene)
{
	t_ray		ray;
	t_vec3		p;
	float		t;

	ray = get_camera_ray(y, x, &scene->v_port, scene->camera.pos);
	if (scene->selection.sel_type == SPHERE)
	{
		p = vec3(ray.direction.x, ray.direction.y, \
			scene->sphere.center[scene->selection.sel_index].z);
		t = (p.z - ray.origin.z) / ray.direction.z;
		scene->sphere.center[scene->selection.sel_index] = \
			ray_at(ray.origin, ray.direction, t);
	}
	else if (scene->selection.sel_type == CYLINDER)
	{
		p = vec3(ray.direction.x, ray.direction.y, \
			scene->cylinder.center[scene->selection.sel_index].z);
		t = (p.z - ray.origin.z) / ray.direction.z;
		scene->cylinder.center[scene->selection.sel_index] = \
			ray_at(ray.origin, ray.direction, t);
	}
}

void	key_move_entity(t_scene *scene, t_vec3 dest, float step)
{
	t_ent_type	sel_type;
	int			i;

	sel_type = scene->selection.sel_type;
	i = scene->selection.sel_index;
	if (sel_type == CAMERA)
		scene->camera.pos = add_vector(scene->camera.pos, \
			scale_vector(dest, step + step));
	if (sel_type == LIGHT)
	{
		scene->light.pos[i] = add_vector(scene->light.pos[i], \
			scale_vector(dest, step + step));
		print_vec(scene->light.pos[i]);
	}
	else if (sel_type == SPHERE)
		scene->sphere.center[i] = add_vector(scene->sphere.center[i], \
			scale_vector(dest, step));
	else if (sel_type == PLANE)
		scene->plane.point[i] = add_vector(scene->plane.point[i], \
			scale_vector(dest, step));
	else if (sel_type == CYLINDER)
		scene->cylinder.center[i] = add_vector(scene->cylinder.center[i], \
			scale_vector(dest, step));
}

void	side_movement(int keycode, t_scene *scene)
{
	t_camera	*camera;
	float		step;

	step = STEP;
	camera = &scene->camera;
	if (keycode == A_KEY || keycode == S_KEY || keycode == SHIFT)
		step = -STEP;
	if (keycode == A_KEY || keycode == D_KEY)
		key_move_entity(scene, camera->right, step);
	else if (keycode == W_KEY || keycode == S_KEY)
		key_move_entity(scene, camera->forward, step);
	else if (keycode == SPACE || keycode == SHIFT)
		key_move_entity(scene, camera->up, step);
}

void	scale_entity(t_scene *scene, int button)
{
	t_ent_type	sel_type;
	int			i;

	sel_type = scene->selection.sel_type;
	i = scene->selection.sel_index;
	if (button == SCROLL_UP && sel_type == CAMERA)
		scene->camera.fov -= 3;
	else if (button == SCROLL_DOWN && sel_type == CAMERA)
		scene->camera.fov += 3;
	else if (button == SCROLL_UP && sel_type == LIGHT)
		scene->light.intensity[i] *= ZOOM_IN;
	else if (button == SCROLL_DOWN && sel_type == LIGHT)
		scene->light.intensity[i] *= ZOOM_OUT;
	else if (button == SCROLL_UP && sel_type == SPHERE)
		scene->sphere.radius[i] *= ZOOM_IN;
	else if (button == SCROLL_DOWN && sel_type == SPHERE)
		scene->sphere.radius[i] *= ZOOM_OUT;
	else if (button == SCROLL_UP && sel_type == CYLINDER)
	{
		//correct this
		scene->cylinder.height[i] *= ZOOM_IN;
		scene->cylinder.radius[i] *= ZOOM_IN;
	}
	else if (button == SCROLL_DOWN && sel_type == CYLINDER)
	{
		scene->cylinder.height[i] *= ZOOM_OUT;
		scene->cylinder.radius[i] *= ZOOM_OUT;
	}
}
