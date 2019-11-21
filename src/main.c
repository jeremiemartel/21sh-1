/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 04:53:07 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/19 04:15:07 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/sh.h"
#include "../../libft/includes/libft.h"

/*
** GENERAL NOTE
** TODO : ajouter la gestion de l'affichage a l'ecran
** TODO : ajouter la gestion de l'historique
** TODO : ajouter la gestion des signaux
** TODO : env->statement handling
*/

/*
** KEY FUNCTION SHITLOAD
*/

int		dbg_key_cn_d(t_env *env)
{
	if (env->edl.len == 0)
		env->loop = 0;
	return (0);
}

/*
** SHLAG PRINTER
*/

void	edl_print(t_env *env)
{
	int		x;

	x = env->edl.opos;
	while (x)
	{
		ft_putstr("\033[D");
		x--;
	}
	ft_putstr(TCL);
	ft_putstr(env->edl.line);
	x = env->edl.len;
	while (x > env->edl.pos)
	{
		ft_putstr("\033[D");
		x--;
	}
	env->edl.opos = env->edl.pos;
}

/*
** CORE MANAGER SHITLOAD
*/

void	dbg_core_manager(t_env *env)
{
	int	ret;

	env->loop = 42;
	ret = 0;
	edl_print(env);
	while (env->loop)
	{
		if (env->edl.line == NULL)
			ft_putstr("\033[0;36m21sh > \033[0;37m");
		ret = edl_controller(env);
		edl_print(env);
		if (ret == 1)
		{
			ft_putchar('\n');
			g_shell->line = env->edl.line;
			ft_lexer(&g_shell->lex, g_shell->line);
			if (ft_strcmp(env->edl.line, "exit") == 0)
				env->loop = 0;
			free(env->edl.line);
			env->edl.line = NULL;
		}
	}
}

t_21sh	*init_shell(t_env env)
{
	t_21sh		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->env = env;
	shell->lex = NULL;
	shell->ast = NULL;
	return (shell);
}

/*
** MAIN AND INSTANTIATION SHITLOAD
*/

int		main(void)
{
	t_env	env;

	env.edl.line = NULL;
	edl_key_assoc(&env.edl);
	edl_fun_assoc(&env.edl);
	g_shell = init_shell(env);
	if (tcgetattr(0, &env.term) == 0)
	{
		sh_term_switch(env.term, 1);
		dbg_core_manager(&env);
		sh_term_switch(env.term, 0);
	}
	return (0);
}
