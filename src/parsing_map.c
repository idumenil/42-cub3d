/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:19 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_copy_map2(char *str, t_r *r)
{
	static int	i = 0;
	int			j;

	j = 0;
	r->map[i] = malloc(sizeof(char) * r->sizeline + 1);
	if (!r->map[i])
		return (0);
	while (str[j] != '\0')
	{
		if (ft_depart(str[j], r, i, j) == 1)
		{
			r->map[i][j] = '0';
			r->dep_x = j;
			r->dep_y = i;
		}
		else if (str[j] == ' ')
			r->map[i][j] = '0';
		else
			r->map[i][j] = str[j];
		j++;
	}
	r->map[i][j] = '\0';
	i++;
	return (0);
}

void	dfs(char **tab, int row, int col, t_r *r)
{
	if (row < 0 || col < 0 || row >= r->nblines
		|| col >= r->sizeline)
	{
		r->valid = 0;
		return ;
	}
	if (tab[row][col] == '1' || tab[row][col] == '2')
	{
		return ;
	}
	tab[row][col] = '2';
	dfs(tab, row - 1, col, r);
	dfs(tab, row + 1, col, r);
	dfs(tab, row, col - 1, r);
	dfs(tab, row, col + 1, r);
}

void	flood_fill(char **tab, t_r *r)
{
	r->valid = 1;
	dfs(tab, r->dep_y, r->dep_x, r);
	if (!r->valid)
		ft_error(r, "Erreur : joueur pas entièrement entouré par des murs\n");
}

int	ft_is_map(char *str, t_r *r)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (ft_charinstr(str, '1') == 1 || ft_charinstr(str, '0') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
				&& str[i] != '\t')
			{
				if (r->in == 1)
					r->wrongcharmap = 2;
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_map(char *str, t_r *r)
{
	int			i;
	static int	snblines = 0;
	static int	ssizeline = 0;

	i = 0;
	if (ft_is_map(str, r) == 1)
	{
		if (r->f == -1 || r->c == -1 || r->no == NULL
			|| r->so == NULL || r->we == NULL
			|| r->ea == NULL)
			r->erreur = 2;
		i = ft_strlen(str);
		if (i > ssizeline)
			ssizeline = i;
		snblines = snblines + 1;
	}
	r->nblines = snblines;
	r->sizeline = ssizeline;
}
