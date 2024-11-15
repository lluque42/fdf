/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_mult3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:12:37 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:38:26 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_ft_mx	*ft_mx_mult3(t_ft_mx *m1, t_ft_mx *m2, t_ft_mx *m3)
{
	t_ft_mx	*result_mx;
	t_ft_mx	*temp_mx;

	temp_mx = ft_mx_mult(m1, m2);
	if (temp_mx == NULL)
		return (NULL);
	result_mx = ft_mx_mult(temp_mx, m3);
	if (result_mx == NULL)
		return (NULL);
	ft_mx_destroy(temp_mx);
	return (result_mx);
}
