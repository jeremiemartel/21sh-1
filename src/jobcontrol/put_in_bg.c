#include <jobcontrol.h>
#include <sh21.h>

void	delete_process(t_process *pro)
{
	if (!pro)
		return ;
	if (pro && pro->next)
		delete_process(pro->next);
	ft_memdel((void**)pro);
}

t_job	*delete_first(t_job *first)
{
	t_job	*tmp;

	delete_process(first->first_process);
	ft_strdel(&first->command);
	tmp = first;
	first = first->next;
	ft_memdel((void**)tmp);
	if (first)
		g_jobcontrol.first_mail = first;
	else
		g_jobcontrol.first_mail = g_jobcontrol.first_job;
	return (first);
}

t_job	*delete_link(pid_t pgid)
{
	t_job 		*first;
	t_job		*tmp;

	first = g_jobcontrol.first_mail;
	if (first->pgid == pgid)
		return (delete_first(first));
	while (first && first->next)
	{
		if (first->next->pgid == pgid)
		{
			ft_strdel(&first->command);
			delete_process(first->next->first_process);
			tmp  = first->next;
			first->next = first->next->next;
			ft_memdel((void**)tmp);
		}
		first = first->next;
	}
	first = NULL;
	return (NULL);
}

t_job	*print_and_del(t_job *job, int i, int check)
{
	t_job	*save;

	save = job;
	if (i != 0 && i == check)
	{
		if (job->stop == 1)
		{
			ft_putchar_fd('[', 2);
			ft_putnbr_fd(job->j_nb, 2);
			ft_putstr_fd("]  ", 2);
			ft_putnbr_fd(job->pgid, 2);
			ft_putchar_fd(' ', 2);
			ft_putstr_fd(job->command, 2);
			ft_putstr_fd("  Terminated ", 2);
			ft_putnbr_fd(job->first_process->status, 2);
			ft_putchar_fd('\n', 2);
		}
		save = delete_link(job->pgid);
		if (!save)
			save = job;
	}
	return (save);
}

t_job	*check_bg_status(t_job *job)
{
	t_process 	*p;
	int			check;
	int			i;

	i = 0;
	check = 0;
	p = job->first_process;
	while (p && p->next)
	{
		i++;
		if ((job->fg == 0 || job->stop == 1) && (p->status > 1))// || p->status == -1))
			check++;
		else if (job->stop != 1 && job->fg == 1)
		{
			check++;
			kill(p->lpid, SIGKILL);
			waitpid(p->lpid, 0, WUNTRACED | WNOHANG);
		}
		p = p->next;
	}
	job = print_and_del(job, i, check);
	return (job);
}

void	update_bg_status(t_process *pro)
{
	int			status = 0;
	pid_t		pid  = 0;
	t_job		*cpy;
	int	errno;
	
	errno =0;
	cpy = g_jobcontrol.first_mail;;
	while (cpy && cpy->next)
	{
		pro = cpy->first_process;
		while (pro && pro->next)
		{
			pid = waitpid(pro->lpid, &status, WUNTRACED | WNOHANG);
			if (pro && pro->lpid == pid)
			{
				process_status(pid, status, pro);
				break ;
			}
			pro = pro->next;
		}
		cpy = check_bg_status(cpy);
		cpy = cpy->next;
	}
}

void	put_in_bg(t_job *job, int cont, char **av, t_process *pro)
{
	pid_t	pgid;
	t_job	*save;

//	ign_jb_sign(1);
	if (!cont)
		wait_for_job(pro, job, 0);
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
				;
				put_last_stp(put_last_stp(job, 1, 2), 0, 1);
//				ft_putnbr(0
///				exit
				break ;
			}
			job = job->next;
		}
		g_jobcontrol.first_job  = save;
	}
}
