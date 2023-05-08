#include "../include/minishell.h"

/*
 * Description: infile
 *            : path를 읽어 입력으로 사용한다.
 *            : heredoc의 경우 입력을 보내고 임시 파일을 삭제한다.
 * Param.   #1: path (redirect의 좌측 자식 노드)
 *            : heredoc 여부
 * Return     : ft_dup2의 성공여부 값.
 */
static t_error	set_infile(char *path, bool heredoc)
{
	int	in_fd;

	in_fd = open(path, O_RDONLY, 0644);
	if (in_fd == -1)
	{
		ft_putstr_fd("JIP-Shell: ", 2);
		perror(path);
		return (ERROR);
	}
	if (heredoc)
		unlink(path);
	return (ft_dup2(in_fd, STDIN_FILENO));
}

/*
 * Description: outfile
 *            : path를 읽어 출력으로 사용한다.
 *            : trunc의 경우 출력을 덮어씌운다.
 *            : append의 경우 출력을 추가한다.
 * Param.   #1: path (redirect의 좌측 자식 노드)
 *            : type trunc, append
 * Return     : ft_dup2의 성공여부 값.
 */
static t_error	set_outfile(char *path, bool type)
{
	int			out_fd;
	const bool	trunc = false;
	const bool	append = true;

	out_fd = -1;
	if (type == trunc)
		out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == append)
		out_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd == -1)
		return (ERROR);
	return (ft_dup2(out_fd, STDOUT_FILENO));
}

/*
 * Description: redirections의 경우.
 *            : 1. <  = infile
 *            : 2. << = heredoc
 *            : 3. >  = outfile
 *            : 4. >> = append outfile
 *            : 
 * Param.   #1: node (cmd)
 * Return     : SUCCES: ft_dup2의 성공값.
 *            : ERROR: 실패
 */
t_error	redirection(t_ASTnode *node)
{
	t_token	*token;
	char	*file;

	file = node->left->token->value;
	token = node->token;
	if (check_token_type(token, REDIRECT_IN))
		return (set_infile(file, false));
	else if (check_token_type(token, DREDIRECT_IN))
		return (set_infile(file, true));
	else if (check_token_type(token, REDIRECT_OUT))
		return (set_outfile(file, false));
	else if (check_token_type(token, DREDIRECT_OUT))
		return (set_outfile(file, true));
	return (ERROR);
}

/*
 * Description: redirect를 처리한다.
 *            : 우측 노드가 redirection의 경우.
 * Param.   #1: node (cmd)
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
t_error	redirect(t_ASTnode *node)
{
	if (!node)
		return (ERROR);
	node = node->right;
	while (node)
	{
		if (redirection(node) == ERROR)
			return (ERROR);
		node = node->right;
	}
	return (SUCCESS);
}
