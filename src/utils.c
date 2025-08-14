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

void handle_error(char *message) {
  if (errno < 1)
    ft_putendl_fd(message, STDERR_FILENO);
  else
    perror("Error");
  exit(EXIT_FAILURE);
}
