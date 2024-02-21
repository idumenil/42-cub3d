/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:24 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:57:04 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Main parsing function
void	ft_parsing(char *fichier, t_r *r)
{
	int	fd;

	fd = open(fichier, O_DIRECTORY);
	if (fd != -1)
		ft_error(r, "Invalide : is a directory\n");
	process_file(fichier, r);
	if (r->sizeline == 0 || r->nblines == 0)
		ft_error(r, "Map absente\n");
	ft_parsing_map(fichier, r);
}

int	ft_cub(char *str, t_r *r)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			ft_error(r, "Nom de la map invalide\n");
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parsing(str, r);
	else
		ft_error(r, "Nom de la map invalide\n");
	return (0);
}

void	ft_redo_map(char **map, t_r *r)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < r->nblines)
	{
		while (map[i][j])
		{
			if (map[i][j] == '2')
				map[i][j] = '0';
			j++;
		}
		j = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_r	r;

	r.dep_x = 0;
	r.dep_y = 0;
	r.save = 0;
	ft_initialisation(&r);
	if (argc == 2 || (argc == 3 && ft_check_save(argv[2]) == 1))
	{
		if (argc == 3)
			r.save = 1;
		ft_cub(argv[1], &r);
	}
	else
		write(1, "Error\nArguments invalides\n", 27);
}
