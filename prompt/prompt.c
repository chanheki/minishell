
#include "../include/minishell.h"


/*
 * Description: 쉘 초기 세팅을 진행한다.
 *            : 쉘 실행시 나오는 ASCII art 표시
 */
void	initialize_setting(void)
{
	ft_putstr_fd(JIPHEADER, 2);
	set_signal();
	set_termianl();
}

/*
 * Description: 전역변수 초기화
 *            : 미니쉘 실행시 입력되는 초기값들을 전역변수에 저장한다.
 *            : env같은 경우는 dictionary 자료구조로 저장.
 * Param.   #1: argc - 미니쉘 실행시 입력되는 커맨드의 수
 * Param.   #2: argv - 미니쉘 실행시 입력되는 커맨드
 * Param.   #3: env - 실행시 해당 쉘로부터 가져오는 env
 */
void	initialize_global_variable(int argc, char **argv, char **env)
{
	g_var.argv = argv;
	g_var.argc = argc;
	g_var.envp = env;
	g_var.exit_status = 0;
}

/*
 * Description: 쉘 실행 시 예외처리.
 *            : 미니쉘 실행시 입력되는 초기값들로 실행 예외처리.
 *            : 현재까지 진행사항이 잘못되면 더 이상 쉘을 진행할 수 없도록 막는다.
 */
void	validator(void)
{	
	if (g_var.exit_status == -1)
	{
		ft_putendl_fd("JIP-shell: Terminal Setting Error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (g_var.argc > 1)
	{
		ft_putendl_fd("JIP-shell: Do not support this mode", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}


/*
 * Description: check signal EOF
 * Param.   #1: readline으로 들어온 str
 *            : ctrl+d은 EOF signal이고, 쉘을 종료하는 명령어로 사용된다. 쉘을 정상 종료한다.
 */
void	check_signal_eof(char *str)
{
	if (str == NULL)
	{
		ft_putendl_fd("\x1b[1A\033[12Cexit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}
