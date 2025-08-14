/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:16:41 by squinn            #+#    #+#             */
/*   Updated: 2025/06/28 15:40:16 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c < 'a' || c > 'z')
		return (c);
	return (c + 'A' - 'a');
}

/*
#include <assert.h>
#include <ctype.h>

int	main(void) {

	assert(ft_toupper('z') == toupper('z'));
	assert(ft_toupper('A') == toupper('A'));
	assert(ft_toupper('&') == toupper('&'));
	assert(ft_toupper(1000) == toupper(1000));
}
*/
