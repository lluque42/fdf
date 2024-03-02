/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rot_xyz_deg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:52:39 by lluque            #+#    #+#             */
/*   Updated: 2024/03/02 13:19:30 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

static t_ft_mx	*get_rot_mx(double x, double y, double z)
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

int	fdf_rot_xyz_deg(t_ft_mx *vertex_mx, double x, double y, double z)
{
	t_ft_mx	*rot_mx;

	rot_mx = get_rot_mx(x, y, z);
	ft_mx_transf_m3v(rot_mx, vertex_mx);
	ft_mx_destroy(rot_mx);
	return (1);
}
