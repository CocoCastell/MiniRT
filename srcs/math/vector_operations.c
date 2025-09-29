/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 12:02:55 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	cross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	crossed_vector;

	crossed_vector.x = vec1.y * vec2.z - vec1.z * vec2.y;
	crossed_vector.y = vec1.z * vec2.x - vec1.x * vec2.z;
	crossed_vector.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (crossed_vector);
}

t_vec3	normalize(t_vec3 vector)
{
	t_vec3	normalized_vector;
	float	magnitude;

	magnitude = vector_length(vector);
	if (magnitude == 0)
	{
		normalized_vector.x = 0;
		normalized_vector.y = 0;
		normalized_vector.z = 0;
		return (normalized_vector);
	}
	normalized_vector.x = vector.x / magnitude;
	normalized_vector.y = vector.y / magnitude;
	normalized_vector.z = vector.z / magnitude;
	return (normalized_vector);
}

t_vec3	scale_vector(t_vec3 vector, float scalar)
{
	t_vec3	new_vector;

	new_vector.x = vector.x * scalar;
	new_vector.y = vector.y * scalar;
	new_vector.z = vector.z * scalar;
	return (new_vector);
}
