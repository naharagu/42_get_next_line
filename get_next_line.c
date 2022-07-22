/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:06:01 by naharagu          #+#    #+#             */
/*   Updated: 2022/07/22 19:09:36 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*all_free(char *buff, char *input)
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
	char	*tmp;
	char	*buf;
	ssize_t	count;

	buf = malloc(((ssize_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	count = 1;
	while (!ft_strchr(input, '\n') && count != 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1 || (!count && input[0] == '\0'))
			return (all_free(buf, input));
		buf[count] = '\0';
		tmp = ft_strjoin(input, buf);
		if (!tmp)
			return (all_free(buf, input));
		all_free(NULL, input);
		input = tmp;
	}
	all_free(buf, NULL);
	return (input);
}

char	*get_line(char *input)
{
	char	*output;
	ssize_t	i;

	output = malloc((ft_strlen(input) + 2) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (input[i])
	{
		output[i] = input[i];
		if (output[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*rest_str(char *input)
{
	char	*rest;
	ssize_t	i;

	i = 0;
	while (input[i] && input[i] != '\n')
		i++;
	if (!input[i])
		return (all_free(NULL, input));
	i++;
	rest = ft_strdup(&input[i]);
	all_free(NULL, input);
	if (!rest)
		return (NULL);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*input;
	char		*output;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!input)
	{
		input = ft_strdup("");
		if (!input)
			return (NULL);
	}
	input = read_fd(fd, input);
	if (!input)
		return (NULL);
	output = get_line(input);
	if (!output)
		return (all_free(NULL, input));
	input = rest_str(input);
	return (output);
}
