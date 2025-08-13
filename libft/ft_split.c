/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:06:56 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/04 00:59:46 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charsequivalent(char stri, char c)
{
	if (stri == c)
		return (1);
	return (0);
}

static int	word_count(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_charsequivalent(*str, c))
			str++;
		if (*str)
		{
			count++;
			while (*str && !is_charsequivalent(*str, c))
				str++;
		}
	}
	return (count);
}

static char	*malloc_word(const char *str, char c)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (str[len] && !is_charsequivalent(str[len], c))
		len++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_freeall_words(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	int		total;
	char	**result;
	int		i;

	total = word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (total + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && is_charsequivalent(*s, c))
			s++;
		if (*s && !is_charsequivalent(*s, c))
		{
			result[i] = malloc_word(s, c);
			if (!result[i])
				return (ft_freeall_words(result));
			i++;
			while (*s && !is_charsequivalent(*s, c))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
