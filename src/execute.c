/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:32:30 by squinn            #+#    #+#             */
/*   Updated: 2025/08/20 09:27:32 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void	execute_last_command(t_program_args program_args, int *pids,
		int input_fd)
{
	int	output_fd;
	int	index;

	output_fd = open_output_file(program_args.output_file,
			program_args.is_heredoc, pids);
	index = program_args.num_commands - 1;
	pids[index] = fork();
	if (pids[index] == CHILD)
	{
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
