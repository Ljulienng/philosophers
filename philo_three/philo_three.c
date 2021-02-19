/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:54:50 by user42            #+#    #+#             */
/*   Updated: 2021/02/18 16:08:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	philo_loop2(t_philo *philo)
{
	sem_wait(philo->fork);
	printf("%ld: Philo #%d has taken a fork\n",
	current_stamp(philo->time), philo->id);
	printf("%ld: Philo #%d has taken a fork\n",
	current_stamp(philo->time), philo->id);
	philo->tmp_eat = ft_time();
	printf("%ld: Philo #%d is eating\n",
	current_stamp(philo->time), philo->id);
	custom_usleep(philo->time_to_eat);
	philo->eaten++;
	sem_post(philo->fork);
	printf("%ld: Philo #%d is sleeping\n",
	current_stamp(philo->time), philo->id);
	custom_usleep(philo->time_to_sleep);
	printf("%ld: Philo #%d is thinking\n",
	current_stamp(philo->time), philo->id);
}

void		*philo_loop(t_philo *philo)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, death_loop, philo);
	while (philo->eat_count == -1 || philo->eat_count > philo->eaten)
		philo_loop2(philo);
	return (NULL);
}

void		*death_loop(void *arg)
{
	t_philo *philo;
	int		var;

	var = 1;
	philo = (t_philo *)arg;
	while (42)
	{
		if (philo->eat_count != -1 && philo->eaten >= philo->eat_count && var)
		{
			sem_post(philo->eating);
			var = 0;
			break ;
		}
		else if (philo->time_to_die < ft_time() - philo->tmp_eat)
		{
			printf("%ld: Philo #%d died\n",
			current_stamp(philo->time), philo->id);
			exit(0);
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
	printf("%ld: Everyone has eaten enough !\n", current_stamp(philo->time));
	sem_unlink("fork");
	sem_unlink("eating");
	exit(0);
	return (NULL);
}
