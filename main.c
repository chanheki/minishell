/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:00:36 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/14 15:11:55 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

t_global	g_var;

/*
 * Description: hosting_loop
 *            : 실질적으로 prompt 되는 구간. 
 *            : 이 쉘은 JIP-Shell 문자열을 프롬프트로 사용한다.
 *            : 명령어를 읽어들이고, parsing하고 excute하고 clear한다.
 */
static void	hosting_loop(void)
{
	char		*str;
	t_ASTnode	*root_node;

	while (1)
	{
		str = readline(PROMPT);
		if (str == NULL)
			check_signal_eof();
		if (ft_strcmp(str, "") == 0)
		{
			free(str);
			continue ;
		}
		add_history(str);
		root_node = parse_command_line(str);
		if (!root_node)
			continue ;
		execute(root_node);
		clear_nodes(&root_node);
		free(str);
	}
}

/*
 * Description: minishell main
 * Param.   #1: argc - 미니쉘 실행시 입력되는 커맨드의 수 (1개 초과시 에러)
 * Param.   #2: argv - 미니쉘 실행시 입력되는 커맨드 (1개 초과시 에러)
 * Param.   #3: env - 실행시 해당 쉘로부터 가져오는 env
 * Return     : 전역변수 g_var의 exit_status
 */
int	main(int argc, char **argv, char **envp)
{
	initialize_global_variable(argc, argv, envp);
	initialize_setting();
	validator();
	hosting_loop();
	return (g_var.exit_status);
}
