#include "../include/parse.h"

int	main(void)
{
	char		*input;
	char		*trimmed;
	int 		read_bytes;
	t_token		*token;

	input = (char *)malloc(sizeof(char) * (BUFSIZ + 1));
	while (1)
	{
		ft_putstr_fd("type command line => ", STDOUT_FILENO);
		read_bytes = read(STDIN_FILENO, input, BUFSIZ);
		if (read_bytes < 1)
			break ;
		input[read_bytes] = '\0';
		trimmed = ft_strtrim(input, " \n");
		token = tokenize_line(trimmed);
		free(trimmed);
		if (is_valid_syntax(token))
			ft_putstr_fd("OK\n", STDOUT_FILENO);
		else
			ft_putstr_fd("KO\n", STDERR_FILENO);
		free_token_list(&token);
		ft_memset(input, 0, read_bytes);
	}
	free(input);
	return (0);
}
