/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_vertex_min_max_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:47:12 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:27:10 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
#include "fdf_bonus.h"

// For some reason norminette does not allows including <float.h> which
// I need to get DBL_MAX and DBL_MIN. So I had to use long type limits
// included in the "allowed" header limits.h.
static void	fdf_init_min_max(double *min, double *max)
{
	min[0] = (double)LONG_MAX;
	min[1] = (double)LONG_MAX;
	min[2] = (double)LONG_MAX;
	max[0] = (double)LONG_MIN;
	max[1] = (double)LONG_MIN;
	max[2] = (double)LONG_MIN;
}

void	fdf_get_vertex_min_max(t_ft_mx *vertex_mx,
		double *min,
		double *max)
{
	int	v;
	int	n;

	n = vertex_mx->n;
	v = 0;
	fdf_init_min_max(min, max);
	while (v < n)
	{
		if (vertex_mx->d[v] > max[0])
			max[0] = vertex_mx->d[v];
		if (vertex_mx->d[v] < min[0])
			min[0] = vertex_mx->d[v];
		if (vertex_mx->d[n + v] > max[1])
			max[1] = vertex_mx->d[n + v];
		if (vertex_mx->d[n + v] < min[1])
			min[1] = vertex_mx->d[n + v];
		if (vertex_mx->d[2 * n + v] > max[2])
			max[2] = vertex_mx->d[2 * n + v];
		if (vertex_mx->d[2 * n + v] < min[2])
			min[2] = vertex_mx->d[2 * n + v];
		v++;
	}
}
