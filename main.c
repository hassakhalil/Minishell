/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/10/15 20:20:51 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	GLOBAL;

int	complete_pipe(char *buff)
{
	int	i;
	int	c;
	int	k;

	i = 0;
	c = 0;
	k = 0;
	while (buff[i])
	{
		if (!is_white_space(buff[i]))
		{
			c = buff[i];
			if (c == '|')
			{
				if (++k > 1)
					return (1);
			}
			else if (k)
				k--;
		}
		i++;
	}
	if (c == '|')
		return (1);
	return (0);
}

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
	GLOBAL = 1;
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
		exit (GLOBAL);
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
		tree = parsecmd(buff, env_list, 1);
		free(buff);
        //parsing_tester(tree);
		executor(tree, &flag_out, &flag_in, env_list);
	}
	signal(SIGINT, SIG_IGN);
	wait(&exits);
	if ((WTERMSIG(exits) == 3 || WTERMSIG(exits) == 2) && GLOBAL != -1)
		GLOBAL = 128 + WTERMSIG(exits);
	else
	GLOBAL = WEXITSTATUS(exits);
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
