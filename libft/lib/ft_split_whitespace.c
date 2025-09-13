/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:46:21 by cochatel          #+#    #+#             */
/*   Updated: 2025/01/21 14:28:24 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static  bool  is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' ||
            c == '\r' || c == '\v' || c == '\f');
}

static int count_words(const char *str)
{
    int   count;
    bool  in_word;

    count = 0;
    in_word = false;
    while (*str)
    {
        if (is_whitespace(*str))
            in_word = false;
        else if (!in_word)
        {
            in_word = true;
            count++;
        }
        str++;
    }
    return (count);
}

static char *word_dup(const char *start, int len)
{
    char  *word;
    int   i;

    i = 0;
    word = malloc(len + 1);
    if (!word)
        return (NULL);
    while (i < len)
    {
        word[i] = start[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

char  **ft_split_whitespace(const char *str)
{
    char        **result;
    int         word_count;
    int         i;
    const char  *start;

    i = 0;
    word_count = count_words(str);
    result = malloc(sizeof(char *) * (word_count + 1));
    if (!result)
        return (NULL);
    while (*str)
    {
        while (*str && is_whitespace(*str))
            str++;
        if (*str)
        {
            start = str;
            while (*str && !is_whitespace(*str))
                str++;
            result[i++] = word_dup(start, str - start);
        }
    }
    result[i] = NULL;
    return (result);
}
