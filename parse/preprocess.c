#include "minishell.h"

void	delete_quotes(char *line)
{

}

void	interpret_dollar_sign(char *line)
{

}

void	preprocess_line(char *line)
{
	delete_quotes(line);
	interpret_dollar_sign(line);
}
