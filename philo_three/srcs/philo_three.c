/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:54:50 by user42            #+#    #+#             */
/*   Updated: 2021/03/06 13:51:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

void		philo_loop(t_philo philo)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, death_loop, &philo);
	pthread_detach(tid);
	while (philo.eat_count == -1 || \
	(philo.eat_count > 0 && philo.eat_count > philo.eaten))
		philo_loop2(&philo);
	usleep(10000000);
}

void		*death_loop(void *arg)
{
	t_philo *philo;
	int		var;

	philo = (t_philo *)arg;
	var = 1;
	while (42)
	{
		if (philo->eat_count != -1 && philo->eaten >= philo->eat_count && var)
		{
			sem_post(philo->eating);
			var = 0;
			return (NULL);
		}
		else if (philo->time_to_die < ft_time() - philo->tmp_eat)
			print_msg(philo, 4);
	}
	return (NULL);
}

void		*meal_loop(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (i < philo->nb)
	{
		sem_wait(philo->eating);
		i++;
	}
	i = 0;
	print_msg(philo, 5);
	while (i < philo->nb)
		kill(philo->pid[i++], SIGTERM);
	free(philo->pid);
	sem_unlink("fork");
	sem_unlink("eating");
	sem_unlink("msg");
	exit(0);
	return (NULL);
}
