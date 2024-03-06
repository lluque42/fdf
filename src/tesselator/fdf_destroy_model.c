/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_destroy_model.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:16:06 by lluque            #+#    #+#             */
/*   Updated: 2024/03/06 12:13:14 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

void	fdf_destroy_model(t_fdf_model *model)
{
	ft_mx_destroy(model->vertex_mx);
	free(model->edge);
	model->edge = NULL;
	free(model->triangle);
	model->triangle = NULL;
	free(model);
}
