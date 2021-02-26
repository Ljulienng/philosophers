/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:07:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/26 15:32:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static char	*ft_itoa_bis(int count, int sign, int div, long nb)
{
	char	*s;
	long	res;
	int		i;

	res = 0;
	i = 0;
	if (!(s = malloc(sizeof(char) * (count + 1 + sign + 1))))
		return (NULL);
	if (sign == 1)
		s[i++] = '-';
	while (div > 0)
	{
		res = (nb / div) % 10;
		s[i++] = res + 48;
		div = div / 10;
	}
	s[i] = '\0';
	return (s);
}

char		*ft_itoa(long n)
{
	int		div;
	int		count;
	int		sign;
	long	nb;

	div = 1;
	sign = 0;
	count = 0;
	nb = (long)n;
	if (nb < 0)
	{
		sign++;
		nb *= -1;
	}
	while (nb / div >= 10)
	{
		div = div * 10;
		count++;
	}
	return (ft_itoa_bis(count, sign, div, nb));
}

int			ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long		current_stamp(long time)
{
	long	stamp;

	stamp = ft_time() - time;
	return (stamp);
}
