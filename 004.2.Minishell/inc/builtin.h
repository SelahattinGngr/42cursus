/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:07:12 by segungor          #+#    #+#             */
/*   Updated: 2023/07/12 17:23:13 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include "global.h"

struct s_builtins
{
	char	*name;
	int		(*func)(int argc, char **argv);
};

int	builtin_check(char **argv);
int	builtin_exec(char **argv, bool subshell, t_list *l_free);
int	builtin_cd(int argc, char **argv);
int	builtin_echo(int argc, char **argv);
int	builtin_env(int argc, char **argv);
int	builtin_exit(int argc, char **argv, bool subshell, t_list *l_free);
int	builtin_export(int argc, char **argv);
int	builtin_pwd(int argc, char **argv);
int	builtin_unset(int argc, char **argv);

#endif
