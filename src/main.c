/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:20:46 by squinn            #+#    #+#             */
/*   Updated: 2025/08/16 09:55:55 by squinn           ###   ########.fr       */
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



int main(int argc, char *argv[], char *environ[]) {
  if (argc < MINIMUM_ARGS)
    handle_error(USAGE, TRUE);


}
