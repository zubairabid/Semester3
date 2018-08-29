from util import NBInput
from util import clear
from util import keypress

import sys
import select

from gamestate import Game

import time
from colorama import init

import configs

if __name__ == "__main__":
    '''
    game loop, environment setup, etc. Happens here
    '''

    # setting up Colorama
    init()

    # sets up keyboard input
    keys = NBInput()

    ##########################
    # Set up the environment #
    ##########################

    try:
        ######################################
        # Start the actual game configs here #
        ######################################

        # clear screen and enable non blocking input
        clear()
        keys.nbTerm()
        level = 0

        print("Choose level you want to play:\n0\t1\t2")
        level = int(keys.getCh())

        if level > 2 or level < 0:
            print('Choice out of bounds. Resetting to 0')
            level = 0

        # Start a new Game with level
        # the screen used is a property of the game object
        lives = configs.MAX_LIFE

        status = 0
        points = 0

        while lives > 0:
            game = Game(level, configs.STD_TIME, lives)

            # Level screen
            game.levelScreen(level, lives, points)
            keys.flush()
            keys.getCh()

            # Game loop executes as time remains
            while game.getTRemain() > 0:

                # frame stores the time remaining at the start of rendering
                # a frame, so as to calculate how long actually rendering it
                # took, and to maintain a framerate
                frame = game.getTRemain()

                # repaint screen
                game.repaint()

                # poll for input
                input = ''
                if keys.kbHit():
                    input = keys.getCh()

                # process input
                cin = keypress(input)
                if cin == -1:
                    status = 2
                    break

                # run game mechanics for each cycle
                status = game.changeState(cin)
                if status != 0:
                    break

                # Clear input buffer to prevent delayed response
                keys.flush()

                # Maintains some sort of framerate
                while(frame - game.getTRemain() < 0.1):
                    continue

            # Game quit
            if status == 2:
                break
            # Level up
            if status == 1:
                status = 0
                level += 1
                points += game.points + game.getTRemain()//1
                continue

            if level >= 3:
                break

            # If here, death has happened.
            lives -= 1

    finally:
        time.sleep(0.5)
        clear()
        print("GAME OVER. Final points: " + str(points) +
              "\nPress any key to exit")

        keys.flush()
        keys.getCh()
        # Switch back to the original terminal state
        keys.orTerm()
