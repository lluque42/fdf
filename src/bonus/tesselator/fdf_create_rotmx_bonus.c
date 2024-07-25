/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_rotmx_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:58:05 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:44:19 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf_bonus.h"

static t_ft_mx	*fdf_create_rotmx_x(double degree)
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

static t_ft_mx	*fdf_create_rotmx_y(double degree)
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

static t_ft_mx	*fdf_create_rotmx_z(double degree)
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

t_ft_mx	*fdf_create_rot_mx(double x, double y, double z)
{
	t_ft_mx	*rx;
	t_ft_mx	*ry;
	t_ft_mx	*rz;
	t_ft_mx	*temp;
	t_ft_mx	*rxyz;

	rx = fdf_create_rotmx_x(x);
	if (rx == NULL)
		return (NULL);
	ry = fdf_create_rotmx_y(y);
	if (ry == NULL)
		return (ft_mx_destroy(rx), NULL);
	rz = fdf_create_rotmx_z(z);
	if (rz == NULL)
		return (ft_mx_destroy(ry), ft_mx_destroy(rx), NULL);
	temp = ft_mx_mult(rx, ry);
	ft_mx_destroy(rx);
	ft_mx_destroy(ry);
	if (temp == NULL)
		return (ft_mx_destroy(rz), NULL);
	rxyz = ft_mx_mult(temp, rz);
	if (rxyz == NULL)
		return (ft_mx_destroy(temp), ft_mx_destroy (rz), NULL);
	return (ft_mx_destroy(temp), ft_mx_destroy (rz), rxyz);
}
