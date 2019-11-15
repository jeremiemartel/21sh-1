/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:22:48 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/15 05:52:18 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	ft_print_debug(t_lex **lex)
{
	if ((*lex)->token == WORD)
		ft_putendl("WORD");
	else if ((*lex)->token == CONTROL_OPE)
	{
		ft_putstr("CONTROL_OPE   |   ");
		if ((*lex)->operator == OTHER)
			ft_putendl("NOT A CONTROL_OPE");
		else if ((*lex)->operator == SEMIC)
			ft_putendl("SEMIC");
		else if ((*lex)->operator == DSEMIC)
			ft_putendl("DSEMIC");
		else if ((*lex)->operator == PIPE)
			ft_putendl("PIPE");
		else if ((*lex)->operator == DPIPE)
			ft_putendl("DPIPE");
		else if ((*lex)->operator == AND)
			ft_putendl("AND");
		else if ((*lex)->operator == DAND)
			ft_putendl("DAND");
	}
	else if ((*lex)->token == REDIR_OPE)
	{
		ft_putstr("REDIR_OPE   |   ");
		if ((*lex)->operator == OTHER)
			ft_putendl("NOT A REDIR_OPE");
		else if ((*lex)->operator == LESS)
			ft_putendl("LESS");
		else if ((*lex)->operator == DLESS)
			ft_putendl("DLESS");
		else if ((*lex)->operator == GREAT)
			ft_putendl("GREAT");
		else if ((*lex)->operator == DGREAT)
			ft_putendl("DGREAT");
		else if ((*lex)->operator == LESS_AND)
			ft_putendl("LESS_AND");
		else if ((*lex)->operator == GREAT_AND)
			ft_putendl("GREAT_AND");
		else if ((*lex)->operator == LESS_GREAT)
			ft_putendl("LESS_GREAT");
		else if ((*lex)->operator == DLESS_DASH)
			ft_putendl("DLESS_DASH");
		else if ((*lex)->operator == CLOBBER)
			ft_putendl("CLOBBER");
	}
	else if ((*lex)->token == IO_NUMBER)
		ft_putendl("IO_NUMBER");
	else if ((*lex)->token == ASSIGN_WORD)
		ft_putendl("ASSIGN_WORD");
	else if ((*lex)->token == NEW_LINE)
		ft_putendl("NEW_LINE");
}
