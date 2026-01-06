#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    // set up envars
    char * user = getenv("USER");
    char * home = getenv("HOME");
    char cwd[PATH_MAX];

    // forever loop
    while (true) {

        // print prompt
        getcwd(cwd, sizeof(cwd));
        cout << user << ":" << cwd << "$ ";
        cout.flush();

        // receive user input
        char input[256];
        fgets(input, sizeof(input), stdin);

        // handle EOF
        if (feof(stdin)) {
            cout << "\n";
            return 0;
        }

        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // tokenize input
        char * tokens[15];
        char * token = strtok(input, " ");

        size_t n_args = 0;
        while (n_args < 15 && token != NULL) {
            tokens[n_args++] = token;
            token = strtok(NULL, " ");
        }
        tokens[n_args] = NULL;

        if (n_args == 0) {
            continue;
        }

        // handle `exit` and `cd`
        if (!strcmp(tokens[0], "exit")) {
            if (n_args == 2) {
                return atoi(tokens[1]);
            }
            else {
                return 0;
            }
        }
        else if (!strcmp(tokens[0], "cd")) {
            if (n_args == 1) {
                chdir(home);
            }
            else if (chdir(tokens[1])) {
                cerr << "shell: cd: no such file or directory '" << tokens[1] << "'\n";
            }
        }
        else { // handle non-builtins
            // fork
            pid_t pid = fork();
            if (pid == 0) { // child

                // execute command
                execvp(tokens[0], tokens); 

                // handle errors
                cerr << "shell: command '" << tokens[0] << "' not found\n";
                exit(1);
            }
            else if (pid < 0) {
                cerr << "shell: invalid PID\n";
            }
            else { // parent
                
                // wait for child
                int status;
                waitpid(pid, &status, 0);
            }
        }
    }
    return 0;
}
