/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:34 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_texture_adress(t_r *r)
{
	r->texture[0].addr = (int *)mlx_get_data_addr(r->texture[0].img,
			&r->texture[0].bits_per_pixel,
			&r->texture[0].line_length, &r->texture[0].endian);
	r->texture[1].addr = (int *)mlx_get_data_addr(r->texture[1].img,
			&r->texture[1].bits_per_pixel,
			&r->texture[1].line_length, &r->texture[1].endian);
	r->texture[2].addr = (int *)mlx_get_data_addr(r->texture[2].img,
			&r->texture[2].bits_per_pixel,
			&r->texture[2].line_length, &r->texture[2].endian);
	r->texture[3].addr = (int *)mlx_get_data_addr(r->texture[3].img,
			&r->texture[3].bits_per_pixel,
			&r->texture[3].line_length, &r->texture[3].endian);
}

void	ft_get_texture(t_r *r)
{
	r->texture[0].img = mlx_xpm_file_to_image(r->data.mlx_ptr,
			r->no, &(r->texture[0].width),
			&(r->texture[0].height));
	if (!r->texture[0].img)
		ft_error(r, "Texture SO\n");
	r->texture[1].img = mlx_xpm_file_to_image(r->data.mlx_ptr,
			r->so, &(r->texture[1].width),
			&(r->texture[1].height));
	if (!r->texture[1].img)
		ft_error(r, "Texture NO\n");
	r->texture[2].img = mlx_xpm_file_to_image(r->data.mlx_ptr,
			r->we, &(r->texture[2].width),
			&(r->texture[2].height));
	if (!r->texture[2].img)
		ft_error(r, "Texture EA\n");
	r->texture[3].img = mlx_xpm_file_to_image(r->data.mlx_ptr,
			r->ea, &(r->texture[3].width),
			&(r->texture[3].height));
	if (!r->texture[3].img)
		ft_error(r, "Texture WE\n");
	ft_get_texture_adress(r);
}

int	ft_raycasting(t_r *r)
{
	r->ray.x = 0;
	while (r->ray.x < r->rx)
	{
		ft_initialisation3(r);
		ft_stepsidedist(r);
		ft_color_column(r);
		r->s.zbuffer[r->ray.x] = r->ray.perpwalldist;
		r->ray.x++;
	}
	if (r->save == 1)
		ft_save(r);
	mlx_put_image_to_window(r->data.mlx_ptr, r->data.mlx_win,
		r->data.img, 0, 0);
	ft_forward_back(r);
	ft_left_right(r);
	ft_rotate_right_left(r);
	ft_swap(r);
	return (0);
}

void	setup_mlx_components(t_r *r)
{
	if (r->rx > r->screenx)
		r->rx = r->screenx;
	if (r->ry > r->screeny)
		r->ry = r->screeny;
	mlx_hook(r->data.mlx_win, 33, 1L << 17, ft_exit, r);
	mlx_hook(r->data.mlx_win, 2, 1L << 0, ft_key_press, r);
	mlx_hook(r->data.mlx_win, 3, 1L << 1, ft_key_release, r);
}

int	ft_mlx(t_r *r)
{
	ft_initialisation2(r);
	r->data.mlx_ptr = mlx_init();
	if (!r->data.mlx_ptr)
		ft_error(r, "Mlx init impossible\n");
	mlx_get_screen_size(r->data.mlx_ptr, &r->screenx, &r->screeny);
	ft_get_texture(r);
	r->data.img = mlx_new_image(r->data.mlx_ptr, r->rx, r->ry);
	r->data.addr = (int *)mlx_get_data_addr(r->data.img,
			&r->data.bits_per_pixel,
			&r->data.line_length, &r->data.endian);
	if (r->save == 1)
		ft_raycasting(r);
	r->data.mlx_win = mlx_new_window(r->data.mlx_ptr,
			r->rx, r->ry, "cub3D");
	r->data.img2 = mlx_new_image(r->data.mlx_ptr, r->rx, r->ry);
	r->data.addr2 = (int *)mlx_get_data_addr(r->data.img2,
			&r->data.bits_per_pixel,
			&r->data.line_length, &r->data.endian);
	setup_mlx_components(r);
	mlx_loop_hook(r->data.mlx_ptr, ft_raycasting, r);
	mlx_loop(r->data.mlx_ptr);
	return (0);
}
