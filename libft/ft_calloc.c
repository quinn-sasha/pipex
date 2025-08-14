/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:40:49 by squinn            #+#    #+#             */
/*   Updated: 2025/07/05 13:31:19 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	unsigned char	*tmp;

	if (nmeb == 0 || size == 0)
		return (malloc(0));
	tmp = malloc(nmeb * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, nmeb * size);
	return (tmp);
}

/*
#include <stdio.h>
#include <assert.h>

int	main(int argc, char *argv[]) {
	(void)argc;
	size_t nmeb = atoi(argv[1]);
	int *nums = calloc(nmeb, sizeof(int));
	for (size_t i = 0; i < nmeb; i++) {
		printf("%d ", nums[i]);
	}

	if (ft_calloc(0, 0) == NULL)
		printf("ft_calloc returned NULL\n");
	if (calloc(0, 0) == NULL)
		printf("alloc returned NULL\n");
	return (0);
}
*/
