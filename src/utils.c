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

void handle_error(char *message, int is_customized, int exit_status) {
  if (is_customized)
    ft_putendl_fd(message, STDERR_FILENO);
  else
    perror(message);
  exit(exit_status);
}

void handle_error_and_free(char *message, int is_customized, pid_t **pids, int exit_status) {
  if (is_customized)
    ft_putendl_fd(message, STDERR_FILENO);
  else
    perror(message);
  free(*pids);
  exit(exit_status);
}

t_program_args new_program_args(int argc, char **argv, char **environ, int is_heredoc) {
  t_program_args program_args;
  program_args.commands = argv + 2 + is_heredoc;
  program_args.environ = environ;
  program_args.output_file = argv[argc - 1];
  return program_args;
}
