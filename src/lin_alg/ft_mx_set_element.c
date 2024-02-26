/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_set_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:19:23 by lluque            #+#    #+#             */
/*   Updated: 2024/02/26 20:52:21 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

void	ft_mx_set_element(t_ft_mx *matrix, double element, int i, int j)
{
	matrix->d[i * matrix->n + j] = element;
}
