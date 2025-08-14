/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:38:58 by squinn            #+#    #+#             */
/*   Updated: 2025/08/06 11:28:21 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_value(char c, const char *base_numbers)
{
	int	i;

	i = 0;
	while (base_numbers[i])
	{
		if (base_numbers[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, const char *base_numbers)
{
	int	sign;
	int	base;
	int	result;
	int	value;

	while (*str == ' ')
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	base = ft_strlen(base_numbers);
	result = 0;
	while (*str)
	{
		value = get_value(*str, base_numbers);
		if (value == -1)
			return (sign * result);
		result = result * base + value;
		str++;
	}
	return (sign * result);
}

/*
#include <stdio.h>

int	main(int argc, char *argv[]) {
  (void)argc;
  char *str = argv[1];
  char *base_numbers = argv[2];
  int result = ft_atoi_base(str, base_numbers);
  printf("%d\n", result);
}
*/
