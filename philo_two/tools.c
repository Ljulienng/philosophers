/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 18:23:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_atoi(const char *str)
{
	unsigned int	i;
	int				sign;
	int				num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' ||
				str[i] == '\r' || str[i] == ' ' || str[i] == '\f'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}

long	ft_time(void)
{
	struct timeval	time;
	long			ret;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000;
	ret += time.tv_usec / 1000;
	return (ret);
}

void	custom_usleep(int sleep_time)
{
	long	time;

	time = ft_time();
	while (sleep_time + time > ft_time())
		usleep(sleep_time);
}

long	current_stamp(long time)
{
	long	stamp;

	stamp = ft_time() - time;
	return (stamp);
}

void	print_msg(t_philo *philo, int msg)
{
	sem_wait(philo->msg);
	if (*philo->no_run == 0)
	{
		sem_wait(philo->msg);
		return ;
	}
	printf("%ld: Philo #%d ", current_stamp(philo->time), philo->id);
	if (!msg)
		printf("has taken a fork\n");
	else if (msg == 1)
		printf("is eating\n");
	else if (msg == 2)
		printf("is sleeping\n");
	else if (msg == 3)
		printf("is thinking\n");
	else if (msg == 4)
	{
		printf("died\n");
		*philo->no_run = 0;
	}
	sem_post(philo->msg);
}
