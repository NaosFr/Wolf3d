/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncella <ncella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:41:50 by ncella            #+#    #+#             */
/*   Updated: 2017/12/27 21:06:32 by ncella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define BUFF_SIZE 9999
# define FLOOR 0x767676
# define SKY 0xcfdeee
# define UP 13
# define RIGHT 2
# define LEFT 0
# define DOWN 1

typedef struct		s_mlx
{
	void		*mlx;
	void		*win;
	int			bpp;
	int			s_l;
	int			endian;
	char		*my_image_string;
	void		*pointeur_image;
	char		*cpy_buffer;
	int			**dest;
	int			len;
	int			nb_lines;
	double		speed;
	double		rotate_speed;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
	double		ray_x;
	double		ray_y;
	double		square_x;
	double		square_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			next_x;
	int			next_y;
	int			side;
	double		len_wall;
	void		*pt_texture;
	char		*texture1;
	int			w_texture1;
	int			h_texture1;
	char		*texture2;
	int			w_texture2;
	int			h_texture2;
	char		*texture3;
	int			w_texture3;
	int			h_texture3;
	char		*texture4;
	int			w_texture4;
	int			h_texture4;
	char		*texture;
	int			w_texture;
	int			h_texture;
	size_t		r;
	size_t		g;
	size_t		b;
	int			tmp;
	int			hit;
}					t_mlx;

int					ft_key(int keycode, t_mlx *smlx);
void				ft_ray_casting(t_mlx *smlx);
void				ft_convert(t_mlx *smlx);
int					ft_read_map(char **buffer, char *argv);
int					ft_check_map(char *str, t_mlx *smlx);
int					ft_mouse_move(int x, int y, t_mlx *smlx);
void				ft_init(t_mlx *smlx);
void				ft_draw(t_mlx *smlx, int x, int start_wall, int end_wall);
int					ft_exit(t_mlx *smlx);
int					map_isdigit(char *str);
int					ft_exit(t_mlx *smlx);
int					verif_spawn(t_mlx *smlx);
#endif
