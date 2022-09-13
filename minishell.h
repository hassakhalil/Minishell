/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:23 by iakry             #+#    #+#             */
/*   Updated: 2022/09/13 12:12:10 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <signal.h>
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
#define EXEC 1
#define REDIR 2
#define PIPE 3

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
} t_redir;

typedef struct pipecmd
{
  int type;
  struct cmd *left;
  struct cmd *right;
} t_pip;

typedef struct execcmd
{
  int type;              // ' '
  char *argv[MAXARGS];
} t_exec;


// utils
char    *ft_strnstr(char	**big, char *little, size_t l);
char	  **ft_split(char const *s, char c);
char	  *ft_strjoin(char *s1, char *s2);
char	  *ft_strdup(const char *str);
size_t  ft_strlen(char *s);
char    *ft_strchr(const char *s, int c);
int     forkk(void);
char    *mkcopy(char *s, char *es);
void    errors(char *msg);
struct cmd* redircmd(struct cmd *subcmd, char *file, int mode, int type);
struct cmd* pipecmd(struct cmd *left, struct cmd *right);
struct cmd* execcmd(void);
struct cmd* parsecmd(char *s);
char	*get_next_line(int fd);

// path
struct env *envpath(char **env);
char    *getpath(char *buff);

// builtins
int      cd(char *buff);

// executor
void    executor(cmd *tree, env *envp, int *flag_out, int *flag_in, int *flag_pipe);
void    parsing_tester(cmd *result_tree);
int     check_in_files(cmd *first_redir);
void    find_in_redir(cmd *tree, int *flag_in);

//parser
struct cmd* parsepipe(char **ps, char *es);
struct cmd* parsecmd(char *s);
struct cmd* parseexec(char **ss, char *es);
struct cmd* parseredirs(struct cmd *cmd, char **ss, char *es);

//lexer
int       gettoken(char **ps, char *es, char **q, char **eq);
int       peek(char **ps, char *es, char *toks);

//signals
void    handler(int sig);

//heredoc
char    *create_heredoc(char *delimiter);

#endif
