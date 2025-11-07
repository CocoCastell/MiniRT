/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:11:14 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/07 19:43:57 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

bool ft_is_str_float(const char *str)
{
	if (!str || *str == '\0' || *str == '.')
		return (false);
	if (*str == '+' || *str == '-')
        str++;
	if (*str == '\0')
		return (false);
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str) && *str != '.')
			return (false);
		str++;
	}
	return (true);
}

