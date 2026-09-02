This is a basic, terminal blackjack machine for UN!X systems (Aka Linux/MacOS). Windows support won't come too soon.

This game requires the g++ compiler for C++. If you don't have it, you can install it using your distro's PM:

    Debian / Debian-based: sudo apt install g++

    Red Hat / Red Hat-based: sudo rpm install g++

    Arch Linux / Arch-based: should be installed by default. If not, run "sudo pacman -S g++"

    MacOS / OS X: brew install g++
    

To start the game, run "run.sh" in your terminal. From there, the game has its own help menu.

This game features saving between hands. This is done automatically. The save location is "stats.txt", created on first run.
The file ".hide_splash.txt" holds two numbers separated by a space: whether to show the game's rules (0 or 1), and whether odds assist is enabled (0 or 1). Like the previous files, it is created on first run.

Odds assist shows a "Suggested action" (hit/stand) hint during your turn, based on the cards already played and the dealer's visible card. It's off by default; toggle it with "a" in the main menu. As a tradeoff, winnings are reduced to 3/4 of the normal amount while assist is enabled.

By running "reset.sh", you reset your stats, settings and the main executable.

The maximum money you can have is (2^63)-1, or the "long long" limit. Anything after that breaks the game. The maximum games you can play is the int limit.

If you want to modify the code for whatever reason, first delete ./main (the executable).