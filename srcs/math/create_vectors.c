/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  create_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec3  add_vector(t_vec3 vector1, t_vec3 vector2)
{
    t_vec3  new_vector;

    new_vector.x = vector1.x + vector2.x;
    new_vector.y = vector1.y + vector2.y;
    new_vector.z = vector1.z + vector2.z;
    return (new_vector);
}

/**
 * @brief Creates a vector from origin_point to dest_point.
 * 
 * @param origin_point Starting point.
 * @param dest_point Ending point.
 * @return Vector from origin to destination.
 */
t_vec3 vector_from_to(t_vec3 origin_point, t_vec3 dest_point)
{
	t_vec3 vector;

	vector.x = dest_point.x - origin_point.x;
	vector.y = dest_point.y - origin_point.y;
	vector.z = dest_point.z - origin_point.z;
	return (vector);
}

t_vec3  vec3(float x, float y, float z)
{
    t_vec3 point;

    point.x = x;
    point.y = y;
    point.z = z;
    return (point);
}

t_vec3  negate_vec(t_vec3 vector)
{
    t_vec3  inverted_vec;

    inverted_vec.x = -vector.x;
    inverted_vec.y = -vector.y;
    inverted_vec.z = -vector.z;
    return (inverted_vec);
}