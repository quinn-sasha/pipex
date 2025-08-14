/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:41:36 by squinn            #+#    #+#             */
/*   Updated: 2025/08/06 16:31:54 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	result;
	int	i;

	if (s[0] == '\0')
		return (0);
	result = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		while (s[i] && s[i] != c)
			i++;
		result++;
	}
	return (result);
}

static void	*free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

static int	get_word_end(char const *s, char c, int start)
{
	int	i;

	i = start;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		nword;
	int		num_words;
	int		i;
	int		word_end;

	num_words = count_words(s, c);
	result = ft_calloc(num_words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	nword = 0;
	while (nword < num_words)
	{
		while (s[i] == c)
			i++;
		word_end = get_word_end(s, c, i);
		result[nword] = ft_substr(s, i, word_end - 1);
		if (!result[nword])
			return (free_words(result));
		i = word_end;
		nword++;
	}
	return (result);
}

/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char const	*s;
	char		c;
	char		**result;

	(void)argc;
	s = argv[1];
	c = argv[2][0];
	result = ft_split(s, c);
	for (int i = 0; result[i]; i++)
	{
		printf("%s\n", result[i]);
	}
}
*/
