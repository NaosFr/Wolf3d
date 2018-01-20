/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncella <ncella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:35:41 by ncella            #+#    #+#             */
/*   Updated: 2017/12/27 18:30:21 by ncella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		ft_draw_floor_sky(int y1, int y2, int x, t_mlx *smlx)
{
	int		*img;

	img = (int*)smlx->my_image_string;
	while (y2 < HEIGHT)
	{
		img[y2 * WIDTH + x] = FLOOR;
		y2++;
	}
	while (y1 >= 0)
	{
		img[y1 * WIDTH + x] = SKY;
		y1--;
	}
	smlx->my_image_string = (char*)img;
}

static void		ft_draw_wall(int y, int x, t_mlx *smlx, int color)
{
	int i;

	i = (y * WIDTH + x) * 4;
	if (i > 0 && i < (WIDTH * HEIGHT * 4))
	{
		smlx->my_image_string[i] = color & 0xFF;
		smlx->my_image_string[i + 1] = (color >> 8) & 0xFF;
		smlx->my_image_string[i + 2] = (color >> 16) & 0xFF;
	}
}

static void		ft_texture_orientation(t_mlx *smlx)
{
	if (smlx->side == 0 && smlx->ray_x > 0)
	{
		smlx->texture = smlx->texture1;
		smlx->w_texture = smlx->w_texture1;
		smlx->h_texture = smlx->h_texture1;
	}
	else if (smlx->side == 0 && smlx->ray_x < 0)
	{
		smlx->texture = smlx->texture2;
		smlx->w_texture = smlx->w_texture2;
		smlx->h_texture = smlx->h_texture2;
	}
	else if (smlx->side == 1 && smlx->ray_y > 0)
	{
		smlx->texture = smlx->texture3;
		smlx->w_texture = smlx->w_texture3;
		smlx->h_texture = smlx->h_texture3;
	}
	else
	{
		smlx->texture = smlx->texture4;
		smlx->w_texture = smlx->w_texture4;
		smlx->h_texture = smlx->h_texture4;
	}
}

static int		ft_value_wall(t_mlx *smlx)
{
	double	value_wall_touch;
	int		texture_x;

	ft_texture_orientation(smlx);
	if (smlx->side == 0)
		value_wall_touch = smlx->player_y + smlx->len_wall * smlx->ray_y;
	else
		value_wall_touch = smlx->player_x + smlx->len_wall * smlx->ray_x;
	value_wall_touch -= floor(value_wall_touch);
	texture_x = (int)(value_wall_touch * (double)smlx->w_texture);
	if (smlx->side == 0 && smlx->ray_x > 0)
		texture_x = smlx->w_texture - texture_x - 1;
	if (smlx->side == 1 && smlx->ray_y < 0)
		texture_x = smlx->w_texture - texture_x - 1;
	return (texture_x);
}

void			ft_draw(t_mlx *smlx, int x, int start_wall, int end_wall)
{
	int		texture_x;
	int		texture_y;
	int		d;
	int		i;

	texture_x = ft_value_wall(smlx);
	smlx->tmp = start_wall;
	while (start_wall < end_wall)
	{
		d = start_wall * 256 - HEIGHT * 128 + ((int)(HEIGHT / smlx->len_wall))
			* 128;
		texture_y = ((d * smlx->h_texture) / ((int)(HEIGHT / smlx->len_wall)))
			/ 256;
		if (texture_y >= 0)
		{
			i = (texture_y * smlx->w_texture + texture_x) * 4;
			smlx->b = smlx->texture[i];
			smlx->g = smlx->texture[i + 1];
			smlx->r = smlx->texture[i + 2];
			ft_draw_wall(start_wall, x, smlx, ((smlx->r << 16) + (smlx->g << 8)
				+ smlx->b));
		}
		start_wall++;
	}
	ft_draw_floor_sky(smlx->tmp, end_wall, x, smlx);
}
