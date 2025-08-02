/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_digit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:11:14 by cochatel          #+#    #+#             */
/*   Updated: 2024/10/05 17:29:00 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

bool ft_is_only_digit(const char *str)
{
    if (!str || *str == '\0')
        return (false);
    if (*str == '+' || *str == '-' || *str == '.')
        str++;
    if (*str == '\0')
        return (false);
    while (*str)
    {
        if (!ft_isdigit((unsigned char)*str))
            return (false);
        str++;
    }
    return (true);
}