/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:18:42 by squinn            #+#    #+#             */
/*   Updated: 2025/08/19 14:09:41 by squinn           ###   ########.fr       */
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
# define HERE_DOC_MINIMUM_ARGS 6
# define DELIMITER_POSITION 2

// Error messages
# define USAGE "Usage: ./pipex input_file cmd1 cmd2 output_file"
# define HERE_DOC_USAGE "Usage: ./pipex here_doc DELIMITER cmd cmd1 file"
# define CMD_NOT_FOUND_ERROR "Error: command not found"
# define PIPE_ERROR "Error: pipe() failed"
# define FORK_ERROR "Error: fork() failed"
# define PERMISSON_DENIED_ERROR "Error: permission denied"
// exit status code
# define SIGNAL_BASE_CODE 128
# define CMD_NOT_FOUND_CODE 127
# define PERMISSION_DENIED_CODE 126

typedef struct s_program_args {
  char **commands;
  int num_commands;
  char **environ;
  char *output_file;
  int is_heredoc;
} t_program_args;

// utils.c
void handle_error(char *message, int is_customized, int exit_status);
void handle_error_and_free(char *message, int is_customized, int *pids, int exit_status);
t_program_args new_program_args(int argc, char **argv, char **environ, int is_heredoc);
int is_same_string(char *s1, char *s2);
// open_wrappers.c
int	open_output_file(char *filename, int is_heredoc, int *pids);
int open_input_file(char *filename);
// main.c
char *find_path(char *command, char *environ[]);
void execute(char *command_and_args, char *environ[], pid_t *pids);
int wait_all_children(pid_t *pids, int num_commands);

#endif
