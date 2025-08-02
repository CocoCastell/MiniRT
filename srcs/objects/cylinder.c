/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void  add_cylinder(t_parse_data data, t_cylinder cylinder, int i)
{
	cylinder.center[i] = data.center;
	cylinder.axis[i] = data.normal;
	cylinder.height[i] = data.height;
	cylinder.color[i] = data.color;
	cylinder.shininess[i] = data.shininess;
	cylinder.spec_force[i] = data.spec_force;
	cylinder.reflectivity[i] = data.reflectivity;
}

/* t_hit_info cylinder_intersect(t_ray ray, t_plane plane, int i)
{
  t_hit_info  hit;
  float       t;
  t_vec3      center;

  hit->has_hit = false;
  center = plane.center[i];
  ||(X - center) - ((X - center) . v) . v ||^2 = r2
  t = 
  if ()
    return (hit);

  hit->has_hit = true;
  hit->distance = ;
  hit->ent_index = i;
  hit->type = CYLINDER;
  return (hit);
} */