#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "config.h"

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
    if (level < MIN || level > MAX) {
        fprintf(stderr, "Error: brightness level not in the range [%d..%d]\n",
                MIN, MAX);
        exit(2);
    }

    int fd = open(BRIGHTNESS_DEV, O_WRONLY);
    if (fd < 0) {
        perror("open(" BRIGHTNESS_DEV ")");
        fprintf(stderr, "Check the ACPI driver for your backlight\n");
        exit(2);
    }

    char buf[64];
    memset(buf, 0, sizeof(buf));
    int len = snprintf(buf, sizeof(buf), "%d", level);
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
        int level;
        if (strcmp(argv[1], "up") == 0) {
            level = get_brightness() + STEP;
            if (level > MAX) {
                return 0;
            }
        } else if (strcmp(argv[1], "down") == 0) {
            level = get_brightness() - STEP;
            if (level < MIN) {
                return 0;
            }
        } else if (strcmp(argv[1], "max") == 0) {
            level = MAX;
        } else if (strcmp(argv[1], "min") == 0) {
            level = MIN;
        } else {
            level = strtol(argv[1], NULL, 10);
        }
        set_brightness(level);
        return 0;
    } else {
        fprintf(stderr, "Usage: %s [<value>|up|down|max|min]\n", argv[0]);
        return 1;
    }
}
