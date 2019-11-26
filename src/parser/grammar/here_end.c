/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 05:07:46 by mabayle           #+#    #+#             */
/*   Updated: 2019/11/26 05:45:14 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"

/*
** Objectif de la fonction : check if lex->next->value == WORD and apply
                             rule 3 of posix grammar : 
                             Quote removal shall be applied to the word to 
                             determine the delimiter that is used to find the 
                             end of the here-document that begins after the 
                             next <newline>
** Valeur de retour : return 1 if match | else return 0
*/
int     here_end(t_lex *lex)
{
    if (lex->token == WORD)
    {
        if (ft_strcmp(lex->value, """") == 0)
        {
            lex->value = "\n";
            return (1);
        }    
        else if (lex->value[0] == '"')
        {
            char *new;
            if (ft_strlen(lex->value) > 0)
            {
                new = ft_memalloc(ft_strlen(lex->value) - 1);
                strcpy(new, lex->value++);
            }
            if (ft_strlen(new) > 1)
                new[ft_strlen(new) - 2] = '\0';
            lex->value = new;
            return (1);
        }
    }
    else
        return (0);
}