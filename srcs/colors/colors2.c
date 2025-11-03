/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:45:18 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/03 19:47:05 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	scale_color(t_color color, float scalar)
{
	t_color	scaled_color;

	scaled_color.r = color.r * scalar;
	scaled_color.g = color.g * scalar;
	scaled_color.b = color.b * scalar;
	return (scaled_color);
}

t_color	color_mult(t_color col1, t_color col2)
{
	t_color	new_color;

	new_color.r = col1.r * col2.r;
	new_color.g = col1.g * col2.g;
	new_color.b = col1.b * col2.b;
	return (new_color);
}
