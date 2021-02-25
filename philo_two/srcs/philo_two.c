/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:54:50 by user42            #+#    #+#             */
/*   Updated: 2021/02/25 21:02:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	philo_loop2(t_philo *philo)
{
	sem_wait(philo->fork);
	print_msg(philo, 0);
	print_msg(philo, 0);
	philo->tmp_eat = ft_time();
	print_msg(philo, 1);
	custom_usleep(philo->time_to_eat);
	philo->eaten++;
	sem_post(philo->fork);
	print_msg(philo, 2);
	custom_usleep(philo->time_to_sleep);
	print_msg(philo, 3);
}

void		*philo_loop(void *arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)arg;
	philo->tmp_eat = philo->time;
	philo->eaten = 0;
	pthread_create(&tid, NULL, death_loop, philo);
	while (*philo->no_run && \
	(philo->eat_count == -1 || philo->eat_count > philo->eaten))
		philo_loop2(philo);
	return (NULL);
}

void		*death_loop(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (*philo->no_run)
	{
		if (philo->eat_count != -1 && philo->eaten >= philo->eat_count)
		{
			custom_usleep(philo->id);
			sem_post(philo->eating);
			return (NULL);
		}
		else if (philo->time_to_die < ft_time() - philo->tmp_eat)
		{
			print_msg(philo, 4);
			sem_post(philo->death);
			return (NULL);
		}
	}
	return (NULL);
}

void		*meal_loop(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (philo->eat_count != 0 && i < philo->nb)
	{
		sem_wait(philo->eating);
		i++;
	}
	*philo->no_run = 0;
	printf("%ld: Everyone has eaten enough !\n", current_stamp(philo->time));
	sem_post(philo->death);
	return (NULL);
}
