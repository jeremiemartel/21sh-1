/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_in_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:56:51 by alalonzo          #+#    #+#             */
/*   Updated: 2019/10/23 20:58:18 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_in_array(char *str, char **row)
{
	int		i;

	i = 0;
	while (row[i])
	{
		if (ft_strcmp(str, row[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}
