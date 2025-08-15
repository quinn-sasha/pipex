/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:20:46 by squinn            #+#    #+#             */
/*   Updated: 2025/08/15 09:45:05 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void set_pipe_and_execute(char *command_and_args, char *environ[]) {

}

int main(int argc, char *argv[], char *environ[]) {
  if (argc < MINIMUM_ARGS)
    handle_error(USAGE);

  int input_fd = open(argv[1], O_RDONLY);
  if (input_fd == FAILED)
    handle_error(argv[1]);
  dup2(input_fd, STDIN_FILENO);
  close(input_fd);

  int command_index = 2;
  int last_command = argc - 2;
  while (command_index < last_command) {
    set_pipe_and_execute(argv[command_index], environ);
    command_index++;
  }
  int output_fd = open(argv[argc - 1], O_CREAT, O_WRONLY, O_TRUNC);
  if (output_fd == FAILED)
    handle_error(argv[argc - 1]);
  dup2(output_fd, STDOUT_FILENO);
  close(output_fd);
  exit(EXIT_SUCCESS);
}
