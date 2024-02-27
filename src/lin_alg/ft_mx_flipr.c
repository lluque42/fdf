/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_flipr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:45:50 by lluque            #+#    #+#             */
/*   Updated: 2024/02/27 20:49:13 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_ft_mx	*ft_mx_flipr(t_ft_mx *matrix)
{
	t_ft_mx	*r;
	t_ft_mx	*bid;

	bid = ft_mx_create_bid(matrix->n);
	if (bid == NULL)
		return (NULL);
	r = ft_mx_mult(matrix, bid);
	ft_mx_destroy(bid);
	return (r);
}
