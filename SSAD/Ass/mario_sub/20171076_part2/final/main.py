'''
Main file of execution
'''

import sys

from colorama import init

from util import NBInput
from util import clear
from util import keypress

from gamestate import Game

import configs

if __name__ == "__main__":

    # setting up Colorama
    init()

    # sets up keyboard INPUT
    KEYS = NBInput()
    played_flag = True
    ##########################
    # Set up the environment #
    ##########################

    try:
        ######################################
        # Start the actual game configs here #
        ######################################

        # clear screen and enable non blocking INPUT
        clear()
        KEYS.nb_term()
        LEVEL = 0

        print("Choose level you want to play:\n0\t1\t2")
        try:
            LEVEL = int(KEYS.get_ch())
        except:
            played_flag = False
            print("An error occured (Faulty Input). Please enter only numbers")
            KEYS.get_ch()
            sys.exit(0)

        if LEVEL > 2 or LEVEL < 0:
            played_flag = False
            print('Choice out of bounds. Press any key to continue')
            KEYS.get_ch()
            sys.exit(0)

        # Start a new Game with level
        # the screen used is a property of the game object
        LIVES = configs.MAX_LIFE

        STATUS = 0
        POINTS = 0

        while LIVES > 0:
            GAME = Game(LEVEL, configs.STD_TIME, LIVES)

            # Level screen
            GAME.level_screen(LEVEL, LIVES, POINTS)
            KEYS.flush()
            KEYS.get_ch()

            # Game loop executes as time remains
            while GAME.get_t_remain() > 0:

                # FRAME stores the time remaining at the start of rendering
                # a frame, so as to calculate how long actually rendering it
                # took, and to maintain a framerate
                FRAME = GAME.get_t_remain()

                # repaint screen
                GAME.repaint()

                # poll for INPUT
                INPUT = ''
                if KEYS.kb_hit():
                    INPUT = KEYS.get_ch()

                # process INPUT
                CIN = keypress(INPUT)
                if CIN == -1:
                    STATUS = 2
                    break

                # run game mechanics for each cycle
                STATUS = GAME.change_state(CIN)
                if STATUS != 0:
                    break

                # Clear INPUT buffer to prevent delayed response
                KEYS.flush()

                # Maintains some sort of framerate
                while FRAME - GAME.get_t_remain() < 0.1:
                    continue

            # Game quit
            if STATUS == 2:
                break
            # Level up
            if STATUS == 1:
                STATUS = 0
                LEVEL += 1
                POINTS += GAME.points + GAME.get_t_remain()//1
                if LEVEL >= 3:
                    sys.exit(0)

                continue

            # If here, death has happened.
            LIVES -= 1

    finally:
        clear()
        if played_flag:
            print("GAME OVER. Final points: " + str(POINTS))

        print("Press any key to exit")
        KEYS.flush()
        KEYS.get_ch()
        # Switch back to the original terminal state
        KEYS.or_term()
