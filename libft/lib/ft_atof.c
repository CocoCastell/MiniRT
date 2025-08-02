/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:11:14 by cochatel          #+#    #+#             */
/*   Updated: 2024/10/05 17:29:00 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static float ft_atof_fraction(const char *str, int *i)
{
    float   frac;
    float   div;

    frac = 0.0f;
    div = 10.0f;
    (*i)++;
    while (str[*i] >= '0' && str[*i] <= '9')
    {
        frac = frac + (str[*i] - '0') / div;
        div = div * 10.0f;
        (*i)++;
    }
    return (frac);
}

static void ft_atof_sign(const char *str, int *i, float *sign)
{
    while (str[*i] == ' ' || str[*i] == '\t')
        (*i)++;
    if (str[*i] == '-')
    {
        *sign = -1.0f;
        (*i)++;
    }
    else if (str[*i] == '+')
        (*i)++;
}

float ft_atof(const char *str)
{
    int   i;
    float result;
    float sign;

    i = 0;
    result = 0.0f;
    sign = 1.0f;
    ft_atof_sign(str, &i, &sign);
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10.0f;
        result = result + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
        result = result + ft_atof_fraction(str, &i);
    result = result * sign;
    return (result);
}