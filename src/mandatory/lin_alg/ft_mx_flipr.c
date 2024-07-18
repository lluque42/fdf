/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_flipr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:45:50 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 00:56:51 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lin_alg.h"

int	ft_mx_flipr(t_ft_mx *matrix)
{
	t_ft_mx	*r;
	t_ft_mx	*bid;

	bid = ft_mx_create_bid(matrix->n);
	if (bid == NULL)
		return (0);
	r = ft_mx_mult(matrix, bid);
	ft_mx_destroy(bid);
	if (r == NULL)
		return (0);
	free(matrix->d);
	matrix->d = r->d;
	free(r);
	return (1);
}