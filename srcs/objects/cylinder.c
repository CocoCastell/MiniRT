/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 12:12:33 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Adds a cylinder at index i in a SoA structure.
 *
 * This function inserts the cylinder data (center, color, radius, etc.)
 * into the corresponding arrays of the `t_cylinder` structure at the given idx.
 * 
 * @param data Parsed cylinder data to insert (position, color, radius, etc.).
 * @param cylinder Structure holding SoA arrays of all cylinders.
 * @param i Index at which to insert the cylinder data in the `cylinder` struct.
 */
void	add_cylinder(t_parse_data data, t_cylinder cylinder, int i)
{
	cylinder.center[i] = data.center;
	cylinder.radius[i] = data.radius;
	cylinder.axis[i] = data.normal;
	cylinder.height[i] = data.height;
	cylinder.color[i] = data.color;
	cylinder.shininess[i] = data.shininess;
	cylinder.spec_force[i] = data.spec_force;
	cylinder.reflectivity[i] = data.reflectivity;
}

/*t_hit_info cylinder_intersect(t_ray ray, t_cylinder cylinder, int i)
{
	t_hit_info  hit;
	t_vec3      center;
	float       t;

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
}*/
