#ifndef SHELL_ENGINE_H_SENTRY
#define SHELL_ENGINE_H_SENTRY

int shell_run_command(char **argv, int in_bg);
void shell_clear_zombies(void);

#endif
