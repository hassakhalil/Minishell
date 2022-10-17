/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/10/17 07:18:19 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_var;

int	empty_cmd(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if (!is_white_space(buff[i]))
			return (1);
		i++;
	}
	return (0);
}

void	handler(int sig)
{
	sig = 0;
	g_var = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

char	*ft_read(t_envvar **env_list)
{
	char	*buff;

	buff = readline("$ ");
	if (!buff)
	{
		free_env(env_list);
		write(1, "exit\n", 5);
		exit (g_var);
	}
	if (buff && *buff)
		add_history(buff);
	return (buff);
}

void	ft_child(char *buff, t_envvar **env_list)
{
	int		pid;
	int		exits;
	int		flag_in;
	int		flag_out;
	t_cmd	*tree;

	flag_in = 0;
	flag_out = 0;
	pid = forkk();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		tree = parsecmd(buff, env_list);
		free(buff);
		executor(tree, &flag_out, &flag_in, env_list);
	}
	signal(SIGINT, SIG_IGN);
	wait(&exits);
	if ((WTERMSIG(exits) == 3 || WTERMSIG(exits) == 2) && g_var != -1)
		g_var = 128 + WTERMSIG(exits);
	else
	g_var = WEXITSTATUS(exits);
}

int	main(int argc, char **argv, char **env)
{
	static char	*buff;
	t_envvar	*env_list;

	argv[argc] = 0;
	env_list = init_envvar(env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		buff = ft_read(&env_list);
		if (!empty_cmd(buff) || parent_builtin(buff, &env_list))
		{
			free(buff);
			continue ;
		}
		ft_child(buff, &env_list);
		free(buff);
	}
	return (0);
}
