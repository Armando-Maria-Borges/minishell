/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 04:01:08 by aborges           #+#    #+#             */
/*   Updated: 2024/10/23 12:22:58 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_comand(char **cmd, t_info **info, char **env)
{
	int	count_arg;
	int	k;

	k = 0;
	count_arg = ft_count(cmd);
	if (ft_redirect(cmd, count_arg, info, env))
		return (1);
	else if (ft_strcmp(cmd[k], "pwd"))
		ft_pwd(count_arg);
	else if (ft_strcmp(cmd[k], "env"))
		ft_env(count_arg, cmd, info);
	else if (ft_strcmp(cmd[k], "exit"))
		ft_exit(cmd, count_arg);
	else if (ft_strcmp(cmd[k], "echo"))
		ft_echo(cmd, count_arg, info);
	else if (ft_strcmp(cmd[k], "cd"))
		ft_cd(cmd, count_arg);
	else if (ft_strcmp(cmd[k], "export"))
		ft_export(cmd, count_arg, info);
	else if (ft_strcmp(cmd[k], "unset"))
		ft_unset(cmd, count_arg, info);
	else if (!execute_cmd(cmd, count_arg, info, env))
	{
		printf("nao encontrou o comando\n");
		return (0);
	}
	return (1);
}

int	check_arg(char *arg, t_info **info, char **env)
{
	char	**result;

	result = ft_split(arg);
	if (!result)
	{
		result = NULL;
		return (0);
	}
	if (ft_count(result) >= 1)
	{
		if (!check_comand(result, info, env))
			printf("zsh: command not found: %s\n", result[0]);
	}
	result = NULL;
	return (1);
}
