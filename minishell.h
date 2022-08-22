/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:23 by iakry             #+#    #+#             */
/*   Updated: 2022/08/21 17:51:13 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <assert.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAXARGS 10

typedef struct env
{
  char **path;
} env;

typedef struct cmd
{
  int type;
} cmd;

typedef struct redircmd
{
  int type;
  struct cmd *cmd;
  char *file;
  int mode;
  int fd;
} redir;

typedef struct pipecmd
{
  int type;
  struct cmd *left;
  struct cmd *right;
} pip;

typedef struct execcmd
{
  int type;              // ' '
  char *argv[MAXARGS];
} exec;


// libft
char    *ft_strnstr(char	**big, char *little, size_t l);
char	  **ft_split(char const *s, char c);
char	  *ft_strjoin(char *s1, char *s2);
char	  *ft_strdup(const char *str);

// utils
size_t  ft_strlen(char *s);
char    *ft_strchr(const char *s, int c);
void	  err_putchar(char *s);
int     forkk(void);
char    *mkcopy(char *s, char *es);

// utils2
void    printheader();
//void	  handle_sig(int sig);

// path
struct env *envpath(char **env);
char    *getpath(char *buff);

// builtins
int      cd(char *buff);

// execution
void      runcmd(struct cmd *cmd, struct env *envp);
int       run(struct execcmd *ecmd, struct env *envp);
void    executor(cmd *result_tree, env *envp);

// lexer
struct cmd* parsepipe(char **ps, char *es);
struct cmd* parsecmd(char *s);
struct cmd* parseline(char **ss, char *es);
struct cmd* parseexec(char **ss, char *es);
struct cmd* parseblock(char **ss, char *es);
struct cmd* parseredirs(struct cmd *cmd, char **ss, char *es);

// tokenizer
int       gettoken(char **ps, char *es, char **q, char **eq);
int       peek(char **ps, char *es, char *toks);

// parser
struct cmd* redircmd(struct cmd *subcmd, char *file, int mode, int type);
struct cmd* pipecmd(struct cmd *left, struct cmd *right);
struct cmd* execcmd(void);

#endif