/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_vertex_mx_sph_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:44:48 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:42:10 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "fdf_bonus.h"

// Base radius is the 0 altitude radius DO NOT confuse with the local variable
// 'r' in this function with the 'r' passed in fdf_get_sph_y() to this function.
// The later naming is confusing but... freaking 42's norm limitations...
static double	fdf_get_sph_z(int j, int i, t_ft_mx *map_mx, double base_radius)
{
	double	z;
	double	r;
	double	step_a;
	double	pi;

	pi = acos(-1);
	r = base_radius + map_mx->d[i * map_mx->n + j];
	step_a = pi / (map_mx->m - 1);
	z = r * cos (step_a * i);
	return (z);
}

// Base radius is the 0 altitude radius DO NOT confuse with the local variable
// 'r' in this function with the 'r' passed in fdf_get_sph_y() to this function.
// The later naming is confusing but... freaking 42's norm limitations...
static double	fdf_get_sph_x(int j, int i, t_ft_mx *map_mx, double base_radius)
{
	double	x;
	double	r;
	double	step_a;
	double	step_b;
	double	pi;

	pi = acos(-1);
	r = base_radius + map_mx->d[i * map_mx->n + j];
	step_a = pi / (map_mx->m - 1);
	step_b = (2 * pi) / (map_mx->n - 1);
	x = r * sin(step_a * i) * cos (step_b * j);
	return (x);
}

// Base radius is the 0 altitude radius DO NOT confuse with the local variable
// 'r' in this function with the 'r' passed in fdf_get_sph_y() to this function.
// The later naming is confusing but... freaking 42's norm limitations...
static double	fdf_get_sph_y(int j, int i, t_ft_mx *map_mx, double base_radius)
{
	double	y;
	double	r;
	double	step_a;
	double	step_b;
	double	pi;

	pi = acos(-1);
	r = base_radius + map_mx->d[i * map_mx->n + j];
	step_a = pi / (map_mx->m - 1);
	step_b = (2 * pi) / (map_mx->n - 1);
	y = r * sin(step_a * i) * sin (step_b * j);
	return (y);
}

t_ft_mx	*fdf_get_vertex_mx_sph(t_ft_mx *z_mx, double r)
{
	t_ft_mx	*v_mx;
	int		i;
	int		j;
	int		v;

	v_mx = ft_mx_create(4, z_mx->m * z_mx->n);
	if (v_mx == NULL)
		return (NULL);
	v = -1;
	i = 0;
	j = 0;
	while (++v < z_mx->m * z_mx->n)
	{
		v_mx->d[v] = fdf_get_sph_x(j, i, z_mx, r);
		v_mx->d[z_mx->m * z_mx->n + v] = fdf_get_sph_y(j, i, z_mx, r);
		v_mx->d[2 * z_mx->m * z_mx->n + v] = fdf_get_sph_z(j, i, z_mx, r);
		v_mx->d[3 * z_mx->m * z_mx->n + v] = 1;
		if (++j == z_mx->n)
		{
			j = 0;
			if (++i == z_mx->m)
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
