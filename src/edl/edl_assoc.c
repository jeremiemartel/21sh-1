/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl_assoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 19:31:16 by alalonzo          #+#    #+#             */
/*   Updated: 2019/11/09 06:43:36 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

void	edl_key_assoc(t_edl *edl)
{
	edl->key[K_RET] = "\012";
	edl->key[K_UP] = "\033[A";
	edl->key[K_DOWN] = "\033[B";
	edl->key[K_RIGHT] = "\033[C";
	edl->key[K_LEFT] = "\033[D";
	edl->key[K_HOME] = "\033[H";
	edl->key[K_END] = "\033[F";
	edl->key[K_DEL] = "\177";
	edl->key[K_SUP] = "\033[3~";
	edl->key[K_CN_UP] = "\033[1;5A";
	edl->key[K_CN_DOWN] = "\033[1;5B";
	edl->key[K_CN_RIGHT] = "\033[1;5C";
	edl->key[K_CN_LEFT] = "\033[1;5D";
	edl->key[K_CN_D] = "\004";
	edl->key[K_COUNT] = NULL;
}

void	edl_fun_assoc(t_edl *edl)
{
	edl->fun[K_RET] = dbg_key_ret;
	edl->fun[K_UP] = dbg_key_up;
	edl->fun[K_DOWN] = dbg_key_down;
	edl->fun[K_RIGHT] = dbg_key_right;
	edl->fun[K_LEFT] = dbg_key_left;
	edl->fun[K_HOME] = dbg_key_home;
	edl->fun[K_END] = dbg_key_end;
	edl->fun[K_DEL] = dbg_key_del;
	edl->fun[K_SUP] = dbg_key_sup;
	edl->fun[K_CN_UP] = dbg_key_cn_up;
	edl->fun[K_CN_DOWN] = dbg_key_cn_down;
	edl->fun[K_CN_RIGHT] = dbg_key_cn_right;
	edl->fun[K_CN_D] = dbg_key_cn_down;
	edl->fun[K_CN_LEFT] = dbg_key_cn_left;
}
