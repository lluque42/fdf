/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tesselate_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:05:33 by lluque            #+#    #+#             */
/*   Updated: 2024/03/13 22:58:46 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

t_fdf_object	*fdf_tesselate_map(t_ft_mx	*map_mx)
{
	t_fdf_object	*object;

	object = fdf_create_object();
	if (object == NULL)
		return (NULL);
	ft_printf("\t[fdf_tesselate_map] Getting vertex matrix from map...'\n");
	object->model_mx = fdf_get_vertex_mx(map_mx);
	if (object->model_mx == NULL)
	{
		ft_printf("There was a problem while getting vertex_mx\n");
		return (NULL);
	}
	if (!fdf_get_edge(map_mx, object))
		return (fdf_destroy_object(object), NULL);
	return (object);
}
