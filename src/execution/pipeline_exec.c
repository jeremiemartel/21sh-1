#include <input.h>
#include <jobcontrol.h>
#include <sh21.h>

int		job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	ft_putendl_fd(p->cmd, 2);
	ft_putendl_fd(j->command, 2);
	while (p && p->next && p->next->next)
	{
//		if (!p->status)
//			return (0);
		p = p->next;
	}
	ft_putendl(p->cmd);
	ft_putendl("NO COMPLETE");
	if (p && (p->status > 1 || p->status == -1))
	{
		ft_putendl("COMPLETED JOB");
		return (1);
	}
	return (0);
}

pid_t	job_nb(int i, t_job *j)
{
	while (j->next)
	{
		if (j->j_nb == i)
			return (j->pgid);
		j = j->next;
	}
	return (0);
}

pid_t		jobs_parser(char *str, t_job *j)
{
	int		i;
	pid_t	pgid;

	i = 0;
	pgid = 0;
	while (j->next)
	{
		if (((j->fg == 0 && !job_is_completed(j)) || j->stop == 1) && ft_strcmp(j->command, str) == 0)
			return (j->pgid);
		else if (((j->fg == 0 && !job_is_completed(j)) || j->stop == 1) && j->command[i] == str[i])
		{
			while (str[i] && str[i] == j->command[i])
				i++;
			if (i == ft_strlenu(str))
				pgid = j->pgid;
			i = 0;
		}
		j = j->next;
	}
	return (pgid);
}

pid_t	last_stp_job(t_job *job)
{
	t_job	*tmp;

	tmp = job->next;
	while (job && job->next && tmp)
	{
		if (tmp && tmp->last_j >= job->last_j)
		{
			tmp = tmp->next;
			job = job->next;
		}
		else
			tmp = tmp->next;
	}
	return (job->pgid);
}

void	print_pid(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p && p->next)
	{
		ft_putnbr_fd(p->lpid, 2);
		p = p->next;
		if (p->next)
			ft_putstr_fd(" | ", 2);
	}
}

void	print_job_status(int i, t_job *j, t_job *f_job)
{
	pid_t	pgid;

	pgid = last_stp_job(f_job);
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(j->j_nb, 2);
	ft_putstr_fd("]  ", 2);
	print_pid(j);
	ft_putchar(' ');
	if (pgid && pgid == j->pgid)
		ft_putstr_fd(" +", 2);
	else
		ft_putstr_fd("  ", 2);
	if (i == 1)
		ft_putstr_fd(" suspended ", 2);
	else
		ft_putstr_fd(" running ", 2);
	ft_putendl_fd(j->command, 2);
}

void	no_param_jobs(t_job *j)
{
	t_job	*save;

	save = j;
	while (j && j->next)
	{
		if (j->stop == 1)
			print_job_status(j->stop, j, save);
		else if (j->fg != 1 && !job_is_completed(j))
			print_job_status(j->stop, j, save);
		j = j->next;
	}
}

void	job_error(const char *str)
{
	ft_putstr_fd("jobs: no such job : ", 2);
	ft_putendl_fd(str, 2);
}

void	ft_jobs(t_job *j, char **av)
{
	int		i;
	pid_t	pgid;
	t_job	*save;

	i = 1;
	save = j;
	pgid = 0;
	if (!av[1])
		no_param_jobs(j);
	else
	{
		while (av[i])
		{
			/* si % modifier dans le lexer par le job number verifer le numero*/
			pgid = av[i][0] != '%' ? jobs_parser(av[i], save) : job_nb(ft_atoi(av[i] + 1), save);
			if (pgid == 0)
				job_error(av[i]);
			ft_putnbr(pgid);
			while (pgid && j->next)
			{
				if (j->pgid == pgid)
					print_job_status(j->stop, j, save);
				j = j->next;
			}
			i++;
			j = save;
		}
	}
}

t_job	*put_last_stp(t_job *job, int i, int l)
{
	t_job	*cpy;
	t_job	*save;

	save = g_jobcontrol.first_job;
	cpy = g_jobcontrol.first_mail;
	while (cpy && cpy->next)
	{
		if (cpy->last_j == l && cpy->pgid != job->pgid)
		{
			g_jobcontrol.first_job = cpy;
			g_jobcontrol.first_job->last_j = i;
			g_jobcontrol.first_job = save;
			return (cpy);
		}
		cpy = cpy->next;
	}
	return (cpy);
}

