/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:29 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_forward_back(t_r *r)
{
	if (r->data.forward == 1)
	{
		if (r->map[(int)(r->ray.posx + (r->ray.dirx
					* r->ray.movespeed * 2))][(int)r->ray.posy] == '0')
			r->ray.posx += r->ray.dirx * r->ray.movespeed;
		if (r->map[(int)r->ray.posx][(int)(r->ray.posy
			+ (r->ray.diry * r->ray.movespeed * 2))] == '0')
			r->ray.posy += r->ray.diry * r->ray.movespeed;
	}
	if (r->data.back == 1)
	{
		if (r->map[(int)(r->ray.posx - (r->ray.dirx
					* r->ray.movespeed * 2))][(int)r->ray.posy] == '0')
			r->ray.posx -= r->ray.dirx * r->ray.movespeed;
		if (r->map[(int)r->ray.posx][(int)(r->ray.posy
			- (r->ray.diry * r->ray.movespeed * 2))] == '0')
			r->ray.posy -= r->ray.diry * r->ray.movespeed;
	}
}

void	ft_left_right(t_r *r)
{
	if (r->data.right == 1)
	{
		if (r->map[(int)(r->ray.posx + r->ray.diry
				* (r->ray.movespeed * 2))][(int)r->ray.posy] == '0')
			r->ray.posx += r->ray.diry * r->ray.movespeed;
		if (r->map[(int)r->ray.posx][(int)(r->ray.posy
			- r->ray.dirx * (r->ray.movespeed * 2))] == '0')
			r->ray.posy -= r->ray.dirx * r->ray.movespeed;
	}
	if (r->data.left == 1)
	{
		if (r->map[(int)(r->ray.posx - r->ray.diry
				* (r->ray.movespeed * 2))][(int)r->ray.posy] == '0')
			r->ray.posx -= r->ray.diry * r->ray.movespeed;
		if (r->map[(int)r->ray.posx][(int)(r->ray.posy
			+ r->ray.dirx * (r->ray.movespeed * 2))] == '0')
			r->ray.posy += r->ray.dirx * r->ray.movespeed;
	}
}

void	ft_rotate_right_left(t_r *r)
{
	double	oldplanx;
	double	olddirx;

	oldplanx = r->ray.planx;
	olddirx = r->ray.dirx;
	if (r->data.rotate_right == 1)
	{
		r->ray.dirx = r->ray.dirx * cos(-r->ray.rotspeed / 2)
			- r->ray.diry * sin(-r->ray.rotspeed / 2);
		r->ray.diry = olddirx * sin(-r->ray.rotspeed / 2)
			+ r->ray.diry * cos(-r->ray.rotspeed / 2);
		r->ray.planx = r->ray.planx * cos(-r->ray.rotspeed / 2)
			- r->ray.plany * sin(-r->ray.rotspeed / 2);
		r->ray.plany = oldplanx * sin(-r->ray.rotspeed / 2)
			+ r->ray.plany * cos(-r->ray.rotspeed / 2);
	}
	ft_rotate_left(r, olddirx);
}

void	ft_rotate_left(t_r *r, double olddirx)
{
	double	oldplanex;

	if (r->data.rotate_left == 1)
	{
		olddirx = r->ray.dirx;
		oldplanex = r->ray.planx;
		r->ray.dirx = r->ray.dirx * cos(r->ray.rotspeed / 2)
			- r->ray.diry * sin(r->ray.rotspeed / 2);
		r->ray.diry = olddirx * sin(r->ray.rotspeed / 2)
			+ r->ray.diry * cos(r->ray.rotspeed / 2);
		r->ray.planx = r->ray.planx * cos(r->ray.rotspeed / 2)
			- r->ray.plany * sin(r->ray.rotspeed / 2);
		r->ray.plany = oldplanex * sin(r->ray.rotspeed / 2)
			+ r->ray.plany * cos(r->ray.rotspeed / 2);
	}
}
