/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:57:19 by squinn            #+#    #+#             */
/*   Updated: 2025/07/02 18:29:46 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	i;
	size_t	j;

	new_string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		new_string[i++] = s1[j++];
	j = 0;
	while (s2[j])
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	return (new_string);
}

/*
#include <stdio.h>

int	main(int argc, char *argv[]) {
	(void)argc;
	char const *s1 = argv[1];
	char const *s2 = argv[2];
	printf("Original string1 and string2: %s, %s\n", s1, s2);
	printf("new_string: %s\n", ft_strjoin(s1, s2));
}
*/
