/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 11:47:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	apply_cam_rotation(t_camera *camera, float r_matrix[3][3])
{
	t_vec3	new_up;
	t_vec3	new_right;
	float	up_length;
	float	right_length;

	camera->forward = normalize(apply_rotation(camera->forward, r_matrix));
	new_up = apply_rotation(camera->up, r_matrix);
	new_right = apply_rotation(camera->right, r_matrix);
	up_length = vector_length(new_up);
	right_length = vector_length(new_right);
	if (up_length > 0.001f)
		camera->up = scale_vector(new_up, 1.0f / up_length);
	if (right_length > 0.001f)
		camera->right = scale_vector(new_right, 1.0f / right_length);
}

static void	apply_axis_rotation(t_vec3 *normal, float r_matrix[3][3])
{
	*normal = normalize(apply_rotation(*normal, r_matrix));
}

// Cool effect if we take of the camera->forward line
void	rotation(int keycode, t_scene *scene)
{
	t_vec3	axis;
	float	r_matrix[3][3];
	float	angle;

	angle = -STEP;
	if (keycode == UP_K || keycode == LEFT_K || keycode == E_KEY)
		angle = STEP;
	if (keycode == UP_K || keycode == DOWN_K)
		axis = scene->camera.right;
	else if (keycode == RIGHT_K || keycode == LEFT_K)
		axis = scene->camera.world_up;
	else if (keycode == Q_KEY || keycode == E_KEY)
		axis = scene->camera.forward;
	else
		return ;
	set_axis_angle_matrix(r_matrix, axis, angle);
	if (scene->selection.sel_type == CAMERA)
		apply_cam_rotation(&scene->camera, r_matrix);
	if (scene->selection.sel_type == PLANE)
		apply_axis_rotation(&scene->plane.normal[scene->selection.sel_index], r_matrix);
	if (scene->selection.sel_type == CYLINDER)
		apply_axis_rotation(&scene->cylinder.axis[scene->selection.sel_index], r_matrix);
}
