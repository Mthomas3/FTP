/*
** errors.c for  in /home/mart_4/rendu/PSU_2015_myftp/src
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Tue May  3 14:45:01 2016 Thomas Martins
** Last update Sun May 15 11:21:33 2016 Thomas Martins
*/

#include "../struct.h"

int		errors_client(const int socket_client, const char *message)
{
  dprintf(socket_client, "%s\r\n", message);
  return (EXIT_FAILURE);
}

int		errors(const char *message)
{
  dprintf(2, "%s\r\n", message);
  return (EXIT_FAILURE);
}

static int	print_errors(const char *error)
{
  fprintf(ERROR, error);
  return (EXIT_FAILURE);
}

int		get_errors(int numbers, const char
			   __attribute__((unused))**arguments)
{
  if (numbers < 3)
    return (print_errors("Usage : ./server port path\n"));
  return (EXIT_SUCCESS);
}
