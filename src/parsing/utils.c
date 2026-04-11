/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:28:41 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/11 14:21:47 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

t_vec	get_vec(t_parsing *p, char *s)
{
	t_vec	vec;
	char	**sp;

	sp = ft_split(s, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3])
		exit_prog_pars(*p, ERROR_FILE_ARGS, ERROE_FILE_ARGS_MSG);
	vec_init(&vec, ft_atof(sp[0]), ft_atof(sp[1]), ft_atof(sp[2]));
	ft_freedb_ptr(sp);
	return (vec);
}

mlx_color	get_color(t_parsing *p, char *s)
{
	mlx_color	color;
	char		**sp;
	int			v[3];

	sp = ft_split(s, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3])
		exit_prog_pars(*p, ERROR_FILE_ARGS, ERROE_FILE_ARGS_MSG);
	v[0] = ft_atoi(sp[0]);
	v[1] = ft_atoi(sp[1]);
	v[2] = ft_atoi(sp[2]);
	ft_freedb_ptr(sp);
	if (v[0] < 0 || v[0] > 255 || v[1] < 0 || v[1] > 255
		|| v[2] < 0 || v[2] > 255)
		exit_prog_pars(*p, ERROR_FILE_ARGS, ERROE_FILE_ARGS_MSG);
	color.r = v[0];
	color.g = v[1];
	color.b = v[2];
	color.a = 255;
	return (color);
}

int	count_line(t_parsing *p, char *file_name)
{
	int		fd;
	char	*str;
	int		count;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_prog_pars(p, ERROR_FILE_NAME, ERROE_FILE_NAME_MSG);
	str = ft_get_next_line(fd);
	while (str)
	{
		if (str[0] != '\n')
			count++;
		ft_freenull((void **)&str);
		str = ft_get_next_line(fd);
	}
	close(fd);
	return (count);
}
