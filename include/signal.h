/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:24:09 by chanheki          #+#    #+#             */
/*   Updated: 2023/05/10 12:10:13 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"
# include "error.h"

t_error	set_signal(void);
void	sigint_prompt(int signumber);
void	sigint_heredoc(int signumber);

#endif