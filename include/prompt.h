/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:24:05 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/11 11:53:39 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"

void	initialize_setting(void);
void	initialize_global_variable(int argc, char **argv, char **env);
void	validator(void);
void	check_signal_eof(void);
#endif