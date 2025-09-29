/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 11:40:51 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Adds a triangle at index i in a SoA structure.
 *
 * This function inserts the triangle data (position, color, radius, etc.)
 * into the corresponding arrays of the `t_triangle` structure at the given idx.
 * 
 * @param data Parsed triangle data to insert (position, color, radius, etc.).
 * @param triangle Structure holding SoA arrays of all triangles.
 * @param i Index at which to insert the triangle data in the `triangle` struct.
 */
void	add_triangle(t_parse_data data, t_triangle triangle, int i)
{
	triangle.pointA[i] = data.point;
	triangle.pointB[i] = data.point2;
	triangle.pointC[i] = data.point3;
	triangle.color[i] = data.color;
	triangle.shininess[i] = data.shininess;
	triangle.spec_force[i] = data.spec_force;
	triangle.reflectivity[i] = data.reflectivity;
}

/* t_hit_info triangle_intersect(t_ray ray, t_triangle triangle, int i)
{
	t_hit_info	hit;
	float				t;

	hit.has_hit = false;
	t_vec3 AB = vector_from_to(triangle.pointA[i], triangle.pointB[i]);	
	t_vec3 BC = vector_from_to(triangle.pointB[i], triangle.pointC[i]);	
	t_vec3 CA = vector_from_to(triangle.pointC[i], triangle.pointA[i]);	
	hit.has_hit = true;
	hit.type = TRIANGLE;
	hit.ent_index = i;
	hit.distance = t;
	return (hit);
} */
