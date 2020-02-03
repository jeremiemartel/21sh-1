/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interactive_shell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 12:40:19 by ymarcill          #+#    #+#             */
/*   Updated: 2019/12/05 07:51:12 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/jobcontrol.h"
#include "../includes/input.h"
void	ign_jb_sign(int i)
{
	sig_t	func;

	func = SIG_IGN;
	if (i)
		func = SIG_DFL;
	signal(SIGINT, func);
	signal(SIGQUIT, func);
	signal(SIGTSTP, func);
	signal(SIGTTIN, func);
	signal(SIGTTOU, func);
//	signal(SIGCHLD, func);
}

int		init_shell_sig()
{
	struct termios	term;
	/* check if shell is interactive so if 0 refers to a tty*/
	if ((g_jobcontrol.shell_is_int = isatty(0)))
	{
		/*loop to check if our shell is in forground so if it has all rights
		(especially reading rights of its controlling terminal)until it is*/
		while (tcgetpgrp(0) != (g_jobcontrol.shell_pgid = getpgrp()))
			kill(-(g_jobcontrol.shell_pgid), SIGTTIN);
		/*ignoring jobcontrol signal*/
		ign_jb_sign(0);
		/*putting our process in our own process group (to be sure) means
		our pid is the same than our pgid*/
		if (setpgid(g_jobcontrol.shell_pgid = getpid(), g_jobcontrol.shell_pgid) < 0)
		{
			ft_putstr_fd("Could not put the shell in its own process group", 2);
			return (0);
		}
		/*putting our process in forground so grab rights of th tty*/
		tcsetpgrp(0, g_jobcontrol.shell_pgid);
		/*save default term attr, if problems return (0) is an error*/
		tcgetattr(0, &g_jobcontrol.term_attr);
		term = g_jobcontrol.term_attr;
		term.c_cc[VTIME] = 0;
		term.c_cc[VMIN] = 1;
		//term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(0, TCSADRAIN, &term);
		/* v don't forget to set the sigint flag refer to
		21shtest/srcs/input/term_mode.c and exec file*/
//		(set_none_canon_mode(0));
		return (0);
	}
	return (g_jobcontrol.shell_is_int);
}
