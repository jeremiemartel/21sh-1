/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_onef.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 06:46:11 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/11 04:32:51 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_onef(char *str, char c)
{
	char	*new;

	new = ft_strjoin_one(str, c);
	if (!new)
		return (NULL);
	free(str);
	str = NULL;
	return (new);
}
