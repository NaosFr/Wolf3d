/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncella <ncella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 13:52:27 by ncella            #+#    #+#             */
/*   Updated: 2017/12/27 18:30:27 by ncella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		ft_init_value(t_mlx *smlx, int x)
{
	double		cam;

	cam = 2 * x / (double)WIDTH - 1;
	smlx->ray_x = smlx->dir_x + smlx->plan_x * cam;
	smlx->ray_y = smlx->dir_y + smlx->plan_y * cam;
	smlx->square_x = (int)smlx->player_x;
	smlx->square_y = (int)smlx->player_y;
	smlx->delta_dist_x = sqrt(1 + (smlx->ray_y * smlx->ray_y) /
			(smlx->ray_x * smlx->ray_x));
	smlx->delta_dist_y = sqrt(1 + (smlx->ray_x * smlx->ray_x) /
			(smlx->ray_y * smlx->ray_y));
}

static void		ft_side_coo_x(t_mlx *smlx)
{
	if (smlx->ray_x < 0)
	{
		smlx->next_x = -1;
		smlx->side_dist_x = (smlx->player_x - smlx->square_x) *
			smlx->delta_dist_x;
	}
	else
	{
		smlx->next_x = 1;
		smlx->side_dist_x = (smlx->square_x + 1.0 - smlx->player_x) *
			smlx->delta_dist_x;
	}
}

static void		ft_side_coo_y(t_mlx *smlx)
{
	if (smlx->ray_y < 0)
	{
		smlx->next_y = -1;
		smlx->side_dist_y = (smlx->player_y - smlx->square_y) *
			smlx->delta_dist_y;
	}
	else
	{
		smlx->next_y = 1;
		smlx->side_dist_y = (smlx->square_y + 1.0 - smlx->player_y) *
			smlx->delta_dist_y;
	}
}

static void		ft_calcul_distance(t_mlx *smlx)
{
	smlx->hit = 0;
	while (smlx->hit == 0)
	{
		if (smlx->side_dist_x < smlx->side_dist_y)
		{
			smlx->side_dist_x += smlx->delta_dist_x;
			smlx->square_x += smlx->next_x;
			smlx->side = 0;
		}
		else
		{
			smlx->side_dist_y += smlx->delta_dist_y;
			smlx->square_y += smlx->next_y;
			smlx->side = 1;
		}
		if (smlx->dest[(int)smlx->square_x][(int)smlx->square_y] > 0)
			smlx->hit = 1;
	}
	if (smlx->side == 0)
		smlx->len_wall = (smlx->square_x - smlx->player_x + (1 - smlx->next_x)
				/ 2) / smlx->ray_x;
	else
		smlx->len_wall = (smlx->square_y - smlx->player_y + (1 - smlx->next_y)
				/ 2) / smlx->ray_y;
}

void			ft_ray_casting(t_mlx *smlx)
{
	int		start_wall;
	int		end_wall;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ft_init_value(smlx, x);
		ft_side_coo_x(smlx);
		ft_side_coo_y(smlx);
		ft_calcul_distance(smlx);
		start_wall = -((int)(HEIGHT / smlx->len_wall)) / 2 + HEIGHT / 2;
		end_wall = ((int)(HEIGHT / smlx->len_wall)) / 2 + HEIGHT / 2;
		if (start_wall < 0)
			start_wall = 0;
		if (end_wall >= HEIGHT)
			end_wall = HEIGHT - 1;
		ft_draw(smlx, x, start_wall, end_wall);
		x++;
	}
	mlx_put_image_to_window(smlx->my_image_string, smlx->win,
			smlx->pointeur_image, 0, 0);
}
