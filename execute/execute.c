
#include "../include/minishell.h"

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(g_var.envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(g_var.envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	_execute(char *argv)
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0]);
	i = -1;
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		perror("path error");
	}
	if (execve(path, cmd, g_var.envp) == -1)
		perror("execve error");
}

void	execute(char *str)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		perror("pipe error");
	pid = fork();
	if (pid < 0)
		perror("fork error");
	if (pid == 0)
		_execute(str);
	if (wait(&pid) == -1)
		perror("waitpid error");
}