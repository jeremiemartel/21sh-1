/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 23:38:57 by mabayle           #+#    #+#             */
/*   Updated: 2020/02/03 06:31:50 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectinclude.h"

t_21sh	*init_shell(int debug)
{
	t_21sh		*shell;

	shell = ft_memalloc(sizeof(*shell));
	shell->lex = NULL;
	shell->lex_size = 0;
	shell->ast = NULL;
	shell->debug = debug;
	return (shell);
}

static void	init_term(t_struct *s)
{
	int ret;
	struct termios	term;

	ret = tgetent(NULL, getenv("TERM"));
	isatty(0);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	s->prompt = 0;
	s->av = NULL;
}

static void	init_struct(t_struct *s, char **envp, int ac, char **av)
{
	(void)av;
	(void)ac;
	init_term(s);
	(*s).exit = 0;
	(*s).env = NULL;
	(*s).l = NULL;
	(*s).lbg = NULL;
	(*s).h = NULL;
	(*s).first = 0;
	s->set_cpt = 0;
	(*s).comp.name = NULL;
	s->bcom = NULL;
	s->com = NULL;
	if (((*s).builtin_ref = init_builtin_ref(0)) == NULL)
		ft_exit(0, &*s);
	if (!*envp)
		(*s).env = NULL;
	else
	{
		if (((*s).env = init_lst_env(NULL, envp, NULL, 0)) == NULL)
			ft_exit(0, &*s);
	}
	if (((*s).env_path = search_pathenv((*s).env)) == NULL)
		ft_eputstr("minishell: "MAGENTA"warning"
		WHITE": the PATH environment variable does not exist.\n\0");
}

static void	tmp_free_struct(t_struct *s, int *c)
{
	t_lst	*del;

	*c = 0;
	while ((del = (*s).lbg))
	{
		(*s).lbg = (*s).lbg->next;
		free(del);
	}
	(*s).l = NULL;
	(*s).lbg = NULL;
	free_dchar(&(*s).av);
	free_dchar(&(*s).envi);
	(*s).av = NULL;
}

static void	minishell(t_struct *s)
{
	(*s).c = check_command(&(*s).av, *s, NULL, 0);
	if ((*s).c < 2)
		ft_exit((*s).c, &*s);
	if ((*s).c > 1)
		(*s).prompt = 0;
	if ((*s).c > 2)
	{
		if ((exec_builtin(&*s, ((*s).c - 3))) == 0)
			ft_exit(0, &*s);
	}
	else if (((*s).first = fork()) == 0)
	{
		if ((*s).c == 2)
			exec_command(&*s, (*s).envi);
		exit(0);
	}
	if ((*s).first == -1)
		ft_exit(2, &*s);
	if ((*s).first > 0)
		wait(0);
	if ((*s).exit)
		ft_exit(0, &*s);
}

char		*create_lex_line(t_lst *s)
{
	char *line;

	while (s)
	{
		line = ft_strjoin_one(line, s->c);
		s = s->next;
	}
	return (line);
}

int			main(int ac, char **av, char **envp)
{
	t_struct	s;
	int			c;
	int			i;

	c = 0;
	init_struct(&s, envp, ac, av);
	g_shell = init_shell(0);
	s.h = create_history(NULL, NULL, NULL, &s);
	ac == 2 && ft_strcmp(av[1], "DEBUG") == 0 ? g_shell->debug = 1 : 0;
	while (1)
	{
		if (print_prompt(s.prompt, &s, 0) == 0)
			ft_exit(0, &s);
		if (((i = get_command(&s)) == 0) || i == 5)
			ft_exit(i, &s);
		else
		{
			while (s.av[0] && s.av[c])
				if (check_expansion(&s, c++, s.env, 0) == 0)
					ft_exit(0, &s);
			c = 1;
			if (s.av[0])
			{
				g_shell->line = create_lex_line(s.l);
				ft_lexer(&g_shell->lex, g_shell->line);
				minishell(&s);
			}
			tmp_free_struct(&s, &c);
		}
	}
	return (0);
}
