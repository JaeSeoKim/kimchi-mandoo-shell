/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_evnp_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:51:06 by jaeskim           #+#    #+#             */
/*   Updated: 2021/05/11 12:52:40 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envp_value(char *name)
{
	char	*result;
	t_list	*home;

	home = get_envp(name, g_sh.envp);
	if (!home || !ft_strchr(home->content, '='))
		result = ft_strdup("");
	else
		result = ft_strdup(home->content + ft_strlen(name) + 1);
	return (result);
}
