/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_destroy_model.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:16:06 by lluque            #+#    #+#             */
/*   Updated: 2024/03/09 20:48:01 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

void	fdf_destroy_model(t_fdf_model *model)
{
	ft_mx_destroy(model->vertex_mx);
	if (model->edge != NULL)
		free(model->edge);
	model->edge = NULL;
	if (model->triangle != NULL)
		free(model->triangle);
	model->triangle = NULL;
	free(model);
}
