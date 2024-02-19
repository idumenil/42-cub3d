/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:27 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/15 08:33:16 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_initialisation2(t_r *r)
{
	r->s.zbuffer = (double *)malloc(sizeof(double) * r->rx);
	if (!r->s.zbuffer)
		exit(0);
	r->data.forward = 0;
	r->data.back = 0;
	r->data.left = 0;
	r->data.right = 0;
	r->data.rotate_right = 0;
	r->data.rotate_left = 0;
	r->ray.posx = (double)r->dx + 0.5;
	r->ray.posy = (double)r->dy + 0.5;
	r->ray.dirx = 0;
	r->ray.diry = 0;
	r->ray.planx = 0;
	r->ray.plany = 0;
	ft_init_dir(r);
}

void	ft_initialisation3(t_r *r)
{
	r->ray.hit = 0;
	r->ray.perpwalldist = 0;
	r->ray.camerax = 2 * r->ray.x / (double)r->rx - 1;
	r->ray.raydirx = r->ray.dirx + r->ray.planx * \
						r->ray.camerax;
	r->ray.raydiry = r->ray.diry + r->ray.plany * \
						r->ray.camerax;
	r->ray.mapx = (int)r->ray.posx;
	r->ray.mapy = (int)r->ray.posy;
	r->ray.movespeed = 0.033 * 1.8;
	r->ray.rotspeed = 0.033 * 3.6;
	ft_init_more3(r);
}

void	ft_init_texture(t_r *r)
{
	if (r->ray.side == 0 && r->ray.raydirx < 0)
		r->t.texdir = 0;
	if (r->ray.side == 0 && r->ray.raydirx >= 0)
		r->t.texdir = 1;
	if (r->ray.side == 1 && r->ray.raydiry < 0)
		r->t.texdir = 2;
	if (r->ray.side == 1 && r->ray.raydiry >= 0)
		r->t.texdir = 3;
	if (r->ray.side == 0)
		r->t.wallx = r->ray.posy + r->ray.perpwalldist \
						* r->ray.raydiry;
	else
		r->t.wallx = r->ray.posx + r->ray.perpwalldist \
						* r->ray.raydirx;
	r->t.wallx -= floor((r->t.wallx));
}
