/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:16:09 by squinn            #+#    #+#             */
/*   Updated: 2025/07/04 17:52:43 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	if (find[0] == '\0')
		return ((char *)(str));
	if (str[0] == '\0')
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		j = 0;
		while (find[j] && str[i + j])
		{
			if (find[j] != str[i + j])
				break ;
			if (i + j >= len)
				return (NULL);
			j++;
		}
		if (find[j] == '\0')
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
