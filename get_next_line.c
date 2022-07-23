/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:18:48 by naharagu          #+#    #+#             */
/*   Updated: 2022/07/23 10:38:48 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	*tmp;
	char	*buf;
	ssize_t	count;

	if (!input)
		input = ft_strdup("");
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!input || !buf)
		return (NULL);
	count = 1;
	while (count && !ft_strchr(input, '\n'))
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1 || (!count && input[0] == '\0'))
			return (safe_free(buf, input));
		buf[count] = '\0';
		tmp = ft_strjoin(input, buf);
		if (!tmp)
			return (safe_free(buf, input));
		safe_free(NULL, input);
		input = tmp;
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

char	*parse_line(char *input)
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
	if (!new_input)
		return (NULL);
	return (new_input);
}

char	*get_next_line(int fd)
{
	static char	*input;
	char		*output;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	input = read_fd(fd, input);
	if (!input)
		return (NULL);
	output = get_one_line(input);
	if (!output)
		return (safe_free(NULL, input));
	input = parse_line(input);
	return (output);
}
