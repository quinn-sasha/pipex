/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:44:32 by squinn            #+#    #+#             */
/*   Updated: 2025/08/14 18:57:59y squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void handle_error(char *message, int is_customized) {
  if (is_customized)
    ft_putendl_fd(message, STDERR_FILENO);
  else
    perror(message);
  exit(EXIT_FAILURE);
}

void handle_error_and_free(char *message, int is_customized, int **pids) {
  if (is_customized)
    ft_putendl_fd(message, STDERR_FILENO);
  else
    perror(message);
  free(*pids);
  exit(EXIT_FAILURE);
}
