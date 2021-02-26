/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/02/26 15:17:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

void	print_msg(t_philo *philo, int msg)
{
	char	*time;
	char	*id;

	if (*philo->died == 0)
		return ;
	time = ft_itoa(current_stamp(philo->time));
	id = ft_itoa(philo->id);
	pthread_mutex_lock(philo->msg);
	write(1, time, ft_strlen(time));
	write (1, ": philo #", 9);
	write(1, id, ft_strlen(id));
	// printf("%ld: Philo #%d ", current_stamp(philo->time), philo->id);
	if (!msg)
		write(1, " has taken a fork\n", 18);
	else if (msg == 1)
		write(1, " is eating\n", 11);
	else if (msg == 2)
		write(1, " is sleeping\n", 13);
	else if (msg == 3)
		write(1, " is thinking\n", 13);
	else
	{
		*philo->died = 0;
		write(1, " died\n", 6);
	}
	pthread_mutex_unlock(philo->msg);
	free(time);
	free(id);
}
