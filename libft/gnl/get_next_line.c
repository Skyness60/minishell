/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:54:28 by sperron           #+#    #+#             */
/*   Updated: 2024/05/28 14:52:24 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * ft_free - Concatene deux chaines de caracteres et 
 * libere la memoire de la premiere.
 *
 * @param buffer: La premiere chaine de caracteres a 
 * concatener.
 * @param buf: La deuxieme chaine de caracteres a concatener.
 * @return: Une nouvelle chaine de caracteres resultant 
 * de la concatenation de buffer et buf,
 *          ou NULL en cas d'erreur d'allocation memoire.
 *
 * - Concatene buffer et buf pour former une seule chaine 
 * de caracteres.
 * - Libere la memoire de buffer pour eviter les fuites memoire.
 * - Retourne la nouvelle chaine de caracteres resultante de la concatenation.
 */

static char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

/**
 * ft_next - Met a jour le buffer en supprimant
 * la premiere ligne, retourne le reste.
 *
 * @param buffer: La chaine de caracteres 
 * contenant les donnees lues.
 * @return: Une nouvelle chaine de caracteres 
 * contenant le reste du buffer apres
 *          la premiere ligne, ou NULL si la fin du buffer est atteinte.
 *
 * - Parcourt le buffer jusqu'a trouver un saut de 
 * ligne ou la fin du buffer.
 * - Si aucun saut de ligne n'est trouve 
 * (fin du buffer atteinte), libere le buffer et retourne NULL.
 * - Alloue de la memoire pour stocker les donnees 
 * apres le saut de ligne trouve.
 * - Copie les donnees restantes apres le saut de 
 * ligne dans la nouvelle chaine.
 * - Termine la nouvelle chaine par un caractere nul.
 * - Libere l'ancienne memoire du buffer.
 * - Retourne la nouvelle chaine contenant les 
 * donnees restantes.
 */

static char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(*buffer));
	if (!line)
		return (NULL);
	j = 0;
	while (buffer[i])
		line[j++] = buffer[++i];
	buffer[j] = '\0';
	free(buffer);
	return (line);
}

/**
 * ft_line - Extrait la premiere ligne du buffer.
 *
 * @param buffer: La chaine de caracteres 
 * contenant les donnees lues.
 * @return: Une nouvelle chaine de caracteres 
 * contenant la premiere ligne du buffer,
 * ou NULL si le buffer est vide ou en 
 * cas d'erreur d'allocation memoire.
 *
 * - Initialise un compteur `i` a 0 en tant qu'index
 * - Si le buffer est vide (premier caractere nul),
 *  retourne NULL.
 * - Parcourt le buffer jusqu'a trouver un saut 
 * de ligne ou la fin du buffer pour determiner 
 * la longueur de la ligne.
 * - Alloue de la memoire pour stocker la ligne, 
 * incluant de la place pour un eventuel saut de ligne 
 * et le caractere nul de fin.
 * - Copie les caracteres du buffer dans la nouvelle 
 * ligne jusqu'a atteindre un saut de ligne ou la fin du buffer.
 * - Ajoute le saut de ligne a la fin de la nouvelle 
 * ligne si present dans le buffer.
 * - Retourne la ligne nouvellement creee.
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
	line = ft_calloc(i + (buffer[i] == '\n') + 1, sizeof(char));
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

/**
 * read_file - Lit les fichier et les ajoute a une chaine.
 *
 * @param fd: Le descripteur de fichier a lire.
 * @param res: La chaine de caracteres existante 
 * a laquelle ajouter les donnees lues.
 * @return: La chaine de caracteres mise a jour 
 * avec les nouvelles donnees, ou NULL en cas d'erreur.
 *
 * - Si `res` est NULL, initialise `res` avec une chaine vide.
 * pour assurer une zone de memoire valide
 * - Alloue un buffer pour la lecture.
 * - Lit les donnees en boucle jusqu'a atteindre la
 *  fin du fichier ou un saut de ligne.
 *  Ajoute un caractere nul a la fin des 
 * donnees lues pour garantir que le buffer est une chaine valide.
 * - En cas d'erreur de lecture, libere la memoire et retourne NULL.
 * 
 * - Ajoute les donnees lues a `res` en utilisant `ft_free`.
 * - Libere le buffer avant de retourner `res`.
 */

static char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buffer), free(res), NULL);
		buffer[byte_read] = 0;
		res = ft_free(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), res);
}

/**
 * Cette fonction utilise un buffer statique 
 * pour gerer les lectures successives 
 * d'un fichier sans perdre la trace de 
 * la position actuelle. Elle combine plusieurs
 * appels a d'autres fonctions auxiliaires 
 * pour effectuer la lecture, extraire la 
 * ligne courante, et preparer le buffer
 * pour la prochaine lecture.
 *
 * - static char *buffer: Buffer statique 
 * pour conserver les donnees entre les appels 
 * de la fonction. Permet de gerer les 
 * lectures partielles.
 * - char *line: Pointeur vers la chaine de
 * caracteres contenant la ligne lue depuis le fichier.
 *
 * if (fd < 0 || BUFFER_SIZE <= 0):
 * - Verifie si le descripteur de fichier est
 * null ou si la taille du buffer est 
 * null.
 *
 * buffer = read_file(fd, buffer):
 * - Lis le fichier avec le fd 
 * et les stocker dans le buffer. Si la lecture echoue, retourne NULL.
 *
 * if (!buffer):
 * - Verifie si le buffer est NULL apres la 
 * tentative de lecture
 *
 * line = ft_line(buffer):
 * - Appelle une fonction auxiliaire `ft_line` 
 * pour extraire la ligne courante du buffer. 
 * La ligne extraite est stockee dans `line`.
 *
 * buffer = ft_next(buffer):
 * - Appelle une fonction auxiliaire `ft_next` 
 * pour mettre a jour le buffer en supprimant 
 * les donnees deja lues. Prepare le buffer 
 * pour la prochaine lecture.
 *
 * return (line):
 * - Retourne la ligne lue depuis le fichier.
 *
 * Notes :
 * - Cette fonction suppose que les fonctions 
 * auxiliaires `read_file`, `ft_line` et 
 * `ft_next` sont correctement implementees 
 * pour gerer les operations specifiques.
 * - Le buffer statique permet de conserver 
 * l'etat entre les appels successifs de 
 * `get_next_line`, qui permet lire ligne par ligne
 */

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}

//#include <stdio.h>
//#include <fcntl.h>

//int main()
//{
//    int fd = open("file.txt", O_RDONLY);
//    if (fd == -1)
//    {
//        perror("open");
//        return (1);
//    }

//    char *line;
//    while ((line = get_next_line(fd)) != NULL)
//    {
//        printf("%s", line);
//        free(line);
//	}
//    close(fd);
//    return (0);
//}
