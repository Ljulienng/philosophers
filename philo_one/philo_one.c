/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:54:50 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 18:53:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	philo_loop2(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_msg(philo, 0);
	pthread_mutex_lock(philo->prev_fork);
	print_msg(philo, 0);
	philo->tmp_eat = ft_time();
	print_msg(philo, 1);
	custom_usleep(philo->time_to_eat);
	philo->eaten++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->prev_fork);
	print_msg(philo, 2);
	custom_usleep(philo->time_to_sleep);
	print_msg(philo, 3);
}

void		*philo_loop(void *arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)arg;
	pthread_create(&tid, NULL, death_loop, philo);
	philo->id % 2 ? 0 : \
	custom_usleep((float)philo->time_to_eat * 0.9 + 1);
	while (philo->eat_count == -1 || philo->eat_count > philo->eaten)
		philo_loop2(philo);
	return (NULL);
}

void		*death_loop(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (42)
	{
		if (philo->eat_count != -1 && philo->eaten >= philo->eat_count)
		{
			custom_usleep((float)philo->id);
			pthread_mutex_unlock(philo->eating);
			break ;
		}
		else if (philo->time_to_die < ft_time() - philo->tmp_eat)
		{
			print_msg(philo, 4);
			pthread_mutex_unlock(philo->thinking);
			break ;
		}
	}
	return (NULL);
}

static void	exec_philo2(t_philo *philo, pthread_t *tid,
pthread_mutex_t *thinking, pthread_mutex_t *eating)
{
	int i;

	i = 0;
	if (philo[0].eat_count > -1)
		pthread_create(tid, NULL, meal_loop, &philo[0]);
	pthread_mutex_lock(thinking);
	while (i < philo[0].nb)
		pthread_mutex_destroy(&philo[i++].fork);
	pthread_mutex_destroy(thinking);
	pthread_mutex_destroy(eating);
	pthread_mutex_destroy(philo->msg);
	free(philo);
}

void		exec_philo(t_philo *philo)
{
	pthread_t		tid;
	int				i;
	pthread_mutex_t	thinking;
	pthread_mutex_t	eating;
	int				died;

	died = 1;
	i = 0;
	philo[0].prev_fork = &philo[philo[0].nb - 1].fork;
	pthread_mutex_init(&thinking, NULL);
	pthread_mutex_init(&eating, NULL);
	pthread_mutex_lock(&thinking);
	while (i < philo[0].nb)
	{
		philo[i].thinking = &thinking;
		philo[i].eating = &eating;
		philo[i].died = &died;
		pthread_create(&tid, NULL, philo_loop, &philo[i++]);
	}
	exec_philo2(philo, &tid, &thinking, &eating);
}
