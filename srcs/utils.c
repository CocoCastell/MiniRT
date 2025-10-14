/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel  cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 11:21:04 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/**
 * @brief Draw a pixel of a given color at specified coordinates in an image buf.
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

void	print_selection(t_ent_type selected)
{
	printf("You selected: ");
	if (selected == 0)
		printf("camera");
	else if (selected == 1)
		printf("light");
	else if (selected == 2)
		printf("plane");
	else if (selected == 3)
		printf("sphere");
	else if (selected == 4)
		printf("cylinder");
	printf("\n");
}

void	print_col(t_color col)
{
	printf("r: %f, g: %f, b: %f\n", col.r, col.g, col.b);
}

void	print_vec(t_vec3 v)
{
	printf("x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}
