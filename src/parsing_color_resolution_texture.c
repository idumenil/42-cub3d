/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_resolution_texture.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:14 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_atoi2(const char *str, t_r *r)
{
	int		sum;

	sum = 0;
	if (str[1] != ' ' || ft_charinstr((char *)str, ',') == 1)
		r->erreur = 2;
	while (str[r->i] == ' ' || str[r->i] == '\t'
		|| str[r->i] == ',' || str[r->i] == '\n'
		|| str[r->i] == '\r' || str[r->i] == '\v'
		|| str[r->i] == '\f')
		r->i++;
	if (str[r->i] == '-' || str[r->i] == '+')
		r->erreur = 2;
	while (str[r->i] >= '0' && str[r->i] <= '9')
	{
		if (sum > 21474636)
			break ;
		sum = (sum * 10) + (str[r->i] - 48);
		r->i++;
	}
	while (str[r->i] >= '0' && str[r->i] <= '9')
		r->i++;
	return (sum);
}

int	ft_atoi3(const char *str, t_r *r)
{
	int		verify;

	verify = 0;
	if (str[1] != ' ')
		r->erreur = 2;
	ft_atoi3_check(str, r);
	while (str[r->i] == ' ' || str[r->i] == '\t' || str[r->i]
		== ',' || str[r->i] == '\n' || str[r->i] == '\r'
		|| str[r->i] == '\v' || str[r->i] == '\f')
	{
		r->i++;
		verify = 0;
		if (str[r->i] >= '0' && str[r->i] <= '9')
			r->indicateur2++;
		while (str[r->i] >= '0' && str[r->i] <= '9')
		{
			verify = (verify * 10) + str[r->i] - 48;
			r->sum = (r->sum * 10) + (str[r->i] - 48);
			r->i++;
		}
		if (verify > 255 || verify < 0)
			r->erreur = 2;
	}
	return (r->sum);
}

// Obtient le path et le stock dans la struct r (r->no, r->so, ...)
int	ft_path_texture(char *str, char **texture, t_r *r, int j)
{
	if (*texture != NULL)
	{
		r->erreur = 2;
		return (0);
	}
	if (ft_charinstr(str, '.') == 0 || ft_charinstr(str, '/') == 0
		|| ft_strlen2(str) <= 2)
		r->erreur = 2;
	while (str[j] != '.')
	{
		if (str[j] != ' ' && str[j] != '.')
			r->erreur = 2;
		j++;
	}
	*texture = (char *)(malloc(sizeof(char) * (ft_strlen2(str) + 1)));
	if (!*texture)
		r->erreur = 2;
	while (str[j] != '\0')
	{
		(*texture)[r->count2] = str[j];
		r->count2++;
		j++;
	}
	(*texture)[r->count2] = '\0';
	return (0);
}

void	ft_texture(char *str, t_r *r)
{
	int			i;
	static int	j = 0;

	i = 0;
	r->count2 = 0;
	if (str[i] == 'S' && str[i + 1] == 'O')
		ft_path_texture(str, &r->so, r, 2);
	else if (str[i] == 'N' && str[i + 1] == 'O')
		ft_path_texture(str, &r->no, r, 2);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		ft_path_texture(str, &r->ea, r, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		ft_path_texture(str, &r->we, r, 2);
	else if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E'
		&& str[0] != 'F' && str[0] != 'C' && str[0] > 65 && str[0] < 122)
		r->erreur = 2;
	j++;
}

void	ft_color_resolution(char **str, t_r *r)
{
	int			i;

	i = 0;
	r->i = 1;
	if (r->sizeline > 0 && (r->no == NULL || r->so == NULL
			|| r->we == NULL || r->ea == NULL))
		r->erreur = 2;
	if ((r->no != NULL || r->so != NULL || r->we != NULL
			|| r->ea != NULL) && (r->rx == 0
			|| r->ry == 0))
		r->erreur = 2;
	else if (*str[i] == 'F')
		r->f = ft_atoi3(*str, r);
	else if (*str[i] == 'C')
		r->c = ft_atoi3(*str, r);
	r->rx = 1080;
	r->ry = 1080;
}
