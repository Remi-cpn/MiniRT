/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_speed_sim_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:06:46 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/04 10:13:59 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	init_speed_sim(t_data *d, int ac, char **av)
{
	if (ac == 3 && int_valid(av[2]))
	{
		d->speed_sim = ft_atoi(av[2]);
		if (d->speed_sim > 120)
			d->speed_sim = 120;
		if (d->speed_sim < 1)
			d->speed_sim = 1;
	}
	else
		d->speed_sim = 0;
}
