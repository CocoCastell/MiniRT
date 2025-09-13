/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/**
 * @brief Draw a pixel of a given color at specified coordinates in an image buffer.
 * 
 * Writes the color value directly into the image's pixel data at (x, y),
 * after verifying that the coordinates are within image bounds.
 * 
 * @param x Horizontal pixel coordinate.
 * @param y Vertical pixel coordinate.
 * @param img Pointer to the image data structure.
 * @param color Color value encoded as an integer (usually 0xAARRGGBB).
 */
void	put_pixel(int x, int y, t_data_img *img, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT && y >= 0)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}