/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_model.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:44:47 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 11:05:05 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

t_fdf_model	*fdf_create_model(void)
{
	t_fdf_model	*model;

	model = malloc(sizeof (t_fdf_model));
	if (model == NULL)
		return (NULL);
	return (model);
}
