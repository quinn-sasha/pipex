/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:04:55 by squinn            #+#    #+#             */
/*   Updated: 2025/06/27 18:13:44 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (TRUE);
	return (FALSE);
}

/*
#include <assert.h>
#include <ctype.h>

int main(void) {
	assert(ft_isprint(' ') != 0);
	assert(isprint(' ') != 0);

	assert(ft_isprint(0) == 0);
	assert(isprint(0) == 0);

	assert(ft_isprint('9') != 0);
	assert(isprint('9') != 0);
	return 0;
}
*/
