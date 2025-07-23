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

/* void  move_entity(t_obj *entity, t_vec3 dest, float distance)
{
  if (entity->obj_type == CAMERA)
    entity->obj.camera->pos = add_vector(entity->obj.camera->pos, scalar_mult(dest, distance));
  else if (entity->obj_type == SPHERE)
    entity->obj.sphere->center = add_vector(entity->obj.sphere->center, scalar_mult(dest, distance));
  else if (entity->obj_type == CYLINDER)
    entity->obj.cylinder->center = add_vector(entity->obj.cylinder->center, scalar_mult(dest, distance));
  else if (entity->obj_type == PLANE)
    entity->obj.plane->pos= add_vector(entity->obj.plane->pos, scalar_mult(dest, distance));
}

void  side_mouvement(int keycode, t_miniRt *minirt)
{
  t_obj     *entity;
  t_camera  *camera;
  float     step;

  camera = minirt->scene->camera;
  entity = minirt->scene->entity_selected;
  step = STEP;
  if (keycode == A || keycode == S || keycode == SHIFT)
    step = -STEP;
  if (keycode == A || keycode == D)
    move_entity(entity, camera->right, step);
  if (keycode == SPACE || keycode == SHIFT)
    move_entity(entity, camera->up, step);
  if (keycode == W || keycode == S)
    move_entity(entity, camera->forward, step);
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
void rotation(int keycode, t_miniRt *minirt)
{
    t_camera *camera;
    t_vec3 axis;
    float r_matrix[3][3];
    float angle;
    
    angle = -STEP;
    camera = minirt->scene->camera;
    if (keycode == UP_K || keycode == LEFT_K || keycode == E)
      angle = STEP;
    if (keycode == UP_K || keycode == DOWN_K)
      axis = camera->right;
    else if (keycode == RIGHT_K || keycode == LEFT_K)
      axis = camera->world_up;
    else if (keycode == Q || keycode == E)
      axis = camera->forward;
    fill_axis_angle_matrix(r_matrix, axis, angle);
    apply_rotation_to_all_vectors(camera, r_matrix);
}

void    scale_entity(t_scene *scene, int button)
{
        if (button == SCROLL_UP && scene->entity_selected->obj_type == CAMERA)
                scene->camera->fov--;
        else if (button == SCROLL_DOWN && scene->entity_selected->obj_type == CAMERA)
                scene->camera->fov++;
        else if (button == SCROLL_UP && scene->entity_selected->obj_type == SPHERE)
                scene->entity_selected->obj.sphere->radius -= ZOOM;
        else if (button == SCROLL_DOWN && scene->entity_selected->obj_type == SPHERE)
                scene->entity_selected->obj.sphere->radius += ZOOM;
        else if (button == SCROLL_UP && scene->entity_selected->obj_type == CYLINDER)
        {
                scene->entity_selected->obj.cylinder->height -= ZOOM;
                scene->entity_selected->obj.cylinder->diameter -= ZOOM;
        }
        else if (button == SCROLL_DOWN && scene->entity_selected->obj_type == CYLINDER)
        {        
                scene->entity_selected->obj.cylinder->height += ZOOM;
                scene->entity_selected->obj.cylinder->diameter += ZOOM;
        }
} */

