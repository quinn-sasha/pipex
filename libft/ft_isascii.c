/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:20:33 by squinn            #+#    #+#             */
/*   Updated: 2025/06/27 17:32:50 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (TRUE);
	return (FALSE);
}

/*
#include <assert.h>
#include <ctype.h>

int main(void) {
	assert(ft_isascii(-1) == isascii(-1));
	assert(ft_isascii('a') == isascii('a'));
	assert(ft_isascii(1000) == ft_isascii(1000));
	return 0;
}
*/
