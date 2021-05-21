/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 22:30:59 by jaeskim           #+#    #+#             */
/*   Updated: 2021/05/21 17:18:28 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <termcap.h>
# include <termios.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/ioctl.h>

# include <libft.h>
# include "minishell_type.h"

# include "parse.h"
# include "exec.h"
# include "util.h"
# include "cursor.h"
# include "envp.h"
# include "builtin.h"

# define TERM_ERROR	"Specify a terminal type with `setenv TERM <yourtype>'.\n"
# define TERM_SUCCES_ERR	"Could not access the termcap data base.\n"
# define TERM_NOT_DEFINE_PART1	"Terminal type `"
# define TERM_NOT_DEFINE_PART2	"' is not defined.\n"

# define ARROW_UP		4283163
# define ARROW_DOWN		4348699
# define CTRL_LEFT		25115
# define CTRL_RIGHT		26139
# define ARROW_LEFT		4479771
# define ARROW_RIGHT	4414235
# define DELETE			127
# define EOF_CHAR		'\4'
# define KEY_HOME		4741915
# define KEY_END		4610843
# define CLS			12

# define PS1	"minishell>"
# define PS2	"> "

extern t_minishell	g_sh;

void	exit_minishell(int exitcode);
void	init_minishell(char *envp[]);

#endif
