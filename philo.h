/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:53:53 by ijmari            #+#    #+#             */
/*   Updated: 2022/04/12 12:01:47 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t					*fork;
	pthread_mutex_t					*is_printing;
	pthread_t						th;
	pthread_mutex_t					done_mutex;
	unsigned long long				start_time;
	unsigned long long				last_meal;
	int								number_of_philos;
	int								number_of_forks;
	unsigned long long				time_to_die;
	unsigned long long				time_to_eat;
	unsigned long long				time_to_sleep;
	int								num_philo_must_eat;
	int								philo_id;
	int								is_eating;
	int								done;
	int								while_eat;
}	t_philos;
int					ft_atoi(const char *str);
int					is_prob(char **str);
t_philos			*preparing(char **av, int ac, t_philos *philo);
unsigned long long	gettime(void);
void				ft_usleep(unsigned long long n);
void				make_c(t_philos *phi);
int					check_numtoeat(t_philos *philo);
void				mutex_destroyer(t_philos *philo);
t_philos			*philo_set(t_philos *philo, pthread_mutex_t *is_printing \
, pthread_mutex_t *mutex);
#endif