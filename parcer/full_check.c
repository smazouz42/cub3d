/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:48:42 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/06 04:34:52 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_color(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 'F' || str[i] == 'C') && (i == 0 || str[i - 1] == ' '))
			return (1);
		i++;
	}
	return (0);
}

int	is_wall(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str) - 1)
	{
		if (((str[i] == 'N' && str[i + 1] == 'O')
				|| (str[i] == 'S' && str[i + 1] == 'O')
				|| (str[i] == 'W' && str[i + 1] == 'E')
				|| (str[i] == 'E' && str[i + 1] == 'A'))
			&& (i == 0 || str[i - 1] == ' '))
			return (1);
		i++;
	}
	return (0);
}

int	is_line(char *str)
{
	int	i;
	int	zero;
	int	one;

	i = 0;
	one = 0;
	zero = 0;
	while (i < ft_strlen(str) - 1)
	{
		if (str[i] != ' ' && str[i] != '1')
			return (0);
		if (str[i] == '1')
			one++;
		else if (str[i] == '0')
			zero++;
		i++;
	}
	if (zero > 0 || one > 0)
		return (1);
	else
		return (0);
}

int	is_empty(char *str)
{
	int	ndx;

	ndx = 0;
	while (ndx < ft_strlen(str) - 1)
	{
		if (str[ndx] != ' ')
			return (0);
		ndx++;
	}
	return (1);
}
