/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tesselate_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:05:33 by lluque            #+#    #+#             */
/*   Updated: 2024/03/09 21:29:12 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

t_fdf_model	*fdf_tesselate_map(t_ft_mx	*map_mx)
{
	t_fdf_model	*model;

	model = ft_calloc(1, sizeof (t_fdf_model));
	if (model == NULL)
		return (NULL);
	ft_printf("\t[fdf_tesselate_map] Getting vertex matrix from map...'\n");
	model->vertex_mx = fdf_get_vertex_mx(map_mx);
	if (model->vertex_mx == NULL)
	{
		ft_printf("There was a problem while getting vertex_mx\n");
		return (NULL);
	}
	if (!fdf_get_edge(map_mx, model))
		return (fdf_destroy_model(model), NULL);
	return (model);
}
