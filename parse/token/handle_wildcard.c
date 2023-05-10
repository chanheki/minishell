/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:54:10 by yena              #+#    #+#             */
/*   Updated: 2023/05/10 20:54:11 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Description: 유효한 와일드카드인지 확인한다.
 * 				1. 패턴이 와일드카드가 아닐 때까지 디렉토리 이름과 비교한다.
 * 				 1.1. 디렉토리 이름이 와일드카드와 일치하지 않으면 false를 반환한다.
 * 				2. 패턴의 끝까지 확인하고 디렉토리의 이름도 끝까지 확인했다면 true, 아니라면 false를 반환한다.
 * 				3. 패턴이 와일드카드 일 때 와일드카드가 아닌 글자가 나올 때까지 패턴의 인덱스를 증가시킨다.
 * 				4. 디렉토리 이름이 패턴의 글자와 일치할 때, 해당 지점부터 1~3을 반복한다.
 * Param.   #1: 와일드카드 패턴 (ex. *.c)
 * Param.   #2: 디렉토리 이름
 * Param.   #3: 와일드카드 패턴의 인덱스
 * Param.   #4: 디렉토리 이름의 인덱스
 * Return     : true : 유효한 와일드카드
 *            : false: 유효하지 않은 와일드카드
 */
bool	is_valid_wildcard(char *wildcard_value, char *dir_name,
					size_t idx_w, size_t idx_d)
{
	while (wildcard_value[idx_w] && wildcard_value[idx_w] != WILDCARD)
	{
		if (wildcard_value[idx_w] != dir_name[idx_d])
			return (false);
		idx_w++;
		idx_d++;
	}
	if (!wildcard_value[idx_w])
		return (dir_name[idx_d] == '\0');
	while (wildcard_value[idx_w] == WILDCARD)
		idx_w++;
	if (!wildcard_value[idx_w])
		return (true);
	while (dir_name[idx_d])
	{
		if (dir_name[idx_d] == wildcard_value[idx_w]
			&& is_valid_wildcard(wildcard_value, dir_name, idx_w, idx_d))
			return (true);
		idx_d++;
	}
	return (false);
}

/*
 * Description: 와일드카드를 해석하여 토큰의 새로운 값으로 지정하거나, 노드를 생성하여 자식으로 지정한다.
 *              1. 첫 번째 디렉토리라면(= *dircount == 0) 토큰의 값을 dir_name(= ".")으로 변경한다.
 *              2. 첫 번째 디렉토리가 아니라면, 토큰을 생성하고, 노드를 생성하여 왼쪽 자식으로 지정한다.
 *               2.1. 루트 노드를 새로 생성한 노드로 지정한다.
 *              3. *dir_count를 1 증가시킨다.
 * Param.   #1: 와일드카드를 해석할 노드의 포인터
 * Param.   #2: 와일드카드를 해석한 횟수(= 디렉토리의 개수)
 * Param.   #3: 디렉토리 이름
 * Return     : SUCCESS: 와일드카드 해석 성공
 *            : ERROR  : 메모리 할당 실패
 */
int	rebuild_wildcard(t_ASTnode **node, int *dir_count, char *dir_name)
{
	t_token		*token;
	t_token		*new_token;
	t_ASTnode	*new_node;

	token = (*node)->token;
	if (*dir_count == 0)
	{
		free(token->value);
		token->value = ft_strdup(dir_name);
	}
	else
	{
		new_token = create_new_token(dir_name, WILDCARD);
		new_node = create_new_node(new_token);
		if (!new_node || !new_token)
			return (ERROR);
		add_node_to_direction(node, new_node, LEFT);
		*node = new_node;
	}
	(*dir_count)++;
	return (SUCCESS);
}

/*
 * Description: 와일드카드를 해석한다.
 *              1. 현재 디렉토리를 열고, 디렉토리를 읽는다.
 *              2. 디렉토리를 읽으면서, 유효한 와일드카드라면, 와일드카드를 해석한다.
 *               2.1. 해당 과정에서 에러가 발생하면, 디렉토리를 닫고 에러를 반환한다.
 *              3. 디렉토리를 닫는다.
 *              4. 디렉토리를 닫는데 실패하거나, errno가 설정되어 있다면 에러를 반환한다.
 *              5. 성공적으로 완료되었다면 SUCCESS를 반환한다.
 * Param.   #1: 와일드카드를 해석할 노드의 포인터
 * Return     : SUCCESS: 와일드카드 해석 성공
 *            : ERROR  : 와일드카드 해석 실패
 */
int	interpret_wildcard(char *wildcard_value, t_ASTnode **node)
{
	DIR						*dir;
	static struct dirent	*dirent;
	int						dir_count;

	dir = opendir(".");
	dir_count = 0;
	if (!dir)
		return (ERROR);
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (is_valid_wildcard(wildcard_value, dirent->d_name, 0, 0)
			&& rebuild_wildcard(node, &dir_count, dirent->d_name) == ERROR)
		{
			closedir(dir);
			return (ERROR);
		}
	}
	if (closedir(dir) == -1 || errno)
		return (ERROR);
	return (SUCCESS);
}

/*
 * Description: 와일드카드를 처리한다.
 *              1. 노드의 토큰이 NORMAL일 경우에만 와일드카드를 처리한다.
 *              2. 왼쪽 자식과 오른쪽 자식을 재귀적으로 처리한다.
 *              3. 와일드카드가 포함된 토큰이라면, 토큰의 타입을 WILDCARD로 변경하고, 와일드카드를 해석한다.
 *              4. 와일드카드 해석 과정에서 에러가 발생하면 에러를 반환한다.
 *              5. 성공적으로 완료되었다면 SUCCESS를 반환한다.
 * Param.   #1: 와일드카드를 처리할 노드의 포인터
 * Return     : SUCCESS: 와일드카드 처리 성공
 *            : ERROR  : 와일드카드 처리 실패
 */
int	handle_wildcard(t_ASTnode *ast_tree)
{
	char	*wildcard_value;

	if (!ast_tree || !ast_tree->token)
		return (SUCCESS);
	if (ast_tree->token->type == WILDCARD)
	{
		wildcard_value = ft_strdup(ast_tree->token->value);
		if (interpret_wildcard(wildcard_value, &ast_tree) == ERROR)
		{
			free(wildcard_value);
			return (ERROR);
		}
		free(wildcard_value);
	}
	if (handle_wildcard(ast_tree->left) == ERROR)
		return (ERROR);
	if (handle_wildcard(ast_tree->right) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
