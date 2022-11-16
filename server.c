/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhousse <abhousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:05:06 by abhousse          #+#    #+#             */
/*   Updated: 2022/03/10 02:33:23 by abhousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_ref = 128;

void	init(int *precedent, char *c, int *i, siginfo_t *se)
{
	if (!*precedent)
		*precedent = se->si_pid;
	if (*precedent != se->si_pid)
	{
		*c = 0;
		g_ref = 128;
		*i = 0;
		*precedent = se->si_pid;
	}
}

void	ft_handler(int signal, siginfo_t *se, void *rien)
{
	static char	c;
	static int	i;
	static int	precedent;

	(void)rien;
	if (precedent != se->si_pid)
		init(&precedent, &c, &i, se);
	if (signal == SIGUSR2)
		c = c | g_ref;
	g_ref = g_ref >> 1;
	i++;
	if (i == 8)
	{
		write (1, &c, 1);
		if (!c)
		{
			write(1, "\n", 1);
		}
		c = 0;
		g_ref = 128;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr (getpid());
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_handler;
	sigemptyset(&sa.sa_mask);
	sigaction (SIGUSR1, &sa, NULL);
	sigaction (SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
