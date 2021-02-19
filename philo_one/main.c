/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:53:50 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 17:11:30 by user42           ###   ########.fr       */
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

void		init_philosophers(t_philo *philo, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		philo[i].prev_fork = (i != 0) ? &philo[i - 1].fork : NULL;
		philo[i].id = i + 1;
		philo[i].nb = ft_atoi(av[1]);
		philo[i].time = ft_time();
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5] != NULL)
			philo[i].eat_count = ft_atoi(av[5]);
		else
			philo[i].eat_count = -1;
		philo[i].tmp_eat = ft_time();
		philo[i].eaten = 0;
		i++;
	}
}

int			main(int ac, char **av)
{
	t_philo *philo;

	if (!(arg_check(ac, av)))
		return (1);
	if (!(philo = malloc(sizeof(t_philo) * ft_atoi(av[1]))))
		return (1);
	init_philosophers(philo, av);
	exec_philo(philo);
	return (0);
}
