/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:20:46 by squinn            #+#    #+#             */
/*   Updated: 2025/08/19 08:38:54 by squinn           ###   ########.fr       */
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
  i = 0;
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

// Assume command and aruments are splited by space.
void execute(char *command_and_args, char *environ[], pid_t *pids) {
  char **argv = ft_split(command_and_args, ' ');
  char *path = find_path(argv[0], environ);
  if (path == NULL) {
    free_words(argv);
    handle_error_and_free(CMD_NOT_FOUND_ERROR, TRUE, pids, CMD_NOT_FOUND_CODE);
  }
  if (access(path, X_OK) == FAILED) {
    free_words(argv);
    free(path);
    handle_error_and_free(PERMISSON_DENIED_ERROR, TRUE, pids, PERMISSION_DENIED_CODE);
  }
  execve(path, argv, environ);
}

void set_pipe_and_execute(t_program_args program_args, pid_t *pids, int num_commands, int input_fd) {
  int pipe_fd[2];
  int i = 0;
  while (i < num_commands - 1) {
    if (pipe(pipe_fd) == FAILED)
      handle_error_and_free(PIPE_ERROR, FALSE, pids, EXIT_FAILURE);
    pids[i] = fork();
    if (pids[i] == CHILD) {
      close(pipe_fd[READ]);
      dup2(input_fd, STDIN_FILENO);
      dup2(pipe_fd[WRITE], STDOUT_FILENO);
      execute(program_args.commands[i], program_args.environ, pids);
    }
    close(pipe_fd[WRITE]);
    close(input_fd);
    input_fd = pipe_fd[READ];
    i++;
  }
  int output_file_fd = open(program_args.output_file, O_CREAT | O_TRUNC | O_WRONLY);
  if (output_file_fd == FAILED)
    handle_error_and_free(program_args.output_file, FALSE, pids, EXIT_FAILURE);
  pids[i] = fork();
  if (pids[i] == CHILD) {
    dup2(input_fd, STDIN_FILENO);
    dup2(output_file_fd, STDOUT_FILENO);
    execute(program_args.commands[i], program_args.environ, pids);
  }
  close(input_fd);
}

int wait_all_children(pid_t *pids, int num_commands) {
  int status;
  int i = 0;
  while (i < num_commands) {
    waitpid(pids[i], &status, 0);
    i++;
  }
  if WIFEXITED(status)
    return WEXITSTATUS(status);
  if WIFSIGNALED(status)
    return SIGNAL_BASE_CODE + WTERMSIG(status);
  return EXIT_FAILURE;
}

// This here document does not implement environmental variable expasion
// and commad substitution.
int here_document_to_input_fd(char *delimiter) {
  int pipe_fd[2];
  if (pipe(pipe_fd) == FAILED)
    handle_error(PIPE_ERROR, FALSE, EXIT_FAILURE);
  pid_t pid = fork();
  if (pid == CHILD) {
    close(pipe_fd[READ]);
    while (TRUE) {
      char *line = get_next_line(STDIN_FILENO);
      if (is_same_string(line, delimiter)) {
        free(line);
        exit(EXIT_SUCCESS);
      }
      if (line)
        write(pipe_fd[WRITE], line, ft_strlen(line));
      free(line);
    }
  }
  close(pipe_fd[WRITE]);
  wait(NULL);
  return pipe_fd[READ];
}

int main(int argc, char *argv[], char *environ[]) {
  if (argc < MINIMUM_ARGS)
    handle_error(USAGE, TRUE, EXIT_FAILURE);
  int input_fd;
  int is_heredoc = FALSE;
  if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0) {
    is_heredoc = TRUE;
    if (argc < HERE_DOC_MINIMUM_ARGS)
      handle_error(HERE_DOC_USAGE, TRUE, EXIT_FAILURE);
    input_fd = here_document_to_input_fd(argv[DELIMITER_POSITION]);
  } else {
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == FAILED)
      handle_error(argv[1], FALSE, EXIT_FAILURE);
  }
  int num_commands = argc - (3 + is_heredoc);
  t_program_args program_args = new_program_args(argc, argv, environ, is_heredoc);
  int output_fd = open_wrapper(); // TODO
  pid_t *pids = malloc(num_commands);

  set_pipe_and_execute(program_args, pids, num_commands, input_fd);
  int last_status;
  last_status = wait_all_children(pids, num_commands);
  free(pids);
  exit(last_status);
}
