/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tesselate_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:05:33 by lluque            #+#    #+#             */
/*   Updated: 2024/03/01 23:17:10 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

t_fdf_model	*fdf_tesselate_map(t_ft_mx	*map_mx)
{
	t_fdf_model	*model;
	t_ft_mx		*transformed_map;

	ft_printf("\t[fdf_tesselate_map] Flipping map matrix...'\n");
	transformed_map = ft_mx_flipr(map_mx);
	model = ft_calloc(1, sizeof (t_fdf_model));
	if (model == NULL)
		return (ft_mx_destroy(transformed_map), NULL);
	ft_printf("\t[fdf_tesselate_map] Getting vertex matrix from map...'\n");
	model->vertex_mx = fdf_get_vertex_mx(transformed_map);
	if (model->vertex_mx == NULL)
	{
		ft_printf("There was a problem while getting vertex_mx\n");
		return (ft_mx_destroy(transformed_map), NULL);
	}
	return (ft_mx_destroy(transformed_map), model);
}
