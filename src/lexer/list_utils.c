/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 05:17:16 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/19 03:52:51 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_lex	*list_new(char *input)
{
	t_lex	*new;

	if (!(new = ft_memalloc(sizeof(t_lex))))
		return (NULL);
	if (input == NULL)
		new->value = NULL;
	else
		new->value = ft_strdup(input);
	new->hdoc = NULL;
	new->token = 0;
	new->state_quote = 0;
	new->operator = 0;
	new->hdoc_delim = 0;
	new->next = NULL;
	return (new);
}

void	list_add(t_lex **alst, t_lex *new)
{
	t_lex		*tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_lex	*lex_last(t_lex *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lex_suppr_elem(t_lex **elem)
{
	t_lex	*suppr;

	suppr = *elem;
	*elem = (*elem)->next;
	ft_strdel(&suppr->value);
	ft_strdel(&suppr->hdoc);
	suppr->next = NULL;
	free(suppr);
}

void	lexdel(t_lex **alst)
{
	t_lex	*current;

	if (!alst)
		return ;
	current = *alst;
	while (current)
		lex_suppr_elem(&(current));
	*alst = NULL;
}
