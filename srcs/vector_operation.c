/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*  vector_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float vector_length(t_vec3 vect)
{
    return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
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