/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:18:42 by squinn            #+#    #+#             */
/*   Updated: 2025/08/16 15:18:24 by squinn           ###   ########.fr       */
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
# define CMD_NOT_FOUND_ERROR "Error: command not found"
# define PIPE_ERROR "Error: pipe() failed"
# define FORK_ERROR "Error: fork() failed"
# define PERMISSON_DENIED_ERROR "Error: permission denied"
// exit status code
# define SIGNAL_BASE_CODE 128
# define CMD_NOT_FOUND_CODE 127
# define PERMISSION_DENIED_CODE 126

// utils.c
void handle_error(char *message, int is_customized, int exit_status);
void handle_error_and_free(char *message, int is_customized, int **pids, int exit_status);
// main.c
char *find_path(char *command, char *environ[]);
void execute(char *command_and_args, char *environ[]);

#endif
