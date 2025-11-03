/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/03 20:08:24 by cochatel         ###   ########.fr       */
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
	triangle.point_a[i] = data.point;
	triangle.point_b[i] = data.point2;
	triangle.point_c[i] = data.point3;
	triangle.color[i] = data.color;
	triangle.shininess[i] = data.shininess;
	triangle.spec_force[i] = data.spec_force;
	triangle.reflectivity[i] = data.reflectivity;
}

void	triangle_intersect(t_hit_info *hit, t_ray ray, t_triangle trgl, int i)
{
	t_vec3		sides[3];
	float		t;

	t = 0;
	hit->has_hit = false;
	sides[0] = vector_from_to(trgl.point_a[i], trgl.point_b[i]);
	sides[1] = vector_from_to(trgl.point_b[i], trgl.point_c[i]);
	sides[2] = vector_from_to(trgl.point_c[i], trgl.point_a[i]);
	hit->has_hit = true;
	hit->type = TRIANGLE;
	hit->ent_index = i;
	hit->distance = t;
	(void)sides;
	(void)ray;
}
