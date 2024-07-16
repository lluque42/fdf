/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_scale_mx.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:58:04 by lluque            #+#    #+#             */
/*   Updated: 2024/03/06 00:00:49 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_ft_mx	*fdf_create_scale_mx(double x, double y, double z)
{
	t_ft_mx	*scale_mx;

	scale_mx = ft_mx_create(4, 4);
	if (scale_mx == NULL)
		return (NULL);
	ft_mx_set_element(scale_mx, x, 0, 0);
	ft_mx_set_element(scale_mx, y, 1, 1);
	ft_mx_set_element(scale_mx, z, 2, 2);
	ft_mx_set_element(scale_mx, 1, 3, 3);
	return (scale_mx);
}
