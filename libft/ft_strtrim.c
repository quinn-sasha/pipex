/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:43:15 by squinn            #+#    #+#             */
/*   Updated: 2025/08/06 16:34:42 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char letter, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == letter)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	left;
	int	right;

	left = 0;
	while (s1[left] && is_in_set(s1[left], set))
		left++;
	if (s1[left] == '\0')
		return (ft_strdup(""));
	right = ft_strlen(s1) - 1;
	while (right >= 0 && is_in_set(s1[right], set))
		right--;
	return (ft_substr(s1, left, right));
}

/*
#include <stdio.h>

int	main(int argc, char *argv[]) {
	(void)argc;
	char const *s = argv[1];
	char const *set = argv[2];
	printf("Result: %s\n", ft_strtrim(s, set));
}
*/
