/*
** commands.c for  in /home/mart_4/rendu/PSU_2015_myftp/src
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Fri May  6 09:50:42 2016 Thomas Martins
** Last update Sun May 15 18:56:22 2016 Thomas Martins
*/

#include "../struct.h"

static void	delete_char(char *str, char c)
{
  int		id_read;
  int		id_write;

  id_read = 0;
  id_write = 0;
  while (str[id_read] != '\0')
    {
      if (str[id_read] != c)
	{
	  str[id_write] = str[id_read];
	  id_write++;
	}
      id_read++;
    }
  str[id_write] = '\0';
}

static char	**find_commands(t_server *serv, char **cmds)
{
  char		buffer[256];
  int		b;
  t_val		val;

  b = 0;
  serv->right = 0;
  bzero((char *)buffer, sizeof(buffer));
  if ((b = read(serv->sockets_client, buffer, 256)) <= 0)
    exit(0);
  delete_char(buffer, '\r');
  if (strncmp(buffer, "PASS", 4) == 0)
    {
      if (buffer[strlen(buffer - 6)] == ' ')
	serv->right = 1;
    }
  if ((strcmp(buffer, "\n")) != 0)
    return (cmds = wordtab(buffer, ' ', &val));
  return (NULL);
}

static t_cmd	*get_cmds(char **tab)
{
  int		i;
  t_cmd		*command;

  if (NULL == (command = malloc(sizeof(*command))))
    return (NULL);
  command->command = NULL;
  command->content = NULL;
  if (NULL == (command->send = malloc(sizeof(t_transfer))))
    return (NULL);
  for (i = 0; tab[i]; ++i)
    {
      if (tab[i] != NULL)
	{
	  command->command = strdup(tab[i]);
	  if (tab[i + 1] != NULL)
	    command->content = strdup(tab[i + 1]);
	  break;
	}
    }
  return (command);
}

t_cmd		*write_cmd(t_server *server, t_sockets
			   __attribute__((unused))*socks, t_cmd *cmd)
{
  char		**cmds;

  cmds = NULL;
  if (NULL == (cmds = find_commands(server, cmds))
      || (NULL == (cmd = get_cmds(cmds))))
    return (NULL);
  return (cmd);
}
