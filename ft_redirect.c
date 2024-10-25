/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborges <aborges@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:29:57 by aborges           #+#    #+#             */
/*   Updated: 2024/10/17 15:15:43 by aborges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect(char **cmd, int count_arg, t_info **info, char **env)
{
	char	*new_input;
	int		k;
	int		i;
	int		j;
	int		file1;
	int		file2;
	int		saved_stdin;
	int		saved_stdout;
	char	**new_cmd;
	int		check_input = 0;
	(void)info;
	(void)env;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if ((*cmd[0] == '<' || (*cmd[0] == '<' && cmd[0][0 + 1] == '<')) && count_arg < 3)
		return (1);
	if (saved_stdin < 0 || saved_stdout < 0)
	{
		perror("Erro ao salvar descritores de arquivo");
		return (-1);
	}
	new_cmd = (char **)malloc(sizeof(char *) * (count_arg + 1));
	if (!new_cmd)
		return (-1);
	i = 0;
	while (i < count_arg)
	{
		if (*cmd[i] && *cmd[i] == '<' && cmd[i][i + 1] == '<')
		{
			while (1)
			{
				new_input = readline("> ");
				if (ft_strcmp(new_input, cmd[i + 1]))
					return (1);
				free(new_input);
			}
		}
		else if (*cmd[i] && *cmd[i] == '<' && *cmd[i + 1] != '<')
		{
			printf("O ficheiro: %s\n", cmd[i + 1]);
			file1 = open_file(cmd[i + 1], O_RDONLY, 0);
			if (file1 < 0)
			{
				perror("Erro ao abrir o arquivo para leitura");
				free(new_cmd);
				return (-1);
			}
			if (dup2(file1, STDIN_FILENO) < 0)
			{
				perror("Erro ao redirecionar entrada");
				close(file1);
				free(new_cmd);
				return (-1);
			}
			close(file1);
			j = 0;
			if (cmd[i + 2])
			{
				printf("\n1: %s \n", cmd[i + 2]);
				while (cmd[i + 2 + j])
				{
					printf("\n: %s \n", cmd[i + 2 + j]);
					new_cmd[j] = (char *)malloc(sizeof(char)
							* (ft_strlen(cmd[i + 2 + j]) + 1));
					if (!new_cmd[j])
					{
						k = 0;
						while (k < j)
						{
							free(new_cmd[k]);
							k++;
						}
						free(new_cmd);
						return (-1);
					}
					ft_strcpy(new_cmd[j], cmd[i + 2 + j]);
					j++;
				}
			}
			new_cmd[j] = NULL;
			check_input = 1;
		}
		else if (cmd[i][0] && cmd[i][0] == '>' && cmd[i][1] == '>')
		{
			file2 = open_file(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (file2 < 0)
			{
				perror("Erro ao abrir o arquivo para escrita");
				free(new_cmd);
				return (-1);
			}
			if (dup2(file2, STDOUT_FILENO) < 0)
			{
				perror("Erro ao redirecionar saída");
				close(file2);
				free(new_cmd);
				return (-1);
			}
			close(file2);
		}
		else if (*cmd[i] && *cmd[i] == '>')
		{
			file2 = open_file(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (file2 < 0)
			{
				perror("Erro ao abrir o arquivo para escrita");
				free(new_cmd);
				return (-1);
			}
			if (dup2(file2, STDOUT_FILENO) < 0)
			{
				perror("Erro ao redirecionar saída");
				close(file2);
				free(new_cmd);
				return (-1);
			}
			close(file2);
		}
		i++;
	}
	if (check_input && new_cmd[0])
	{
		execute_cmd(new_cmd, count_arg, info, env);//executando o comando
		if (dup2(saved_stdin, STDIN_FILENO) < 0
			|| dup2(saved_stdout, STDOUT_FILENO) < 0)
		{
			perror("Erro ao restaurar os descritores de arquivo");
			free(new_cmd);
			return (-1);
		}
		close(saved_stdin);
		close(saved_stdout);
		k = 0;
		while (new_cmd[k])
		{
			free(new_cmd[k]);
			k++;
		}
		free(new_cmd);
		return (1);
	}
	free(new_cmd);
	return (0);
}

int	open_file(const char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd < 0)
		perror("Erro ao abrir o arquivo");
	return (fd);
}

void	close_files(int file1, int file2, int pipefd[2])
{
	close(file1);
	close(file2);
	close(pipefd[0]);
	close(pipefd[1]);
}