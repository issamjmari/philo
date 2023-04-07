/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 08:05:20 by ijmari            #+#    #+#             */
/*   Updated: 2022/04/12 12:07:38 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*make(void *s)
{
	t_philos	*phi;

	phi = (t_philos *) s;
	while (1)
	{
		pthread_mutex_lock(&phi->fork[phi->philo_id - 1]);
		pthread_mutex_lock(phi->is_printing);
		printf("%llu %d has taken a fork\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(phi->is_printing);
		pthread_mutex_lock(&phi->fork[(phi->philo_id) % phi->number_of_philos]);
		phi->last_meal = gettime();
		phi->while_eat = 1;
		pthread_mutex_lock(phi->is_printing);
		printf("%llu %d has taken a fork\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(phi->is_printing);
		pthread_mutex_lock(phi->is_printing);
		printf("%llu %d is eating\n", \
		(gettime() - phi->start_time) / 1000, phi->philo_id);
		pthread_mutex_unlock(phi->is_printing);
		make_c(phi);
	}
	return (0);
}

t_philos	*mutex_init(t_philos *philo)
{
	int				i;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*is_printing;

	mutex = malloc (sizeof(pthread_mutex_t) * philo->number_of_philos);
	if (!mutex)
		return (0);
	is_printing = malloc (sizeof(pthread_mutex_t));
	if (!is_printing)
		return (0);
	i = 0;
	while (i < philo->number_of_philos)
		if (pthread_mutex_init(&mutex[i++], NULL) != 0)
			return (0);
	if (pthread_mutex_init(is_printing, NULL) != 0)
		return (0);
	return (philo_set(philo, is_printing, mutex));
}

void	check_death(t_philos *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		i = i % philo->number_of_philos;
		if (check_numtoeat(philo))
			return ;
		if (philo[i].while_eat == 0 && \
		((gettime() - philo[i].last_meal)) >= philo[i].time_to_die)
		{
			pthread_mutex_lock(philo[i].is_printing);
			printf("\033[31;1m%llu %d has died\n", (gettime() / 1000) - \
			(philo[i].start_time / 1000), philo[i].philo_id);
			return ;
		}
		usleep(50);
		i++;
	}
}

int	create_philos(t_philos *philo)
{
	int			i;

	philo = mutex_init(philo);
	if (!philo)
		return (0);
	i = 0;
	while (i < philo->number_of_philos)
	{
		if (pthread_create(&philo[i].th, NULL, &make, &philo[i]) == -1)
			return (0);
		i += 2;
	}
	ft_usleep (500);
	i = 1;
	while (i < philo->number_of_philos)
	{
		if (pthread_create(&philo[i].th, NULL, &make, &philo[i]) == -1)
			return (0);
		i += 2;
	}
	check_death(philo);
	return (1);
}

int	main(int ac, char **av)
{
	t_philos	*philo;

	philo = NULL;
	if (!is_prob(&av[1]))
		return (0);
	if (ac != 5 && ac != 6)
	{
		printf("Error : Arguments not valid\n");
		return (0);
	}
	philo = preparing(av, ac, philo);
	if (!philo)
	{
		printf("Error : Numbers not valid\n");
		return (0);
	}
	if (!create_philos(philo))
	{
		printf("Can't create or initialize the threads\n");
		return (0);
	}
	mutex_destroyer(philo);
	return (0);
}
