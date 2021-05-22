/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_ctrl_right_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 22:17:57 by jaeskim           #+#    #+#             */
/*   Updated: 2021/05/22 18:22:42 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	cursor_ctrl_right(void)
{
	while (g_sh.cmd_i < g_sh.cmd_s && g_sh.line[g_sh.cmd_i] == ' ')
	{
		cursor_right();
		++g_sh.cmd_i;
	}
	while (g_sh.cmd_i < g_sh.cmd_s && g_sh.line[g_sh.cmd_i] != ' ')
	{
		cursor_right();
		++g_sh.cmd_i;
	}
}
