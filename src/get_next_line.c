/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j_sk8 <j_sk8@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:44:53 by jmiccio           #+#    #+#             */
/*   Updated: 2024/10/10 17:24:32 by j_sk8            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/include.h"

static char	*ft_copy_to_stash(char *stash, char *buf, size_t *size)
{
	char		*tmp;
	size_t		needed_size;
	size_t		curren_size;

	curren_size = *size;
	tmp = NULL;
	if (!stash)
		return (ft_strdup(buf, *size, 1));
	needed_size = ((ft_strlen(stash) + ft_strlen(buf)) + 1);
	if ((needed_size * 2) >= curren_size)
	{
		while (*size <= (needed_size * 2))
			*size *= 2;
		tmp = ft_strdup(stash, *size, 1);
		if (!tmp)
			return (free(stash), NULL);
		ft_strcat(tmp, buf);
		return (free(stash), tmp);
	}
	ft_strcat(stash, buf);
	return (stash);
}

static int	ft_have_nl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_extract_line(char *stash)
{
	size_t	i;
	size_t	copy_size;
	char	*line;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		copy_size = i + 1;
	else
		copy_size = i ;
	line = ft_substr(stash, 0, copy_size);
	return (line);
}

static char	*ft_extract_and_recreat_stash(char **stash)
{
	size_t	i;
	char	*res;
	char	*line;

	i = 0;
	if (!*stash)
		return (NULL);
	line = ft_extract_line(*stash);
	if (!line)
		return (ft_free_stash(stash, 0));
	while ((*stash)[i] != '\n' && (*stash)[i] != '\0')
		i++;
	if ((*stash)[i + 1] == '\0')
		return (ft_free_stash(stash, 0), line);
	res = ft_substr(*stash, i + 1, ft_strlen(*stash) - i - 1);
	if (!res)
	{
		ft_free_stash(stash, 0);
		return (free(line), NULL);
	}
	ft_free_stash(stash, 0);
	*stash = res;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	long		ret;
	static char	*stash = NULL;
	size_t		current_size;

	current_size = (BUFFER_SIZE * 2);
	ret = BUFFER_SIZE;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (ft_free_stash(&stash, 0));
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ft_free_stash(&stash, 0));
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((!ret && !stash) || ret == -1)
			return (free(buf), ft_free_stash(&stash, 0));
		buf[ret] = '\0';
		stash = ft_copy_to_stash(stash, buf, &current_size);
		if (!stash)
			return (free(buf), NULL);
		if (ft_have_nl(stash))
			return (free(buf), ft_extract_and_recreat_stash(&stash));
	}
	return (free(buf), ft_free_stash(&stash, 1));
}
/*
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("multiple_line_no_nl", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return 1;
	}
	int i = 0;
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s",line);
		i++;
		free(line);
	}
	close(fd);
	return 0;
}*/
