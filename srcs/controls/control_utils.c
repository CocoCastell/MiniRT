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
			keycode == K_4 || keycode == K_5 || keycode == K_6 || keycode == I_KEY);
}

const char* print_setting_state(bool setting)
{
	if (setting)
		return ("on");
	else
		return ("off");
}

void	print_menu(t_settings settings)
{
	printf("Press: \n");
	printf("1 - Scene creation mode %s\n", print_setting_state(settings.scene_creation_on));
	printf("2 - Checkered %s\n", print_setting_state(settings.checkered_on));
	printf("3 - Gamma %s\n", print_setting_state(settings.gamma_on));
	printf("4 - Mirror %s\n", print_setting_state(settings.mirror_on));
	printf("5 - Plane %s\n", print_setting_state(settings.plane_on));
	printf("6 - Anti-aliasing %s\n", print_setting_state(settings.antialias_on));
	printf("I - Print menu\n");
}

void	set_opposite_bool(bool *bool_to_set)
{
	if (*bool_to_set == true)
		*bool_to_set = false;
	else
		*bool_to_set = true;
}
