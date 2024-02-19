/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:09 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_key_press(int keycode, t_r *r)
{
	if (keycode == FORWARD_W_Z)
		r->data.forward = 1;
	else if (keycode == BACK_S_S)
		r->data.back = 1;
	else if (keycode == LEFT_A_Q)
		r->data.left = 1;
	else if (keycode == RIGHT_D_D)
		r->data.right = 1;
	else if (keycode == ROTATE_LEFT)
		r->data.rotate_left = 1;
	else if (keycode == ROTATE_RIGHT)
		r->data.rotate_right = 1;
	else if (keycode == 65307)
		ft_error(r, "Program closed with ESC\n");
	return (1);
}

int	ft_key_release(int keycode, t_r *r)
{
	if (keycode == FORWARD_W_Z)
		r->data.forward = 0;
	else if (keycode == BACK_S_S)
		r->data.back = 0;
	else if (keycode == LEFT_A_Q)
		r->data.left = 0;
	else if (keycode == RIGHT_D_D)
		r->data.right = 0;
	else if (keycode == ROTATE_LEFT)
		r->data.rotate_left = 0;
	else if (keycode == ROTATE_RIGHT)
		r->data.rotate_right = 0;
	return (1);
}

int	ft_color_column(t_r *r)
{
	int	j;
	int	i;

	j = -1;
	r->ray.drawend = r->ry - r->ray.drawstart;
	i = r->ray.drawend;
	while (++j < r->ray.drawstart)
		r->data.addr[j * r->data.line_length / 4
			+ r->ray.x] = r->c;
	if (j <= r->ray.drawend)
		ft_draw_texture(r, r->ray.x, j);
	j = i;
	while (++j < r->ry)
		r->data.addr[j * r->data.line_length / 4
			+ r->ray.x] = r->f;
	return (0);
}

void	ft_draw_texture(t_r *r, int x, int y)
{
	y = r->ray.drawstart - 1;
	ft_init_texture(r);
	r->t.step = 1.0 * r->texture[0].height / r->ray.lineheight;
	r->t.texx = (int)(r->t.wallx * (double)r->texture
		[r->t.texdir].width);
	if (r->ray.side == 0 && r->ray.raydirx > 0)
		r->t.texx = r->texture[r->t.texdir].width
			- r->t.texx - 1;
	if (r->ray.side == 1 && r->ray.raydiry < 0)
		r->t.texx = r->texture[r->t.texdir].width
			- r->t.texx - 1;
	r->t.texpos = (r->ray.drawstart - r->ry / 2
			+ r->ray.lineheight / 2) * r->t.step;
	while (++y <= r->ray.drawend)
	{
		r->t.texy = (int)r->t.texpos
			& (r->texture[r->t.texdir].height - 1);
		r->t.texpos += r->t.step;
		if (y < r->ry && x < r->rx)
			r->data.addr[y * r->data.line_length / 4 + x]
				= r->texture[r->t.texdir].addr[r->t.texy
				* r->texture[r->t.texdir].line_length
				/ 4 + r->t.texx];
	}
}

int	ft_murs(t_r *r)
{
	int	i;

	i = 0;
	while (i < r->nblines)
	{
		if (r->map[i][0] == '2' || r->map[i][r->sizeline - 1] == '2')
			return (1);
		i++;
	}
	i = 0;
	while (i < r->sizeline)
	{
		if (r->map[0][i] == '2' || r->map[r->nblines - 1][i] == '2')
			return (1);
		i++;
	}
	return (0);
}
