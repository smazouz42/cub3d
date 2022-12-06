/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:51:03 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/30 14:05:34 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double mod(double n1, double n2)
{
	while (n1 >= n2)
		n1 -= n2;
	if (n1 < 0)
		n1 += n2;
	return n1;
}

double distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int max(int a, int b){
	return (a > b ? a : b);
}