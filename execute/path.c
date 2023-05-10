/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 03:02:23 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 03:02:23 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Description: join_cmd_path
 *            : cmd와 path을 join
 * Param.   #1: *path
 * Param.   #2: *cmd
 * Return     : cmd path 성공
 *            : NULL 실패
 */
static char	*join_cmd_path(char *path, char *cmd)
{
	char	*cmd_dir;
	char	*cmd_path;

	cmd_dir = ft_strjoin("/", cmd);
	if (!cmd_dir)
		return (NULL);
	cmd_path = ft_strjoin(path, cmd_dir);
	free(cmd_dir);
	cmd_dir = NULL;
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

/*
 * Description: parse_paths(**envp)
 *            : envp 에서 path를 찾는다.
 * Param.   #1: envp
 * Return     : **paths : 성공시 paths list 반환
 *            : NULL: 실패
 */
static char	**parse_paths(char **envp)
{
	char	**paths;

	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			break ;
		envp++;
	}
	if (*envp == NULL)
		return (NULL);
	paths = ft_split((*envp) + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

/*
 * Description: check_path
 *            : path list 에서 사용할 수 있는 path를 고른다.
 * Param.   #1: **path_list
 * Param.   #2: *cmd_name
 * Param.   #3: **path
 * Return     : SUCCESS 성공
 *            : ERROR 실패
 */
static int	check_path(char **path)
{
	if (!is_directory(*path) && access(*path, X_OK) == 0)
		return (1);
	free(*path);
	*path = NULL;
	return (0);
}

/*
 * Description: generate_path
 *            : path list 에서 사용할 수 있는 path를 고른다.
 * Param.   #1: **path_list
 * Param.   #2: *cmd_name
 * Param.   #3: **path
 * Return     : SUCCESS 성공
 *            : ERROR 실패
 */
static int	generate_path(char **path_list, char *cmd_name, char **path)
{
	int		i;

	i = 0;
	while (path_list[i])
	{
		*path = join_cmd_path(path_list[i], cmd_name);
		if (!(*path))
		{
			ft_split_free(path_list);
			path_list = NULL;
			return (FAIL);
		}
		if (check_path(path) == 1)
			return (SUCCESS);
		i++;
	}
	return (SUCCESS);
}

/*
 * Description: generate_cmd_path(name, path, env)
 *            : cmd name이 디렉토리 거나 access 할 수 있는지 확인한다.
 *            : 둘다 아니라면 envp의 path list를 만들어 확인한다.
 *            : 해당하는 path를 만들어 반환한다.
 * Param.   #1: node (root)
 * Return     : SUCCESS 성공
 *            : ERROR 실패
 */
t_error	generate_cmd_path(char *cmd_name, char **path, char **envp)
{
	char	**path_list;

	*path = NULL;
	if (!is_directory(cmd_name) && access(cmd_name, X_OK) == 0)
	{
		*path = ft_strdup(cmd_name);
		return (SUCCESS);
	}
	path_list = parse_paths(envp);
	if (!path_list)
		return (FAIL);
	if (generate_path(path_list, cmd_name, path) == -1)
		return (FAIL);
	ft_split_free(path_list);
	path_list = NULL;
	return (SUCCESS);
}
