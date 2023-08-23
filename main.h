#ifndef _MAIN_H_
#define _MAIN_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3


extern char **environ;
extern char *name;
extern int record;


/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command'str function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getroute(char **routeptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *route, char *delimator);
char *get_command_path(char *cmd);
list_t *get_path(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);

/* Input Helpers */
void imp_route(char **route, ssize_t route_size);
void var_proxy(char **args, int *exe_cmd);
char *get_args(char *route, int *exe_cmd);
int call_args(char **args, char **front, int *exe_cmd);
int run_args(char **args, char **front, int *exe_cmd);
int handle_args(int *exe_cmd);
int check_args(char **args);
void free_memory_arg(char **args, char **front);
char **replace_aliases(char **args);

/* Utility String */
int _strlen(const char *str);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *str, char c);
int _strspn(char *str, char *prefix);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int hsh_exit(char **args, char **front);
int hsh_env(char **args, char __attribute__((__unused__)) **front);
int hsh_setenv(char **args, char __attribute__((__unused__)) **front);
int hsh_unsetenv(char **args, char __attribute__((__unused__)) **front);
int hsh_cd(char **args, char __attribute__((__unused__)) **front);
int hsh_alias(char **args, char __attribute__((__unused__)) **front);
int hsh_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Utility exceptions */
int throw_except(char **args, int except);
char *exception_env(char **args);
char *exception_1(char **args);
char *exception_exit(char **args);
char *exception_cd(char **args);
char *exception_syx(char **args);
char *exception_126(char **args);
char *exception_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int file_cmds(char *fpath, int *exe_cmd);
#endif /* _MAIN_H_ */
