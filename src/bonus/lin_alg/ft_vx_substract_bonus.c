/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vx_substract_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:01:52 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:36:50 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_ft_mx	*ft_vx_substract(t_ft_mx *b, t_ft_mx *c)
{
	t_ft_mx	*a;

	if (b->n != 1 || c->n != 1 || b->m != c->m || b->m < 3)
		return (NULL);
	a = ft_mx_create(b->m, 1);
	if (a == NULL)
		return (NULL);
	a->d[0] = b->d[0] - c->d[0];
	a->d[1] = b->d[1] - c->d[1];
	a->d[2] = b->d[2] - c->d[2];
	return (a);
}