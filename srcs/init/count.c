/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/08 13:34:39 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Initialize all object counters to zero.
 * 
 * @param counter Pointer to the object counter structure to initialize.
 */
void	init_counter(t_o_cnt *counter)
{
	counter->sphere = 0;
	counter->plane = 0;
	counter->triangle = 0;
	counter->cylinder = 0;
	counter->light = 0;
	counter->camera = 0;
	counter->ambient = 0;
}

/**
 * @brief Increment the counter for the given object type token.
 * 
 * Matches the token string to known identifiers and increments the
 * corresponding counter. Calls error handler on unknown token.
 * 
 * @param token String identifier of the object type.
 * @param counter Pointer to the object counters.
 * @param minirt Pointer to the main program structure for error handling.
 */
void	compute_count(char *token, t_o_cnt *counter, t_minirt *minirt)
{
	if (ft_strncmp(token, "sp", 3) == 0)
		counter->sphere++;
	else if (ft_strncmp(token, "pl", 3) == 0)
		counter->plane++;
	else if (ft_strncmp(token, "cy", 3) == 0)
		counter->cylinder++;
	else if (ft_strncmp(token, "tr", 3) == 0)
		counter->triangle++;
	else if (ft_strncmp(token, "L", 2) == 0)
		counter->light++;
	else if (ft_strncmp(token, "C", 2) == 0)
		counter->camera++;
	else if (ft_strncmp(token, "A", 2) == 0)
		counter->ambient++;
	else
		free_error(minirt, "Wrong identifier.\n", 1);
}

/**
 * @brief Count occurrences of each object type in a scene description file.
 * 
 * Reads the file line-by-line, splits tokens by whitespace, and updates
 * the object counters accordingly. Checks for invalid duplicates of
 * camera and ambient light, and closes the file at the end.
 * 
 * @param fd File descriptor of the open scene file.
 * @param minirt Pointer to the main program structure for error handling.
 * @return t_o_cnt Struct containing counts of each object type found.
 */
t_o_cnt	count_objects(int fd, t_minirt *minirt)
{
	t_o_cnt	counter;
	char	*line;
	char	**tokens;
	int		is_eof;

	init_counter(&counter);
	while (1)
	{
		line = get_next_line(fd, &is_eof);
		if (line == NULL && is_eof == -1)
			free_error(minirt, "Get_next_line error.\n", 1);
		if (line == NULL)
			break ;
		tokens = ft_split_whitespace(line);
		if (tokens && tokens[0])
			compute_count(tokens[0], &counter, minirt);
		ft_free_string_array(tokens);
		free(line);
	}
	if (counter.camera > 1)
		free_error(minirt, "Camera is defined twice.\n", 1);
	if (counter.ambient > 1)
		free_error(minirt, "Ambient light is defined twice.\n", 1);
	close(fd);
	return (counter);
}
