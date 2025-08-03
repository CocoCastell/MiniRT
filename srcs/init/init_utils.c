/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	get_fd_file(char *file, t_miniRt *minirt)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		free_error(minirt, "Cannot open file\n", 1);
	return (fd);
}

bool	has_rt_extension(const char *filename)
{
  size_t	len;

	len = strlen(filename);
  if (len < 3)
    return false;
  return (strcmp(filename + len - 3, ".rt") == 0);
}

void	init_pixel_offsets(t_scene *scene)
{
    int i;

		i = -1;
		while (++i < WIN_WIDTH)
        scene->v_port.x_offsets[i] = i - WIN_WIDTH / 2.0f;
		i = -1;
		while (++i < WIN_HEIGHT)
        scene->v_port.y_offsets[i] = WIN_HEIGHT / 2.0f - i;
}