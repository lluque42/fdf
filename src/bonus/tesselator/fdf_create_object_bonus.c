/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_object_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:07:59 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:57:17 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf_bonus.h"

static void	init_m2w_settings(t_fdf_object *object)
{
	object->m2w_rot_par[0] = 0;
	object->m2w_rot_par[1] = 0;
	object->m2w_rot_par[2] = 0;
	object->m2w_tra_par[0] = 0;
	object->m2w_tra_par[1] = 0;
	object->m2w_tra_par[2] = 0;
	object->m2w_sca_par[0] = 1;
	object->m2w_sca_par[1] = 1;
	object->m2w_sca_par[2] = 1;
}

//(256, 172, 89)
/*
object->w2c_rot_par[0] = 256;
object->w2c_rot_par[1] = 172;
object->w2c_rot_par[2] = 89;
*/
static void	init_w2c_settings(t_fdf_object *object)
{
	object->w2c_rot_par[0] = 90 - 35.264;
	object->w2c_rot_par[1] = 0;
	object->w2c_rot_par[2] = 360 - 45;
	object->w2c_tra_par[0] = 0;
	object->w2c_tra_par[1] = 0;
	object->w2c_tra_par[2] = 0;
	object->w2c_sca_par[0] = 1;
	object->w2c_sca_par[1] = 1;
	object->w2c_sca_par[2] = 1;
}

static void	init_c2s_settings(t_fdf_object *object)
{
	object->c2s_rot_par[0] = 0;
	object->c2s_rot_par[1] = 0;
	object->c2s_rot_par[2] = 0;
	object->c2s_tra_par[0] = 0;
	object->c2s_tra_par[1] = 0;
	object->c2s_tra_par[2] = 0;
	object->c2s_sca_par[0] = 1;
	object->c2s_sca_par[1] = 1;
	object->c2s_sca_par[2] = 1;
}

t_fdf_object	*fdf_create_object(t_ft_mx **map_mx)
{
	t_fdf_object	*object;

	object = ft_calloc(1, sizeof(t_fdf_object));
	if (object == NULL)
		return (NULL);
	init_m2w_settings(object);
	init_w2c_settings(object);
	init_c2s_settings(object);
	object->map_mx = map_mx;
	object->tesselation_type = PLANE_TESSELATION;
	object->force_monochromatic = 0;
	return (object);
}
