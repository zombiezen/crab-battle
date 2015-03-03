# Platform #
SDL (2D game)

# Abstract #

Crab Battle is a multiplayer fighting game in the style of Super Smash Brothers. Two (possibly more) people choose characters from a programmed list (e.g. Chuck Norris, Mario, etc.) and an arena. The game involves the players navigating the arena and inflicting damage upon the other until the maximum damage is received by one player and the other player wins.

# Storyboard #
The game is activated from the operating system and the game shows some form of splash screen and/or introductory animation. After the user(s) has pressed a key, the game goes to the main menu, which has two options: _Multiplayer_ and _Exit_.

The user(s) chooses Multiplayer, and the _Player 1 Character Select_ screen is shown. The first player selects a character, then confirms his or her choice. At any time, the player may cancel the operation and return to the previous screen. Then the _Player 2 Character Select_ screen is shown, and the process is repeated. Optionally, an arena select screen is shown (if we have time for multiple arenas), and both players must click on the arena they wish to play on. Then the game begins.

When play starts, there is an initial three second countdown where neither player can make any actions (to make sure both players are ready), which will be shown on-screen (i.e. 3 will flash, then 2, etc.). After the countdown, players may use a combination of keyboard and joystick to move their respective characters. The characters may move left, move right, jump, and attack. When one player attacks and the other player is within a small proximity, the other player takes a certain amount of damage. Once a character receives over a certain amount of damage, the game is over and the opposing player wins.

After the game ends, a screen showing the winner and the friendly message _You win!_ will appear on the screen. After pressing a key, the game switches back to the main menu, where the user(s) may either play again or exit.

## Additional Notes ##

Of course, additional features will be added as we need them (TJ suggested pick-ups)