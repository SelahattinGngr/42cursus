/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:23:28 by segungor          #+#    #+#             */
/*   Updated: 2023/08/31 08:23:30 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tables.h"
# include "macros.h"
# include "builtin.h"
# include "unistd.h"

t_core	g_data;

t_lexlist		*add_new_lex_node(t_lexlist **cmd_table);
size_t			ft_strlen(const char *s);
size_t			trim_spaces(char **cmd_line);
t_env			*add_newenv(t_env **env_table, char *env);

void			parser(void);
void			print_parser(void);
void			lexer(void);
void			print_lexer(void);
void			update_loop(void);
void			update_history(char *cmd);
void			signalhandler(int sig);
void			print_error(char *ptr1, char *ptr2, char *ptr3);
void			create_cmdtable(t_lexlist *lex_table);
void			own_strjoin(char **dst, char *src);
void			str_addchar(char **dst, char c);
void			fill_cmdtable(void);
void			expand_cmd(char **dst);
void			create_files(t_cmdlist *node);
void			run_heradocs(t_cmdlist *node);
void			free_for_loop(void);
void			free_core(void);
void			syntax_check(void);
void			classify(t_lexlist *lex_table);
void			create_lexlist(char *cmdline, t_lexlist **lex_table);
void			free_lexer_without_heradoc(t_lexlist *stop_list);
void			expander(void);
void			expand_envs(char **dst, char *ptr);
void			expand_dollar(char **dst, char **src);
void			exec_command(t_cmdlist *cmd_node, int *fd, int fd_index);
void			clear_void_contents(void);
void			executer(void);
void			clear_pipe(int *fd);
void			create_dup(t_cmdlist *cmd_list, int *fd, int fd_index);
void			run_cd(t_cmdlist *cmd_node);
void			set_title(void);
void			change_title(void);
void			fill_envs(char **env);
void			free_metachars(void);
void			free_envtable(void);
void			free_title(void);
void			free_env_cpy(char **envlist);
void			run_process(t_cmdlist *cmd_list, int *fd, int fd_index);
void			wait_all(void);
void			close_heradoc_file(void);
void			init_core(char **env);

char			*get_env_name(char *content);
char			*get_missing_arg(void);
char			*compare_metachars(char *cmd_line);
char			*ft_strpcpy(char *dst, char *src, int count);
char			*ft_strdup(char *ptr);
char			*ft_itoa(int number);

int				print_lex_error(t_lexlist *lex_list);
int				str_compare(char *str1, char *str2);
int				create_new_filelist(t_cmdlist *node, t_lexlist **lex_list);
int				env_init(char **env);
int				line_count(char **str);
int				get_array_len(char **array);
int				env_arg_control(char *env);
int				update_env(char *env_name, char *new_arg);
int				ft_atoi(const char *str);

#endif
