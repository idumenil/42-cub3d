/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:11 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_parsing_map(char *fichier, t_r *r)
{
	int	flag;

	flag = ft_read_and_parse_map(fichier, r);
	if (!flag)
		return (0);
	ft_process_parsed_map(r);
	return (1);
}

void	process_file(char *fichier, t_r *r)
{
	int		fd;
	int		ret;
	char	*str;

	str = NULL;
	ret = 1;
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
	{
		ft_error(r, "Fichier .cub invalide\n");
		return ;
	}
	r->erreur = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, r);
		if (r->erreur == 2)
			ft_error(r, "La partie parsing detecte une erreur\n");
		ft_color_resolution(&str, r);
		ft_texture(str, r);
		ft_map(str, r);
		free(str);
	}
	close(fd);
}

int	ft_read_and_parse_map(char *fichier, t_r *r)
{
	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = NULL;
	fd = open(fichier, O_RDONLY);
	r->map = malloc(sizeof(char *) * r->nblines);
	if (!r->map)
	{
		close(fd);
		return (0);
	}
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, r);
		ft_process_line(str, r);
		free(str);
	}
	close(fd);
	return (1);
}

void	ft_process_line(char *str, t_r *r)
{
	if (r->in == 1 && ft_lignevide(str) == 0 && r->count < r->nblines)
		r->lignevide = 1;
	r->in = ft_is_map(str, r);
	if (r->in == 1)
	{
		r->count++;
		ft_copy_map2(str, r);
	}
}

void	ft_process_parsed_map(t_r *r)
{
	flood_fill(r->map, r);
	ft_verify_errors(r);
	ft_redo_map(r->map, r);
	ft_mlx(r);
}
