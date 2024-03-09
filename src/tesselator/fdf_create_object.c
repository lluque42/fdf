/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:07:59 by lluque            #+#    #+#             */
/*   Updated: 2024/03/09 21:23:19 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tesselator.h"

t_fdf_object	*fdf_create_object(void)
{
	t_fdf_object	*object;

	object = ft_calloc(1, sizeof(t_fdf_object));
	if (object == NULL)
		return (NULL);
	return (object);
}
