/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tesselate_map_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:05:33 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:41:27 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf_bonus.h"

double	fdf_get_radius(t_fdf_object *object)
{
	double	radius;
	double	mid_altitude;
	double	base_radius;

	base_radius = ((object->map_max[0] + object->map_max[1]) / 2) / RADIUS_RATE;
	mid_altitude = object->map_max[2] - object->map_min[2];
	radius = base_radius + object->map_min[2] + mid_altitude * RADIUS_RATE;
	return (radius);
}

double	fdf_get_cyl_height(t_fdf_object *object)
{
	double	radius;
	double	pi;
	double	height;

	radius = fdf_get_radius(object);
	pi = acos(-1);
	height = object->map_max[1] * 2 * pi * radius / object->map_max[0];
	return (height);
}

int	fdf_tesselate_map(t_fdf_object *object)
{
	if (object->model_mx == NULL)
	{
		object->model_mx = fdf_get_vertex_mx(object->map_mx[Z]);
		if (object->model_mx == NULL)
			return (0);
		fdf_get_vertex_min_max(object->model_mx,
			object->map_min,
			object->map_max);
		if (!fdf_get_edge(object))
			return (0);
		fdf_print_instructions();
	}
	ft_mx_destroy(object->model_mx);
	if (object->tesselation_type == PLANE_TESSELATION)
		object->model_mx = fdf_get_vertex_mx(object->map_mx[Z]);
	if (object->tesselation_type == SPHERICAL_TESSELATION)
		object->model_mx = fdf_get_vertex_mx_sph(object->map_mx[Z],
				fdf_get_radius(object));
	if (object->tesselation_type == CYLINDRICAL_TESSELATION)
		object->model_mx = fdf_get_vertex_mx_cyl(object->map_mx[Z],
				fdf_get_radius(object),
				fdf_get_cyl_height(object));
	if (object->model_mx == NULL)
		return (0);
	return (1);
}
//		ft_mx_print(object->model_mx, ' ');
