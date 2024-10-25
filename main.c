/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:55:19 by aborges           #+#    #+#             */
/*   Updated: 2024/10/16 15:57:39 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_env(t_info **info, char **env)
{
	t_info	*tmp;
	int		i;

	*info = NULL;
	i = 0;
	while (env[i])
	{
		tmp = (t_info *)malloc(sizeof(t_info));
		if (!tmp)
			return (0);
		tmp->indice = i;
		tmp->value = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!tmp->value)
		{
			free(tmp);
			return (0);
		}
		strcpy(tmp->value, env[i]);
		tmp->next = *info;
		*info = tmp;
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	t_info	*info;
	char	*input;
	argv = argv;
	argc = argc;

	info = NULL;
	if (!fill_env(&info, env))
		return (1);
	while (1)
	{
		ft_signal();
		input = readline("aborges42> ");
		ft_ctrld(input);
		add_history(input);
		if (!check_arg(input, &info, env))
			break ;
		free(input);
	}
	return (0);
}

/*

< main.c cat > aaa.txt

< main.c ls -l >> outro.c
< main.c ls >> outro.c

./minishell < file.txt

./minishell ls >> output.txt

./minishell < input.txt cat

*/