#include "../include/parse.h"

void	print_tokens(t_token *token)
{
	t_token	*head;
	int		i;

	i = 1;
	head = token;
	while (head->next)
	{
		printf("%d: \n", i);
		printf("\tvalue: %s\n\ttype: %d\n\tis_in_dquote: %d\n\tis_in_quote: %d\n\tis_in_escape: %d\n\t",
			   head->value, head->type, head->is_in_dquote, head->is_in_quote, head->is_in_escape);
		head = head->next;
	}
}

void init_buffer(char *buffer, int length)
{
	int i;

	i = -1;
	while (++i < length)
		buffer[i] = 0;
}

int	main(void)
{
	char		*input;
	char		*trimmed;
	int 		read_bytes;
	t_token		*token;

	input = (char *)malloc(sizeof(char) * (BUFSIZ + 1));
	ft_putstr_fd("type command line => ", STDOUT_FILENO);
	while (1)
	{
		read_bytes = read(STDIN_FILENO, input, BUFSIZ);
		if (read_bytes < 1)
			break ;
		input[read_bytes] = '\0';
		trimmed = ft_strtrim(input, " ");
		token = tokenize_line(trimmed);
		print_tokens(token);
		free(trimmed);
		free_token_list(&token);
		init_buffer(input, read_bytes);
	}
	free(input);
	return (0);
}