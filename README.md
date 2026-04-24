This is a basic, terminal blackjack machine for UN!X sistems (Aka Linux/MacOS). Windows support won't come too soon.

This game requires the g++ compiler for C++. If you don't have it, you can install it using your distro's PM:
    Debian / Debian-based: sudo apt install g++
    Red Hat/ Red Hat-based: sudo rmp install g++
    Arch Linux / Arch-based: should be installed by default. If not, run "sudo pacman -S g++"
    MacOS: brew install g++

To start the game, run "run.sh" in your terminal. From there, the game has it's own help menu.

This game features saving between hands. This is done automatically. The save location is "stats.txt", created on first run.
The file ".hide_splash.txt" holds a single number, 0 or 1. It's used to display the game's rules. Like the previous files, it
is created on first run.

By running "reset.sh", you reset your stats, settings and the main executable.

The maximum money you can have is (2^63)-1, or the "long long" limit. Anything after that breaks the game. The maximum games 
you can play is the int limit.