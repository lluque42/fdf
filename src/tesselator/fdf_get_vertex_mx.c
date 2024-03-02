/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_vertex_mx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:44:48 by lluque            #+#    #+#             */
/*   Updated: 2024/03/01 22:45:02 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lin_alg.h"
#include "tesselator.h"

t_ft_mx	*fdf_get_vertex_mx(t_ft_mx *map_mx)
{
	t_ft_mx	*vertex_mx;
	int		i;
	int		j;
	int		v;

	ft_printf("\t\t[fdf_get_vertex_mx] Creating vertex matrix...'\n");
	vertex_mx = ft_mx_create(3, map_mx->m * map_mx->n);
	if (vertex_mx == NULL)
		return (NULL);
	v = 0;
	i = -1;
	while (++i < map_mx->m)
	{
		j = -1;
		while (++j < map_mx->n)
		{
			vertex_mx->d[v] = j;
			vertex_mx->d[v + 1] = i;
			vertex_mx->d[v + 2] = map_mx->d[i * map_mx->n + j];
			v += 3;
		}
	}
	return (vertex_mx);
}
