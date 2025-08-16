/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:20:46 by squinn            #+#    #+#             */
/*   Updated: 2025/08/16 13:54:08 by squinn           ###   ########.fr       */
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

void wait_all_children(pid_t *pids, int num_commands, int *status) {
  int i = 0;
  while (i < num_commands) {
    waitpid(pids[i], status, 0);
    i++;
  }
}

int main(int argc, char *argv[], char *environ[]) {
  if (argc < MINIMUM_ARGS)
    handle_error(USAGE, TRUE);
  int input_fd = open(argv[1], O_RDONLY);
  if (input_fd == FAILED)
    handle_error(argv[1], FALSE);
  int num_commands = argc - 3;
  pid_t *pids = malloc(num_commands);
  char **command = argv + 2;

  int pipe_fd[2];
  int i = 0;
  while (i < num_commands - 1) {
    if (pipe(pipe_fd) == FAILED)
      handle_error_and_free(PIPE_ERROR, TRUE, &pids);
    pid_t pid = fork();
    pids[i] = pid;
    if (pid == CHILD) {
      close(pipe_fd[READ]);
      dup2(input_fd, STDIN_FILENO);
      dup2(pipe_fd[WRITE], STDOUT_FILENO);
      execute(*command, environ);
    }
    close(pipe_fd[WRITE]);
    close(input_fd);
    input_fd = pipe_fd[READ];
    i++;
    command++;
  }
  int output_fd = open(argv[argc - 1], O_CREAT, O_TRUNC, O_WRONLY);
  if (output_fd == FAILED)
    handle_error_and_free(argv[argc - 1], FAILED, &pids);
  pid_t pid = fork();
  pids[i] = pid;
  if (pid == CHILD) {
    dup2(input_fd, STDIN_FILENO);
    dup2(output_fd, STDOUT_FILENO);
    execute(*command, environ);
  }
  int status;
  wait_all_children(pids, num_commands, &status);
  free(pids);
  exit(status);
}
