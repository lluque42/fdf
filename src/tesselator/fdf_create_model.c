/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_model.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:44:47 by lluque            #+#    #+#             */
/*   Updated: 2024/03/06 13:57:09 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tesselator.h"

t_fdf_model	*fdf_create_model(void)
{
	t_fdf_model	*model;

	model = ft_calloc(1, sizeof (t_fdf_model));
	if (model == NULL)
		return (NULL);
	return (model);
}
