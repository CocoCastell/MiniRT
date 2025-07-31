/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void  update_v_port(t_scene *scene)
{
  t_camera  *camera;
  t_v_port  *viewport;
  float     vec_w;
  float     vec_h;

  viewport = &scene->v_port;
 	camera = &scene->camera;
  viewport->v_port_height = 2.0f * tan(to_radian(camera->fov) / 2.0f) * v_port_DIST;
  viewport->v_port_width = WIN_WIDTH * viewport->v_port_height / WIN_HEIGHT;
  viewport->v_port_center = add_vector(camera->pos, scale_vec(camera->forward, v_port_DIST));
  vec_w = viewport->v_port_width / WIN_WIDTH;
	vec_h = viewport->v_port_height/ WIN_HEIGHT;
	viewport->right_vec = scale_vec(camera->right, vec_w);
	viewport->up_vec = scale_vec(camera->up, vec_h);
}

void  move_entity(t_scene *scene, t_vec3 dest, float step)
{
  t_selection selected;
  int      i;

  selected = scene->entity_selected;
  i = selected.index;
  if (selected.type == CAMERA)
    scene->camera.pos = add_vector(scene->camera.pos, scale_vec(dest, step));
  else if (selected.type == SPHERE)
    scene->sphere.center[i] = add_vector(scene->sphere.center[i], scale_vec(dest, step));
  else if (selected.type == PLANE)
    scene->plane.point[i] = add_vector(scene->plane.point[i], scale_vec(dest, step));
  // else if (selected.type == CYLINDER)
  //   scene->cylinder.center[i] = add_vector(scene->cylinder.center[i], scale_vec(dest, step));
}

void  side_movement(int keycode, t_scene *scene)
{
  t_camera  *camera;
  float     step;

  step = STEP;
  camera = &scene->camera;
  if (keycode == A_KEY || keycode == S_KEY || keycode == SHIFT)
    step = -STEP;
  if (keycode == A_KEY || keycode == D_KEY)
    move_entity(scene, camera->right, step);
  else if (keycode == W_KEY || keycode == S_KEY)
    move_entity(scene, camera->forward, step);
  else if (keycode == SPACE || keycode == SHIFT)
    move_entity(scene, camera->up, step);
}

void apply_rotation_to_all_vectors(t_camera *camera, float r_matrix[3][3])
{
    t_vec3 new_up;
    t_vec3 new_right;
    float up_length;
    float right_length;
    
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

// Cool effect if we take of the camera->forward line
void rotation(int keycode, t_scene *scene)
{
    t_vec3    axis;
    float     r_matrix[3][3];
    float     angle;
    
    angle = -STEP;
    if (keycode == UP_K || keycode == LEFT_K || keycode == E_KEY)
      angle = STEP;
    if (keycode == UP_K || keycode == DOWN_K)
      axis = scene->camera.right;
    else if (keycode == RIGHT_K || keycode == LEFT_K)
      axis = scene->camera.world_up;
    else if (keycode == Q_KEY || keycode == E_KEY)
      axis = scene->camera.forward;
    fill_axis_angle_matrix(r_matrix, axis, angle);
    apply_rotation_to_all_vectors(&scene->camera, r_matrix);
}

void    scale_entity(t_scene *scene, int button)
{
  int  i;

  i = scene->entity_selected.index;
  if (button == SCROLL_UP && scene->entity_selected.type == CAMERA)
    scene->camera.fov -= 3;
  else if (button == SCROLL_DOWN && scene->entity_selected.type == CAMERA)
    scene->camera.fov += 3;
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