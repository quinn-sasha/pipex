#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

# define CHILD 0

void execute(char *command, char *environ[]);
void write_into_pipe(char *command, char *environ[]) {

}

int main(int argc, char *argv[], char *environ[]) {
  int input_file_fd = open("./input_file", O_RDONLY);
  dup2(input_file_fd, STDIN_FILENO);
  close(input_file_fd);

  int cmd_index = 2;
  while (cmd_index < argc - 2) {
    write_into_pipe(argv[cmd_index], environ);
    cmd_index++;
  }
  int output_file_fd = open("./output_file", O_WRONLY);
  dup2(output_file_fd, STDOUT_FILENO);
  close(output_file_fd);
  execute(argv[cmd_index], environ);
  exit(EXIT_SUCCESS);
}
