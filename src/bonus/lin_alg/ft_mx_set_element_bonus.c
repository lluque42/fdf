/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_set_element_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:19:23 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:37:46 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_mx_set_element(t_ft_mx *matrix, double element, int i, int j)
{
	matrix->d[i * matrix->n + j] = element;
}
