# Color Flood

By cpcitor https://github.com/cpcitor

Coded in C + SDCC + cpc-dev-tool-chain

# Principle of the game

A puzzle game for 2 to 4 player.

* Each player owns a colored domain.
* At each move change your domain color and annex neighbours of target color.
* When no more moves are possible, *player with biggest area wins.*

What makes the game somewhat interesting is that it's sometimes good
to play not what is the best for you (sometimes nothing is really
better than another) but playing what will slow down your opponent.

# How to use

## First screen

Use cursor keys to select your options :

* grid size 12x12 16x16 or 24x24
* which corners are occupied by an active player.

## Game screen

* The next player to play is shown with a cross in the corner.
* Each color is associated with a key in the set s d f g h j.
* Choose the color you want and press the associated key.  Be careful, no undo!

At the bottom, progress bars allow to compare surface of each player
(easier than trying to count squares).

## Game end

The program shows the final area of each players.
Sometimes there are draw games.

# How to compile

* Get a computer (preferably running Linux, but Windows or Mac should do).
* Get a copy of https://github.com/cpcitor/cpc-dev-tool-chain .
* Install it as explained on https://github.com/cpcitor/cpc-dev-tool-chain/blob/master/documentation/how_to_install.md
* Run the script `cdtc-project-setup.sh` so that your local copy of the current source code knows where to find your local copy of cpc-dev-tool-chain. For example: `/path/to/cpc-dev-tool-chain/cdtc-project-setup.sh /path/to/cpcitor__color_flood__source_code/`
* Now, in `cpcitor__color_flood__source_code` run `make`
* You can also yo `make cdt`, `make dsk`, etc.
* Run the cdt or dsk in an emulator or transfer to real CPC.
* Enjoy!
