/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:51:57 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/13 00:19:11 by alicekamlah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers_bonus.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	n;
	size_t	nlen;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nlen = 0;
	n = 0;
	while (str[nlen] <= '9' && str[nlen] >= '0')
	{
		n = n * 10 + str[nlen] - 48;
		nlen++;
	}
	return (sign * n);
}
