/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjung <yjung@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:13:05 by yjung             #+#    #+#             */
/*   Updated: 2021/05/17 19:53:28 by yjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pwd_store(void)
{
	char	name[PATH_MAX];
	char	*path;

	if (getcwd(name, PATH_MAX) == NULL)
		return (OPEN_FAIL);
	path = ft_strjoin("PWD=", name);
	if (path == NULL)
		return (MALLOC_FAIL);
	if (set_envp(path) == MALLOC_FAIL)
	{
		free(path);
		return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

static int	cd_home_dir(void)
{
	int		status;
	char	*path;

	path = get_envp_value("HOME");
	if (path == NULL)
		return (MALLOC_FAIL);
	status = chdir(path);
	free(path);
	return (SUCCESS);
}

static int	cd_args_dir(t_list *args)
{
	int		status;
	char	*path;

	path = strdup(args->content);
	if (path == NULL)
		return (MALLOC_FAIL);
	status = chdir(path);
	free(path);
	if (status < 0)
	{
		ft_error_print("cd", strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}

int	ft_cd(t_list *args)
{
	int		status;

	status = 0;
	if (!args)
		status = cd_home_dir();
	else
		status = cd_args_dir(args);
	if (status == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (pwd_store() == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}
