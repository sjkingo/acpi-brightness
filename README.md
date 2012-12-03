acpi-brightness
===============

This is a small program for adjusting the brightness of a backlight through
ACPI (e.g. a laptop screen). The binary is setuid root so it can be run by any
user.

It may be configured by editing `config.h` and recompiling.

Installation
------------

1. Modify `config.h` if needed.
2. Compile using `make` (required sudo access to setuid the binary).
3. Profit?

Usage
-----

    $ brightness

Displays current brightness value.

$ brightness [MIN-MAX]
    Sets the brightness to the given value (must be between MIN and MAX, as
    specified in `config.h`. By default this is 0-10.)

$ brightness up
    Increases the current brightness level by one.

$ brightness down
    Decreases the current brightness level by one.
