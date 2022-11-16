/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhousse <abhousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:14:36 by abhousse          #+#    #+#             */
/*   Updated: 2022/03/09 19:41:45 by abhousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_ref = 0b10000000;

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
			kill (precedent, SIGUSR1);
			write (1, "\n", 1);
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
