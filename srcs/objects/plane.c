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

/**
 * @brief Adds a plane at index i in a SoA structure.
 *
 * This function inserts the plane data (point, normal, color, etc.)
 * into the corresponding arrays of the `t_plane` structure at the given index.
 * 
 * @param data Parsed plane data to insert (point, normal, color, etc.).
 * @param sphere Structure holding SoA arrays of all planes.
 * @param i Index at which to insert the sphere data in the `plane` structure.
 */
void  add_plane(t_parse_data data, t_plane plane, int i)
{
	plane.point[i] = data.point;
	plane.normal[i] = data.normal;
	plane.color[i] = data.color;
	plane.shininess[i] = data.shininess;
	plane.spec_force[i] = data.spec_force;
	plane.reflectivity[i] = data.reflectivity;
}

/**
 * @brief Computes the intersection between a ray and a plane.
 *
 * This function checks if the input ray intersects the i-th plane and, if so,
 * stores the intersection distance, type, and entity index in a t_hit_info structure.
 *
 * @param ray The incident ray.
 * @param plane Structure containing all planes in a Structure of Arrays layout.
 * @param i Index of the plane to test against.
 * @return A t_hit_info struct describing the hit result.
 */
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
    var.d = -dot(plane.normal[i], plane.point[i]);
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
}