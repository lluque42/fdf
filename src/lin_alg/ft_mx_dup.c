/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:17:52 by lluque            #+#    #+#             */
/*   Updated: 2024/02/27 17:55:37 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"
#include "libft.h"

t_ft_mx	*ft_mx_dup(t_ft_mx *old)
{
	t_ft_mx	*new;
	double	*temp;
	int		i;

	new = ft_mx_create(old->m, old->n);
	if (new == NULL)
		return (NULL);
	i = -1;
	while (++i < old->m)
	{
		temp = new->d + i * new->n;
		ft_memmove(temp, old->d + i * old->n, old->n * sizeof (double));
	}
	return (new);
}
