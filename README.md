acpi-brightness
===============

This is a small program for adjusting the brightness of a backlight through
ACPI (e.g. on a laptop screen). The binary is setuid root so it can be run by
any user.

It may be configured by editing the `config.h` file and re-compiling.

Installation
------------

1. Modify `config.h` if needed.
2. Compile using `make` (sudo access is required to setuid root the binary).
3. Run as below.

Usage
-----

To display the current brightness level

    $ brightness

To set the current brightness level to a given `<value>` (note that this value must be in
the range [`MIN`..`MAX`], which is configured in `config.h`. By default this is
`[0..10]`):

    $ brightness <value>

To increase the current brightness level by 1:

    $ brightness up

To decrease the current brightness level by 1:

    $ brightness down

To set the brightest level:

    $ brightness max

To set the dimmest level:

    $ brightness min
