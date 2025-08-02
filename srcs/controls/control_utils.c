/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool    is_movement_key(int keycode)
{
        return (keycode == A_KEY || keycode == D_KEY || keycode == W_KEY || keycode == S_KEY || keycode == SPACE || keycode == SHIFT);
}

bool    is_rotation_key(int keycode)
{
        return (keycode == UP_K || keycode == DOWN_K || keycode == LEFT_K || keycode == RIGHT_K || keycode == Q_KEY || keycode == E_KEY);
}