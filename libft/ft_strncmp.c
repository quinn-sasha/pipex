/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:07:30 by squinn            #+#    #+#             */
/*   Updated: 2025/07/04 17:25:35 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int	main(int argc, char *argv[]) {
	(void)argc;
	assert(ft_strncmp(argv[1], argv[2], 100) == strncmp(argv[1], argv[2], 100));
	assert(ft_strncmp("abc", "abd", 2) ==  strncmp("abc", "abd", 2));
}
*/
