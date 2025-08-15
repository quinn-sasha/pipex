/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:20:46 by squinn            #+#    #+#             */
/*   Updated: 2025/08/15 15:35:26 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char *find_path(char *command, char *environ[]) {
  int i = 0;
  while (environ[i]) {
    if (ft_strncmp(environ[i], "PATH", 4) == 0)
      break;
    i++;
  }
  char **paths = ft_split(environ[i] + ft_strlen("PATH="), ':');
  int i = 0;
  while (paths[i]) {
    char *dir_path = ft_strjoin(paths[i], "/");
    char *path = ft_strjoin(dir_path, command);
    free(dir_path);
    if (access(path, F_OK) == FAILED) {
      free(path);
      i++;
      continue;
    }
    free_words(paths);
    return path;
  }
  free_words(paths);
  return NULL;
}

void execute(char *command_and_args, char *environ[]) {
  char **argv = ft_split(command_and_args, ' ');
  char *path = find_path(argv[0], environ);
  if (path == NULL) {
    free_words(argv);
    handle_error(COMMAND_NOT_FOUND, TRUE);
  }
  execve(path, argv, environ);
  free_words(argv);
  free(path);
  // TODO: better error message needed
  handle_error("execve", FALSE);
}

void set_pipe_and_execute(char *command_and_args, char *environ[]) {
  int fd[2];
  if (pipe(fd) == FAILED)
    handle_error(PIPE_ERROR, FALSE);
  pid_t pid = fork();
  if (pid == FAILED)
    handle_error(FORK_ERROR, FALSE);
  if (pid == CHILD) {
    close(fd[READ]);
    dup2(fd[WRITE], STDOUT_FILENO);
    close(fd[WRITE]);
    execute(command_and_args, environ);
  }
  close(fd[WRITE]);
  dup2(fd[READ], STDIN_FILENO);
  close(fd[READ]);
  waitpid(pid, NULL, 0);
}

int main(int argc, char *argv[], char *environ[]) {
  if (argc < MINIMUM_ARGS)
    handle_error(USAGE, TRUE);

  int input_fd = open(argv[1], O_RDONLY);
  if (input_fd == FAILED)
    handle_error(argv[1], FALSE);
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
    handle_error(argv[argc - 1], FALSE);
  dup2(output_fd, STDOUT_FILENO);
  close(output_fd);
  execute(argv[command_index], environ);
}
