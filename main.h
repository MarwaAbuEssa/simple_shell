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

extern char *name;
/**
 * struct system_s - system.
 * @name: name.
 * @f: pointer.
 */
typedef struct system_s
{
	char *name;
	int (*f)(char **argv, char **front);
} system_t;

#define END_OF_FILE -2
#define EXIT -3

/* other utilites */
extern int record;
ssize_t _getroute(char **routeptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *route, char *delimator);
char *get_command_path(char *cmd);

/**
 * struct list_s - custom struct.
 * @dir:  path.
 * @next: pointer.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

list_t *get_path(char *path);

/* commands func */
extern char **environ;
int execute(char **args, char **front);
void free_node_list(list_t *head);
char *_itoa(int num);

/* utility help and argument function */
void imp_route(char **route, ssize_t route_size);
void var_proxy(char **args, int *exe_cmd);
char *arg_get(char *route, int *exe_cmd);
int arg_call(char **args, char **front, int *exe_cmd);
int arg_run(char **args, char **front, int *exe_cmd);
int arg_handle(int *exe_cmd);
int arg_check(char **args);
void free_memory_arg(char **args, char **front);
char **edit_alias(char **args);

/* Utility string */
int _strlen(const char *str);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *str, char c);
int _strspn(char *str, char *prefix);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);

/* system functyions */
int (*get_system_cmd(char *command))(char **args, char **front);
int hsh_exit(char **args, char **front);
int hsh_env(char **args, char __attribute__((__unused__)) **front);
int hsh_setenv(char **args, char __attribute__((__unused__)) **front);
int hsh_unsetenv(char **args, char __attribute__((__unused__)) **front);
int hsh_cd(char **args, char __attribute__((__unused__)) **front);
int hsh_alias(char **args, char __attribute__((__unused__)) **front);
int hsh_help(char **args, char __attribute__((__unused__)) **front);

char **_copyenv(void);
void env_free(void);
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

/**
 * struct alias_s - custom struct.
 * @name: name.
 * @value: value.
 * @next: node pointer.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

alias_t *aliases;

/* list func  */
alias_t *add_end_alias(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_end_node(list_t **head, char *dir);
void free_node_list(list_t *head);

/* Utility Help func */

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
