/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:03:11 by lluque            #+#    #+#             */
/*   Updated: 2024/02/23 14:18:51 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main_utils.h"

int	filename_valid(const char *filename)
{
	int	len;
	int	ext_len;

	len = ft_strlen(filename);
	ext_len = ft_strlen(FILE_EXTENSION);
	if (len < ext_len + 1)
		return (0);
	filename += len - ft_strlen(FILE_EXTENSION);
	if (ft_strncmp(FILE_EXTENSION, filename, ext_len))
		return (0);
	return (1);
}
