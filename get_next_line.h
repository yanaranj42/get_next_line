/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:01:41 by yanaranj          #+#    #+#             */
/*   Updated: 2023/12/12 17:25:18 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>//lib gestion de memoria
#include <fcntl.h> //file control

/* Funciones principales*/
char	*get_next_line (int fd);


/* Funciones auxiliares */
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_free(char *s1, char *s2);

#endif
