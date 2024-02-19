/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:06 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_more(t_r *r)
{
	r->depart = 'x';
	r->indicateur2 = 0;
	r->indicateur3 = 0;
	r->data.img = NULL;
	r->texture[0].img = NULL;
	r->texture[1].img = NULL;
	r->texture[2].img = NULL;
	r->texture[3].img = NULL;
	r->texture[4].img = NULL;
	r->data.mlx_win = NULL;
	r->map = NULL;
	r->s.order = NULL;
	r->s.dist = NULL;
	r->s.zbuffer = NULL;
	r->sxy = NULL;
}

void	ft_init_dir(t_r *r)
{
	if (r->depart == 'N')
		r->ray.dirx = -1;
	if (r->depart == 'S')
		r->ray.dirx = 1;
	if (r->depart == 'E')
		r->ray.diry = 1;
	if (r->depart == 'W')
		r->ray.diry = -1;
	if (r->depart == 'N')
		r->ray.plany = 0.66;
	if (r->depart == 'S')
		r->ray.plany = -0.66;
	if (r->depart == 'E')
		r->ray.planx = 0.66;
	if (r->depart == 'W')
		r->ray.planx = -0.66;
}

void	ft_init_more3(t_r *r)
{
	if (r->ray.raydiry == 0)
		r->ray.deltadistx = 0;
	else if (r->ray.raydirx == 0)
		r->ray.deltadistx = 1;
	else
		r->ray.deltadistx = sqrt(1 + (r->ray.raydiry
					* r->ray.raydiry) / (r->ray.raydirx
					* r->ray.raydirx));
	if (r->ray.raydirx == 0)
		r->ray.deltadisty = 0;
	else if (r->ray.raydiry == 0)
		r->ray.deltadisty = 1;
	else
		r->ray.deltadisty = sqrt(1 + (r->ray.raydirx
					* r->ray.raydirx) / (r->ray.raydiry
					* r->ray.raydiry));
}

void	ft_atoi3_check(const char *str, t_r *r)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != ',')
		i++;
	if (str[i] == ',')
		j = 1;
	i++;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while ((str[i] < '0' || str[i] > '9') && str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		r->erreur = 2;
	if (ft_nb_virgule(str) != 2)
		r->erreur = 2;
}

int	ft_lignevide(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0'
			&& str[i] != '\n' && str[i] != '\r' && str[i] != '\v'
			&& str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}
