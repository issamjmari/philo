/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:56:02 by ijmari            #+#    #+#             */
/*   Updated: 2022/04/12 13:24:34 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_c(t_philos *phi)
{
	ft_usleep(phi->time_to_eat);
	phi->while_eat = 0;
	phi->is_eating++;
	if (phi->is_eating == phi->num_philo_must_eat)
		phi->done = 1;
	ft_usleep(50);
	pthread_mutex_unlock(&phi->fork[phi->philo_id - 1]);
	pthread_mutex_unlock(&phi->fork[(phi->philo_id) % \
	phi->number_of_philos]);
	pthread_mutex_lock(phi->is_printing);
	printf("%llu %d is sleeping\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
	pthread_mutex_unlock(phi->is_printing);
	ft_usleep(phi->time_to_sleep);
	pthread_mutex_lock(phi->is_printing);
	printf("%llu %d is thinking\n", \
	(gettime() - phi->start_time) / 1000, phi->philo_id);
	pthread_mutex_unlock(phi->is_printing);
}

t_philos	*preparing(char **av, int ac, t_philos *philo)
{
	int	i;

	i = 0;
	philo = malloc (sizeof(t_philos) * ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		philo[i].start_time = gettime();
		philo[i].last_meal = gettime();
		philo[i].philo_id = i + 1;
		philo[i].number_of_philos = ft_atoi(av[1]);
		philo[i].time_to_die = ft_atoi(av[2]) * 1000;
		philo[i].time_to_eat = ft_atoi(av[3]) * 1000;
		philo[i].time_to_sleep = ft_atoi(av[4]) * 1000;
		if (ac == 6)
			philo[i].num_philo_must_eat = ft_atoi(av[5]);
		i++;
	}
	return (philo);
}

int	check_numtoeat(t_philos *philo)
{
	int	j;

	j = 0;
	while (j < philo->number_of_philos)
	{
		if (philo[j].done != 1)
			break ;
		if (j == philo->number_of_philos - 1 && philo[j].done == 1)
			return (1);
		j++;
	}
	return (0);
}

t_philos	*philo_set(t_philos *philo, pthread_mutex_t *is_printing \
, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philos)
	{
		philo[i].is_printing = is_printing;
		philo[i].fork = mutex;
		philo[i].is_eating = 0;
		philo[i].done = 0;
		i++;
	}
	return (philo);
}
