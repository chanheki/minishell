#include "../include/minishell.h"

/*
 * Description: str로 들어온 문자열을 코드로 실행시킨다.
 */
static void	run_code(char *str)
{
	t_ASTnode	*root;

	root = parse_command_line(str);
	if (!root)
		return ;
	execute(root);
	clear_nodes(&root);
}

/*
 * Description: mkdir -p 옵션을 사용하여 디렉토리안에 디렉토리를 만든다.
 */
static t_error	ft_mkdir(void)
{
	char	*path;

	path = ft_strjoin("mkdir -p ", g_var.tmp_path);
	if (!path)
		return (ERROR);
	run_code(path);
	free(path);
	return (SUCCESS);
}

/*
 * Description: set tmp folder (cmdlist)
 *            : 현재 디렉토리 + tmp를 tmp_path로 잡고 dir을 생성한다.
 */
void	set_tmp(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		exit(1);
	g_var.tmp_path = ft_strjoin(path, "/tmp");
	free(path);
	if (!g_var.tmp_path || ft_mkdir() == ERROR)
		exit(1);
}

/*
 * Description: heredoc인지 체크한다.
              : line breaking
 */
static bool	is_heredoc(t_token *token)
{
	return (check_token_type(token, DREDIRECT_IN));
}

/*
 * Description: heredoc (cmdlist)
 *            : signal SIGINT를 heredoc의 시그널로 대체한다. ctrl+c
 *            : cmdlist를 돌면서, 해당 cmd에 heredoc node가 우측에 달렸는지 확인한다.
 *            : heredoc token type을 만나게 되면 heredoc을 실행한다.
 *            : ctrl+c시그널이 들어오면 prompt signal로 원상복구 시키고 fail을 반환한다.
 *            : 성공시에도 원상복구 시킨다.
 * Param.   #1: node (**cmd_list)
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
t_error	heredoc(t_ASTnode **cmd_list)
{
	int			i;
	t_ASTnode	*node;

	i = -1;
	if (signal(SIGINT, sigint_heredoc) == SIG_ERR)
		return (ERROR);
	while (cmd_list[++i])
	{
		node = cmd_list[i];
		while (node)
		{
			if (is_heredoc(node->token) && execute_heredoc(node) == ERROR)
				return (ERROR);
			if (g_var.is_signal)
			{
				g_var.is_signal = 0;
				signal(SIGINT, sigint_prompt);
				return (FAIL);
			}
			node = node->right;
		}
	}
	if (signal(SIGINT, sigint_prompt) == SIG_ERR)
		return (ERROR);
	return (SUCCESS);
}
