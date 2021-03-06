/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:55:21 by epresa-c          #+#    #+#             */
/*   Updated: 2022/03/18 11:05:47 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_print_bits(char *bits)
{
	int		pow;
	char	c;
	int		i;

	pow = 1;
	c = 0;
	i = 7;
	while (i + 1 > 0)
	{
		c = c + (pow * (bits[i] - '0'));
		pow = pow * 2;
		i--;
	}
	write(1, &c, 1);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

void	ft_putnbr(unsigned int i)
{
	char	*base_set;

	base_set = "0123456789";
	if (i / 10 > 0)
		ft_putnbr(i / 10);
	ft_putchar(base_set[i % 10]);
}

void	ft_read_binary(int sig)
{
	static char	bits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	static int	i = 0;

	if (sig == 30)
		bits[i++] = '1';
	else
		bits[i++] = '0';
	if (i == 8)
	{
		ft_print_bits(bits);
		i = 0;
		while (i < 8)
			bits[i++] = 0;
		i = 0;
	}
}

int	main(void)
{
	write(1, "Server PID: ", 13);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, ft_read_binary);
	signal(SIGUSR2, ft_read_binary);
	while (1)
		pause();
	return (0);
}
