/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_wrappers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:14:25 by squinn            #+#    #+#             */
/*   Updated: 2025/08/19 13:47:07 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_output_file(char *filename, int is_heredoc, int *pids)
{
    int fd;
	if (is_heredoc)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND);
    else
        fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC);
    if (fd == FAILED)
        handle_error_and_free(filename, FALSE, pids, EXIT_FAILURE);
    return fd;
}

int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == FAILED)
		handle_error(filename, FALSE, EXIT_FAILURE);
	return (fd);
}
