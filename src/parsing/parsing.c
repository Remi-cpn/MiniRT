/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:58:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 16:00:37 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

static int	check_file_name(char *file_name)
{
	if (!ft_strnstr(file_name, ".rt", ft_strlen(file_name)))
		return (0);
	return (1);
}

static void	pars_file(t_data *d, char *file_name)
{
	int		fd;
	char	*str;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_prog(d, ERROR_FILE_NAME, ERROE_FILE_NAME_MSG);
	str = ft_get_next_line(fd);
	while (str)
	{
		if (str[0] != '\n')
			
		ft_freenull((void **)&str);
		str = ft_get_next_line(fd);
	}
	//finir la lecture de gnl pour 0 leak;
	close(fd);
}

void	parsing(t_data *d, char *file_name)
{
	int	count;
	
	if (check_file_name(file_name))
		exit_prog(d, ERROR_FILE_NAME, ERROE_FILE_NAME_MSG);
	count = count_line(d, file_name);
	pars_file(d, file_name);
}
