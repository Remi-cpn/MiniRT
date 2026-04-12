/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_type_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:21:08 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/12 13:46:18 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include <math.h>

int	double_valid(char *s)
{
	int		i;
	int		dot_count;
	double	d;

	if (!s || ft_strlen(s) > 20 || ft_strlen(s) == 0 ||
		(s[0] == '-' && ft_strlen(s) == 1))
		return (0);
	i = 0;
	dot_count = 0;
	if (s[i] == '-')
		i++;
	while (ft_isdigit(s[i]) || s[i] == '.')
	{
		if (s[i] == '.')
			dot_count++;
		i++;
	}
	if (s[i] || dot_count > 1)
		return (0);
	d = ft_atod(s);
	if (isinf(d))
		return (0);
	return (1);
}

int	float_valid(char *s)
{
	int		i;
	int		dot_count;
	float	f;

	if (!s || ft_strlen(s) > 20 || ft_strlen(s) == 0 ||
		(s[0] == '-' && ft_strlen(s) == 1))
		return (0);
	i = 0;
	dot_count = 0;
	if (s[i] == '-')
		i++;
	while (ft_isdigit(s[i]) || s[i] == '.')
	{
		if (s[i] == '.')
			dot_count++;
		i++;
	}
	if (s[i] || dot_count > 1)
		return (0);
	f = ft_atof(s);
	if (isinf(f))
		return (0);
	return (1);
}

int	long_valid(char *s)
{
	int	i;

	if (!s || ft_strlen(s) > 20 || ft_strlen(s) == 0 ||
		(s[0] == '-' && ft_strlen(s) == 1))
		return (0);
	i = 0;
	if (s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (0);
	if (s[0] == '-')
	{
		if ((ft_strlen(&s[1]) == 19 && ft_strncmp(&s[1], P_LONG_MIN, 19) <= 0)
			|| ft_strlen(&s[1]) < 19)
			return (1);
	}
	else
	{
		if ((ft_strlen(s) == 19 && ft_strncmp(s, P_LONG_MAX, 19) <= 0)
			|| ft_strlen(s) < 19)
			return (1);
	}
	return (0);
}

int	int_valid(char *s)
{
	int	i;

	if (!s || ft_strlen(s) > 11 || ft_strlen(s) == 0 ||
		(s[0] == '-' && ft_strlen(s) == 1))
		return (0);
	i = 0;
	if (s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (0);
	if (s[0] == '-')
	{
		if ((ft_strlen(&s[1]) == 10 && ft_strncmp(&s[1], P_INT_MIN, 10) <= 0)
			|| ft_strlen(&s[1]) < 10)
			return (1);
	}
	else
	{
		if ((ft_strlen(s) == 10 && ft_strncmp(s, P_INT_MAX, 10) <= 0)
			|| ft_strlen(s) < 10)
			return (1);
	}
	return (0);
}
