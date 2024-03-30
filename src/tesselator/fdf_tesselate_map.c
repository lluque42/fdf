/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tesselate_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:05:33 by lluque            #+#    #+#             */
/*   Updated: 2024/03/27 09:56:39 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

int	fdf_tesselate_map(t_fdf_object *object)
{
	ft_printf("\t[fdf_tesselate_map] Getting vertex matrix from map...'\n");
	if (object->tesselation_type == PLANE_TESSELATION)
		object->model_mx = fdf_get_vertex_mx(object->map_mx);
	if (object->tesselation_type == SPHERICAL_TESSELATION)
		object->model_mx = fdf_get_vertex_mx_sph(object->map_mx, 100);
	if (object->tesselation_type == CYLINDRICAL_TESSELATION)
		object->model_mx = fdf_get_vertex_mx_cyl(object->map_mx, 100, 200);
	if (object->model_mx == NULL)
	{
		ft_printf("There was a problem while getting vertex_mx\n");
		return (0);
	}
	ft_printf("\t[fdf_tesselate_map] Getting edges...'\n");
	if (!fdf_get_edge(object->map_mx, object))
		return (0);
	ft_printf("\t[fdf_tesselate_map] Exiting...'\n");
	return (1);
}
