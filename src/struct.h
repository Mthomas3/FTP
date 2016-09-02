/*
** struct.h for  in /home/mart_4/rendu/PSU_2015_myftp/src
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Mon May  2 22:30:00 2016 Thomas Martins
** Last update Sun May 15 18:47:50 2016 Thomas Martins
*/

#ifndef STRUCT_H_
# define STRUCT_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

# define	ERROR		stderr
# define	CLIENT		10
# define	RUNNING		100

typedef struct	s_sockets	t_sockets;
typedef enum	e_bool		t_bool;
typedef struct	s_server	t_server;
typedef struct	s_val		t_val;
typedef struct	s_cmd		t_cmd;
typedef struct	s_list		t_list;
typedef struct	s_transfer	t_transfer;
typedef enum	s_status	t_status;
typedef enum	s_mode		t_mode;

enum			s_mode
  {
    PASSIVE = 0,
    ACTIF = 1,
    UNDEFINED = 2
  };

enum			s_status
  {
    CONNECTED = 0,
    DECONNECTED = 1,
    UNKNOWN = 2
  };

struct			s_transfer
{
  int			sockets;
  enum s_status		status;
  int			port;
  char			ip[56];
};

struct			s_list
{
  char			*name;
  int			connection;
  int			(*func)(t_cmd *, t_server *);
  struct s_list		*next;
  struct s_list		*prev;
};

enum			e_bool
  {
			FALSE = 1,
			TRUE = 0
  };

struct			s_cmd
{
  char			*command;
  char			*content;
  int			connection;
  char			**commands_knows;
  struct s_transfer	*send;
  struct s_sockets	*sockets;
};

struct			s_val
{
  int			i;
  int			a;
  int			b;
};

struct			s_server
{
  struct sockaddr_in	addr_client;
  pid_t			pid_client;
  socklen_t		lenght_client;
  int			sockets_client;
  int			connection;
  char			*path;
  char			*save;
  int			right;
  enum s_mode		mode;
  int			socket;
};

struct			s_sockets
{
  int			port;
  char			*path;
};

int			get_errors(int, const char **);
int			start_sockets(t_sockets *);
t_cmd			*write_cmd(t_server *, t_sockets *, t_cmd *);
int			user(t_cmd *, t_server *);
int			server_user(t_cmd *, t_server*);
int			server_quit(t_cmd *, t_server *);
int			server_help(t_cmd *, t_server *);
int			server_pwd(t_cmd *, t_server *);
int			server_noop(t_cmd *, t_server *);
int			server_list(t_cmd *, t_server *);
int			server_cwd(t_cmd *, t_server *);
int			server_cdup(t_cmd *, t_server *);
int			server_remove(t_cmd *, t_server *);
int			server_pasv(t_cmd *, t_server *);
int			server_port(t_cmd *, t_server *);
int			server_retr(t_cmd *, t_server *);
int			server_stor(t_cmd *, t_server *);
int			user(t_cmd *cmd, t_server *serv);
int			set_pass(t_cmd *, t_server *);
int			(*get_matchs(const char *find, t_list
				     *list))(t_cmd *, t_server *);
t_list			*get_commander(t_list *list);
t_list			*create_list(void);
int			printf_list(t_list *);
int			printf_list_fd(t_list *, const int);
int			errors(const char *);
int			errors_client(const int, const char *);
int			get_data(t_transfer *);
t_transfer		*create_transfer(t_transfer *);
char			*getip(void);
int			asprintf(char **strp, const char *fmt, ...);
char			**wordtab(char *, char c, t_val *);
int			set_clients(t_server *server, t_sockets *socks,
				    t_cmd *cmd);
char			*get_path(t_server *);
int			free_cmd(t_cmd *, t_list *);
int			manage_pass(t_cmd *, t_list *, t_server *);
int			init_value(t_val *);
char			*get_informations(const char *);
char			*get_informations_port(const char *);
char			*delete_comma(char *);
int			get_coma_path(const char *);

#endif
