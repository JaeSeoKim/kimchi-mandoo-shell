/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 12:22:59 by jaeskim           #+#    #+#             */
/*   Updated: 2021/05/11 12:46:05 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_util.h"

static char	*free_paths_char(char **paths)
{
	int		i;

	i = 0;
	while (paths[i])
		ft_free(paths[i++]);
	free(paths);
	return (PARSE_MALLOC);
}

static char	*check_path_cmd(char *cmd, char **paths, int i)
{
	int		fd;
	char	*path;

	path = ft_strjoin(paths[i], "/");
	if (!path)
		return (free_paths_char(paths));
	path = ft_strjoin_free(path, cmd, 1);
	if (!path)
		return (free_paths_char(paths));
	fd = open(path, O_RDONLY);
	if (fd > 2)
	{
		close(fd);
		free_paths_char(paths);
		return (path);
	}
	return ((char *)PARSE_CMD_NONE);
}

static char	*find_path_cmd(char *cmd)
{
	int		i;
	t_list	*path_env;
	char	**paths;
	char	*result;

	path_env = get_envp("PATH", g_sh.envp);
	if (!path_env || !ft_strchr(path_env->content, '='))
		return ((char *)PARSE_CMD_NONE);
	paths = ft_split(path_env->content + 5, ':');
	if (paths == NULL)
		return (PARSE_MALLOC);
	i = -1;
	while (paths[++i])
	{
		result = check_path_cmd(cmd, paths, i);
		if (!result || result != (char *)PARSE_CMD_NONE)
			return (result);
	}
	return ((char *)PARSE_CMD_NONE);
}

char	*parse_cmd(char *cmd)
{
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
		return (ft_strdup(cmd));
	return (find_path_cmd(cmd));
}
