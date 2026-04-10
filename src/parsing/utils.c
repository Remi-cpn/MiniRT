/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:28:41 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 15:31:23 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

int	count_line(t_data *d, char *file_name)
{
	int		fd;
	char	*str;
	int		count;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_prog(d, ERROR_FILE_NAME, ERROE_FILE_NAME_MSG);
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