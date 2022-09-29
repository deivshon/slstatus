/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>
#include <wordexp.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../util.h"

void expand_command(char *dest, const char *command) {
    wordexp_t exp_result;
    wordexp(command, &exp_result, 0);
    strcpy(dest, exp_result.we_wordv[0]);
    wordfree(&exp_result);
}

int get_cmd_output(char *dest, int dest_size, char *cmd, char **cmd_args) {
    int piped[2];
    if(pipe(piped) == -1) {
        return 0;
    }

    if(fork() == 0) {
        close(piped[0]);
        dup2(piped[1], 1);
        dup2(piped[1], 2);
        close(piped[1]);

        execvp(cmd, cmd_args);
		return 0;
    }
    else {
        strcpy(dest, "");

        int c = 0; // Bytes read into buffer each time
        char buffer[1024] = "";
        close(piped[1]);

        while((c = read(piped[0], buffer, sizeof(buffer) - 1))) {
            // Sets the byte after the last one read to '\0', terminating the string
            buffer[c] = '\0';

            if(strlen(dest) + strlen(buffer) >= (size_t) dest_size)
                break;

            strcat(dest, buffer);
        }
        close(piped[0]);
		return 1;
    }
}

const char *run_command(const char *cmd)
{
	expand_command(run_cmd_expanded, cmd);

	char local_cmd[1024];
	strcpy(local_cmd, cmd);

	char *buffer = strtok(local_cmd, " ");
	int args_index = 0;
	while(buffer != NULL) {
		run_cmd_args[args_index] = malloc(sizeof(char) * 128);
		strcpy(run_cmd_args[args_index], buffer);

		buffer = strtok(NULL, " ");
		args_index++;
	}
	run_cmd_args[args_index] = NULL;

	int cmd_result = get_cmd_output(buf, sizeof(buf) - 1, run_cmd_expanded, run_cmd_args);
	wait(NULL);
	if(!cmd_result) return NULL;

	for(int i = 0; i < args_index; i++) free(run_cmd_args[i]);

	char *nl;
	if ((nl = strrchr(buf, '\n'))) {
		nl[0] = '\0';
	}

	return buf[0] ? buf : NULL;
}
