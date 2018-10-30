'''
File with functionality for managing individual gamestates
'''

from time import monotonic as timer

from random import random
from random import randrange

from util import clear

import configs

from screen import Screen

from objects import Brick

from people import Mario
from people import Enemy
from people import Boss

from backgrounds import Background as Backg
from backgrounds import Cloud


class Game:
    '''
    Class to define an individual game
    Each game is represented as an object
    '''

    def __init__(self, level, time, lives):
        '''
        Initializes game, includes:
        1. Setup map+screen, player 1, position player on map
        2. Set numeric codes for class instances
        3. Starts the game timer
        4. Initializes any other variables needed for each game
        '''

        self.screen = Screen(36, 96, level, self)

        self.player = Mario(self, lives)

        # 0: Back, 1: Cloud (Back) ...  5. Mario, 6. Brick, 7. PowerUp

        self.codes = [Backg(), Cloud(), None, None, None, self.player, Brick()]
        for temp in range(1000):
            self.codes.append(None)
            temp += 1
            temp -= 1

        self.screen.position(self.player)

        self.stime = timer()
        self.etime = self.stime + time

        # self.count - self.count_l indicates number of
        # enemies onscreen within any cycle
        self.count = 20
        self.count_l = 20

        self.level = level

        self.points = 0

    def change_state(self, keypress):
        '''
        Calculates and applies changes within each cycle
        '''

        # To check if life is lost within cycle
        clife = self.player.lives

        # Apply mario movement
        self.player.move(keypress)

        # Update background (right/left)
        if self.player.get_loc()[1] > self.screen.offset + configs.OFFSTRAIGHT:
            self.screen.offset += 1

        # Generate any enemies
        if self.level != 0:
            self.generate_enemy()

        # Apply gravity and movement
        # > On powerup
        if self.codes[7] is not None:
            self.codes[7].vertical()
            if (self.get_time()//1) % 2 == 0:
                self.codes[7].move(1)

        # > On enemy
        for enemy in range(self.count_l, self.count):
            if self.codes[enemy] is not None:
                self.codes[enemy].vertical()
                self.codes[enemy].move()

        # > On boss
        if self.codes[999] is not None:
            self.codes[999].move()
            if self.player.j > configs.LEV_J//2:
                self.codes[999].vertical()

        # > On player
        self.player.vertical()

        # Check interactions
        # > Checks which enemy is alive and updates accordingly
        for enemy in range(self.count_l, self.count):
            enj = self.codes[enemy]
            if enj is not None:
                if enj.lives <= 0:
                    self.erase(enemy, 1, enj.i, enj.j)
                    self.count_l += 1

        # > Checks if player is alive and updates accordingly
        if self.player.lives < clife:
            return -1

        # Crossed game level
        if self.player.j >= 400:
            return 1

        return 0

    def generate_enemy(self):
        '''
        Creates an enemy
        '''

        if random() < configs.PROB_ENEMY:
            copy_j = self.screen.offset + configs.DIM_J - randrange(10)
            copy_i = 1
            mush = Enemy(self, self.count, copy_i, copy_j)
            self.screen.position(mush)
            self.codes[self.count] = mush
            self.count += 1

        if self.level == 2 and self.player.j == 50:
            boss = Boss(self, 999, 8, 50)
            self.screen.position(boss)
            self.codes[999] = boss

    def erase(self, objn, direct, copy_i, copy_j):
        '''
        Recursively erases all elements of type objn in direct contact
        '''

        if direct == 1:
            i = copy_i
            j = copy_j + 1
        elif direct == 2:
            i = copy_i
            j = copy_j - 1
        elif direct == 3:
            i = copy_i - 1
            j = copy_j
        elif direct == 4:
            i = copy_i + 1
            j = copy_j

        if i >= 36 or i <= -1:
            return

        if self.screen.gmap[i, j] == objn:
            self.screen.add(Backg(), i, i+1, j, j+1)
            for k in range(1, 5):
                self.erase(objn, k, i, j)

    def delete(self):
        '''
        compatibility
        '''
        pass

    def repaint(self):
        '''
        Repaints the board
        '''
        clear()
        self.screen.render()
        self.headline()

    def headline(self):
        '''
        Part of the render, gives status
        '''
        print('Level: ' + str(self.level) +
              '\t\u23f1 : ' + str(self.get_t_remain()//1) +
              '\t\u2661 : ' + str(self.player.lives))
        print('POINTS: ' + str(self.points))

    @classmethod
    def level_screen(cls, level, lives, points):
        '''
        Printed in between levels
        '''
        clear()
        print("Level: " + str(level))
        print("Lives left: " + str(lives))
        print("Total Points: " + str(points))
        print("Press any key to continue")

    def get_t_remain(self):
        '''
        returns the time remaining for a game
        '''
        return self.etime - timer()

    def get_t_past(self):
        '''
        returns the time elapsed in a game
        '''
        return timer() - self.stime

    @classmethod
    def get_time(cls):
        '''
        returns the current time
        '''
        return timer()
