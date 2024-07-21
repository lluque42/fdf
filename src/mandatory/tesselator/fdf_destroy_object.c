/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_destroy_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:11:42 by lluque            #+#    #+#             */
/*   Updated: 2024/07/21 15:48:28 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

void	fdf_destroy_object(t_fdf_object *object)
{
	ft_mx_destroy(object->map_mx[Z]);
	ft_mx_destroy(object->map_mx[C]);
	ft_mx_destroy(object->model_mx);
	ft_mx_destroy(object->world_mx);
	ft_mx_destroy(object->camera_mx);
	ft_mx_destroy(object->screen_mx);
	free(object->edge);
	free(object->triangle);
	free(object);
}
