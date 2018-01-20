/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_to_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncella <ncella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 03:04:25 by ncella            #+#    #+#             */
/*   Updated: 2017/12/27 18:30:19 by ncella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void			ft_free_char(char **str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static int			**ft_convert_to_int(char *buffer, t_mlx *smlx)
{
	char	**str;
	int		**dest;
	int		i;
	int		j;
	int		y;

	str = ft_split_whitespaces(buffer);
	dest = malloc(sizeof(int*) * smlx->nb_lines);
	i = 0;
	y = 0;
	while (y < smlx->nb_lines)
	{
		dest[y] = malloc(sizeof(int) * smlx->len);
		j = 0;
		while (j < smlx->len)
		{
			dest[y][j] = ft_atoi(str[i]);
			j++;
			i++;
		}
		y++;
	}
	ft_free_char(str);
	return (dest);
}

void				ft_convert(t_mlx *smlx)
{
	smlx->dest = ft_convert_to_int(smlx->cpy_buffer, smlx);
}
