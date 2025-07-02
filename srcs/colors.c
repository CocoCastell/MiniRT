/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color create_color(t_vec3 rgb, int alpha)
{
	t_color color;

	color.r = 0;
	color.g = 0;
	color.b = -rgb.y * 255; //negatif + *255 a cause du vecteur position entre 0 et 2.0
	color.a = alpha;
	return (color);
}

int	convert_int_color(t_color color)
{
	return ((color.a & 0xFF) << 24 | (color.r & 0xFF) << 16 | \
	(color.g & 0xFF) << 8 | (color.b & 0xFF));
}