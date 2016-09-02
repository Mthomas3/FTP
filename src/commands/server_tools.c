/*
** server_tools.c for  in /home/mart_4/rendu/PSU_2015_myftp/src/commands
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Sun May 15 11:23:07 2016 Thomas Martins
** Last update Sun May 15 19:12:18 2016 Thomas Martins
*/

#include "../struct.h"

int		server_remove(t_cmd __attribute__((unused))*cmd,
			      t_server *server)
{
  int		ret;

  ret = 0;
  if (cmd->content == NULL)
    {
      dprintf(server->sockets_client, "501 Invalid number of arguments\r\n");
      return (EXIT_FAILURE);
    }
  if ((ret = remove(cmd->content)) >= 0)
    dprintf(server->sockets_client, "250 DELE commands is ok.\r\n");
  else
    dprintf(server->sockets_client, "550 DELE: No such file or directory\r\n");
  return (EXIT_SUCCESS);
}

int		get_coma_path(const char *cmd)
{
  int		i;
  int		count;

  for (count = 0, i = 0; cmd[i] != '\0'; ++i)
    {
      if (cmd[i] == ',')
	++count;
    }
  return (count);
}

char		*delete_comma(char *ip)
{
  int		i;
  int		max;

  max = strlen(ip);
  for (i = 0; ip[i]; ++i)
    {
      if (ip[i] == ',' && i == max - 1)
	{
	  ip[i] = '\0';
	}
      if (ip[i] == ',')
	ip[i] = '.';
    }
  return (ip);
}

char		*get_informations_port(const char *cmd)
{
  int		i;
  int		max;
  char		*port;
  int		j;

  j = 0;
  port = malloc(sizeof(char) * strlen(cmd) + 1);
  i = 0;
  max = 0;
  while ((unsigned int)i < strlen(cmd))
    {
      if (max == 4)
	break;
      if (cmd[i] == ',')
	max++;
      ++i;
    }
  while ((unsigned int)i < strlen(cmd))
    {
      port[j] = cmd[i];
      ++j;
      ++i;
    }
  port[j] = '\0';
  return (port);
}

char		*get_informations(const char *cmd)
{
  int		coma;
  char		*ip;
  int		i;
  int		max_size;
  int		up;

  if (NULL == (ip = malloc(sizeof(char) * strlen(cmd) + 1)))
    return (NULL);
  coma = get_coma_path(cmd);
  if (coma < 5)
    return (NULL);
  for (max_size = 0, up = 0, i = 0; max_size < 4; ++i, ++up)
    {
      if (cmd[i] == ',')
	max_size++;
      ip[up] = cmd[i];
    }
  ip[up] = '\0';
  ip = delete_comma(ip);
  return (ip);
}
