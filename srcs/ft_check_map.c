/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncella <ncella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:30:53 by ncella            #+#    #+#             */
/*   Updated: 2017/12/27 18:30:24 by ncella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		map_len(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			while (str[i] >= 48 && str[i] <= 57)
				i++;
			len++;
		}
		else
			i++;
	}
	return (len);
}

static int		map_nb_lines(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i - 1] != '\n')
			len++;
		i++;
	}
	if (str[i - 1] != '\n')
		len++;
	return (len);
}

static int		ft_nb_number(char *str, int i)
{
	int n;
	int tmp;

	n = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] != '\n' && str[i] != '\0' && str[i] != ' ')
		{
			i++;
			tmp = 1;
		}
		if (str[i] == '\n' || str[i] == '\0' || str[i] == ' ')
		{
			if (tmp == 1)
				n++;
			if (str[i] != '\0' && str[i] != '\n')
				i++;
			tmp = 0;
		}
	}
	return (n);
}

static int		verif_nb_lines(char *str, t_mlx *smlx)
{
	int leng;
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < smlx->nb_lines)
	{
		leng = ft_nb_number(str, i);
		if (leng != smlx->len)
			return (0);
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		leng = 0;
		if (str[i] != '\0')
			i++;
		j++;
	}
	return (1);
}

int				ft_check_map(char *str, t_mlx *smlx)
{
	smlx->len = map_len(str);
	if (smlx->len <= 1)
		return (0);
	smlx->nb_lines = map_nb_lines(str);
	if (verif_nb_lines(str, smlx) == 0)
		return (0);
	return (1);
}
