/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tesselate_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:05:33 by lluque            #+#    #+#             */
/*   Updated: 2024/07/17 16:53:09 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "tesselator.h"

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
		object->model_mx = fdf_get_vertex_mx(object->map_mx);
		fdf_get_vertex_min_max(object->model_mx,
			object->map_min,
			object->map_max);
		if (!fdf_get_edge(object->map_mx, object))
			return (0);
	}
	ft_mx_destroy(object->model_mx);
	if (object->tesselation_type == PLANE_TESSELATION)
		object->model_mx = fdf_get_vertex_mx(object->map_mx);
	if (object->tesselation_type == SPHERICAL_TESSELATION)
		object->model_mx = fdf_get_vertex_mx_sph(object->map_mx,
				fdf_get_radius(object));
	if (object->tesselation_type == CYLINDRICAL_TESSELATION)
		object->model_mx = fdf_get_vertex_mx_cyl(object->map_mx,
				fdf_get_radius(object),
				fdf_get_cyl_height(object));
	if (object->model_mx == NULL)
	{
		ft_printf("There was a problem while getting vertex_mx\n");
		return (0);
	}
	return (1);
}
/*
		printf("\t[fdf_tesselate_map] map_min[0]...%f\n", object->map_min[0]);
		printf("\t[fdf_tesselate_map] map_min[1]...%f\n", object->map_min[1]);
		printf("\t[fdf_tesselate_map] map_min[2]...%f\n", object->map_min[2]);
		printf("\t[fdf_tesselate_map] map_max[0]...%f\n", object->map_max[0]);
		printf("\t[fdf_tesselate_map] map_max[1]...%f\n", object->map_max[1]);
		printf("\t[fdf_tesselate_map] map_max[2]...%f\n", object->map_max[2]);
*/
