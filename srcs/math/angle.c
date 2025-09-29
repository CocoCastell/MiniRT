/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 11:31:38 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vec3	apply_rotation(t_vec3 vector, float R[3][3])
{
	t_vec3	new_vector;

	new_vector.x = R[0][0] * vector.x + R[0][1] * vector.y + R[0][2] * vector.z;
	new_vector.y = R[1][0] * vector.x + R[1][1] * vector.y + R[1][2] * vector.z;
	new_vector.z = R[2][0] * vector.x + R[2][1] * vector.y + R[2][2] * vector.z;
	return (new_vector);
}

// Matrice de rotation autour d'un axe arbitraire (formule de Rodrigues)
void	set_axis_angle_matrix(float matrix[3][3], t_vec3 axis, float angle)
{
	float	t;
	float	x;
	float	y;
	float	z;

	axis = normalize(axis);
	t = 1 - cos(angle);
	x = axis.x;
	y = axis.y;
	z = axis.z;
	matrix[0][0] = t * x * x + cos(angle);
	matrix[0][1] = t * x * y - sin(angle) * z;
	matrix[0][2] = t * x * z + sin(angle) * y;
	matrix[1][0] = t * x * y + sin(angle) * z;
	matrix[1][1] = t * y * y + cos(angle);
	matrix[1][2] = t * y * z - sin(angle) * x;
	matrix[2][0] = t * x * z - sin(angle) * y;
	matrix[2][1] = t * y * z + sin(angle) * x;
	matrix[2][2] = t * z * z + cos(angle);
}
