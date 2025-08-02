/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_hit_info plane_intersect(t_ray ray, t_plane plane, int i)
{
  t_plane_eq  var;
  t_hit_info  hit;
  float       denom;
  float       t;
  
  hit.has_hit = false;
  var.O = ray.origin;
  var.D = ray.direction;
  var.n = plane.normal[i];
  var.d = dot(plane.normal[i], plane.point[i]);
  denom = dot(var.n, var.D);
  if (fabs(denom) < 1e-6)
    return (hit);
  t = -(dot(var.n, var.O) + var.d) / denom;
  if (t < 1e-4)
    return (hit);
  hit.has_hit = true;
  hit.type = PLANE;
  hit.ent_index = i;
  hit.distance = t;
  return (hit);
  // t = -(aOx + bOy + cOz + d) / (aDx + bDy + cDz);
  // ax + by + zc + d = 0;
} 