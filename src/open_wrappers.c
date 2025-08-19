/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_wrappers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:14:25 by squinn            #+#    #+#             */
/*   Updated: 2025/08/19 13:14:49 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_output_file(char *filename, int is_heredoc)
{
	if (is_heredoc)
		return (open(filename, O_CREAT | O_WRONLY | O_APPEND));
	return (open(filename, O_CREAT | O_WRONLY | O_TRUNC));
}

int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == FAILED)
		handle_error(filename, FALSE, EXIT_FAILURE);
	return (fd);
}
