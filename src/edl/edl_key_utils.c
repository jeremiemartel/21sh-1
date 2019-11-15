/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl_key_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:32:47 by alalonzo          #+#    #+#             */
/*   Updated: 2019/11/09 06:19:58 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

int		dbg_key_home(t_env *env)
{
	env->edl.pos = 0;
	return (0);
}

int		dbg_key_end(t_env *env)
{
	env->edl.pos = env->edl.len;
	return (0);
}

int		dbg_key_del(t_env *env)
{
	if (env->edl.pos > 0)
	{
		ft_strcpy(env->edl.line + env->edl.pos - 1, env->edl.line + env->edl.pos);
		env->edl.pos--;
		env->edl.len--;
	}
	return (0);
}

int		dbg_key_sup(t_env *env)
{
	if (env->edl.pos < env->edl.len)
	{
		ft_strcpy(env->edl.line + env->edl.pos, env->edl.line + env->edl.pos + 1);
		env->edl.len--;
	}
	return (0);
}

int		dbg_key_ret(t_env *env)
{
	(void) env;
	return (1);
}
