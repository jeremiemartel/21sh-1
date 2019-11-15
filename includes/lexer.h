/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 04:21:06 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/15 05:22:25 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** INCLUDES
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sh.h"

/*
** ENUM
*/

enum			e_tok_type
{
	WORD,
	CONTROL_OPE,
	REDIR_OPE,
	IO_NUMBER,
	ASSIGN_WORD,
	NEW_LINE,
};

enum			e_operator
{
	OTHER,
	SEMIC,
	DSEMIC,
	PIPE,
	DPIPE,
	AND,
	DAND,
	LESS,
	DLESS,
	GREAT,
	DGREAT,
	LESS_AND,
	GREAT_AND,
	LESS_GREAT,
	DLESS_DASH,
	CLOBBER,
};

/*
** STRUCTURES
*/

typedef struct 			s_lex
{
	char				*value;
	char				*hdoc;
	int					hdoc_delim;
	int					state_quote;
	enum e_tok_type		token;
	enum e_operator		operator;
	struct s_lex		*next;
}						t_lex;

typedef struct 			s_ast
{
	struct s_lex		*lex;
	struct s_21sh		*inputhell;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef struct			s_21sh
{
	char				*line;
	t_lex				*lex;
	t_ast				*ast;
	t_env				*env;
}						t_21sh;

t_21sh					*g_shell;

/*
** PROTOTYPE
*/

/*
** LEXER.C
*/
void	ft_lexer(t_lex **lex, char *input);
void	valid(t_lex **lex, char *input, int io, int aword, int i);
void	invalid(t_lex **lex);
int		end_case_index(t_lex *lex, char *input, int *io_nbr);
int		find_end(int i, char *input);

/*
** LIST_UTILS.C
*/
t_lex	*list_new(char *input);
void	list_add(t_lex **alst, t_lex *new);
t_lex	*lex_last(t_lex *lst);
void	lexdel(t_lex **alst);
void	lex_suppr_elem(t_lex **elem);

/*
** UTILS.C
*/
int		check_redirection(char *input);
int		check_operator(char *input);
int		quote_case(int i, char *input);
int		ft_is_separator(char c);

/*
** PRINT_DEBUG.C
*/
void	ft_print_debug(t_lex **lex);

/*
** TYPE_TOKEN.C
*/
void	is_operator(t_lex *new);
void	is_redirection(t_lex *new);
void	is_assignword(t_lex *new);
void	token_type(t_lex *new, int io_nbr, int *assignword);

#endif
