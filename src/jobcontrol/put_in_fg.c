#include <input.h>
#include <jobcontrol.h>
#include <sh21.h>

pid_t		stopped_pgid(char **av, t_job *job)
{
	pid_t	pgid;
	t_job	*save;

	save = job;
	if ((av && !av[1]) || !av)
	{
		
		while (job && job->next)
		{
			if (job->pgid == last_stp_job(save))
				break ;;
			job = job->next;
		}
	}
	else if (av[2])
		return (-1);
	else
	{
		pgid = av[1][0] != '%' ? jobs_parser(av[1], job) : job_nb(ft_atoi(av[1] + 1), job);
		if (pgid == 0)
			ft_putendl_fd("Error no job", 2);
		while (pgid && job->next)
		{
			if (job->pgid == pgid)
				break;
			job = job->next;
		}
	}
	if (job->stop == 1 || (job->stop != 1 && job->fg != 1))
		return (job->pgid);
	else
		return (0);
}

void		change_stop_flag()
{
	
}

int		fg_or_bg(pid_t pgid, t_job *job)
{
	t_job	*save;

	save = job;
	while (save && save->next)
	{
		if (save->pgid == pgid)
			return (save->fg);
		save = save->next;
	}
	return (-1);
}

pid_t		right_job(int cont, char **av, t_job *job)
{
	pid_t 	pgid;

	if (cont)
	{
		pgid = stopped_pgid(av, job);
		if (pgid < 1)
		{
			if (fg_or_bg(pgid, job))
				ft_putstr_fd("fg: ", 2);
			else
				ft_putstr_fd("bg: ", 2);
			if (pgid == 0)
				ft_putendl_fd("no current job", 2);
			else if (pgid == -1)
				ft_putendl_fd("Too many arguments", 2);
		}
	}
	else
		pgid = g_jobcontrol.first_job->pgid;
	return (pgid);
}

void		put_in_fg(int cont, t_job *job, char **av, t_process *pro)
{
	pid_t	pgid;
	t_job	*save;

	save = g_jobcontrol.first_job;
	pgid = right_job(cont, av, job);
	tcsetpgrp(0, pgid);
	if (cont && pgid > 0)
	{
//		ign_jb_sign(1);
		tcsetattr(0, TCSANOW, &g_jobcontrol.term_attr);
		if (kill(-(pgid), SIGCONT) < 0)
			ft_putendl_fd("Fail to continue", 2);
		while (job && job->next)
		{
			if (job->pgid == pgid)
			{
				g_jobcontrol.first_job = job;
				g_jobcontrol.first_job->stop = -1;
				g_jobcontrol.first_job->last_j = 0;
				g_jobcontrol.first_job->fg = 1;
				put_last_stp(job, 2, 1);
				break;
			}
			job = job->next;
		}
		g_jobcontrol.first_job = save;
		pro = job->first_process;
		save = job;
	}
	wait_for_job(pro, save, 1);
	tcsetpgrp(0, g_jobcontrol.shell_pgid);
	tcsetattr(0, TCSANOW, &g_jobcontrol.term_attr);
}
