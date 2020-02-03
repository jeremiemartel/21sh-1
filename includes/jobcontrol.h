/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:30:26 by ymarcill          #+#    #+#             */
/*   Updated: 2019/12/05 07:57:17 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/errno.h>
#include "input.h"

/*a process is a single process*/
typedef struct				s_process
{
	struct s_process		*next;
	char					*cmd;
	pid_t					lpid;
	int						status;
	int						my_stdin;
	int						my_stdout;

}							t_process;

/*a job is a pipeline of process*/
typedef struct				s_job
{
	struct s_process		*first_process;
	struct s_job			*next;
	char					*command;
	int						fg;
	int						j_nb;
	int						stop;
	int						completed;
	pid_t					pgid;
	int						last_j;
}							t_job;

typedef struct				s_jobcontrol
{
	struct termios			term_attr;
	struct s_job			*first_job;
	struct s_job			*first_mail;
	struct s_process		*pro_mail;
	pid_t					shell_pgid;
	pid_t					shell_pid;
	int						shell_is_int;
	int						repere;
}							t_jobcontrol;

struct s_jobcontrol				g_jobcontrol;

int							job_is_completed(t_job *job);
void						update_bg_status(t_process *pro);
int							check_if_stop(t_process *p, t_job *job);
int							process_status(pid_t pid, int status, t_process *p);
void						put_in_bg(t_job *job, int cont, char **av, t_process *pro);
pid_t						right_job(int cont, char **av, t_job *job);
t_job						*put_last_stp(t_job *job, int i, int l);
pid_t						stopped_pgid(char **av, t_job *job);
pid_t						last_stp_job(t_job *j);
pid_t						job_nb(int i, t_job *j);
pid_t						jobs_parser(char *str, t_job *j);
void						wait_for_job(t_process *pro, t_job *job, int i);
void						put_in_fg(int cont, t_job *job, char **av, t_process *pro);
int							pipe_exec(char **av, char **env, t_job *job, int fg);
int							init_shell_sig();
t_process					*init_process_struct();
t_job						*init_job_struct();
void						launch_fg(int foreground);
void						ign_jb_sign(int i);
void						ft_freetab(char **s1);
char						**get_line(char **env);
char						*get_pathh(char *nwav, char **path);
int							ft_strlenu(char *str);
char						*ft_strjoinnf(char const *s1, char const *s2);

#endif
