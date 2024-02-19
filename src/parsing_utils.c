/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:22 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strlen2(char *str)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (str[i] != '.')
		i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

int	ft_charinstr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_depart(char c, t_r *r, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (r->depart != 'x')
			r->multijoueurs = 1;
		r->depart = c;
		r->dx = i;
		r->dy = j;
		return (1);
	}
	return (0);
}

int	ft_murs_util(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

// initialise une partie de la structure
void	ft_initialisation(t_r *r)
{
	r->no = NULL;
	r->so = NULL;
	r->we = NULL;
	r->ea = NULL;
	r->f = -1;
	r->c = -1;
	r->rx = 0;
	r->ry = 0;
	r->nblines = 0;
	r->sizeline = 0;
	r->map = NULL;
	r->dx = 0;
	r->dy = 0;
	r->multijoueurs = 0;
	r->lignevide = 0;
	r->in = 0;
	r->count = 0;
	r->sum = 0;
	r->wrongcharmap = 0;
	ft_init_more(r);
}
