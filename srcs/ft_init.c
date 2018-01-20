/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncella <ncella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 19:28:20 by ncella            #+#    #+#             */
/*   Updated: 2017/12/27 18:30:16 by ncella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		ft_exit(t_mlx *smlx)
{
	mlx_clear_window(smlx->mlx, smlx->win);
	free(smlx);
	exit(0);
	return (0);
}

int		map_isdigit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 0 && str[i] <= 32) || (str[i] >= 48 && str[i] <= 57)
				|| str[i] == 127 || str[i] == 45)
			i++;
		else
			return (0);
	}
	return (1);
}

int		verif_spawn(t_mlx *smlx)
{
	if (smlx->dest[(int)smlx->player_y][(int)smlx->player_x] != 0)
		return (0);
	if (smlx->dest[(int)smlx->player_y + 1][(int)smlx->player_x] != 0)
		return (0);
	if (smlx->dest[(int)smlx->player_y - 1][(int)smlx->player_x] != 0)
		return (0);
	if (smlx->dest[(int)smlx->player_y][(int)smlx->player_x + 1] != 0)
		return (0);
	if (smlx->dest[(int)smlx->player_y][(int)smlx->player_x - 1] != 0)
		return (0);
	if (smlx->dest[(int)smlx->player_y + 1][(int)smlx->player_x + 1] != 0)
		return (0);
	if (smlx->dest[(int)smlx->player_y + 1][(int)smlx->player_x - 1] != 0)
		return (0);
	if (smlx->dest[(int)smlx->player_y - 1][(int)smlx->player_x + 1] != 0)
		return (0);
	if (smlx->dest[(int)smlx->player_y - 1][(int)smlx->player_x - 1] != 0)
		return (0);
	if (smlx->len < 4 || smlx->nb_lines < 4)
		return (0);
	return (1);
}

void	ft_init(t_mlx *smlx)
{
	smlx->player_x = 2;
	smlx->player_y = 2;
	smlx->dir_x = -1;
	smlx->dir_y = 0;
	smlx->plan_x = 0;
	smlx->plan_y = 0.66;
	smlx->speed = 0.1;
	smlx->rotate_speed = 0.05;
	smlx->pt_texture = mlx_xpm_file_to_image(smlx->mlx, "texture/texture_1.xpm",
			&smlx->w_texture1, &smlx->h_texture1);
	smlx->texture1 = mlx_get_data_addr(smlx->pt_texture, &(smlx->bpp),
			&(smlx->s_l), &(smlx->endian));
	smlx->pt_texture = mlx_xpm_file_to_image(smlx->mlx, "texture/texture_2.xpm",
			&smlx->w_texture2, &smlx->h_texture2);
	smlx->texture2 = mlx_get_data_addr(smlx->pt_texture, &(smlx->bpp),
			&(smlx->s_l), &(smlx->endian));
	smlx->pt_texture = mlx_xpm_file_to_image(smlx->mlx, "texture/texture_3.xpm",
			&smlx->w_texture3, &smlx->h_texture3);
	smlx->texture3 = mlx_get_data_addr(smlx->pt_texture, &(smlx->bpp),
			&(smlx->s_l), &(smlx->endian));
	smlx->pt_texture = mlx_xpm_file_to_image(smlx->mlx, "texture/texture_4.xpm",
			&smlx->w_texture4, &smlx->h_texture4);
	smlx->texture4 = mlx_get_data_addr(smlx->pt_texture, &(smlx->bpp),
			&(smlx->s_l), &(smlx->endian));
}
