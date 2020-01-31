/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:38:57 by mabayle           #+#    #+#             */
/*   Updated: 2020/01/21 02:51:40 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"
hello
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

t_21sh	*init_shell(t_env *env, int debug)
{
	t_21sh		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->env = env;
	shell->lex = NULL;
	shell->lex_size = 0;
	shell->ast = NULL;
	shell->debug = debug;
	return (shell);
}

/*
** MAIN AND INSTANTIATION SHITLOAD
*/

int		main(int argc, char **argv)
{
	t_env	env;
	int		debug;

	env.edl.line = NULL;
	debug = 0;
	edl_key_assoc(&env.edl);
	edl_fun_assoc(&env.edl);
	argc == 2 && ft_strcmp(argv[1], "DEBUG") == 0 ? debug++ : 0;
	g_shell = init_shell(&env, debug);
	if (tcgetattr(0, &env.term) == 0)
	{
		sh_term_switch(env.term, 1);
		dbg_core_manager(&env);
		sh_term_switch(env.term, 0);
	}
	return (0);
}
