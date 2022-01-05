/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salegre- <salegre-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:48:20 by salegre-          #+#    #+#             */
/*   Updated: 2021/11/15 18:22:07 by salegre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_a_line(int fd, char **fifi, char **buffer, int bytesread)
{
	char	*return_temp;
	char	*temp;

	if (bytesread <= 0)
	{
		if ((*fifi) != NULL)
			free(*fifi);
		*fifi = NULL;
		free(*buffer);
		return (NULL);
	}
	(*buffer)[bytesread] = '\0';
	return_temp = ft_strdup(*buffer);
	while (bytesread > 0 && !ft_strchr(*buffer, '\n'))
	{
		bytesread = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[bytesread] = '\0';
		temp = ft_strjoin(return_temp, *buffer);
		free(return_temp);
		return_temp = ft_strdup(temp);
		free(temp);
	}
	if (*buffer != NULL)
		free(*buffer);
	return (return_temp);
}

char	*fifi_no_new_line(char **fifi, char *buffer)
{
	char	*str_fin;

	if (buffer != NULL)
		free(buffer);
	str_fin = ft_strdup(*fifi);
	free(*fifi);
	*fifi = NULL;
	return (str_fin);
}

char	*criar_str_final(char **fifi, char *str_temp, size_t i)
{
	char	*str_fin;
	char	*temp;

	str_fin = ft_substr(str_temp, 0, i + 1);
	if (*fifi != NULL)
	{
		temp = ft_strjoin(*fifi, str_fin);
		free (str_fin);
		str_fin = ft_strdup(temp);
		free (temp);
	}
	if (ft_strlen(str_temp) != i)
	{
		temp = ft_substr(str_temp, i + 1, ft_strlen(str_temp));
		free (*fifi);
		*fifi = ft_strdup(temp);
		free(temp);
	}
	else
	{
		free (*fifi);
		*fifi = NULL;
	}
	free (str_temp);
	return (str_fin);
}

char	*fifi_has_a_line(char **fifi)
{
	size_t		i;
	char		*str_fin;
	char		*temp;

	i = 0;
	while ((*fifi)[i] != '\n' && (*fifi)[i] != '\0')
		i++;
	str_fin = ft_substr(*fifi, 0, i + 1);
	if (ft_strlen(*fifi) != i)
	{
		temp = ft_substr(*fifi, i + 1, ft_strlen(*fifi));
		free(*fifi);
		*fifi = ft_strdup(temp);
		free(temp);
	}
	return (str_fin);
}

char	*get_next_line(int fd)
{
	char		*str_temp;
	static char	*fifi;
	char		*buffer;
	int			bytesread;
	size_t		i;

	if (fd < 0)
		return (NULL);
	if (fifi != NULL && ft_strchr(fifi, '\n'))
		return (fifi_has_a_line(&fifi));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread == 0 && fifi != NULL && (fifi)[0] != '\0')
		return (fifi_no_new_line(&fifi, buffer));
	str_temp = read_a_line(fd, &fifi, &buffer, bytesread);
	if (str_temp == NULL)
		return (NULL);
	i = 0;
	while (str_temp[i] != '\n' && str_temp[i] != '\0')
		i++;
	return (criar_str_final(&fifi, str_temp, i));
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int fd;
	char *line;

	fd = open("multiple_line_no_nl", O_RDONLY);

	line = get_next_line(fd);
	printf("-->%s", line);
	free(line);

	line = get_next_line(fd);
	printf("-->%s", line);
	free(line);

	line = get_next_line(fd);
	printf("-->%s", line);
	free(line);

	line = get_next_line(fd);
	printf("-->%s", line);
	free(line);


}
*/