#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main() {

    int fd = open("output.txt", O_WRONLY | O_CREATE);

    write(fd, "niu\n", 4);

    exit(0);
}