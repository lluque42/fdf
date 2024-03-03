/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_create_transl_mx.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:50:54 by lluque            #+#    #+#             */
/*   Updated: 2024/03/03 15:01:41 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_ft_mx	*ft_mx_create_transl_mx(double x, double y, double z)
{
	t_ft_mx	*translation_mx;

	translation_mx = ft_mx_create(3, 4);
	if (translation_mx == NULL)
		return (NULL);
	ft_mx_set_element(translation_mx, 1, 0, 0);
	ft_mx_set_element(translation_mx, 1, 1, 1);
	ft_mx_set_element(translation_mx, 1, 2, 2);
	ft_mx_set_element(translation_mx, x, 0, 3);
	ft_mx_set_element(translation_mx, y, 1, 3);
	ft_mx_set_element(translation_mx, z, 2, 3);
	return (translation_mx);
}
