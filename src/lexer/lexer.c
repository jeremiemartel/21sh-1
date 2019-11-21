/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:48:49 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/19 04:39:07 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int		find_end(int i, char *input)
{
	while (input[i] && input[i] != '\n' && !ft_is_separator(input[i])
			&& !check_operator(input + i))
	{
		if (input[i] == '\\')
			i++;
		if (input[i] == '\'' || input[i] == '"')
		{
			i = quote_case(i, input);
			break ;
		}
		if (input[i])
			i++;
	}
	return (i);
}

int		end_case_index(t_lex *lex, char *input, int *io_nbr)
{
	int		i;
	t_lex	*last;

	i = 0;
	if (input[i] == '\n')
		while (input[i] == '\n')
			i++;
	else if (ft_isdigit(input[i]) == 1)
	{
		while (ft_isdigit(input[i]) == 1)
			i++;
		check_redirection(input + i) >= 1 ? *io_nbr = 1 : find_end(i, input);
	}
	else if ((i = check_operator(input)))
		;
	else if (*input == '-')
	{
		last = lex_last(lex);
		i = last && (last->operator == GREAT_AND || last->operator == LESS_AND)
				? 1 : find_end(i, input);
	}
	else
		i = find_end(i, input);
	return (i);
}

void	valid(t_lex **lex, char *input, int io, int aword, int i)
{
	char	*token;
	t_lex	*new;

	token = ft_strsub(input, 0, i);
	new = list_new(token);
	token_type(new, io, &aword);
	list_add(lex, new);
	ft_strdel(&token);
}
size_t	ft_lstsize(t_lex *lst)
{
	size_t	count;

	if (!lst)
	{
		return (0);
	}
	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	*exception(char *input, t_lex *lex)
{
	char	*new;
	char	*last;
	t_lex	*tmp;

	new = NULL;
	tmp = lex;
	ft_putendl("[DEBUG] Exception ok avant while");
	while (lex->next)
	{
		tmp = lex;
		lex = lex->next;
		ft_putstr("[DEBUG] Valeur de input dans le while de exception = ");
		ft_putendl(lex->value);
	}
	last = lex->value;
	new = ft_strjoin_one(last, ' ');
	new = ft_strjoin_free(new, input);
	lex = tmp;
	if (ft_lstsize(lex) < 2)
		lexdel(&lex);
	else
		lex_suppr_elem(&(lex->next));
	ft_putendl("[DEBUG] Exception ok");
	return (new);
}

#include <stdio.h>

void	ft_lexer(t_lex **lex, char *input)
{
	int		i;
	int		io_nbr;
	int		assignword;

	assignword = 0;
	ft_putendl("[DEBUG] Je rentre dans ft_lexer");
	if (!lex || !input)
		return ;
	if (g_shell->lex != NULL)
		if (g_shell->lex->state_quote == 1)
			input = exception(input, g_shell->lex);
	while (*input)
	{
		while (ft_is_separator(*input) == 1)
			input++;
		io_nbr = 0;
		ft_putstr("[DEBUG] Valeur de input = ");
		ft_putendl(input);
		i = end_case_index(*lex, input, &io_nbr);
		ft_putstr("[DEBUG] Valeur de i a la sortie de end_case_index = ");
		ft_putnbr(i);
		write(1, "\n", 1);
		if (i != -1)
		{
			ft_putendl("[DEBUG] SEGV OK (valid)");
			valid(lex, input, io_nbr, assignword, i);
			g_shell->lex->state_quote == 1 ? change_state(1) : 0;
			ft_putendl("[DEBUG] State_quote a 0");
			input = input + i++;
		}	
		else
		{
			ft_putendl("[DEBUG] SEGV OK (invalid)");
			i = ft_strlen(input);
			valid(lex, input, io_nbr, assignword, i);
			g_shell->lex->state_quote == 0 ? change_state(0) : 0;
			ft_putendl("[DEBUG] State_quote a 1");
			return ;
		}
	}
	/*****  DEBUG *****/
	while (g_shell->lex)
	{
		ft_putendl("[DEBUG][FT_LEXER][VALUE]");
		ft_putstr("   VALUE DU TOKEN => ");
		ft_putendl(g_shell->lex->value);
		ft_putstr("   TYPE DE TOKEN => ");
		ft_print_debug(lex);
		g_shell->lex = g_shell->lex->next;
	}
	/*****  FIN DEBUG ******/
	lexdel(lex);
}
