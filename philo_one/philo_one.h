/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:54:00 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 15:47:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct		s_philo
{
	pthread_mutex_t	fork;
	pthread_mutex_t	*prev_fork;
	pthread_mutex_t	*thinking;
	pthread_mutex_t	*eating;
	int				id;
	int				nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				eaten;
	long			time;
	long			tmp_eat;

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
