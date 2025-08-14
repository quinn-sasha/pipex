/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:52:41 by squinn            #+#    #+#             */
/*   Updated: 2025/08/03 10:55:53 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, int last)
{
	int		src_len;
	char	*new_string;
	int		i;

	src_len = ft_strlen(s);
	if (start >= src_len)
		return (ft_strdup(""));
	if (start > last)
		return (ft_strdup(""));
	new_string = malloc(last - start + 2);
	if (!new_string)
		return (NULL);
	i = 0;
	while (i + start <= last)
	{
		new_string[i] = s[i + start];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
