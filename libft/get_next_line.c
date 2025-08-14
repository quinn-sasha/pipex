/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squinn <squinn@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 09:31:41 by squinn            #+#    #+#             */
/*   Updated: 2025/08/14 09:31:43 by squinn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*handle_error(char **prefix, char **buffer)
{
	free(*buffer);
	if (*prefix)
		free(*prefix);
	*prefix = NULL;
	return (NULL);
}

static void	*handle_end_of_file(char **prefix, char **buffer)
{
	char	*temp;

	free(*buffer);
	if (*prefix == NULL)
		return (NULL);
	temp = *prefix;
	*prefix = NULL;
	return (temp);
}

static void	join_prefix_and_buffer(char **prefix, char **buffer)
{
	char	*temp;

	if (*prefix == NULL)
		*prefix = ft_strdup("");
	temp = *prefix;
	*prefix = ft_strjoin(temp, *buffer);
	free(temp);
	free(*buffer);
}

static void	set_new_prefix(char **prefix, int newline_pos)
{
	char	*temp;
	int		last;

	temp = *prefix;
	last = ft_strlen(*prefix) - 1;
	if (newline_pos == last)
		*prefix = NULL;
	else
		*prefix = ft_substr(*prefix, newline_pos + 1, last);
	free(temp);
}

/*
Assume fd and BUFFER_SIZE is valid.
Line doesn't contain newline.
*/
char	*get_next_line(int fd)
{
	char		*buffer;
	ssize_t		num_bytes_read;
	static char	*prefix;
	int			newline_pos;
	char		*line;

	while (TRUE)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (handle_error(&prefix, &buffer));
		ft_bzero(buffer, BUFFER_SIZE + 1);
		num_bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes_read < 0)
			return (handle_error(&prefix, &buffer));
		if (num_bytes_read == 0 && ft_strchr(prefix, '\n') == NOT_FOUND)
			return (handle_end_of_file(&prefix, &buffer));
		join_prefix_and_buffer(&prefix, &buffer);
		newline_pos = ft_strchr(prefix, '\n');
		if (newline_pos == NOT_FOUND)
			continue ;
		line = ft_substr(prefix, 0, newline_pos - 1);
		set_new_prefix(&prefix, newline_pos);
		return (line);
	}
}
