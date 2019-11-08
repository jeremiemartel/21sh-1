/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:32:35 by alalonzo          #+#    #+#             */
/*   Updated: 2019/11/08 16:51:04 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

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

void	rdl_controller(t_env *env)
{
}

/*
** CORE MANAGER SHITLOAD
*/



void	dbg_core_manager(t_env *env)
{
	int		ret;

	env->loop = 42;
	ret = 0;
	edl_print(env);
	while (env->loop)
	{
		if (env->edl.line == NULL)
		{
			ft_putstr("21sh> ");
		}
		ret = edl_controller(env);
		edl_print(env);
		if (ret == 1)
		{
			ft_putchar('\n');
			if (ft_strcmp(env->edl.line, "exit") == 0)
				env->loop = 0;
			free(env->edl.line);
			env->edl.line = NULL;
		}
		/*
		if ((ret = edl_controller(env)) >= 0)
			if (ret == 1)
				if (lexer_parser() == 1)
					do_that_shet();
		*/
		//si edl_controller renvoie 1, alors la ligne a ete cloturee
		//si edl_controller renvoie 0, alors la ligne n'est pas cloturee
		//si edl_controller renvoie -1, probleme, donc break 
	}
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
	if (tcgetattr(0, &env.term) == 0)
	{
		sh_term_switch(env.term, 1);
		dbg_core_manager(&env);
		sh_term_switch(env.term, 0);
	}
	return (0);
}
