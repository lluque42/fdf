/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:17:52 by lluque            #+#    #+#             */
/*   Updated: 2024/03/02 11:10:52 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"
#include "libft.h"

t_ft_mx	*ft_mx_dup(t_ft_mx *src)
{
	t_ft_mx	*dst;
	double	*temp;
	int		i;

	dst = ft_mx_create(src->m, src->n);
	if (dst == NULL)
		return (NULL);
	i = -1;
	while (++i < src->m)
	{
		temp = dst->d + i * dst->n;
		ft_memmove(temp, src->d + i * src->n, src->n * sizeof (double));
	}
	return (dst);
}
