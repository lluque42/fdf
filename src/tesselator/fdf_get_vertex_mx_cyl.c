/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_vertex_mx_cyl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:44:48 by lluque            #+#    #+#             */
/*   Updated: 2024/03/27 10:04:05 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "lin_alg.h"
#include "tesselator.h"

// Base radius is the 0 altitude radius DO NOT confuse with the local variable
// 'r' in this function with the 'r' passed in fdf_get_sph_y() to this function.
// The later naming is confusing but... freaking 42's norm limitations...
static double	fdf_get_cyl_z(int i, t_ft_mx *map_mx, double cyl_h)
{
	int		z;
	double	step_a;

	step_a = cyl_h / (map_mx->m - 1);
	z = step_a * i;
	return (z);
}

// Base radius is the 0 altitude radius DO NOT confuse with the local variable
// 'r' in this function with the 'r' passed in fdf_get_sph_y() to this function.
// The later naming is confusing but... freaking 42's norm limitations...
static double	fdf_get_cyl_x(int j, int i, t_ft_mx *map_mx, double base_radius)
{
	int		x;
	int		r;
	double	step_b;
	double	pi;

	pi = acos(-1);
	r = base_radius + map_mx->d[i * map_mx->n + j];
	step_b = (2 * pi) / (map_mx->n - 1);
	x = r * cos (step_b * j);
	return (x);
}

// Base radius is the 0 altitude radius DO NOT confuse with the local variable
// 'r' in this function with the 'r' passed in fdf_get_sph_y() to this function.
// The later naming is confusing but... freaking 42's norm limitations...
static double	fdf_get_cyl_y(int j, int i, t_ft_mx *map_mx, double base_radius)
{
	int		y;
	int		r;
	double	step_b;
	double	pi;

	pi = acos(-1);
	r = base_radius + map_mx->d[i * map_mx->n + j];
	step_b = (2 * pi) / (map_mx->n - 1);
	y = r * sin (step_b * j);
	return (y);
}

t_ft_mx	*fdf_get_vertex_mx_cyl(t_ft_mx *map_mx, double r, double h)
{
	t_ft_mx	*v_mx;
	int		i;
	int		j;
	int		v;

	v_mx = ft_mx_create(4, map_mx->m * map_mx->n);
	if (v_mx == NULL)
		return (NULL);
	v = -1;
	i = 0;
	j = 0;
	while (++v < map_mx->m * map_mx->n)
	{
		v_mx->d[v] = fdf_get_cyl_x(j, i, map_mx, r);
		v_mx->d[map_mx->m * map_mx->n + v] = fdf_get_cyl_y(j, i, map_mx, r);
		v_mx->d[2 * map_mx->m * map_mx->n + v] = fdf_get_cyl_z(i, map_mx, h);
		v_mx->d[3 * map_mx->m * map_mx->n + v] = 1;
		if (++j == map_mx->n)
		{
			j = 0;
			if (++i == map_mx->m)
				i = 0;
		}
	}
	return (v_mx);
}
/*
	while (++v < map_mx->m * map_mx->n)
	{
		v_mx->d[v] = j;
		v_mx->d[map_mx->m * map_mx->n + v] = i;
		v_mx->d[2 * map_mx->m * map_mx->n + v] = map_mx->d[i * map_mx->n + j];
		v_mx->d[3 * map_mx->m * map_mx->n + v] = 1;
		if (++j == map_mx->n)
		{
			j = 0;
			if (++i == map_mx->m)
				i = 0;
		}
	}
*/
