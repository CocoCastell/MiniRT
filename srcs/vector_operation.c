/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  vector_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float   to_radian(float degree)
{
    return (degree * M_PIF / 180.0f);
}

float   dot(t_vec3 vec1, t_vec3 vec2)
{
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3  cross(t_vec3 vec1, t_vec3 vec2)
{
    t_vec3  crossed_vector;

    crossed_vector.x = vec1.y * vec2.z - vec1.z * vec2.y;
    crossed_vector.y = vec1.z * vec2.x - vec1.x *vec2.z;
    crossed_vector.z = vec1.x * vec2.y - vec1.y *vec2.x;
    return (crossed_vector);
}

t_vec3  scalar_mult(t_vec3 vector, float scalar)
{
    t_vec3 scaled_vector;

    scaled_vector.x = vector.x * scalar;
    scaled_vector.y = vector.y * scalar;
    scaled_vector.z = vector.z * scalar;
    return (scaled_vector);
}

bool	is_shorter_vec(t_vec3 main_vec, t_vec3 vec_to_compare, t_vec3 origin_point)
{
	t_vec3	sub_main_vec;
	t_vec3	sub_comp_vec;

	sub_main_vec = sub_vector(main_vec, origin_point);
	sub_comp_vec = sub_vector(vec_to_compare, origin_point);
	return (vector_sq_length(sub_main_vec) < vector_sq_length(sub_comp_vec));
}

t_vec3  apply_rotation(t_vec3 vector, float  R[3][3])
{
    t_vec3  new_vector;

    new_vector.x = R[0][0] * vector.x + R[0][1] * vector.y + R[0][2] * vector.z;
    new_vector.y = R[1][0] * vector.x + R[1][1] * vector.y + R[1][2] * vector.z;
    new_vector.z = R[2][0] * vector.x + R[2][1] * vector.y + R[2][2] * vector.z;
    return (new_vector);
}

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
t_vec3 sub_vector(t_vec3 origin_point, t_vec3 dest_point)
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

float vector_length(t_vec3 vect)
{
    return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

float vector_sq_length(t_vec3 vect)
{
    return (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
}

t_vec3  normalise_vector(t_vec3 vector)
{
    t_vec3  normalised_vector;
    float   magnitude;
    
    magnitude = vector_length(vector);
    if (magnitude == 0)
    {
        normalised_vector.x = 0;
        normalised_vector.y = 0;
        normalised_vector.z = 0;
        return (normalised_vector);
    }
    normalised_vector.x = vector.x / magnitude;
    normalised_vector.y = vector.y / magnitude;
    normalised_vector.z = vector.z / magnitude;
    return (normalised_vector);
}

t_vec3  scale_vector(t_vec3 vector, float scale_factor)
{
    t_vec3  new_vector;

    new_vector.x = vector.x * scale_factor;
    new_vector.y = vector.y * scale_factor;
    new_vector.z = vector.z * scale_factor;
    return (new_vector);
}

// Matrice de rotation autour d'un axe arbitraire (formule de Rodrigues)
void fill_axis_angle_matrix(float matrix[3][3], t_vec3 axis, float angle)
{
    float t;
    float x;
    float y;
    float z;
    
    axis = normalise_vector(axis);
    t = 1 - cos(angle);
    x = axis.x;
    y = axis.y;
    z = axis.z;
    matrix[0][0] = t*x*x + cos(angle);
    matrix[0][1] = t*x*y - sin(angle)*z;
    matrix[0][2] = t*x*z + sin(angle)*y;
    matrix[1][0] = t*x*y + sin(angle)*z;
    matrix[1][1] = t*y*y + cos(angle);
    matrix[1][2] = t*y*z - sin(angle)*x;
    matrix[2][0] = t*x*z - sin(angle)*y;
    matrix[2][1] = t*y*z + sin(angle)*x;
    matrix[2][2] = t*z*z + cos(angle);
}

