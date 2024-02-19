/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_net_line_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:55:59 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	process_positive_start(char **line, char **buff, int start)
{
	char	*temp;
	char	*line_temp;

	temp = ft_substr(*buff, 0, start);
	line_temp = *line;
	*line = ft_strjoin(*line, temp);
	free(temp);
	free(line_temp);
	*buff = ft_subbuff(*buff, start + 1, (ft_strlen(*buff) - start));
	return (0);
}

int	process_negative_start(char **line, char **buff)
{
	char	*temp;

	temp = NULL;
	if (*line)
		temp = *line;
	*line = ft_strjoin(*line, *buff);
	if (temp)
		free(temp);
	return (1);
}

int	ft_copy(char **line, char **buff)
{
	int	start;

	start = ft_check(*buff);
	if (start >= 0)
		return (process_positive_start(line, buff, start));
	else
		return (process_negative_start(line, buff));
}
