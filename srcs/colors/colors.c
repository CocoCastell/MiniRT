/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/03 19:46:04 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	create_color(float r, float g, float b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	add_color_no_limit(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r + color2.r;
	new_color.g = color1.g + color2.g;
	new_color.b = color1.b + color2.b;
	return (new_color);
}

t_color	add_color(t_color color1, t_color color2)
{
	t_color	new_color;

	new_color.r = color1.r + color2.r;
	new_color.g = color1.g + color2.g;
	new_color.b = color1.b + color2.b;
	if (new_color.r > 1.0f)
		new_color.r = 1.0f;
	if (new_color.g > 1.0f)
		new_color.g = 1.0f;
	if (new_color.b > 1.0f)
		new_color.b = 1.0f;
	return (new_color);
}

int	float_color_to_int(t_color color)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = (int)(color.a * 255.0f) & 0xFF;
	r = (int)(color.r * 255.0f) & 0xFF;
	g = (int)(color.g * 255.0f) & 0xFF;
	b = (int)(color.b * 255.0f) & 0xFF;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

void	mean_color(t_color *color, int ratio)
{
	color->r /= ratio;
	color->g /= ratio;
	color->b /= ratio;
}
