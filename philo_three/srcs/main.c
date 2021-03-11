/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:53:50 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 20:42:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

static void	init2(t_philo *philo, char **av)
{
	philo->fork = philo->fork;
	philo->eating = philo->eating;
	philo->nb = ft_atoi(av[1]);
	philo->time = ft_time();
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		philo->eat_count = ft_atoi(av[5]);
	else
		philo->eat_count = -1;
	philo->tmp_eat = ft_time();
	philo->eaten = 0;
}

void		init_philosophers(t_philo philo)
{
	int				i;
	pthread_t		tid;

	i = 0;
	if (!(philo.pid = malloc(sizeof(pid_t) * philo.nb)))
		return ;
	while (i < philo.nb)
	{
		philo.pid[i] = fork();
		if (philo.pid[i] == 0)
		{
			philo.id = i + 1;
			philo_loop(philo);
			i = philo.nb;
		}
		i++;
	}
	if (philo.eat_count > -1)
		pthread_create(&tid, NULL, meal_loop, &philo);
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < philo.nb)
		kill(philo.pid[i++], SIGKILL);
	free(philo.pid);
}

int			main(int ac, char **av)
{
	t_philo philo;
	int		died;
	sem_t	*msg;

	died = 1;
	if (!(arg_check(ac, av)))
		return (1);
	init2(&philo, av);
	sem_unlink("fork");
	sem_unlink("eating");
	sem_unlink("msg");
	philo.fork = sem_open("fork", O_CREAT, S_IRWXU, (philo.nb / 2));
	msg = sem_open("msg", O_CREAT, S_IRWXU, 1);
	philo.eating = sem_open("eating", O_CREAT, S_IRWXU, 0);
	philo.msg = msg;
	philo.died = &died;
	init_philosophers(philo);
	sem_close(philo.fork);
	sem_close(philo.eating);
	sem_close(philo.msg);
	sem_unlink("msg");
	sem_unlink("fork");
	sem_unlink("eating");
	return (0);
}
