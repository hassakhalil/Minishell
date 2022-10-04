/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:23 by iakry             #+#    #+#             */
/*   Updated: 2022/10/04 22:12:26 by hkhalil          ###   ########.fr       */
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
# include <errno.h>
 #include <dirent.h>

# define MAXARGS 100
#define EXEC 1
#define REDIR 2
#define PIPE 3

extern int GLOBAL;

typedef struct s_envvar
{
  char *name;
  char *value;
  struct s_envvar *next;
} t_envvar;

typedef struct s_localvar
{
  char *name;
  char *value;
  struct s_localvar *next;
} t_localvar;

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
  int type;
  char *argv[MAXARGS];
} t_exec;


// libft utils
char    *ft_strnstr(char	**big, char *little, size_t l);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	  **ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin2(char const *s1, char *s2);
char	*ft_strjoin3(char const *s1, char const *s2);
char	  *ft_strdup(const char *str);
size_t  ft_strlen(const char *s);
char    *ft_strchr(const char *s, int c);
char	*ft_itoa(int n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strncpy(char *dest, const char *src, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);

//minishell utils
int     forkk(void);
char    *mkcopy(char *s, char *es);
void    errors(char * name, int flag);
t_cmd *redircmd(t_cmd *subcmd, char *file, int mode, int type);
t_cmd *pipecmd(t_cmd *left, t_cmd *right);
t_cmd  *execcmd(void);
int empty_cmd(char *buff);
int complete_pipe(char *buff);

// path
t_env *envpath(void);
char    *getpath(char *buff);

// builtins
int builtin(char *buff, t_envvar *env_list);
t_envvar *init_envvar(char **env);
void ft_exit(t_exec *cmd);
void ft_cd(t_exec *cmd, t_envvar *env);
void ft_pwd(void);
int ft_check_for_pwd(char *s);
void ft_echo(t_exec *cmd);
int ft_check_for_echo(char *s);
void  ft_env(t_exec *cmd, t_envvar *env_list);
int ft_check_for_env(char *s);

// executor
void    executor(t_cmd *tree, char **env, t_env *envp, int *flag_out, int *flag_in, t_envvar *env_list);
void    parsing_tester(t_cmd *result_tree);
void     check_in_files(t_cmd *redir);
void    find_in_redir(t_cmd *tree);

//parser
t_cmd* parsepipe(char **ps, char *es);
t_cmd* parsecmd(char *s);
t_cmd* parseexec(char **ss, char *es);
t_cmd* parseredirs(t_cmd *cmd, char **ss, char *es);

//lexer
int       gettoken(char **ps, char *es, char **q, char **eq);
int       peek(char **ps, char *es, char *toks);

//expander
char  *expander(char *arg);
int is_white_space(int c);

//quotes
char    *quote_remover(char *s);

//signals
void    handler(int sig);

//heredoc
char    *create_heredoc(char *delimiter);
//readline
void rl_replace_line (const char *text, int clear_undo);

#endif