int		check_jb_nb()
{
	t_job	*first;
	int		nb;

	nb = 1;
	first = g_jobcontrol.first_mail;
	while (first && first->next)
	{
		if (first->stop == 1)
			nb = first->j_nb + 1;
		first = first->next;
	}
	return (nb);
}

void	to_do_if_stp(t_job *job, t_job *save, int i)
{
	if (g_jobcontrol.first_job->pgid == job->pgid)
	{
		g_jobcontrol.repere += 1;
		g_jobcontrol.first_job->j_nb = check_jb_nb();
	}
	g_jobcontrol.first_job = job;
	g_jobcontrol.first_job->last_j = 2;	
	put_last_stp(put_last_stp(job, 1, 2), 0, 1);
//	put_last_stp(job, 1, 2);
	ft_putstr_fd("\n[", 2);
	ft_putnbr_fd(g_jobcontrol.first_job->j_nb, 2);
	ft_putstr_fd("] +  ", 2);
	ft_putnbr_fd(g_jobcontrol.first_job->pgid, 2);
	if (i)
	{
		g_jobcontrol.first_job->stop = 1;
		ft_putstr_fd("  suspended ", 2);
	}
	else
		ft_putstr_fd("  running ", 2);
	ft_putendl_fd(g_jobcontrol.first_job->command, 2);
	g_jobcontrol.first_job = save;
}

int		check_if_stop(t_process *p, t_job *job)
{
	t_job	*save;

	save = g_jobcontrol.first_job;
	while (p && p->next)
	{
		if (p->status == 1)
		{
			to_do_if_stp(job, save, 1);
			return (1);
		}
		if (job->fg != 1)
		{
			to_do_if_stp(job, save, 0);
			return (1);
		}

		p = p->next;
	}
	return (0);
}

int		process_status(pid_t pid, int status, t_process *p)
{
	g_jobcontrol.first_job->first_process = p;
	if (pid < 0)
		return (-1);
	if (WIFEXITED(status) == TRUE)
	{
		g_jobcontrol.first_job->first_process->status = 2;
		g_jobcontrol.first_job->first_process->status = status ? 2 : -1;;
	}
	else if (WIFSIGNALED(status) == TRUE)
	{
		g_jobcontrol.first_job->first_process->status = status;
//		ft_putstr_fd("Terminated : ",2);
//		ft_putnbr(WTERMSIG(status));
	}
	else if (WIFSTOPPED(status) == TRUE)
		g_jobcontrol.first_job->first_process->status = 1;
	return (status);
}

void	sign_chld(int i)
{
	//BEFORE CALL IT SET G_ STRUC POINT TO FIRST  JOB
	(void)i;
	t_job *job;

	job = g_jobcontrol.first_job;


}

int		process_nb(t_process *pro)
{
	int	i;

	i = 0;
	while (pro && pro->next)
	{
		i++;
		pro = pro->next;
	}
	return (i);
}

void	wait_for_job(t_process *pro, t_job *job, int fg)
{
	pid_t	pid;
	int		status;
	t_process	*save;

	save = pro;
	pid = 0;
	if (!pro)
		return ;
	status = 0;
	signal(SIGCHLD, SIG_DFL);
	while (pro)
	{
		(waitpid(pro->lpid, &status, WUNTRACED | WNOHANG));
		process_status(pro->lpid, status, pro);
		pro = pro->next;
	}
	pro = save;
	while (pro && pro->next && pro->next->next)
		pro = pro->next;
	if (fg)
		waitpid(pro->lpid, &status, WUNTRACED);
	process_status(pro->lpid, status, pro);
	pro = save;
	check_if_stop(pro, job);
}

