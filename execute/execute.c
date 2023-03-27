#include "../include/minishell.h"

t_global	g_var;

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

void	execute_(char *str)
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

void	execute_validator_handler(char *cmd, t_exitcode errcode)
{
	if (errcode == EXIT_COMMAND_NOT_FOUND)
	{
		ft_putstr_fd("jip: ", STDOUT_FILENO);
		ft_putstr_fd(cmd, STDOUT_FILENO);
		ft_putstr_fd(": command not found \n", STDERR_FILENO);
	}
	g_var.exit_status = EXIT_COMMAND_NOT_FOUND;

}
void exec_cmd_list(t_cmd_list *exec_cmd_list)
{
	(void)(exec_cmd_list);
}

void	execute(t_ASTnode *cmdTree)
{
	// 재귀로 구현하는게 편할지 다시 생각해 볼 것.
	t_ASTnode	*cmd;
	t_cmd_list	*cmd_list;
	int			excute_count;

	cmd_list = NULL;
	cmd = cmdTree;

	if (cmdTree == NULL || cmd->token == NULL)
		return ;

	while (cmd->token->type != NORMAL)
		cmd = cmd->left;
	// 여기서 left 타고  내려가는 cmd list 
	// 해당하는 리스트가 만들어졌으면 실행 
	
	if (cmd->token->type == DAMPERSAND && g_var.exit_status == 0)
	{
		// right 타고 내려가는 cmd list 실행.
		while (cmd->token->type != NORMAL)
			cmd = cmd->right;
	}
	else if (cmd->token->type == DPIPE && g_var.exit_status != 0)
	{
		// right 타고 내려가는 cmd list 실행.
		while (cmd->token->type != NORMAL)
			cmd = cmd->right;
	}

	excute_count = 0;
	while (true)	
	{
		if (check_builtin(cmd_list->cmd))
			exec_builtin(cmd_list);
		else if (!find_path(cmd_list->cmd))
			execute_validator_handler(cmd->token->value, EXIT_COMMAND_NOT_FOUND);
		else
			exec_cmd_list(cmd_list);
		if (!cmd_list->next_list->cmd)
		{
			execute_(cmd_list->cmd);
			break;
		}
		cmd_list = cmd_list->next_list;
		excute_count ++;
	}
	// 여기서 전부 실행 끝났는지 기다릴 것. (excute count 만큼 기다리고 마지막 값은 exit code로 넘겨주면 됨.)
}
