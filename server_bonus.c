/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelmokh <ybelmokh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:00:20 by ybelmokh          #+#    #+#             */
/*   Updated: 2022/03/31 00:27:58 by ybelmokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pid;

static int	convert_bits(int pos)
{
	int	i;
	int	j;

	if (!pos)
		return (1);
	i = 2;
	j = 2;
	while (pos > 1)
	{
		i = i * j;
		pos--;
	}
	return (i);
}

static	void	handler(int sig, siginfo_t *id, void *empty)
{
	static int	sum;
	static int	pos;

	(void)empty;
	if (g_pid != id->si_pid)
	{
		pos = 7;
		sum = 0;
	}
	if (sig == SIGUSR1)
	{
		sum += convert_bits(pos);
		pos--;
	}
	else
		pos--;
	if (pos == -1)
	{
		ft_putchar_fd(sum, 1);
		pos = 7;
		sum = 0;
	}
	g_pid = id->si_pid;
}

int	main(void)
{
	struct sigaction	sa;
	int					i;

	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	while (1)
	{
		if (i != g_pid)
		{
			i = g_pid;
			kill(g_pid, SIGUSR2);
		}
		pause();
	}
	return (0);
}
