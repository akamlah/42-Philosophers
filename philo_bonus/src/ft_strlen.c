/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicekamlah <alicekamlah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:52:04 by akamlah           #+#    #+#             */
/*   Updated: 2022/01/13 00:19:07 by alicekamlah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	slen;

	slen = 0;
	while (s[slen] != '\0')
		slen++;
	return (slen);
}
