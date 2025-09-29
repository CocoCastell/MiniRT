/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 11:45:35 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	is_movement_key(int keycode)
{
	return (keycode == A_KEY || keycode == D_KEY || keycode == W_KEY || \
			keycode == S_KEY || keycode == SPACE || keycode == SHIFT);
}

bool	is_rotation_key(int keycode)
{
	return (keycode == UP_K || keycode == DOWN_K || keycode == LEFT_K || \
			keycode == RIGHT_K || keycode == Q_KEY || keycode == E_KEY);
}

bool	is_setting_key(int keycode)
{
	return (keycode == K_1 || keycode == K_2 || keycode == K_3 || \
			keycode == K_4 || keycode == K_5);
}

void	set_opposite_bool(bool *bool_to_set)
{
	if (*bool_to_set == true)
		*bool_to_set = false;
	else
		*bool_to_set = true;
}
