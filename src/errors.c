/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:55:55 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_verify_errors(t_r *r)
{
	if (r->depart == 'x')
		ft_error(r, "Pas de joueur\n");
	if (r->indicateur2 != 6)
		ft_error(r, "Mauvaises donnees F ou C\n");
	if (r->multijoueurs == 1)
		ft_error(r, "Plus d'un joueur\n");
	if (r->lignevide == 1)
		ft_error(r, "Ligne vide dans la map\n");
	if (r->wrongcharmap == 2)
		ft_error(r, "Caractere incorrect dans la map\n");
}

void	ft_error2(t_r *r)
{
	if (r->map)
		free(r->map);
	if (r->s.order)
		free(r->s.order);
	if (r->s.dist)
		free(r->s.dist);
	if (r->sxy)
		free(r->sxy);
	if (r->s.zbuffer)
		free(r->s.zbuffer);
	ft_exit(r);
}

void	ft_error(t_r *r, char *str)
{
	int	i;

	i = -1;
	r->indicateur3 = 1;
	if (strcmp(str, "Program closed with ESC\n"))
		write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
	if (r->no)
		free(r->no);
	if (r->so)
		free(r->so);
	if (r->we)
		free(r->we);
	if (r->ea)
		free(r->ea);
	if (r->map)
	{
		while (++i < r->nblines)
			free(r->map[i]);
	}
	ft_error2(r);
}

int	ft_exit(t_r *r)
{
	if (r->data.img)
		mlx_destroy_image(r->data.mlx_ptr, r->data.img);
	if (r->texture[0].img)
		mlx_destroy_image(r->data.mlx_ptr, r->texture[0].img);
	if (r->texture[1].img)
		mlx_destroy_image(r->data.mlx_ptr, r->texture[1].img);
	if (r->texture[2].img)
		mlx_destroy_image(r->data.mlx_ptr, r->texture[2].img);
	if (r->texture[3].img)
		mlx_destroy_image(r->data.mlx_ptr, r->texture[3].img);
	if (r->texture[4].img)
		mlx_destroy_image(r->data.mlx_ptr, r->texture[4].img);
	if (r->data.mlx_win)
		mlx_destroy_window(r->data.mlx_ptr, r->data.mlx_win);
	exit(0);
}
