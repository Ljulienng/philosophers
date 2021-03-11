/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:53:50 by user42            #+#    #+#             */
/*   Updated: 2021/03/10 11:09:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	arg_check(int ac, char **av)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Wrong amount of arguments\n");
		return (0);
	}
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Arguments must be digits\n");
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

long		current_stamp(long time)
{
	long	stamp;

	stamp = ft_time() - time;
	return (stamp);
}

void		*meal_loop(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	if (philo->eat_count != 0)
		pthread_mutex_lock(philo->eating);
	while (philo->eat_count != 0 && i < philo->nb)
	{
		pthread_mutex_lock(philo->eating);
		i++;
		if (*philo->died == 0)
		{
			pthread_mutex_unlock(philo->thinking);
			return (NULL);
		}
	}
	printf("%ld: Everyone has eaten enough !\n", current_stamp(philo->time));
	pthread_mutex_unlock(philo->thinking);
	return (NULL);
}

void		init_philosophers(t_philo *philo, char **av)
{
	int		i;
	long	time;

	time = ft_time();
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		philo[i].prev_fork = (i != 0) ? &philo[i - 1].fork : NULL;
		philo[i].id = i + 1;
		philo[i].died = 0;
		philo[i].nb = ft_atoi(av[1]);
		philo[i].time = time;
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5] != NULL)
			philo[i].eat_count = ft_atoi(av[5]);
		else
			philo[i].eat_count = -1;
		philo[i].tmp_eat = time;
		philo[i].eaten = 0;
		i++;
	}
}

int			main(int ac, char **av)
{
	t_philo	*philo;
	int		x;

	x = 0;
	if (!(arg_check(ac, av)))
		return (1);
	if (!(philo = malloc(sizeof(t_philo) * ft_atoi(av[1]))))
		return (1);
	init_philosophers(philo, av);
	exec_philo(philo, x);
	return (0);
}
