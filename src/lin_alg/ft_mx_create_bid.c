/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_create_bid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:59:53 by lluque            #+#    #+#             */
/*   Updated: 2024/02/27 18:33:15 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_ft_mx	*ft_mx_create_bid(int size)
{
	t_ft_mx	*r;
	int		c;

	r = ft_mx_create(size, size);
	if (r == NULL)
		return (NULL);
	c = -1;
	while (++c < size)
		r->d[c * size + (size - c - 1)] = 1;
	return (r);
}
