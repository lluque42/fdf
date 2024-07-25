/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_create_id_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:59:53 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:39:58 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_ft_mx	*ft_mx_create_id(int size)
{
	t_ft_mx	*r;
	int		c;

	r = ft_mx_create(size, size);
	if (r == NULL)
		return (NULL);
	c = -1;
	while (++c < size)
		r->d[c * size + c] = 1;
	return (r);
}
