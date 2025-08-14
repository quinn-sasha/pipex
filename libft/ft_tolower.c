/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:46:32 by squinn            #+#    #+#             */
/*   Updated: 2025/07/02 15:12:18 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c < 'A' || c > 'Z')
		return (c);
	return (c + 'a' - 'A');
}

/*
#include <assert.h>
#include <ctype.h>

int main(void) {
	assert(ft_tolower('Z') == tolower('Z'));
	assert(ft_tolower('z') == tolower('z'));
	assert(ft_tolower('&') == tolower('&'));
	assert(ft_tolower(1000) == tolower(1000));
}
*/
