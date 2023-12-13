/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:01:11 by yanaranj          #+#    #+#             */
/*   Updated: 2023/12/13 12:32:18 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*			Elimina la linea ya encontrada y almacena el resto
 * *line: linea que debe eliminar
 * i: contador para line
 * j: contador para el buffer
 * while(): bucle para saber la len del buff.
 * Si el buffer es diferente a \0, libera la memoria asignada y el NULL
 * Asigna memoria en line
 * incrementa i e iguala j a 0
 * while(): mientras buffer en la posicion 'i' tenga contenido
 * 			copia el valor del buffer en line
 * Libera el contenido del buffer y retorna la linea
 * Retorna el valor de line
*/
static char	*ft_next (char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = malloc(sizeof (char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);

}

/* 			Leera la linea que debe retornar
 * *line: cadena a devolver
 * i: iterador de la cadena
 * Primera lectura del bufer, si no hay nada, NULL.
 * Si el buffer tiene contenido y es distinto a '\n', itera en el buffer
 * para encontrar su len 
 * Asigna memoria en line y NULL en caso de fallo.
 * while(): lee el buffer y comprueba si es diferente a '\n'
 * 			copia el buffer en line en cada posicion de i.
 * 			sigue leyendo los caracteres del archivo.
 * if(): cuando el buffer sea igual a '\n'
 * 		 se mueve en la pos de line y agrega el '\n'
 * retorna line.
*/
static char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

/* 			Leera en el FD y concatena las cadenas en el
 * STRG y devuelve el resultado de la cadena(strg).
 * *buffer: almacena datos leido de manera temp.
 * byte: num de bytes que ira contando. Se inicia en 1 para entrar en
 *		 el bucle
 * malloc: para asignar memoria en el buffer.
 * while(): bucle que busca el caracter '\n' o hasta el final de linea
 * 			primero lee los bytes desde el fd al BS
 * 			Si se leyeron, primero asegura que que no termina en nulo.
 * 			Concatena el buffer a una cadena existente y lo almacena en
 * 			strg. Si falla, return NULL.
 * 			Else (si no ha leido bytes), libera los datos.
 * Al salir del bucle, libera la memoria de buffer despues de leer las lineas
 */
static char	*read_file(int fd, char *strg)
{
	char	*buffer;
	int		bytes;

	bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(NULL, strg));
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';//iguala a nulo para que sea una cadena ok
			strg = ft_strjoin(strg, buffer);
			if (!strg)
				return (NULL);
		}
		else if (bytes < 0)
			return (ft_free(strg, buffer));
	}
	free(buffer);
	return (strg);	
}

/*			Leera dentro del archivo y devolvera la linea obtenida
 * *strg: variable donde almacenamos temporalmente el resto del string
 * *line: variable a retornar con la linea leida
 * Si el fd y el BS no son validos para la lectura, retorna NULL.
 * almacena en strg el resultado de read_file (todo lo que ha leido).
 * En caso de error, retorna NULL.
 * Almacena en line la linea que debe retornar (linea que termina en '\n')
 * Almacena en strg el resto leido del fd y guardalo para la siguiente
 * y elimina la linea ya obtenida
 */
char	*get_next_line(int fd)
{
	static char	*strg = NULL;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	strg = read_file(fd, strg);
	if (!strg)
		return (NULL);
	line = ft_line(strg);
	strg = ft_next(strg);
	return (line);
}

/* fd: archivo que leera
 * l: lineas del archivo que queremos devolver
 * *line: valor a imprimir
 * primero abrimos el fd, si no existe, lo crea
 * while(): bucle que repite el gnl hasta llegar a 10
 * 			escribe en line llamando a la funcion gnl
 * 			imprime y luego libera la memoria de linea
 * 			incrementa 'l' hasta salir del bucle
 * cierra el fd y retorna 0.
*/
int main()
{
	int		fd;
	int		l = 0;
	char	*line;

	fd = open("test.txt", O_RDONLY | O_CREAT);
	while (l < 10)
	{
		line = get_next_line(fd);
		printf("\n%i: %s", l, line);
		free(line);
		l++;
	}
	close (fd);
	return (0);
}
