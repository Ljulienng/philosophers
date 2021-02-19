/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:54:00 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 15:46:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct		s_philo
{
	sem_t			*fork;
	sem_t			*eating;
	sem_t			*death;
	int				id;
	int				nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				eaten;
	long			time;
	long			tmp_eat;
	int				*no_run;

}					t_philo;

int					main(int ac, char **av);
void				init_philosophers(t_philo *philo, char **av);
int					ft_atoi(const char *str);
long				ft_time(void);
void				custom_usleep(int sleep_time);
long				current_stamp(long time);
void				exec_philo(t_philo *philo);
void				*death_loop(void *arg);
void				*meal_loop(void *arg);
void				*philo_loop(void *arg);
#endif
