/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:54:36 by epresa-c          #+#    #+#             */
/*   Updated: 2022/03/18 11:05:54 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi_simplified(const char *str)
{
	int	result;

	result = 0;
	while (*str)
		result = result * 10 + (*str++ - '0');
	return (result);
}

char	*ft_convert_char_to_bits(char c)
{
	static char	bits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int			i;

	i = 7;
	while (i + 1 > 0)
	{
		if (c % 2 == 1)
			bits[i--] = '1';
		else
			bits[i--] = '0';
		c = c / 2;
	}
	return (bits);
}

void	ft_send_bit(char *bits, int pid)
{
	size_t	i;

	i = 0;
	while (bits[i] != '\0')
	{
		if (bits[i] == '1')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*bits;
	int		i;

	i = 0;
	if (argc != 3)
		write(1, "Correct use of the client program: \
		./client [server pid] [string to send]\n", 74);
	else
	{
		pid = ft_atoi_simplified(argv[1]);
		while (argv[2][i] != '\0')
		{
			bits = ft_convert_char_to_bits(argv[2][i++]);
			ft_send_bit(bits, pid);
			usleep(80);
		}
	}
	return (0);
}
