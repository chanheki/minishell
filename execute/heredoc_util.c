/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 03:02:06 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 03:02:08 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*
 * Description: 영어 대문자 30글자를 난수로 생성하는 파일이름을 생성한다.
 * Return     : tmp_path뒤에 랜덤파일명을 붙인 문자열을 반환한다.
 *            : ex) /jipshell/tmp/EUHUSFIUUEESDNHJFLVTTFERHNKHEA
 */
static char	*generate_random_heredoc_filename(void)
{
	char	*res;
	char	*path;
	int		fd;
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	res = (char *)ft_calloc(sizeof(char), 31);
	read(fd, res, 30);
	if (!res || close(fd) < 0)
	{
		free(res);
		return (NULL);
	}
	i = 31;
	while (--i)
		res[i] = ft_abs(res[i]) % 26 + 'A';
	res[0] = '/';
	path = ft_strjoin(g_var.tmp_path, res);
	free(res);
	return (path);
}

/*
 * Description: heredoc readline(fd, delimiter)
 *            : 랜덤 생성된 파일의 fd를 받아오고 기록
 *            : deliiter를 받아와서 line과 비교하여 heredoc 종료
 * Param.   #1: fd(랜덤 생성 파일의 fd)
 * Param.   #2: heredoc의 delimiter (좌측 자식 노드)
 */
static void	heredoc_readline(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter) || g_var.is_signal)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

/*
 * Description: node value를 변경한다.
 *            : delimiter가 있던 자리를 
 *            : random file name의 path로 교체한다.
 * Param.   #1: node(<<)
 * Param.   #2: random_file_name_path 
 */
static void	replace_node_value(t_ASTnode *node, char *random_file_name_path)
{
	t_token	*path;

	path = node->left->token;
	path->value = NULL;
	free(path->value);
	path->value = random_file_name_path;
}

/*
 * Description: heredoc (node)
 *            : << node가 들어오면 왼쪽 자식 노드가 delimiter고
 *            : 30자리 난수 대문자를 파일이름으로 갖는 파일을 생성해서
 *            : 해당 파일에 heredoc을 임시 저장하고, 해당하는 파일을 교체한다.
 *            : ctrl+c시그널이 들어오면 난수파일을 삭제한다.
 * Param.   #1: node (<<)
 * Return     : SUCCESS : 성공
 *            : ERROR: 실패
 */
t_error	execute_heredoc(t_ASTnode *node)
{
	char	*delimiter;
	char	*random_file_name_path;
	int		fd;

	delimiter = node->left->token->value;
	random_file_name_path = generate_random_heredoc_filename();
	if (!random_file_name_path)
		return (ERROR);
	fd = open(random_file_name_path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (ERROR);
	heredoc_readline(fd, delimiter);
	replace_node_value(node, random_file_name_path);
	if (g_var.is_signal)
		unlink(random_file_name_path);
	if (close(fd) == -1)
		return (ERROR);
	return (SUCCESS);
}
