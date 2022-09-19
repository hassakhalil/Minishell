/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:23 by iakry             #+#    #+#             */
/*   Updated: 2022/09/17 18:32:39 by hkhalil          ###   ########.fr       */
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

extern int GLOBAL;

typedef struct s_env
{
  char **path;
} t_env;

typedef struct s_cmd
{
  int type;
} t_cmd;

typedef struct s_redircmd
{
  int type;
  t_cmd *cmd;
  char *file;
  int mode;
  int fd;
} t_redir;

typedef struct s_pipecmd
{
  int type;
  t_cmd *left;
  t_cmd *right;
} t_pip;

typedef struct s_execcmd
{
  int type;              // ' '
  char *argv[MAXARGS];
} t_exec;


// libft utils
char    *ft_strnstr(char	**big, char *little, size_t l);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	  **ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin2(char const *s1, char *s2);
char	  *ft_strdup(const char *str);
size_t  ft_strlen(const char *s);
char    *ft_strchr(const char *s, int c);
char	*ft_itoa(int n);

//minishell utils
int     forkk(void);
char    *mkcopy(char *s, char *es);
void    errors(char * name, char *msg);
t_cmd *redircmd(t_cmd *subcmd, char *file, int mode, int type);
t_cmd *pipecmd(t_cmd *left, t_cmd *right);
t_cmd  *execcmd(void);

// path
t_env *envpath(char **env);
char    *getpath(char *buff);

// builtins
int      cd(char *buff);

// executor
void    executor(t_cmd *tree, t_env *envp, int *flag_out, int *flag_in);
void    parsing_tester(t_cmd *result_tree);
int     check_in_files(t_cmd *first_redir);
void    find_in_redir(t_cmd *tree, int *flag_in);

//parser
t_cmd* parsepipe(char **ps, char *es);
t_cmd* parsecmd(char *s);
t_cmd* parseexec(char **ss, char *es);
t_cmd* parseredirs(t_cmd *cmd, char **ss, char *es);

//lexer
int       gettoken(char **ps, char *es, char **q, char **eq);
int       peek(char **ps, char *es, char *toks);

//expander
void    expander(t_cmd *tree, char **env);

//signals
void    handler(int sig);

//heredoc
char    *create_heredoc(char *delimiter);
//readline
void rl_replace_line (const char *text, int clear_undo);

#endif
