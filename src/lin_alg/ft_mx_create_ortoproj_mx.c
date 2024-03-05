/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_create_ortoproj_mx.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:59:53 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 01:33:18 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_ft_mx	*ft_mx_create_ortoproj_mx(void)
{
	t_ft_mx	*r;

	r = ft_mx_create_id(4);
	if (r == NULL)
		return (NULL);
	ft_mx_set_element(r, 0, 2, 2);
	return (r);
}
