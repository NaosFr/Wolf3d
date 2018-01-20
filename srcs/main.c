/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncella <ncella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:35:56 by ncella            #+#    #+#             */
/*   Updated: 2017/12/27 18:29:49 by ncella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int			ft_error(char *str)
{
	ft_putstr(str);
	return (1);
}

static int			verif_border_map_2(t_mlx *smlx)
{
	int i;

	i = 0;
	while (i < smlx->len)
	{
		if (smlx->dest[0][i] == 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < smlx->len)
	{
		if (smlx->dest[smlx->nb_lines - 1][i] == 0)
			return (0);
		i++;
	}
	return (1);
}

static int			verif_border_map(t_mlx *smlx)
{
	int i;

	i = 0;
	if (verif_border_map_2(smlx) == 0)
		return (0);
	while (i < smlx->nb_lines)
	{
		if (smlx->dest[i][0] == 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < smlx->nb_lines)
	{
		if (smlx->dest[i][smlx->len - 1] == 0)
			return (0);
		i++;
	}
	return (1);
}

static int			fill_pixel(t_mlx *smlx, char *buffer)
{
	if (map_isdigit(buffer) == 0)
		return (0);
	if (ft_check_map(buffer, smlx) == 0)
		return (0);
	smlx->cpy_buffer = buffer;
	smlx->win = mlx_new_window(smlx->mlx, WIDTH, HEIGHT, "Wolf3d");
	smlx->pointeur_image = mlx_new_image(smlx->mlx, WIDTH, HEIGHT);
	smlx->my_image_string = mlx_get_data_addr(smlx->pointeur_image,
			&(smlx->bpp), &(smlx->s_l), &(smlx->endian));
	ft_init(smlx);
	ft_convert(smlx);
	if (verif_border_map(smlx) == 0)
		return (0);
	if (verif_spawn(smlx) == 0)
		return (0);
	ft_ray_casting(smlx);
	mlx_hook(smlx->win, 2, 3, ft_key, smlx);
	mlx_hook(smlx->win, 17, 0, ft_exit, smlx);
	mlx_loop(smlx->mlx);
	ft_memdel((void**)&smlx->cpy_buffer);
	ft_memdel((void**)&smlx->my_image_string);
	ft_memdel((void**)&smlx->dest);
	ft_memdel((void**)&smlx);
	return (1);
}

int					main(int argc, char **argv)
{
	t_mlx	*smlx;
	char	*buffer;

	buffer = NULL;
	if (argc != 2)
		return (ft_error("\033[31m[ ✘ ] ./wolf3d [MAP]\n"));
	if ((smlx = malloc(sizeof(t_mlx))) == NULL)
		return (ft_error("\033[31m[ ✘ ] error malloc\n"));
	if ((smlx->mlx = mlx_init()) == NULL)
		return (ft_error("\033[31m[ ✘ ] mlx couldn't init\n"));
	if (!buffer && !(buffer = ft_strnew(BUFF_SIZE + 1)))
		return (ft_error("\033[31m[ ✘ ] error buffer\n"));
	if (ft_read_map(&buffer, argv[1]) == 0)
		return (0);
	if (fill_pixel(smlx, buffer) == 0)
		return (ft_error("\033[31m[ ✘ ] error map\n"));
	return (0);
}
