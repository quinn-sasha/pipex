/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:20:46 by squinn            #+#    #+#             */
/*   Updated: 2025/08/19 18:33:00 by squinn           ###   ########.fr       */
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
