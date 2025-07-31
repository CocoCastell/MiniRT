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

t_color  scale_color(t_color color, float scalar)
{
    t_color scaled_color;

    scaled_color.r = color.r * scalar;
    scaled_color.g = color.g * scalar;
    scaled_color.b = color.b * scalar;
    // scaled_color.a = color.a * scalar;
    return (scaled_color);
}

t_color color_mult(t_color col1, t_color col2)
{
    t_color new_color;

    new_color.r = col1.r * col2.r;
    new_color.g = col1.g * col2.g;
    new_color.b = col1.b * col2.b;
    // new_color.a = col1.a * col2.a;
    return (new_color);
}

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

t_color create_color(float r, float g, float b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
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

int float_color_to_int(t_color color)
{
    int a = (int)(color.a * 255.0f) & 0xFF;
    int r = (int)(color.r * 255.0f) & 0xFF;
    int g = (int)(color.g * 255.0f) & 0xFF;
    int b = (int)(color.b * 255.0f) & 0xFF;

    return ((a << 24) | (r << 16) | (g << 8) | b);
}

t_color	get_color(t_ray ray, t_hit_info hit_info, t_scene *scene)
{
	t_color pix_color;

	if (hit_info.has_hit == false)
	{
		if (ray.direction.y > -0.1)
			pix_color = ambient_reflection(scene, create_color(0.5f, 0.5f, 0.9f));
		else
			pix_color = ambient_reflection(scene, create_color(0.0f, 0.5f, 0.0f));
	}
	else
		pix_color = hit_info.color;
	return (pix_color);
}