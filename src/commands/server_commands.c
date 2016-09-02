/*
** server_commands.c for  in /home/mart_4/rendu/PSU_2015_myftp/src/commands
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Mon May  9 23:32:07 2016 Thomas Martins
** Last update Sun May 15 11:47:06 2016 Thomas Martins
*/

#include "../struct.h"

int	server_cdup(t_cmd __attribute__((unused))*cmd,
		    t_server *server)
{
  if (chdir("..") < 0)
    dprintf(server->sockets_client, "550 failed change directory \r\n");
  else
    dprintf(server->sockets_client, "200 Directory successfully changed\r\n");
  return (EXIT_SUCCESS);
}

int	server_retr(t_cmd __attribute__((unused))*cmd, t_server *serv)
{
  char	*buffer[100 + 1];
  int	fd;
  int	b_read;

  if (serv->mode != ACTIF)
    return (errors_client(serv->sockets_client,
			  "425 Use PORT or PASV first.\r\n"));
  if (cmd->content == NULL)
    return (errors_client(serv->sockets_client,
			  "501 Invalid number of arguments\r\n"));
  if (access(cmd->content, F_OK | R_OK | W_OK) < 0)
    return (errors_client(serv->sockets_client, "550 RETR .\r\n"));
  if ((fd = open(cmd->content, O_RDONLY)) == -1)
    return (errors_client(serv->sockets_client, "550 RETR \r\n"));
  dprintf(serv->sockets_client,
	  "150 Opening file, mode data connection : \r\n");
  while ((b_read = read(fd, buffer, 100)) > 0)
    {
      if (write(serv->sockets_client, buffer, b_read) == -1)
	return (EXIT_FAILURE);
    }
  close(fd);
  dprintf(serv->sockets_client, "226 Transfer done\r\n");
  return (EXIT_SUCCESS);
}

int	server_stor(t_cmd __attribute__((unused))*cmd,
		    t_server __attribute__((unused))*serv)
{
  char	buffer[100 + 1];
  int	fd;
  int	b_write;

  if (serv->mode != ACTIF)
    {
      dprintf(serv->sockets_client, "425 Use PORT or PASV first.\r\n");
      return (EXIT_FAILURE);
    }
  if (cmd->content == NULL)
    {
      dprintf(serv->sockets_client, "501 Invalid number of arguments\r\n");
      return (EXIT_FAILURE);
    }
  if ((fd = creat(cmd->content, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (EXIT_FAILURE);
  dprintf(serv->sockets_client, "150 Opening ASCII mode data connection\r\n");
  while ((b_write = read(serv->sockets_client, buffer, 100)) > 0)
    {
      if (write(fd, buffer, b_write) == -1)
	return (EXIT_FAILURE);
    }
  close(fd);
  dprintf(serv->sockets_client, "226 Transfer complete\r\n");
  return (EXIT_SUCCESS);
}
