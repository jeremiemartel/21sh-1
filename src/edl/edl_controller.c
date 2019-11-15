/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:30:44 by alalonzo          #+#    #+#             */
/*   Updated: 2019/11/08 15:30:58 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

static char	*edl_inser(t_edl *edl, int size)
{
	char	*tmp;

	if ((tmp = ft_strnew(edl->len + size)))
	{
		ft_strcpy(tmp, edl->line);
		ft_strcpy(tmp + edl->pos, edl->buf);
		ft_strcpy(tmp + edl->pos + size, edl->line + edl->pos);
		free(edl->line);
		edl->len += size;
		edl->pos += size;
		edl->line = tmp;
	}
	return (tmp);
}

static char	*edl_line_state(t_edl *edl)
{
	if (edl->line == NULL)
	{
		if ((edl->line = ft_strnew(10)))
		{
			edl->len = 0;
			edl->pos = 0;
			edl->opos = 0; //
		}
	}
	return (edl->line);
}

int			edl_controller(t_env *env)
{
	int		ret;
	int		pos;

	if (edl_line_state(&env->edl))
	{
		if ((ret = read(0, env->edl.buf, 2048)) > 0)
		{
			env->edl.buf[ret] = 0;
			if ((pos = ft_str_in_array(env->edl.buf, env->edl.key)) >= 0)
				return (env->edl.fun[pos](env)); // A REVOIR
			if (edl_inser(&env->edl, ret))
				return (0);
		}
	}
	return (-1);
}
