/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_print_edges.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:08:03 by lluque            #+#    #+#             */
/*   Updated: 2024/03/13 15:00:45 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tesselator.h"

void	fdf_print_edges(t_ft_mx *map_mx, t_fdf_object *object, t_ft_mx *v_mx)
{
	int	e;

	e = -1;
	if (map_mx != NULL)
	{
		ft_printf("The map_mx...\n");
		ft_mx_print(map_mx, ' ');
	}
	ft_printf("\nThe vertex_mx...\n");
	ft_mx_print(v_mx, ' ');
	while (++e < object->edges)
	{
		ft_printf("\n\tEdge %3d from vertex %3d to ", e, object->edge[e].start);
		ft_printf("(%d, %d, %d) vertex %3d ",
			(int)ft_mx_get_element(v_mx, 0, object->edge[e].start),
			(int)ft_mx_get_element(v_mx, 1, object->edge[e].start),
			(int)ft_mx_get_element(v_mx, 2, object->edge[e].start),
			object->edge[e].end); 
		ft_printf("(%d, %d, %d) (is_hidden = %d)\n",
			(int)ft_mx_get_element(v_mx, 0, object->edge[e].end),
			(int)ft_mx_get_element(v_mx, 1, object->edge[e].end),
			(int)ft_mx_get_element(v_mx, 2, object->edge[e].end),
			object->edge[e].is_hidden);
	}
}
