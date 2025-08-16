/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:18:42 by squinn            #+#    #+#             */
/*   Updated: 2025/08/16 09:56:03 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include "../libft/libft.h"

# define CHILD 0
# define READ 0
# define WRITE 1
# define MINIMUM_ARGS 5

// Error messages
# define USAGE "Error: ./pipex input_file cmd1 cmd2 output_file"
# define COMMAND_NOT_FOUND "Error: command not found"
# define PIPE_ERROR "Error: pipe() failed"
# define FORK_ERROR "Error: fork() failed"

char *find_path(char *command, char *environ[]);
void execute(char *command_and_args, char *environ[]);
void handle_error(char *message, int is_customized_message);

#endif
