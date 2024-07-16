/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_get_row.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:00:30 by lluque            #+#    #+#             */
/*   Updated: 2024/02/27 17:54:22 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lin_alg.h"

t_ft_mx	*ft_mx_get_row(t_ft_mx *matrix, int i)
{
	t_ft_mx	*r;

	if (i >= matrix->m)
		return (NULL);
	r = ft_mx_create(1, matrix->n);
	if (r == NULL)
		return (NULL);
	ft_memmove(r->d, matrix->d + i * matrix->n, sizeof (double) * matrix->n);
	return (r);
}
