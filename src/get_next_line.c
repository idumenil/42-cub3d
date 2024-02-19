/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:03 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_eof(int ret, char **buff, char **line)
{
	if (ret == -1)
		return (-1);
	free(*buff);
	*buff = NULL;
	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 1);
		*line[0] = 0;
	}
	return (0);
}

int	ft_free_buff(char **buff, t_r *r)
{
	if (r->erreur == 2 && *buff)
	{
		free(*buff);
		return (1);
	}
	return (0);
}

int	read_and_process(int fd, char **line, char **buff)
{
	int	ret;

	ret = read(fd, *buff, BUFFER_SIZE);
	while (ret > 0)
	{
		(*buff)[ret] = '\0';
		if (!ft_copy(line, buff))
			return (1);
		ret = read(fd, *buff, BUFFER_SIZE);
	}
	return (ret);
}

int	get_next_line(int fd, char **line, t_r *r)
{
	static char	*buff = NULL;
	int			ret;

	if (ft_free_buff(&buff, r) == 1)
		return (0);
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	ret = 1;
	if (buff)
		ret = ft_copy(line, &buff);
	if (ret == 0)
		return (1);
	if (!buff)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (-1);
	}
	ret = read_and_process(fd, line, &buff);
	if (ret <= 0)
		return (ft_eof(ret, &buff, line));
	return (1);
}
