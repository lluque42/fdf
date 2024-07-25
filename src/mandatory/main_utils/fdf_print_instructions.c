/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_print_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 03:29:33 by lluque            #+#    #+#             */
/*   Updated: 2024/07/23 23:11:16 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fdf_print_instructions(void)
{
	ft_printf("\nlluque's fdf instructions:\n");
	ft_printf("\t* Press the ESCAPE key or clic the window's X button to ");
	ft_printf("exit.\n");
	ft_printf("\t* Press the I, K, J, L, U, or O keys to rotate along each ");
	ft_printf("axis.\n");
	ft_printf("\t* Press the T key to cycle through ");
	ft_printf("planar/spherical/cylindrical projections.\n");
	ft_printf("\t* Press the D key to show/hide valid diagonal edges.\n");
	ft_printf("\t* Press the H key to show/hide all hidden edges.\n");
	ft_printf("\t* Press the C key to toggle rendering with color (if ");
	ft_printf("available) or forcing monochromatic rendering.\n");
	ft_printf("\t* Press the TAB key to turn on/off the ");
	ft_printf("autofit and center feature.\n");
	ft_printf("\t\t* With autofit disabled:\n");
	ft_printf("\t\t\t* Press W or S keys to change the scale/zoom.\n");
	ft_printf("\t\t\t* Use the arrow keys to translate (displace) the ");
	ft_printf("model:\n");
	ft_printf("\t\t\t\t* UP/DOWN to move the camera perspective along Z ");
	ft_printf("axis.\n");
	ft_printf("\t\t\t\t* LEFT/RIGHT to move the camera in each direction.\n");
	ft_printf("\t\t\t\t* LEFT/RIGHT simultanously with UP/DOWN to move the");
	ft_printf("camera perspective along X and Y axis.\n");
}
