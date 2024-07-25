/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vx_create_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:39:45 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:37:07 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_ft_mx	*ft_vx_create(double x, double y, double z, double w)
{
	t_ft_mx	*a;

	a = ft_mx_create(4, 1);
	if (a == NULL)
		return (NULL);
	a->d[0] = x;
	a->d[1] = y;
	a->d[2] = z;
	a->d[3] = w;
	return (a);
}
