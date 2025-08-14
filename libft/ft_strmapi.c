/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:14:04 by squinn            #+#    #+#             */
/*   Updated: 2025/07/05 13:08:39 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_string;
	unsigned int	i;

	new_string = malloc(ft_strlen(s) + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_string[i] = (*f)(i, s[i]);
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
