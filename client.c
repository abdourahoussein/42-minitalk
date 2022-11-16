/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhousse <abhousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:05:02 by abhousse          #+#    #+#             */
/*   Updated: 2022/03/10 02:33:04 by abhousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// donne le message;
#include "minitalk.h"

int	g_ref = 128;

void	ft_message(int i, char **str, int *len)
{
	while (i < 8)
	{
		if ((g_ref & str[2][*len]) == 0)
		{
			if (kill(ft_atoi(str[1]), SIGUSR1) == -1)
			{
				write (1, "pid invalid\n", 13);
				exit(1);
			}
		}
		else
		{
			if (kill(ft_atoi(str[1]), SIGUSR2) == -1)
			{
				write (1, "pid invalid\n", 13);
				exit(1);
			}
		}
		usleep(500);
		g_ref = g_ref >> 1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		len;

	len = 0;
	if (argc != 3)
	{
		write (1, "nombre des arguments invalides\n", 33);
		exit (1);
	}
	if (ft_atoi(argv[1]) <= 0)
		return (write (1, "pid invalid\n", 13), 0);
	while (len <= ft_strlen(argv[2]))
	{
		i = 0;
		g_ref = 128;
		ft_message(i, argv, &len);
		len++;
	}
	i = 0;
}
