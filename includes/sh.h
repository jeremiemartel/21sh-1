/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:17:46 by alalonzo          #+#    #+#             */
/*   Updated: 2019/11/09 06:44:18 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <termios.h>

#define TCL "\033[J"
#define TSC	"\033[s"
#define TRC	"\033[u"
#define GLP "\033[6n"

typedef struct termios	t_termios;

enum			e_keys
{
	K_RET,
	K_UP,
	K_DOWN,
	K_RIGHT,
	K_LEFT,
	K_HOME,
	K_END,
	K_DEL,
	K_SUP,
	K_CN_UP,
	K_CN_DOWN,
	K_CN_RIGHT,
	K_CN_LEFT,
	K_CN_D,
	//K_CN_U  ***  \25
	K_COUNT
};

/*
** RDL STAND FOR : REDACTEUR DE LIGNE
** IN COMPARISON OF EDL WICH STAND FOR : EDITEUR DE LIGNE
*/
typedef struct	s_rdl
{
}				t_rdl;

typedef struct	s_edl
{
	char		*line;
	char		buf[2048];
	int			len;
	int			pos;
	int			opos; // MIGHT BE REPLACED LATER
	char		*key[K_COUNT + 1];
	int			(*fun[K_COUNT])();
}				t_edl;

typedef struct	s_env
{
	t_termios	term;
	t_edl		edl;
	char		loop;
	char		state; //
}				t_env;



/*
** KEY FUNCTION PROTOTYPE START ---
*/
int				dbg_key_up(t_env *env);
int				dbg_key_down(t_env *env);
int				dbg_key_right(t_env *env);
int				dbg_key_left(t_env *env);

int				dbg_key_home(t_env *env);
int				dbg_key_end(t_env *env);
int				dbg_key_del(t_env *env);
int				dbg_key_sup(t_env *env);

int				dbg_key_cn_up(t_env *env);
int				dbg_key_cn_down(t_env *env);
int				dbg_key_cn_right(t_env *env);
int				dbg_key_cn_left(t_env *env);

int				dbg_key_ret(t_env *env);
int				dbg_key_cn_d(t_env *env);
/*
** KEY FUNCTION PROTOTYPE END ---
*/


void			sh_cursor_move(int x, int y);
void			edl_key_assoc(t_edl *edl);
void			edl_fun_assoc(t_edl *edl);
int				edl_controller(t_env *env);
int				ft_str_in_array(char *str, char **row);
void			sh_term_switch(struct termios term, int mode);

#endif
