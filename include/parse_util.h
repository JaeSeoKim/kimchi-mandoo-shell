/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 13:41:05 by jaeskim           #+#    #+#             */
/*   Updated: 2021/05/11 12:52:48 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTIL_H
# define PARSE_UTIL_H

# include "minishell.h"

# define NO_COLOR "\e[0m"
# define TEXT_COLOR "\e[38;2;255;121;198m"
# define VALUE_COLOR "\e[38;2;189;147;249m"

# define TK_IFS		" \n\t"
# define TK_NONE	0
# define TK_QOUTE	1
# define TK_QOUTES	2
# define TK_ESCAPE	4

# define LX_NONE		0
# define LX_POSSIBLE	1
# define LX_CMD			2
# define LX_ARG			4
# define LX_REDIRECT	8
# define LX_FILE		16
# define LX_PIPE		32
# define LX_CTR_OP		64
# define LX_SEPERATOR	128

typedef struct s_token
{
	int		type;
	char	*value;
}	t_token;

char	*get_token(char **line);
char	*get_static_token(char **line, int *status);
t_list	*lexical_analyzer(char *line);
t_list	*syntax_analyzer(t_list *type);

t_AST	*syntax_cmd(t_list **token);
t_AST	*syntax_AST(t_list **token);

void	print_AST(t_AST	*AST, int depth);
void	print_depth(int depth);

#endif
