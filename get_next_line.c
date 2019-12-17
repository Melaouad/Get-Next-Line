/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaouad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 22:13:03 by melaouad          #+#    #+#             */
/*   Updated: 2019/12/17 22:15:20 by melaouad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		l3mara(char **line, char **str)
{
	char			*temp;
	int				i;

	i = 0;
	temp = NULL;
	while ((*str)[i] != '\n' && (*str)[i])
		i++;
	if (i != 0 || (*str)[i] == '\n')
	{
		*line = ft_substr(*str, 0, i);
		if ((*str)[i] != '\0')
		{
			temp = ft_strdup(*str + i + 1);
			free(*str);
		}
		else if ((*str)[i] == '\0')
		{
			temp = ft_strdup(*str + i);
			free(*str);
		}
		*str = temp;
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int				ret;
	char			*buff;
	static char		*str[4864];
	char			*ptr;

	if (fd < 0 || line == NULL || fd > 4864 || BUFFER_SIZE < 0)
		return (-1);
	if (!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!str[fd])
		if (!(str[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		ptr = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = ptr;
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	free(buff);
	return (l3mara(line, &str[fd]));
}
