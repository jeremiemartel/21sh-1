/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cursor_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:34:47 by alalonzo          #+#    #+#             */
/*   Updated: 2019/11/01 19:14:20 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoa_buf(char *buf, int nb)
{
	int		i;

	i = 0;
	if (nb <= 0)
		buf[i] = 0 + 48;
	while (nb > 0)
	{
		buf[i] = (nb % 10) + 48;
		nb = nb / 10;
		i++;
	}
	ft_strrev(buf);
}

void	sh_cursor_move(int x, int y)
{
	int		len[2];
	char	buf_x[1024];
	char	buf_y[1024];
	char	cur[1024];

	ft_memset(buf_x, 0, 1024);
	ft_memset(buf_y, 0, 1024);
	ft_itoa_buf(buf_x, x);
	ft_itoa_buf(buf_y, y);
	len[0] = ft_strlen(buf_x);
	len[1] = ft_strlen(buf_y);
	ft_strcpy(cur, "\033[");
	ft_strcpy(cur + 2, buf_y);
	ft_strcpy(cur + 2 + len[1], ";");
	ft_strcpy(cur + 2 + len[1] + 1, buf_x);
	ft_strcpy(cur + 2 + len[1] + 1 + len[0], "H");
	ft_putstr(cur);
}
