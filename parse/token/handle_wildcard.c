#include "../../include/minishell.h"

/*
 * Description: 유효한 와일드카드인지 확인한다.
 *              1. token_value와 dir_name이 같은지 확인한다.
*               2. token_value의 문자열이 끝났다면, dir_name의 문자열이 끝났는지 확인한다.
 *               2.1. token_value와 dir_name의 문자열이 길이는 같지만,
 *                    그 값이 다르다면(예: token_value = "*", dir_name = ".") true를 반환한다.
 *               2.2. token_value와 dir_name의 문자열이 길이가 다르다면 false를 반환한다.
 *              3. token_value의 문자열이 끝나지 않았다면, 토큰이 와일드카드일 때 아래의 동작을 수행한다.
 *               3.1. token_value[i]의 시작 인덱스와 dir_name[i]의 시작 인덱스를 하나씩 증가시킨다.
 *                    추가로 dir_name은 dir_idx만큼 더 증카시키고,
 *                    i + dir_idx가 dir_length이 될 때까지 2번~3번의 과정을 반복한다.
 *              4. 위의 과정을 거쳤음에도 불구하고, 유효한 와일드카드가 아니라면 false를 반환한다.
 * Param.   #1: 토큰의 포인터
 * Param.   #2: 토큰의 값
 * Param.   #3: 디렉토리 이름
 * Return     : true : 유효한 와일드카드
 *            : false: 유효하지 않은 와일드카드
 */
bool	is_valid_wildcard(t_token *token, char *token_value, char *dir_name)
{
	size_t	value_length;
	size_t	dir_length;
	size_t	i;
	size_t	dir_idx;

	value_length = ft_strlen(token_value);
	dir_length = ft_strlen(dir_name);
	i = 0;
	while (i < value_length && i < dir_length
		&& (token_value[i] == dir_name[i]))
		i++;
	if (i == value_length)
		return (i == dir_length);
	if (token->type == WILDCARD)
	{
		dir_idx = 0;
		while (i + dir_idx <= dir_length)
		{
			if (is_valid_wildcard(token, token_value + i + 1,
					dir_name + i + dir_idx))
				return (true);
			dir_idx++;
		}
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
int	interpret_wildcard(t_ASTnode **node)
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
		if (is_valid_wildcard((*node)->token, (*node)->token->value,
				dirent->d_name)
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
	if (!ast_tree)
		return (SUCCESS);
	if (ast_tree->token->type == NORMAL && ast_tree->token->value)
	{
		if (handle_wildcard(ast_tree->left) == ERROR
			|| handle_wildcard(ast_tree->right) == ERROR)
			return (ERROR);
		if (!ft_strchr(ast_tree->token->value, WILDCARD))
			return (SUCCESS);
		ast_tree->token->type = WILDCARD;
		if (interpret_wildcard(&ast_tree) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
