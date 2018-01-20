/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncella <ncella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:27:12 by ncella            #+#    #+#             */
/*   Updated: 2017/12/27 18:30:08 by ncella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		ft_error(char *str)
{
	ft_putstr(str);
}

static int		read_buffer(int const fd, char **buffer)
{
	char	*buff;
	char	*tmp;
	int		ret;

	buff = malloc(sizeof(char*) * (BUFF_SIZE + 1));
	if (buff == NULL)
		return (-1);
	ret = read(fd, buff, BUFF_SIZE);
	buff[ret] = '\0';
	tmp = *buffer;
	if (tmp == 0)
		tmp = ft_strnew(0);
	*buffer = ft_strjoin(tmp, buff);
	ft_memdel((void**)&buff);
	ft_memdel((void**)&tmp);
	return (ret);
}

int				ft_read_map(char **buffer, char *argv)
{
	int		fd;
	int		ret;

	ret = 1;
	if ((fd = open(argv, O_RDONLY)) < 3 && fd != 0)
	{
		ft_error("\033[31m[ ✘ ] error open\n");
		return (0);
	}
	while (ret > 0)
		ret = read_buffer(fd, buffer);
	if (ret < 0)
	{
		ft_error("\033[31m[ ✘ ] error read\n");
		return (0);
	}
	return (1);
}
