/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:32 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_stepsidedist(t_r *r)
{
	if (r->ray.raydirx < 0)
	{
		r->ray.stepx = -1;
		r->ray.sidedistx = (r->ray.posx - r->ray.mapx) \
							* r->ray.deltadistx;
	}
	else
	{
		r->ray.stepx = 1;
		r->ray.sidedistx = (r->ray.mapx + 1.0 - r->ray.posx) \
							* r->ray.deltadistx;
	}
	if (r->ray.raydiry < 0)
	{
		r->ray.stepy = -1;
		r->ray.sidedisty = (r->ray.posy - r->ray.mapy) \
							* r->ray.deltadisty;
	}
	else
	{
		r->ray.stepy = 1;
		r->ray.sidedisty = (r->ray.mapy + 1.0 - r->ray.posy) \
							* r->ray.deltadisty;
	}
	ft_incrementray(r);
}

void	ft_incrementray(t_r *r)
{
	while (r->ray.hit == 0)
	{
		if (r->ray.sidedistx < r->ray.sidedisty)
		{
			r->ray.sidedistx += r->ray.deltadistx;
			r->ray.mapx += r->ray.stepx;
			r->ray.side = 0;
		}
		else
		{
			r->ray.sidedisty += r->ray.deltadisty;
			r->ray.mapy += r->ray.stepy;
			r->ray.side = 1;
		}
		if (r->map[r->ray.mapx][r->ray.mapy] == '1')
			r->ray.hit = 1;
	}
	ft_drawstartend(r);
}

void	ft_drawstartend(t_r *r)
{
	if (r->ray.side == 0)
		r->ray.perpwalldist = ((double)r->ray.mapx - r->ray.posx
				+ (1 - (double)r->ray.stepx) / 2) / r->ray.raydirx;
	else
		r->ray.perpwalldist = ((double)r->ray.mapy - r->ray.posy
				+ (1 - (double)r->ray.stepy) / 2) / r->ray.raydiry;
	r->ray.lineheight = (int)(r->ry / r->ray.perpwalldist);
	r->ray.drawstart = -r->ray.lineheight / 2 + r->ry / 2;
	if (r->ray.drawstart < 0)
		r->ray.drawstart = 0;
	r->ray.drawend = r->ray.lineheight / 2 + r->ry / 2;
	if (r->ray.drawend >= r->ry
		|| r->ray.drawend < 0)
		r->ray.drawend = r->ry - 1;
}

void	ft_swap(t_r *r)
{
	void	*tmp;

	tmp = r->data.img;
	r->data.img = r->data.img2;
	r->data.img2 = tmp;
	tmp = r->data.addr;
	r->data.addr = r->data.addr2;
	r->data.addr2 = tmp;
}
