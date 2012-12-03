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

To display the current brightness value:

    $ brightness

To set the current brightness to a given value (note that this value must be in
the range [`MIN`..`MAX`], which is configured in `config.h`. By default this is
[0..10]):

    $ brightness value

To increase the current brightness level by 1:

    $ brightness up

To decrease the current brightness level by 1:

    $ brightness down
