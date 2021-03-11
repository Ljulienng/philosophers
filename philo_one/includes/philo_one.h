/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:54:00 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 20:47:45 by user42           ###   ########.fr       */
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
	pthread_mutex_t	*msg;
	int				id;
	int				nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				eaten;
	int				i;
	long			time;
	long			tmp_eat;
	int				*died;
}					t_philo;

int					main(int ac, char **av);
void				init_philosophers(t_philo *philo, char **av);
int					ft_atoi(const char *str);
long				ft_time(void);
void				custom_usleep(int sleep_time);
long				current_stamp(long time);
void				exec_philo(t_philo *philo, int x);
void				*death_loop(void *arg);
void				*meal_loop(void *arg);
void				*philo_loop(void *arg);
void				print_msg(t_philo *philo, int msg);
char				*ft_itoa(long n);
int					ft_strlen(const char *str);
#endif