void	fill_jc_struc(pid_t pid, char *cmd)
{
	if (pid == -1)
		return ;

	g_jobcontrol.first_job->first_process->lpid = pid;
//	g_jobcontrol.first_job->first_process->status = 0;
	g_jobcontrol.first_job->first_process->cmd = ft_strdup(cmd);
	g_jobcontrol.first_job->first_process->next = ft_memalloc(sizeof(*g_jobcontrol.first_job->first_process));
	g_jobcontrol.first_job->first_process = g_jobcontrol.first_job->first_process->next;
	g_jobcontrol.first_job->first_process->next = NULL;
	if (g_jobcontrol.shell_is_int)
	{
		if (!g_jobcontrol.first_job->pgid)
			g_jobcontrol.first_job->pgid = pid;
		setpgid(pid, g_jobcontrol.first_job->pgid);
	}
}

void	set_id_sign(int foreground)
{
	pid_t   pid;
	
	pid = getpid();
	if (g_jobcontrol.first_job->pgid == 0)
       g_jobcontrol.first_job->pgid = pid;
	setpgid(pid, g_jobcontrol.first_job->pgid);
	if (foreground)
		tcsetpgrp(0, g_jobcontrol.first_job->pgid);
	ign_jb_sign(1);
}

void    fill_pipe(int oldlink[2], int newlink[2], char **av, int i)
{
    if (i > 1)
	{
        dup2(oldlink[0], 0);
		close(oldlink[0]);
	}
    if (av[i + 1])
	{
        dup2(newlink[1], 1);
		close(newlink[1]);
	}
}

int		pipe_exec(char **av, char **env, t_job *job, int fg)
{
	int			i;
	int			status;
	int			oldlink[2];
	int			newlink[2];
	char    	**cmd;
	char		*mypath;
	pid_t   	pid;
	int			errno;
	t_process	*pro;

	pid = -1;
	i = 0;
	errno = 0;
	ft_putendl("im in the exec");
	newlink[0] = -1;
	newlink[1] = -1;
	g_jobcontrol.first_job->first_process =
				ft_memalloc(sizeof(*g_jobcontrol.first_job->first_process));
	g_jobcontrol.first_job->first_process->next = NULL;
	pro = g_jobcontrol.first_job->first_process;
//	g_jobcontrol.first_mail->first_process = pro;
	signal(SIGCHLD, SIG_DFL);
	g_jobcontrol.first_job->fg = fg;
	while (av[i])
	{
		if (ft_strcmp(av[i], "|") == 0)
			i++;
		else
		{
			cmd = ft_strsplit(av[i], ' ');
			oldlink[0] = newlink[0];
			if (av[i + 1] && ft_strcmp(av[i + 1], "|") == 0)
				if (pipe(newlink) < 0)
					ft_putendl_fd("Could not create the pipe", 2);
			mypath = get_pathh(cmd[0], get_line(env));
			if (!mypath && ft_strcmp(cmd[0], "jobs"))
				ft_putendl_fd("no cmd found", 2);
			else if (ft_strcmp(cmd[0], "jobs") == 0)
				ft_jobs(g_jobcontrol.first_mail, cmd); 
			else if (ft_strcmp(cmd[0], "fg") == 0)
				put_in_fg(1, job, cmd, NULL);
			else if (ft_strcmp(cmd[0], "bg") == 0)
				put_in_bg(job, 1, cmd, pro);
			else if (mypath && (pid = fork()) == 0)
			{
				set_id_sign(fg);
				fill_pipe(oldlink, newlink, av, i);
				execve(mypath, cmd, env);
				abort();
				exit(errno);
			}
			fill_jc_struc(pid, av[i]);
			close (oldlink[0]);
			close(newlink[1]);
			i++;
		}
	}
	close(oldlink[0]);
	close(newlink[1]);
	close(newlink[0]);
	g_jobcontrol.first_job->first_process = NULL;
	status = 0;
	if (fg)
		put_in_fg(0, g_jobcontrol.first_mail, NULL, pro);
	else
	{
		put_in_bg(g_jobcontrol.first_mail, 0, NULL, pro);
	}
	ign_jb_sign(0);
	g_jobcontrol.first_job->first_process = pro;
	ft_putnbr(g_jobcontrol.first_job->stop);
	ft_putnbr(g_jobcontrol.first_job->fg);
	ft_putnbr(g_jobcontrol.first_job->last_j);
	ft_putendl(g_jobcontrol.first_job->command);
	return (0);
}
