/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:30:14 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/16 21:02:15 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

int	find_next_line(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}

int	read_and_join(int fd, char **buffer, char *temp)
{
	int		read_byte;
	char	*old_buffer;

	read_byte = read(fd, temp, BUFFER_SIZE);
	if (read_byte == -1)
	{
		free(*buffer);
		*buffer = NULL;
		return (-1);
	}
	if (read_byte == 0)
		return (0);
	temp[read_byte] = '\0';
	old_buffer = *buffer;
	*buffer = ft_strjoin(old_buffer, temp);
	free(old_buffer);
	if (!(*buffer))
		return (0);
	return (1);
}

char	*read_until_next_line(int fd, char *buffer, int i)
{
	int		read_result;
	char	*temp;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	i = find_next_line(buffer);
	while (i <= 0)
	{
		read_result = read_and_join(fd, &buffer, temp);
		if (read_result <= 0)
		{
			if (read_result == -1)
				buffer = NULL;
			break ;
		}
		if (!buffer || *buffer == '\0')
		{
			free(temp);
			return (NULL);
		}
		i = find_next_line(buffer);
	}
	free(temp);
	return (buffer);
}

char	*substr_and_update(char **buffer)
{
	char	*line;
	char	*new_buffer;
	int		i;

	if (!(*buffer) || *buffer[0] == '\0')
	{
		if (*buffer)
			free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	i = find_next_line(*buffer);
	if (i <= 0)
		i = ft_strlen(*buffer);
	line = ft_substr(*buffer, 0, i);
	new_buffer = ft_substr(*buffer, i, ft_strlen(*buffer) - i);
	free(*buffer);
	*buffer = new_buffer;
	if (*buffer && (*buffer)[0] == '\0')
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			i;
	int			j;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	i = find_next_line(buffer);
	j = 0;
	if (i <= 0)
	{
		buffer = read_until_next_line(fd, buffer, j);
		if (buffer == NULL)
		{
			return (NULL);
		}
	}
	return (substr_and_update(&buffer));
}
