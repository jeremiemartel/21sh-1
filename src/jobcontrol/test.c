#include <jobcontrol.h>
#include <sh21.h>

void	delete_link(t_job *job)
{
	t_job *first;

	first = g_jobcontrol.first_mail;
	while (first)
	{
		if (first->pgid == job->pgid)
		{
			ft_strdel(&g_jobcontrol.first_job->command);
			while (g_jobcontrol.first_job->first_process)
			{
				ft_strdel(&g_jobcontrol.first_job->first_process->cmd);
				g_jobcontrol.first_job->first_process = g_jobcontrol.first_job->first_process->next;
			}
			free(g_jobcontrol.first_job->first_process);
			free(g_jobcontrol.first_job);
			g_jobcontrol.first_job = NULL;
			first = first->next;
		//	g_jobcontrol.first_job = first;
	//		g_jobcontrol.first_job->next = first->next;
		//	break ;
		}
		g_jobcontrol.first_job = first;
		first = first->next;
	}
}

void	check_bg_status(t_job *job)
{
	t_process *p;
	t_process *ps;
	t_job		*save;
	int			check;
	int			i;

	i = 0;
	check = 0;
	save = g_jobcontrol.first_job;
	p = job->first_process;
	ps = job->first_process;
	while (p && p->next)
	{
		i++;
		if ((job->fg == 0 || job->stop == 1) && (p->status > 1  || p->status == -1))
		{
			check++;
		}
		else if (job->stop != 1 && job->fg == 1)
		{
			kill(p->lpid, SIGKILL);
			waitpid(p->lpid, 0, WUNTRACED | WNOHANG);
		}
		p = p->next;
	}
	p = job->first_process;
	if (i != 0  && i == check)
	{
			delete_link(job);
			ft_putchar_fd('[', 2);
			ft_putnbr(job->j_nb);
			ft_putchar_fd(']', 2);
			ft_putnbr_fd(job->pgid, 2);
			ft_putchar_fd(' ', 2);
			ft_putstr_fd(job->command, 2);
			ft_putstr_fd("  Terminated ", 2);
			ft_putnbr_fd(p->status, 2);
			ft_putchar_fd('\n', 2);
			ft_putendl(job->command);
			ft_putendl(p->cmd);
	//		g_jobcontrol.first_job = save;
	}
}

void	update_bg_status(t_process *pro)
{
	int			check;
	int			status;
	pid_t		pid;
	t_job		*cpy;
	int	errno;
	
	errno =0;

	check = 0;
	cpy = g_jobcontrol.first_mail;;
	while (cpy && cpy->next && check == 0)
	{
		pro = cpy->first_process;
		while (pro && pro->next)
		{
			pid = waitpid(pro->lpid, &status, WUNTRACED | WNOHANG);
			if (pro->lpid == pid)
			{
				process_status(pid, status, pro);
				check = 1;
				break ;
			}
			if (check == 1)
				break ;
			pro = pro->next;
		}
		check_bg_status(cpy);
		cpy = cpy->next;
	}
}

void	put_in_bg(t_job *job, int cont, char **av)
{
	pid_t	pgid;
	t_job	*save;

	pgid = right_job(cont, av, job);
	save = g_jobcontrol.first_job;
	if (cont && pgid > 0)
	{
		if (kill(-(pgid), SIGCONT) < 0)
			ft_putendl_fd("Fail to continue", 2);
		while (job && job->next)
		{
			if (job->pgid == pgid)
			{
				g_jobcontrol.first_job = job;
				g_jobcontrol.first_job->stop = 0;
				g_jobcontrol.first_job->fg = 0;
				g_jobcontrol.first_job->last_j = 2;
				put_last_stp(job, 1);
				break ;
			}
			job = job->next;
		}
		g_jobcontrol.first_job  = save;
	}
}
