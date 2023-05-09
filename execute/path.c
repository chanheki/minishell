#include "../include/minishell.h"

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

static int	check_path(char **path)
{
	if (!is_directory(*path) && access(*path, X_OK) == 0)
		return (1);
	free(*path);
	*path = NULL;
	return (0);
}

static int	make_path(char **path_list, char *cmd_name, char **path)
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
			return (-1);
		}
		if (check_path(path) == 1)
			return (0);
		i++;
	}
	return (0);
}

t_error	make_cmd_path(char *cmd_name, char **path, char **envp)
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
	if (make_path(path_list, cmd_name, path) == -1)
		return (FAIL);
	ft_split_free(path_list);
	path_list = NULL;
	return (SUCCESS);
}
