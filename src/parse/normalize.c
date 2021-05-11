/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 13:37:29 by jaeskim           #+#    #+#             */
/*   Updated: 2021/05/11 12:59:16 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_util.h"

static char	*joinstatus(char **token, char *result)
{
	char	*status;

	*token += 2;
	status = ft_itoa(g_sh.status);
	if (status == NULL)
		return (ft_free_ret(result, NULL));
	return (ft_strjoin_free(result, status, 3));
}

static char	*joinenv(char **token, char *result)
{
	t_list	*env;
	char	*key;

	if (!ft_strncmp(*token, "$?", 2))
		return (joinstatus(token, result));
	key = ft_strdup("");
	if (key == NULL)
		return (ft_free_ret(result, NULL));
	++(*token);
	while (**token && (ft_isalnum(**token) || **token == '_'))
	{
		key = ft_strappendc(key, **token);
		if (key == NULL)
			return (ft_free_ret(result, NULL));
		++(*token);
	}
	env = get_envp(key, g_sh.envp);
	if (env)
		result = ft_strjoin_free(result, env->content + ft_strlen(key) + 1, 1);
	free(key);
	--(*token);
	return (result);
}

static int	init_normalize(char **token, char **result, int *flag)
{
	*flag = TK_NONE;
	if (!ft_strncmp(*token, "~/", 2) || !ft_strcmp(*token, "~"))
	{
		*result = get_envp_value("HOME");
		++(*token);
	}
	else
		*result = ft_calloc(sizeof(char), 1);
	if (*result == NULL)
		return (0);
	return (1);
}

static int	handle_flag(char *token, int *flag)
{
	if (!(*flag & ~(TK_QOUTES)) && *token == '"')
	{
		*flag ^= TK_QOUTES;
		return (1);
	}
	else if (!(*flag & ~(TK_QOUTE)) && *token == '\'')
	{
		*flag ^= TK_QOUTE;
		return (1);
	}
	else if (!(*flag & ~(TK_QOUTE)) && *token == '\\')
	{
		*flag |= TK_ESCAPE;
		return (1);
	}
	*flag &= ~TK_ESCAPE;
	return (0);
}

char	*normalize(char **token, int type)
{
	int		flag;
	char	*result;

	flag = TK_NONE;
	if (!init_normalize(token, &result, &flag))
		return (NULL);
	while (**token)
	{
		if (type == NORMALIZE_ARG && flag == TK_NONE && **token == '*')
			break ;
		if (!handle_flag(*token, &flag))
		{
			if (!(flag & ~(TK_QOUTES)) && **token == '$' && (**token + 1) && \
				(!ft_strncmp(*token, "&?", 2) || ft_isalpha(*(*token + 1)) || \
				*(*token + 1) == '_'))
				result = joinenv(token, result);
			else
				result = ft_strappendc(result, **token);
			if (result == NULL)
				return (NULL);
		}
		++(*token);
	}
	return (result);
}
