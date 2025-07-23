/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void  update_viewport(t_scene *scene)
{
  t_camera  *camera;
  float     r;
  float     u;

 	camera = &scene->camera;
  scene->viewport_height = 2.0f * tan(to_radian(camera->fov) / 2.0f) * VIEWPORT_DIST;
  scene->viewport_width = WIN_WIDTH * scene->viewport_height / WIN_HEIGHT;
  scene->viewport_center = add_vector(camera->pos, scalar_mult(camera->forward, VIEWPORT_DIST));
  r = scene->viewport_width / WIN_WIDTH;
	u = scene->viewport_height/ WIN_HEIGHT;
	scene->right_vec = scalar_mult(camera->right, r);
	scene->up_vec = scalar_mult(camera->up, u);
}

void  move_entity(t_scene *scene, t_vec3 dest, float step)
{
  t_selection selected;
  size_t      i;

  selected = scene->entity_selected;
  i = selected.index;
  if (selected.type == CAMERA)
    scene->camera.pos = add_vector(scene->camera.pos, scalar_mult(dest, step));
  else if (selected.type == SPHERE)
    scene->sphere.center[i] = add_vector(scene->sphere.center[i], scalar_mult(dest, step));
  // else if (selected.type == CYLINDER)
  // else if (selected.type == PLANE)
}

void  side_mouvement(int keycode, t_scene *scene)
{
  t_camera  *camera;
  float     step;

  step = STEP;
  camera = &scene->camera;
  if (keycode == A || keycode == S || keycode == SHIFT)
    step = -STEP;
  if (keycode == A || keycode == D)
    move_entity(scene, camera->right, step);
  if (keycode == SPACE || keycode == SHIFT)
    move_entity(scene, camera->up, step);
  if (keycode == W || keycode == S)
    move_entity(scene, camera->forward, step);
}

void apply_rotation_to_all_vectors(t_camera *camera, float r_matrix[3][3])
{
    t_vec3 new_up;
    t_vec3 new_right;
    float up_length;
    float right_length;
    
    camera->forward = normalise_vector(apply_rotation(camera->forward, r_matrix));
    new_up = apply_rotation(camera->up, r_matrix);
    new_right = apply_rotation(camera->right, r_matrix);
    up_length = vector_length(new_up);
    right_length = vector_length(new_right);
    if (up_length > 0.001f)
        camera->up = scale_vector(new_up, 1.0f / up_length);
    if (right_length > 0.001f)
        camera->right = scale_vector(new_right, 1.0f / right_length);
}

// Cool efect if we take of the camera->foward line
void rotation(int keycode, t_scene *scene)
{
    t_vec3    axis;
    float     r_matrix[3][3];
    float     angle;
    
    angle = -STEP;
    if (keycode == UP_K || keycode == LEFT_K || keycode == E)
      angle = STEP;
    if (keycode == UP_K || keycode == DOWN_K)
      axis = scene->camera.right;
    else if (keycode == RIGHT_K || keycode == LEFT_K)
      axis = scene->camera.world_up;
    else if (keycode == Q || keycode == E)
      axis = scene->camera.forward;
    fill_axis_angle_matrix(r_matrix, axis, angle);
    apply_rotation_to_all_vectors(&scene->camera, r_matrix);
}

void    scale_entity(t_scene *scene, int button)
{
  size_t  i;

  i = scene->entity_selected.index;
  if (button == SCROLL_UP && scene->entity_selected.type == CAMERA)
    scene->camera.fov--;
  else if (button == SCROLL_DOWN && scene->entity_selected.type == CAMERA)
    scene->camera.fov++;
  else if (button == SCROLL_UP && scene->entity_selected.type == SPHERE)
    scene->sphere.radius[i] -= ZOOM;
  else if (button == SCROLL_DOWN && scene->entity_selected.type == SPHERE)
    scene->sphere.radius[i] += ZOOM;
   else if (button == SCROLL_UP && scene->entity_selected.type == CYLINDER)
  {
    // scene->cylinder.height[i] -= ZOOM;
    // scene->cylinder.diameter[i] -= ZOOM;
  }
  else if (button == SCROLL_DOWN && scene->entity_selected.type == CYLINDER)
  {        
    // scene->cylinder.height[i] += ZOOM;
    // scene->cylinder.diameter[i] += ZOOM;
  }
}