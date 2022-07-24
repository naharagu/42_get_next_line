/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:18:48 by naharagu          #+#    #+#             */
/*   Updated: 2022/07/24 09:20:04 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*safe_free(char *buff, char *input)
{
	if (buff)
	{
		free(buff);
		buff = NULL;
	}
	if (input)
	{
		free(input);
		input = NULL;
	}
	return (NULL);
}

char	*read_fd(int fd, char *input)
{
	char	*buf;
	char	*tmp;
	ssize_t	count;

	if (!input)
		input = ft_strdup("");
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!input || !buf)
		return (safe_free(buf, input));
	count = 1;
	while (count && !ft_strchr(input, '\n'))
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1 || (!count && input[0] == '\0'))
			return (safe_free(buf, input));
		buf[count] = '\0';
		tmp = input;
		input = ft_strjoin(tmp, buf);
		safe_free(NULL, tmp);
	}
	safe_free(buf, NULL);
	return (input);
}

char	*get_one_line(char *input)
{
	char	*output;
	size_t	i;

	output = malloc((ft_strlen(input) + 1) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (input[i])
	{
		output[i] = input[i];
		if (output[i++] == '\n')
			break ;
	}
	output[i] = '\0';
	return (output);
}

char	*split_input(char *input)
{
	char	*new_input;
	size_t	i;

	i = 0;
	while (input[i] && input[i] != '\n')
		i++;
	if (!input[i])
		return (safe_free(NULL, input));
	new_input = ft_strdup(&input[++i]);
	safe_free(NULL, input);
	return (new_input);
}

char	*get_next_line(int fd)
{
	static char	*input[OPEN_MAX];
	char		*output;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	input[fd] = read_fd(fd, input[fd]);
	if (!input[fd])
		return (NULL);
	output = get_one_line(input[fd]);
	if (!output)
		return (safe_free(NULL, input[fd]));
	input[fd] = split_input(input[fd]);
	return (output);
}
