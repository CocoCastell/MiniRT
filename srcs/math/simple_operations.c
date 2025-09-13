/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  simple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float max(float a, float b)
{
  if (a > b)
    return a;
  return b;
}

float   to_radian(float degree)
{
    return (degree * M_PIF / 180.0f);
}

float vector_length(t_vec3 vect)
{
    return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

float vector_sq_length(t_vec3 vect)
{
    return (vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
}