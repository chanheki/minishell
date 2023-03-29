#ifndef UTIL_H
# define UTIL_H

# define MINISHELLHEADER "\n\033[35m\
  ██╗██╗██████╗   ███╗   ███╗██╗███╗  ██╗██╗ ██████╗██╗  ██╗███████╗██╗     ██╗     \n\
 ██╔╝██║╚════██╗  ████╗ ████║██║████╗ ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔╝ ██║  ███╔═╝  ██╔████╔██║██║██╔██╗██║██║╚█████╗ ███████║█████╗  ██║     ██║     \n\
███████║██╔══╝    ██║╚██╔╝██║██║██║╚████║██║ ╚═══██╗██╔══██║██╔══╝  ██║     ██║     \n\
╚════██║███████╗  ██║ ╚═╝ ██║██║██║ ╚███║██║██████╔╝██║  ██║███████╗███████╗███████╗\n\
     ╚═╝╚══════╝  ╚═╝     ╚═╝╚═╝╚═╝  ╚══╝╚═╝╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
\033[37m\n\n"

# define JIPHEADER "\n\033[35m\
                                .-. .-') _  .-')    ('-.    _  .-')              .-. .-') _  .-')       ,-. \n\
                                \\  ( OO ( \\( -O )  ( OO ).-( \\( -O )             \\  ( OO ( \\( -O )      / / \n\
    .---.  .-----.,--.     ,-.-');-----.\\,------.  / . --. /,------.  ,--.   ,--.,--. ,--.,------.     / /\n\
   / .  | / ,-.   |  |.-') |  |OO| .-.  ||   /`. ' | \\-.  \\ |   /`. '  \\  `.'  / |  .'   /|   /`. '   / /\n\
  / /|  | '-'  |  |  | OO )|  |  | '-' /_|  /  | .-'-'  |  ||  /  | |.-')     /  |      /,|  /  | |  / /\n\
 / / |  |_   .'  /|  |`-' ||  |(_| .-. `.|  |_.' |\\| |_.'  ||  |_.' (OO  \\   /   |     ' _|  |_.' | / /\n\
/  '-'    |.'  /_(|  '---.,|  |_.| |  \\  |  .  '.' |  .-.  ||  .  '.'|   /  /\\_  |  .   \\ |  .  '.'/ /\n\
`----|  |-|       |      (_|  |  | '--'  |  |\\  \\  |  | |  ||  |\\  \\ `-./  /.__.-|  |\\   \\|  |\\  \\/ /\n\
     `--' `-------`------' `--'  `------'`--' '--' `--' `--'`--' '--'  `--'    `-`--' '--'`--' '--`-'\n\
\033[37m\n\n"


/*---------------------------------- UTILS ----------------------------------*/
int	token_typecheck(t_token *token, t_token_type type);
int	check_token_type_operator(t_token *token);

#endif