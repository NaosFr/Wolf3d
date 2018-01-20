/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncella <ncella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 13:26:24 by ncella            #+#    #+#             */
/*   Updated: 2017/12/27 18:30:13 by ncella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		ft_move_player_up_and_down(t_mlx *smlx, int i)
{
	int		tmpx;
	int		tmpy;

	tmpx = smlx->dest[(int)(smlx->player_x + (smlx->dir_x * smlx->speed) * i)]
		[(int)smlx->player_y];
	tmpy = smlx->dest[(int)(smlx->player_x)]
		[(int)(smlx->player_y + (smlx->dir_y * smlx->speed) * i)];
	if (tmpx == 0)
		smlx->player_x += (smlx->dir_x * smlx->speed) * i;
	if (tmpy == 0)
		smlx->player_y += (smlx->dir_y * smlx->speed) * i;
}

static void		ft_move_player_right_and_left(t_mlx *smlx, int i)
{
	double		tmp1;
	double		tmp2;
	double		val_cos;
	double		val_sin;

	val_cos = cos(smlx->rotate_speed * i);
	val_sin = sin(smlx->rotate_speed * i);
	tmp1 = smlx->dir_x;
	smlx->dir_x = smlx->dir_x * val_cos - smlx->dir_y * val_sin;
	smlx->dir_y = tmp1 * val_sin + smlx->dir_y * val_cos;
	tmp2 = smlx->plan_x;
	smlx->plan_x = smlx->plan_x * val_cos - smlx->plan_y * val_sin;
	smlx->plan_y = tmp2 * val_sin + smlx->plan_y * val_cos;
}

int				ft_key(int keycode, t_mlx *smlx)
{
	if (keycode == 53)
		ft_exit(smlx);
	if (keycode == UP)
		ft_move_player_up_and_down(smlx, 1);
	if (keycode == DOWN)
		ft_move_player_up_and_down(smlx, -1);
	if (keycode == RIGHT)
		ft_move_player_right_and_left(smlx, -1);
	if (keycode == LEFT)
		ft_move_player_right_and_left(smlx, 1);
	mlx_destroy_image(smlx->mlx, smlx->pointeur_image);
	smlx->pointeur_image = mlx_new_image(smlx->mlx, WIDTH, HEIGHT);
	ft_ray_casting(smlx);
	return (0);
}
