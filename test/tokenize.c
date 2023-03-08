#include "../include/parse.h"

char	*int_to_bool_string(int i)
{
	if (!i)
		return ("false");
	else
		return ("true");
}

void	print_tokens(t_token *token)
{
	t_token	*head;
	int		i;

	i = 1;
	if (!token)
		return ;
	head = token;
	while (head)
	{
		printf("token %d info: \n", i);
		printf("\tvalue: %s\n", head->value);
		printf("\ttype: %d\n", head->type);
		printf("\tis_in_dquote: %s\n", int_to_bool_string(head->is_in_dquote));
		printf("\tis_in_quote: %s\n", int_to_bool_string(head->is_in_quote));
		printf("\tis_in_escape: %s\n", int_to_bool_string(head->is_in_escape));
		head = head->next;
		i++;
	}
	printf("\n");
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
	while (1)
	{
		ft_putstr_fd("type command line => ", STDOUT_FILENO);
		read_bytes = read(STDIN_FILENO, input, BUFSIZ);
		if (read_bytes < 1)
			break ;
		input[read_bytes] = '\0';
		trimmed = ft_strtrim(input, " \n");
		token = tokenize_line(trimmed);
		print_tokens(token);
		free(trimmed);
		free_token_list(&token);
		init_buffer(input, read_bytes);
	}
	free(input);
	return (0);
}