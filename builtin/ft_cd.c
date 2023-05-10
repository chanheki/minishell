#include "../include/minishell.h"

/*
 * Description: 환경 변수에 저장된 현재 작업 디렉토리를 변경한다.
 * Param.  #1 : 변경할 디렉토리 경로
 * Return     : 성공 시 0, 실패 시 1
 */
int	move_to_dir(char *path)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: cd: getcwd failed\n", 2);
		return (1);
	}
	if (!chdir(path))
	{
		delete_env("OLDPWD");
		set_env("OLDPWD", cwd);
		free(cwd);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory", 2);
		free(cwd);
		return (1);
	}
}

/*
 * Description: 환경 변수에 저장된 현재 작업 디렉토리를 변경한다.
 * Param.  #1 : 변경할 디렉토리 경로
 * Return     : 성공 시 0, 실패 시 1
 */
int	update_cwd(char *path)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: cd: getcwd failed\n", 2);
		return (1);
	}
	delete_env("PWD");
	set_env("PWD", path);
	free(cwd);
	return (0);
}

/*
 * Description: 환경 변수에 저장된 HOME으로 현재 작업 디렉토리를 변경한다.
 * Param.  #1 : 없음
 * Return     : 성공 시 0, 실패 시 1
 */
int	move_to_home(void)
{
	char	*home_path;

	home_path = find_value("HOME");
	if (!home_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (!chdir(home_path))
	{
		ft_putstr_fd("minishell: cd: change directory to HOME failed\n", 2);
		return (1);
	}
	return (update_cwd(home_path));
}

/*
 * Description: *path 값에 따라 현재 작업 디렉토리를 변경한다.
 * Param.  #1 : 변경할 디렉토리 경로
 * Return     : 성공 시 0, 실패 시 1
 */
int	ft_cd(char **path)
{
	if (!(*path) || !path || ft_strcmp(*path, "~"))
		return (move_to_home());
	else if (!ft_strcmp(*path, "-"))
		return (move_to_prev_dir());
	else if (!ft_strcmp(*path, "."))
		return (update_cwd(getcwd(NULL, 0)));
	else if (!ft_strcmp(*path, "/"))
		return (move_to_root());
	else
		return (move_to_dir(*path));
}
