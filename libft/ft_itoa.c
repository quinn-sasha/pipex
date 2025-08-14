/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:31:49 by squinn            #+#    #+#             */
/*   Updated: 2025/07/02 19:31:50 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_converted(long long int num)
{
	int	result;

	result = 0;
	if (num < 0)
	{
		num = -num;
		result++;
	}
	while (num > 0)
	{
		num /= 10;
		result++;
	}
	return (result);
}

static void	check_negative_and_initialize(long long int *num, int *is_negative)
{
	(*is_negative) = 0;
	if ((*num) < 0)
	{
		(*num) = -(*num);
		(*is_negative) = 1;
	}
}

char	*ft_itoa(int n)
{
	long long int	num;
	char			*result;
	int				is_negative;
	int				i;

	num = (long long int)n;
	if (num == 0)
		return (ft_strdup("0"));
	result = malloc(len_converted(num) + 1);
	if (!result)
		return (NULL);
	i = len_converted(num);
	result[i--] = '\0';
	check_negative_and_initialize(&num, &is_negative);
	while (num > 0)
	{
		result[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	if (is_negative)
		result[i] = '-';
	return (result);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int	n;

	(void)argc;
	n = atoi(argv[1]);
	printf("Result: %s\n", ft_itoa(n));
}
*/
