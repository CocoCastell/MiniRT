/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:14:49 by cochatel          #+#    #+#             */
/*   Updated: 2024/10/05 18:05:29 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void int_to_str(int value, char *buffer, int *index, int j)
{
    char  temp[12];
    char  c;
    int   i;

    i = 0;
    if (value == 0)
        temp[i++] = '0';
    else
    {
        while (value > 0)
        {
            temp[i++] = '0' + (value % 10);
            value /= 10;
        }
    }
    while (++j < i / 2)
    {
        c = temp[j];
        temp[j] = temp[i - 1 - j];
        temp[i - 1 - j] = c;
    }
    j = -1;
    while (++j < i)
        buffer[(*index)++] = temp[j];
}

static void frac_to_str(float frac_part, int precision, char *buffer, int *i)
{
  int p;
  int digit;

  p = -1;
  while (++p < precision)
  {
    frac_part *= 10;
    digit = (int)frac_part;
    buffer[(*i)++] = '0' + digit;
    frac_part -= digit;
  }
}

char    *ft_float_to_str(float value, char *buffer, int precision)
{
    int   i;
    int   int_part;
    float frac_part;
    
    i = 0;
    if (value < 0)
    {
        buffer[i++] = '-';
        value = -value;
    }
    int_part = (int)value;
    frac_part = value - int_part;
    int_to_str(int_part, buffer, &i, -1);
    buffer[i++] = '.';
    frac_to_str(frac_part, precision, buffer, &i);
    buffer[i] = '\0';
    return (buffer);
}