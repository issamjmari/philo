/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:18:37 by ijmari            #+#    #+#             */
/*   Updated: 2022/04/12 12:14:51 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_prob(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!(str[i][j] >= '0' && str[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

unsigned long long	gettime(void)
{
	struct timeval	l;

	gettimeofday(&l, NULL);
	return (l.tv_sec * 1000000 + l.tv_usec);
}

void	ft_usleep(unsigned long long n)
{
	unsigned long long	first_time;

	first_time = gettime();
	while ((gettime() - first_time) < n)
		usleep(50);
}

void	mutex_destroyer(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philos)
	{
		pthread_mutex_destroy(&philo->fork[i]);
		i++;
	}
	pthread_mutex_destroy(philo->is_printing);
}
