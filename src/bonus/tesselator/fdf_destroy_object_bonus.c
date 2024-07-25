/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_destroy_object_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:11:42 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:43:48 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf_bonus.h"

void	fdf_destroy_object(t_fdf_object *object)
{
	ft_mx_destroy(object->map_mx[Z]);
	ft_mx_destroy(object->map_mx[C]);
	free(object->map_mx);
	ft_mx_destroy(object->model_mx);
	ft_mx_destroy(object->world_mx);
	ft_mx_destroy(object->camera_mx);
	ft_mx_destroy(object->screen_mx);
	free(object->edge);
	free(object->triangle);
	free(object);
}
