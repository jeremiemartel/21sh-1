/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2eputendl_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frameton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 23:09:16 by frameton          #+#    #+#             */
/*   Updated: 2019/09/14 23:43:08 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_2eputendl_fd(char *s1, char *s2, int fd)
{
	if (s1)
		write(fd, s1, ft_strlen(s1));
	if (s2)
		write(fd, s2, ft_strlen(s2));
	ft_putchar_fd('\n', fd);
}
