/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:53:50 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 17:32:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

static void	init2(t_philo *philo, char **av, int i)
{
	philo[i].fork = philo[0].fork;
	philo[i].eating = philo[0].eating;
	philo[i].death = philo[0].death;
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
}

static void	freelosophers(t_philo *philo, pthread_t *tid,
pthread_t tid2, sem_t *msg)
{
	int i;

	i = 0;
	while (i < philo->nb)
		pthread_join(tid[i++], NULL);
	if (philo->eat_count > -1)
	{
		sem_post(philo->eating);
		pthread_join(tid2, NULL);
	}
	sem_wait(philo[0].death);
	custom_usleep(philo[0].time_to_eat + philo[0].time_to_sleep);
	sem_close(msg);
	(void)tid2;
}

void		init_philosophers(t_philo *philo, char **av, int x)
{
	int				i;
	int				no_run;
	pthread_t		tid[ft_atoi(av[1])];
	pthread_t		tid2;
	sem_t			*msg;

	no_run = 1;
	i = 0;
	sem_unlink("msg");
	msg = sem_open("msg", O_CREAT, S_IRWXU, 1);
	if (philo[0].eat_count == -1)
		(void)tid2;
	while (i < ft_atoi(av[1]))
	{
		init2(philo, av, i);
		philo[i].msg = msg;
		philo[i].no_run = &no_run;
		pthread_create(&tid[x++], NULL, philo_loop, &philo[i++]);
	}
	if (philo[0].eat_count > -1)
		pthread_create(&tid2, NULL, meal_loop, &philo[0]);
	freelosophers(philo, tid, tid2, msg);
}

int			main(int ac, char **av)
{
	t_philo *philo;
	int		x;

	if (!(arg_check(ac, av)))
		return (1);
	if (!(philo = malloc(sizeof(t_philo) * ft_atoi(av[1]))))
		return (1);
	x = 0;
	sem_unlink("fork");
	sem_unlink("eating");
	sem_unlink("death");
	philo[0].fork = sem_open("fork", O_CREAT, S_IRWXU, (ft_atoi(av[1]) / 2));
	philo[0].eating = sem_open("eating", O_CREAT, S_IRWXU, 0);
	philo[0].death = sem_open("death", O_CREAT, S_IRWXU, 0);
	init_philosophers(philo, av, x);
	sem_close(philo[0].fork);
	sem_close(philo[0].eating);
	sem_close(philo[0].death);
	sem_unlink("msg");
	sem_unlink("fork");
	sem_unlink("eating");
	sem_unlink("death");
	free(philo);
	return (0);
}
