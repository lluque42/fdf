/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_getz_3drect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:06:41 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:00:16 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_getz_3drect_fromx(double *z, t_fdf_3drect *rect, double x)
{
	double	tx;
	double	tz;

	if (rect->parallel_to_yz && rect->parallel_to_xz)
		return (0);
	if (rect->parallel_to_yz && rect->parallel_to_yz_at_x != x)
		return (0);
	if (rect->parallel_to_xy)
	{
		*z = rect->parallel_to_xy_at_z;
		return (1);
	}
	tx = rect->x2 - rect->x1;
	tz = rect->z2 - rect->z1;
	*z = x - rect->x1;
	*z *= tz / tx;
	*z += rect->z1;
	return (1);
}

int	fdf_getz_3drect_fromy(double *z, t_fdf_3drect *rect, double y)
{
	double	ty;
	double	tz;

	if (rect->parallel_to_yz && rect->parallel_to_xz)
		return (0);
	if (rect->parallel_to_xz && rect->parallel_to_xz_at_y != y)
		return (0);
	if (rect->parallel_to_xy)
	{
		*z = rect->parallel_to_xy_at_z;
		return (1);
	}
	ty = rect->y2 - rect->y1;
	tz = rect->z2 - rect->z1;
	*z = y - rect->y1;
	*z *= tz / ty;
	*z += rect->z1;
	return (1);
}
