/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl_key_cn_arrow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:17:59 by alalonzo          #+#    #+#             */
/*   Updated: 2019/11/09 06:19:07 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "libft.h"

int		dbg_key_cn_up(t_env *env)
{
	/*
	** MUST BE USED FOR HISTORY
	*/
	(void) env;
	//ft_putstr("K_CN_UP FUNCTION\n");
	return (0);
}

int		dbg_key_cn_down(t_env *env)
{
	/*
	** MUST BE USED FOR HISTORY
	*/
	(void) env;
	//ft_putstr("K_CN_DOWN FUNCTION\n");
	return (0);
}

int		dbg_key_cn_right(t_env *env)
{
	int		i;

	i = env->edl.pos;
	while (i < env->edl.len && ft_isspace(env->edl.line[i]) == 0)
		i++;
	while (i < env->edl.len && ft_isspace(env->edl.line[i]) == 1)
		i++;
	env->edl.pos = i;
	return (0);
}

int		dbg_key_cn_left(t_env *env)
{
	int		i;

	i = env->edl.pos - 1;
	while (i > 0 && ft_isspace(env->edl.line[i]) == 0)
		i--;
	while (i > 0 && ft_isspace(env->edl.line[i]) == 1)
		i--;
	while (i > 0 && ft_isspace(env->edl.line[i]) == 0)
		i--;
	if (i != 0)
		i++;
	env->edl.pos = i;
	return (0);
}
