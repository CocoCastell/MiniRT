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

# define STEP 1

void  camera_side_mouvement(int keycode, t_miniRt *minirt)
{
  t_camera *camera;

  camera = &minirt->scene->camera;
  if (keycode == A_KEY)
    camera.pos = add_vector(camera.pos, scalar_mult(camera.right, -STEP));
  if (keycode == D_KEY)
    camera.pos = add_vector(camera.pos, scalar_mult(camera.right, STEP));
  raytracing(minirt);
}