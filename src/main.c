/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:20:46 by squinn            #+#    #+#             */
/*   Updated: 2025/08/19 14:22:31 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*find_path(char *command, char *environ[])
{
	int		i;
	char	**paths;
	char	*dir_path;
	char	*path;

	i = 0;
	while (!is_same_string(environ[i], "PATH"))
		i++;
	paths = ft_split(environ[i] + ft_strlen("PATH="), ':');
	i = -1;
	while (paths[++i])
	{
		dir_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(dir_path, command);
		free(dir_path);
		if (access(path, F_OK) == FAILED)
		{
			free(path);
			continue ;
		}
		free_words(paths);
		return (path);
	}
	free_words(paths);
	return (NULL);
}

// It can only execute shell command.
// Assume command and arguments are splited by space.
void	execute(char *command_and_args, char *environ[], pid_t *pids)
{
	char	**argv;
	char	*path;

	argv = ft_split(command_and_args, ' ');
	path = find_path(argv[0], environ);
	if (path == NULL)
	{
		free_words(argv);
		handle_error_and_free(CMD_NOT_FOUND_ERROR, TRUE, pids,
			CMD_NOT_FOUND_CODE);
	}
	if (access(path, X_OK) == FAILED)
	{
		free_words(argv);
		free(path);
		handle_error_and_free(PERMISSON_DENIED_ERROR, TRUE, pids,
			PERMISSION_DENIED_CODE);
	}
	execve(path, argv, environ);
}

void execute_last_command(t_program_args program_args, int *pids, int input_fd) {
  int output_fd = open_output_file(program_args.output_file, program_args.is_heredoc, pids);
  int index = program_args.num_commands - 1;
  pids[index] = fork();
  if (pids[index] == CHILD) {
    dup2(input_fd, STDIN_FILENO);
    dup2(output_fd, STDOUT_FILENO);
    execute(program_args.commands[index], program_args.environ, pids);
  }
  close(input_fd);
}

void	set_pipe_and_execute(t_program_args program_args, pid_t *pids,
		int input_fd)
{
	int	pipe_fd[2];
	int	i;
	int	output_fd;

	i = 0;
	while (i < program_args.num_commands - 1)
	{
		if (pipe(pipe_fd) == FAILED)
			handle_error_and_free(PIPE_ERROR, FALSE, pids, EXIT_FAILURE);
		pids[i] = fork();
		if (pids[i] == CHILD)
		{
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
  execute_last_command(program_args, pids, input_fd);
}

int	wait_all_children(pid_t *pids, int num_commands)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_commands)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if WIFEXITED (status)
		return (WEXITSTATUS(status));
	if WIFSIGNALED (status)
		return (SIGNAL_BASE_CODE + WTERMSIG(status));
	return (EXIT_FAILURE);
}

// This here document does not implement environmental variable expasion
// and commad substitution.
int	here_document_to_input_fd(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*line;

	pipe(pipe_fd);
	if (fork() == CHILD)
	{
		close(pipe_fd[READ]);
		while (TRUE)
		{
			ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
			line = get_next_line(STDIN_FILENO);
			if (is_same_string(line, delimiter))
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			if (line)
				ft_putendl_fd(line, pipe_fd[WRITE]);
			free(line);
		}
	}
	close(pipe_fd[WRITE]);
	wait(NULL);
	return (pipe_fd[READ]);
}

int	main(int argc, char *argv[], char *environ[])
{
	int				input_fd;
	t_program_args	program_args;
	pid_t			*pids;
	int				last_status;

	if (argc < MINIMUM_ARGS)
		handle_error(USAGE, TRUE, EXIT_FAILURE);
	if (!is_same_string(argv[1], "here_doc"))
	{
		program_args.is_heredoc = FALSE;
		input_fd = open_input_file(argv[1]);
	}
	else
	{
		program_args.is_heredoc = TRUE;
		if (argc < HERE_DOC_MINIMUM_ARGS)
			handle_error(HERE_DOC_USAGE, TRUE, EXIT_FAILURE);
		input_fd = here_document_to_input_fd(argv[DELIMITER_POSITION]);
	}
	program_args = new_program_args(argc, argv, environ,
			program_args.is_heredoc);
	pids = malloc(program_args.num_commands);
	set_pipe_and_execute(program_args, pids, input_fd);
	last_status = wait_all_children(pids, program_args.num_commands);
	free(pids);
	exit(last_status);
}
