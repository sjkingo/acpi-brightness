#ifndef CONFIG_H
#define CONFIG_H

// ACPI backlight device - this should not need changing.
#define BRIGHTNESS_DEV "/sys/class/backlight/acpi_video0/brightness"

// Minimum and maximum valid values for brightness - if you are getting
// invalid brightness errors when setting, try adjusting these.
#define MIN 0
#define MAX 10

// Number of brightness levels to change when using the up/down keywords.
#define STEP 1

#endif
