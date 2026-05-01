/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:28:41 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/21 11:17:19 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"
#include <stdio.h>

double	get_mass(char *s)
{
	double	mass_kg;

	mass_kg = strtod(s, NULL);
	return (mass_kg);
}

t_vec	get_vec(t_parsing *p, char *s)
{
	t_vec	vec;
	char	**sp;

	sp = ft_split(s, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3])
	{
		printf("get_vec1\n");
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	}
	if (!double_valid(sp[0]) || !double_valid(sp[1]) || !double_valid(sp[2]))
	{
		printf("get_vec1\n");
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	}
	vec_init(&vec, ft_atod(sp[0]), ft_atod(sp[1]), ft_atod(sp[2]));
	ft_free_array(sp);
	return (vec);
}

mlx_color	get_color(t_parsing *p, char *s)
{
	mlx_color	color;
	char		**sp;
	int			v[3];

	sp = ft_split(s, ',');
	if (!sp || !sp[0] || !sp[1] || !sp[2] || sp[3])
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	if (!int_valid(sp[0]) || !int_valid(sp[1]) || !int_valid(sp[2]))
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	v[0] = ft_atoi(sp[0]);
	v[1] = ft_atoi(sp[1]);
	v[2] = ft_atoi(sp[2]);
	ft_free_array(sp);
	if (v[0] < 0 || v[0] > 255 || v[1] < 0 || v[1] > 255
		|| v[2] < 0 || v[2] > 255)
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	color.r = v[0];
	color.g = v[1];
	color.b = v[2];
	color.a = 255;
	return (color);
}

int	count_light(t_parsing *p, char *file_name)
{
	int		fd;
	char	*str;
	int		count;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_prog_pars(p, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);
	str = ft_get_next_line(fd);
	while (str)
	{
		if (str[0] == 'L')
			count++;
		str = ft_freenull(str);
		str = ft_get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	count_line(t_parsing *p, char *file_name, t_world *w)
{
	int		fd;
	char	*str;
	int		count;
	int		count_so;
	int		count_light;

	count = 0;
	count_so = 0;
	count_light = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_prog_pars(p, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);
	str = ft_get_next_line(fd);
	while (str)
	{
		if (str[0] != '\n')
			count++;
		if (str[0] == 's' && str[1] =='o')
			count_so++;
		if (str[0] == 'L')
			count_light++;
		str = ft_freenull(str);
		str = ft_get_next_line(fd);
	}
	close(fd);
	w->nb_sun = count_so;
	w->nb_light = count_light;
	return (count);
}
