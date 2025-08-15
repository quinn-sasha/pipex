/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:20:46 by squinn            #+#    #+#             */
/*   Updated: 2025/08/15 09:18:26 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


int main(int argc, char *argv[], char *environ[]) {
  if (argc < MINIMUM_ARGS)
    handle_error(USAGE);

  int input_fd = open(argv[1], O_RDONLY);
  if (input_fd == FAILED)
    handle_error(argv[1]);
  dup2(input_fd, STDIN_FILENO);
  close(input_fd);

}
