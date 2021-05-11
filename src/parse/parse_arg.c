/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 09:31:53 by jaeskim           #+#    #+#             */
/*   Updated: 2021/05/11 14:11:04 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*destrocter(t_list *token, t_list *file, int err)
{
	if (token)
		ft_lstclear(&token, ft_free);
	if (file)
		ft_lstclear(&token, ft_none);
	return (err);
}

static t_list	*tokenizer_arg(char *arg)
{
	t_list	**curr;
	t_list	*token;

	token = NULL;
	curr = &token;
	while (*arg)
	{
		if (!ft_malloc((void **)curr, sizeof(t_list)))
			return (destrocter(token, NULL, PARSE_MALLOC));
		if (*arg != '*')
		{
			(*curr)->content = normalize(&arg, NORMALIZE_ARG);
			if ((*curr)->content == NULL)
				return (destrocter(token, NULL, PARSE_MALLOC));
		}
		else
			++arg;
		curr = &(*curr)->next;
	}
	return (token);
}

static t_list	*recursive_serch_file(
		t_list *token,
		t_list *file,
		char *path,
		int depth)
{
	DIR				*dir;
	t_list			*file;
	struct dirent	*entity;

	if (token == NULL)
		return (file);
	if (token->content == NULL)
		return (recursive_serch_file(token->next, file, path, depth + 1));
	dir = opendir(path);
	if (dir == NULL)
		return ((t_list *)PARSE_OPEN);
	entity = readdir(dir);
	while (entity)
	{
		if(token->next && token->next->content)
		entity = readdir(dir);
	}
	closedir(dir);
}

t_list	*find_file(t_list *token)
{
	int		wild_count;
	t_list	**curr;
	t_list	*file;

	file = NULL;
	curr = &file;
	while (token)
	{
		wild_count = 0;
		while (token && token->content == NULL)
		{
			++wild_count;
			token = token->next;
		}
		token = token->next;
	}
	return (file);
}

t_list	*parse_arg(char *arg)
{
	t_list	*token;
	t_list	*file;

	token = tokenizer_arg(arg);
	if (token == NULL)
		return (NULL);
	if (ft_lstsize(token) == 1 && token->content)
		return (token);
	file = find_file(token);
	if (file == PARSE_OPEN)
		return (destrocter(token, NULL, PARSE_MALLOC));
	if (file == NULL)
	{
		destrocter(token, NULL, PARSE_MALLOC);
		return (normalize(&arg, NORMALIZE_CMD));
	}
	return (file);
}
