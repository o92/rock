#include "shell.h"
#include "shitio.h"

void version() {
	k_print("\ncrepOS beta 1.1\n");
}

char *command_list[] = { "version" };

typedef void (*command_functions)();
command_functions comm_func[] = { version };

void command_handler(char *input) {

	bool commandFound = false;

	for(int i = 0; i < sizeof command_list/sizeof *command_list; i++) {
		t_print("%s", input);
		if(!strcmp(input, command_list[i])) {
			comm_func[i]();
			commandFound = true;
		}
		if(commandFound)
			break;
	}
	if(!commandFound)
		k_print("\n%s commnad not found\n");
	k_print("> ");
}
