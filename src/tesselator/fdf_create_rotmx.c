/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_rotmx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:58:05 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 01:32:02 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "tesselator.h"

t_ft_mx	*fdf_create_rotmx_x(double degree)
{
	t_ft_mx	*rotmx;
	double	pi;
	double	rad;

	pi = acos(-1);
	rad = degree * pi / 180;
	rotmx = ft_mx_create(4, 4);
	if (rotmx == NULL)
		return (NULL);
	ft_mx_set_element(rotmx, 1, 0, 0);
	ft_mx_set_element(rotmx, cos(rad), 1, 1);
	ft_mx_set_element(rotmx, -1 * sin(rad), 1, 2);
	ft_mx_set_element(rotmx, sin(rad), 2, 1);
	ft_mx_set_element(rotmx, cos(rad), 2, 2);
	ft_mx_set_element(rotmx, 1, 3, 3);
	return (rotmx);
}

t_ft_mx	*fdf_create_rotmx_y(double degree)
{
	t_ft_mx	*rotmx;
	double	pi;
	double	rad;

	pi = acos(-1);
	rad = degree * pi / 180;
	rotmx = ft_mx_create(4, 4);
	if (rotmx == NULL)
		return (NULL);
	ft_mx_set_element(rotmx, cos(rad), 0, 0);
	ft_mx_set_element(rotmx, sin(rad), 0, 2);
	ft_mx_set_element(rotmx, 1, 1, 1);
	ft_mx_set_element(rotmx, -1 * sin(rad), 2, 0);
	ft_mx_set_element(rotmx, cos(rad), 2, 2);
	ft_mx_set_element(rotmx, 1, 3, 3);
	return (rotmx);
}

t_ft_mx	*fdf_create_rotmx_z(double degree)
{
	t_ft_mx	*rotmx;
	double	pi;
	double	rad;

	pi = acos(-1);
	rad = degree * pi / 180;
	rotmx = ft_mx_create(4, 4);
	if (rotmx == NULL)
		return (NULL);
	ft_mx_set_element(rotmx, cos(rad), 0, 0);
	ft_mx_set_element(rotmx, -1 * sin(rad), 0, 1);
	ft_mx_set_element(rotmx, sin(rad), 1, 0);
	ft_mx_set_element(rotmx, cos(rad), 1, 1);
	ft_mx_set_element(rotmx, 1, 2, 2);
	ft_mx_set_element(rotmx, 1, 3, 3);
	return (rotmx);
}
