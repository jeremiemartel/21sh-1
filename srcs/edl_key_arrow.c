/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl_key_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 19:14:33 by alalonzo          #+#    #+#             */
/*   Updated: 2019/11/02 17:46:04 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		dbg_key_up(t_env *env)
{
//	ft_putstr("K_UP FUNCTION\n");
	return (0);
}

int		dbg_key_down(t_env *env)
{
//	ft_putstr("K_DOWN FUNCTION\n");
	return (0);
}

int		dbg_key_right(t_env *env)
{
	if (env->edl.pos < env->edl.len)
		env->edl.pos++;
	return (0);
}

int		dbg_key_left(t_env *env)
{
	if (env->edl.pos > 0)
		env->edl.pos--;
	return (0);
}
