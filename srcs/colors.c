/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color linear_gradient(t_color color1, t_color color2, float a)
{
    t_color new_color;
    
    if (a < 0.0f)
			a = 0.0f;
    if (a > 1.0f)
			a = 1.0f;
    new_color.r = (1.0f - a) * color1.r + a * color2.r;
    new_color.g = (1.0f - a) * color1.g + a * color2.g;
    new_color.b = (1.0f - a) * color1.b + a * color2.b;
    return new_color;
}

t_color create_color2(float r, float g, float b)
{
	t_color color;

	color.r = r * 255;
	color.g = g * 255;
	color.b = b * 255;
	return (color);
}

t_color create_color(t_vec3 rgb, int alpha)
{
	t_color color;

	color.r = 130;
	color.g = 130;
	color.b = 200;
	color.a = alpha;
	(void)rgb;
	return (color);
}

int	convert_int_color(t_color color)
{
	return ((color.a & 0xFF) << 24 | (color.r & 0xFF) << 16 | \
	(color.g & 0xFF) << 8 | (color.b & 0xFF));
}