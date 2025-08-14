/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:06:08 by squinn            #+#    #+#             */
/*   Updated: 2025/07/04 15:06:00 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;
	size_t			i;

	if (n == 0 || dest == src)
		return (dest);
	tmp_dest = (unsigned char *)dest;
	tmp_src = (unsigned char *)src;
	if (tmp_dest < tmp_src)
	{
		i = 0;
		while (i < n)
		{
			tmp_dest[i] = tmp_src[i];
			i++;
		}
		return (dest);
	}
	while (n > 0)
	{
		n--;
		tmp_dest[n] = tmp_src[n];
	}
	return (dest);
}

/*
#include <unistd.h>

int main() {
	char src[] = "lorem ipsum dolor sit amet";

	char *dest = src + 1;
	ft_memmove(dest, "consectetur", 5);
	write(1, dest, 22);
}
*/
