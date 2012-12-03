#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>

#define BRIGHTNESS_DEV "/sys/class/backlight/acpi_video0/brightness"
#define MAX_BRIGHTNESS_DEV "/sys/class/backlight/acpi_video0/max_brightness"

static int get_brightness(void) {
    int fd = open(BRIGHTNESS_DEV, O_RDONLY);
    if (fd < 0) {
        perror("open(" BRIGHTNESS_DEV ")");
        fprintf(stderr, "Check the ACPI driver for your backlight\n");
        exit(2);
    }

    char buf[64];
    memset(buf, 0, sizeof(buf));
    if (read(fd, buf, sizeof(buf)) < 0) {
        perror("read");
        exit(2);
    }
    close(fd);

    int level = strtol(buf, NULL, 10);
    return level;
}

static void set_brightness(int level) {
    int fd = open(BRIGHTNESS_DEV, O_WRONLY);
    if (fd < 0) {
        perror("open(" BRIGHTNESS_DEV ")");
        fprintf(stderr, "Check the ACPI driver for your backlight\n");
        exit(2);
    }

    char buf[64];
    memset(buf, 0, sizeof(buf));
    int len = sprintf(buf, "%d", level);
    if (write(fd, buf, len) < 0) {
        int e = errno;
        if (e == EINVAL) {
            fprintf(stderr, "Error: invalid brightness given\n");
        } else {
            perror("write");
        }
        exit(2);
    }
    close(fd);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        int level = get_brightness();
        printf("%d\n", level);
        return 0;
    } else if (argc == 2) {
        int level = strtol(argv[1], NULL, 10);
        set_brightness(level);
        return 0;
    } else {
        fprintf(stderr, "Usage: %s [level-to-set]\n" \
                        "       if no argument is given, displays current brightness level\n",
                        argv[0]);
        return 1;
    }
}
