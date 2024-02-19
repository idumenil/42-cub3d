/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjavary <sjavary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:55:25 by sjavary           #+#    #+#             */
/*   Updated: 2024/02/13 09:55:32 by sjavary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../mlx/mlx.h"

# define ROTATE_LEFT	65361
# define ROTATE_RIGHT	65363
# define FORWARD_W_Z	119
# define BACK_S_S		115
# define RIGHT_D_D		100
# define LEFT_A_Q		97
# define BUFFER_SIZE	4096

typedef struct s_sprxy
{
	double			x;
	double			y;
}					t_sprxy;

typedef struct s_sprite
{
	int				nbspr;
	int				*order;
	double			*dist;
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstartx;
	int				drawstarty;
	int				drawendy;
	int				drawendx;
	int				spritewidth;
	double			*zbuffer;
}					t_sprite;

typedef struct s_texture
{
	int				texdir;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
}					t_texture;

typedef struct s_ray
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			raydirx;
	double			raydiry;
	double			camerax;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;

	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				mapx;
	int				mapy;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			movespeed;
	double			rotspeed;
	int				x;
	int				texture;
}					t_ray;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				forward;
	int				back;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
	int				minimapechelle;
	int				width;
	int				height;
	void			*img2;
	int				*addr2;
}					t_data;

typedef struct s_r
{
	int				valid;
	int				rx;
	int				ry;
	int				i;
	int				f;
	int				c;
	int				dep_x;
	int				dep_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				nblines;
	int				sizeline;
	char			**map;
	char			depart;
	int				dx;
	int				dy;
	int				indicateur;
	int				indicateur2;
	int				indicateur3;
	int				save;
	int				screenx;
	int				screeny;
	int				erreur;
	int				multijoueurs;
	int				lignevide;
	int				in;
	int				count;
	int				count2;
	int				sum;
	int				wrongcharmap;
	t_data			texture[5];
	t_data			data;
	t_ray			ray;
	t_texture		t;
	t_sprite		s;
	t_sprxy			*sxy;
}					t_r;

int					ft_check(char *str);
int					process_positive_start(char **line, char **buff, int start);
int					process_positive_start(char **line, char **buff, int start);
int					ft_cub(char *str, t_r *r);
int					ft_parsing_map(char *fichier, t_r *r);
int					ft_strlen2(char *str);
int					ft_charinstr(char *str, char c);
int					ft_murs_util(char *str);
int					ft_depart(char c, t_r *r, int i, int j);
int					ft_atoi2(const char *str, t_r *r);
int					ft_atoi3(const char *str, t_r *r);
int					ft_murs(t_r *r);
int					ft_is_map(char *str, t_r *r);
int					ft_copy_map(char *str, t_r *r);
int					ft_copy_map2(char *zone, t_r *r);
int					ft_copy(char **line, char **buff);
int					ft_raycasting(t_r *r);
int					ft_mlx(t_r *r);
int					ft_key_press(int keycode, t_r *r);
int					ft_key_release(int keycode, t_r *r);
int					ft_color_column(t_r *r);
int					ft_exit(t_r *r);
int					get_next_line(int fd, char **line, t_r *r);
int					ft_strlen(char *str);
int					ft_lignevide(char *str);
int					ft_check_save(char *str);
int					ft_nb_virgule(const char *str);
int					ft_minimap(t_r *r);
int					ft_read_and_parse_map(char *fichier, t_r *r);
void				ft_process_line(char *str, t_r *r);
void				ft_process_parsed_map(t_r *r);
void				process_file(char *fichier, t_r *r);
void				ft_redo_map(char **map, t_r *r);
void				ft_parsing(char *fichier, t_r *r);
void				flood_fill(char **tab, t_r *r);
void				ft_imprime_map(t_r *r);
void				ft_color_resolution(char **str, t_r *r);
void				ft_texture(char *str, t_r *r);
void				ft_initialisation(t_r *r);
void				ft_map(char *str, t_r *r);
void				ft_init_sprite(t_r *r);
void				ft_draw_texture(t_r *r, int x, int y);
void				ft_initialisation2(t_r *r);
void				ft_initialisation3(t_r *r);
void				ft_init_texture(t_r *r);
void				ft_init_sprite2(t_r *r, int i, int j, int v);
void				ft_stepsidedist(t_r *r);
void				ft_incrementray(t_r *r);
void				ft_drawstartend(t_r *r);
void				ft_swap(t_r *r);
void				ft_forward_back(t_r *r);
void				ft_left_right(t_r *r);
void				ft_rotate_right_left(t_r *r);
void				ft_error(t_r *r, char *str);
void				ft_verify_errors(t_r *r);
void				ft_header(t_r *r, int fd);
void				ft_save(t_r *r);
void				ft_sprite(t_r *r);
void				my_color_cube(t_data *data, int x, int y, int color);
void				my_color_perso(t_data *data, int x, int y, int color);
void				ft_hitpoints(t_r *r);
void				ft_init_more(t_r *r);
void				ft_init_dir(t_r *r);
void				ft_init_more3(t_r *r);
void				ft_rotate_left(t_r *r, double olddirx);
void				ft_atoi3_check(const char *str, t_r *r);

char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_subbuff(char *buff, int start, int len);

#endif
