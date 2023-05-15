/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:52:37 by yena              #+#    #+#             */
/*   Updated: 2023/05/11 05:02:05 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: 환경 변수에 저장된 현재 작업 디렉토리를 변경한다.
 * Param.  #1 : 변경할 디렉토리 경로
 * Return     : 성공 시 0, 실패 시 1
 */
int	move_to_dir(char *path)
{
	if (chdir(path))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (update_cwd());
}

/*
 * Description: 환경 변수에 저장된 현재 작업 디렉토리와 이전 디렉토리를 변경한다.
 * Param.  #1 : 변경할 디렉토리 경로
 * Return     : 성공 시 0, 실패 시 1
 */
int	update_cwd(void)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = find_value("PWD");
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: cd: PWD failed\n", 2);
		return (1);
	}
	if (set_env(ft_strdup("OLDPWD"), ft_strdup(oldpwd)) == ERROR)
	{
		ft_putstr_fd("minishell: cd: OLDPWD setenv failed\n", 2);
		return (1);
	}
	if (set_env(ft_strdup("PWD"), pwd) == ERROR)
	{
		ft_putstr_fd("minishell: cd: PWD setenv failed\n", 2);
		return (1);
	}
	return (0);
}

/*
 * Description: 환경 변수에 저장된 HOME으로 현재 작업 디렉토리를 변경한다.
 * Param.  #1 : 없음
 * Return     : 성공 시 0, 실패 시 1
 */
int	move_to_home(void)
{
	char	*home_path;

	home_path = find_value("HOME");
	if (!home_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home_path))
	{
		ft_putstr_fd("minishell: cd: change directory to HOME failed\n", 2);
		return (1);
	}
	return (update_cwd());
}

/*
 * Description: 환경 변수에 저장된 OLDPWD로 현재 작업 디렉토리를 변경한다.
 * Param.  #1 : 없음
 * Return     : 성공 시 0, 실패 시 1
 */
int	move_to_prev_dir(void)
{
	char	*oldpwd;

	oldpwd = find_value("OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(oldpwd))
	{
		ft_putstr_fd("minishell: cd: change directory to OLDPWD failed\n", 2);
		return (1);
	}
	return (update_cwd());
}

/*
 * Description: *path 값에 따라 현재 작업 디렉토리를 변경한다.
 * Param.  #1 : 변경할 디렉토리 경로
 * Return     : 성공 시 0, 실패 시 1
 */
int	ft_cd(char **path)
{
	if (!(*path) || !path || !ft_strcmp(*path, "~"))
		return (move_to_home());
	else if (!ft_strcmp(*path, "-"))
		return (move_to_prev_dir());
	else if (!ft_strcmp(*path, "."))
		return (update_cwd());
	else
		return (move_to_dir(*path));
}
