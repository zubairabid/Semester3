import configs

from objects import Generic
from objects import Brick

import backgrounds as back

from colorama import Fore, Back, Style


class Person(Generic):
    '''
    Generic class for all living beings in the game.
    Defines a subclass':
        Location
        Max jump height
        Parent game
        Lives
    Functionality provided includes:
        getLoc() returns location
        getSize() returns size (default: 1,1)
        collison(dir) returns (collision val, co-ordinates) in direction dir
        move(dir) moves the object by 1 in dir
        vertical() provides gravitational + jump functionality to the object
    '''

    def __init__(self, game, i=0, j=0, s_i=1, s_j=1):
        '''
        Location is a default property of all "people"
        '''
        super().__init__()

        # Game object being referred to
        self.game = game

        # Max jump height of Person
        self.maxj = 7

        # Location of Person
        self.i = i
        self.j = j

        # Size of a Person
        self.s_i = s_i
        self.s_j = s_j

        # Default jump state of Person
        # (>0: jumping up, 0: stable, <0: falling)
        self.jstate = 0

        self.lives = 1

    def getLoc(self):
        return (self.i, self.j)

    def getSize(self):
        # Default size of a Person is set to 1,1 unless overridden
        return (self.s_i, self.s_j)

    def collision(self, dir):
        '''
        returns True, (location of crash object) if crash,
                and False, (0,0) if no crash

        To check for collision, it checks if the object in
        dir direction is not background; aka code >= 5
        '''

        # Direction: right
        if dir == 1:
            for i in range(self.i+1-self.getSize()[0], self.i+1):
                if self.game.screen.map[i, self.j + self.getSize()[1]-1] >= 5:
                    return (True, (i, self.j + self.getSize()[1]-1))

        # Direction: left
        elif dir == 2:
            for i in range(self.i + 1 - self.getSize()[0], self.i + 1):
                if self.game.screen.map[i, self.j - 2] >= 5:
                    return (True, (i, self.j - 2))

        # Direction: up
        elif dir == 3:
            for j in range(self.j - 1, self.j - 1 + self.getSize()[1]):
                if self.game.screen.map[self.i - self.getSize()[0], j] >= 5:
                    return (True, (self.i - self.getSize()[0], j))

        # Direction: down
        elif dir == 4:

            # Death
            if self.i == 35:
                self.lives -= 1
                return True, (0, 0)

            for j in range(self.j - 1, self.j - 1 + self.getSize()[1]):
                if self.game.screen.map[self.i + 1, j] >= 5:
                    return (True, (self.i + 1, j))

        return (False, (0, 0))

    def move(self, key):
        '''
        For left/right movements, adds -1 or +1 to self.i accordingly
        For up, it sets jstate to maxj. vertical() takes care of actual
        movement here
        '''

        # d, go right
        if key == 1:
            # right collision
            if not self.collision(1)[0]:
                self.j += 1

                # Delete the layer Person crossed, and add to the layer added
                t_i = self.i+1
                f_i = self.i+1-self.getSize()[0]

                del_j = self.j-1
                add_j = self.j-1+self.getSize()[1]

                self.game.screen.add(back.Back(), f_i, t_i, del_j-1, del_j)
                self.game.screen.add(self, f_i, t_i, add_j-1, add_j)

        # a, go left
        if key == 2:
            # left collision
            if not self.collision(2)[0]:
                self.j -= 1

                # Delete the layer Person crossed, and add to the layer added
                t_i = self.i+1
                f_i = self.i+1-self.getSize()[0]

                add_j = self.j-1
                del_j = self.j-1+self.getSize()[1]

                self.game.screen.add(back.Back(), f_i, t_i, del_j, del_j+1)
                self.game.screen.add(self, f_i, t_i, add_j, add_j+1)

        # w, go up
        if key == 3:
            if self.jstate == 0:
                self.jstate = self.maxj

    def vertical(self):
        '''
        Responsible for all vertical movement of a Person
        Applies gravity - unless Person is in a positive jstate
        '''

        if self.jstate > 0:
            # Up collision
            if not self.collision(3)[0]:

                self.jstate -= 1

                #  minor hack to stop double jumps
                if self.jstate == 0:
                    self.jstate -= 1

                self.i -= 1

                # Delete the layer Person crossed, and add to the layer added
                t_j = self.j+self.getSize()[1]-1
                f_j = self.j-1

                del_i = self.i+1
                add_i = self.i+1-self.getSize()[0]

                self.game.screen.add(back.Back(), del_i, del_i+1, f_j, t_j)
                self.game.screen.add(self, add_i, add_i+1, f_j, t_j)
            else:
                self.jstate = 0
        else:
            # down collison
            if not self.collision(4)[0]:
                self.jstate -= 1
                self.i += 1

                # Delete the layer Person crossed, and add to the layer added
                t_j = self.j+self.getSize()[1]-1
                f_j = self.j-1

                add_i = self.i+1
                del_i = self.i+1-self.getSize()[0]

                self.game.screen.add(back.Back(), del_i-1, del_i, f_j, t_j)
                self.game.screen.add(self, add_i-1, add_i, f_j, t_j)
            else:
                self.jstate = 0


class Mario(Person):
    '''
    Class defining the main Mario player. Makes some modifications to parent
    class Person
    '''

    def __init__(self, game, lives):
        super().__init__(game, 31, 3, 3, 3)

        self.jstate = 0
        self.maxj = 7

        self.code = 5

        self.lives = lives

    def resize(self, size):
        # small
        if size == 0:
            self.s_i = 3
            self.game.screen.add(back.Back(), self.i-3, self.i-2, self.j-1,
                                 self.j+2)
            self.maxj = 7
        # large
        else:
            self.s_i = 4
            self.game.screen.add(self, self.i-3, self.i-2, self.j-1, self.j+2)
            self.maxj = 11

    def collision(self, dir):
        '''
        Defines exactly how the Mario object will behave on collision
        beyond the regular generic Person functions
        '''

        contact = super().collision(dir)
        obj = self.game.screen.map[contact[1][0], contact[1][1]]

        if contact:

            # Collision with brick from below as large body
            if obj == 6 and dir == 3 and self.getSize()[0] == 4:
                self.game.erase(obj, dir, contact[1][0], contact[1][1])

            # Collison with a PowerUp
            if obj == 7:
                self.resize(1)
                self.game.erase(obj, dir, contact[1][0], contact[1][1])
                self.game.codes[obj] = None
                self.game.points += configs.POINTS_PUP

            # Collision with a hidden brick
            if obj == 8 and dir == 3:
                hi = contact[1][0]
                hj = contact[1][1]
                pow = PowerUp(self.game, hi-2, hj)
                self.game.codes[7] = pow
                self.game.screen.position(pow)
                self.game.erase(8, 1, hi - 1, hj)
                self.game.erase(8, 2, hi - 1, hj)
                self.game.screen.add(Brick(), hi - 1, hi + 1, hj, hj + 4)

            # On collison with a coin
            if obj == 9:
                self.game.erase(obj, dir, contact[1][0], contact[1][1])
                self.game.points += configs.POINTS_COIN

            # On collison with enemy
            if obj >= 20:
                # Collision below
                if dir == 4:
                    if self.game.codes[obj] is not None:
                        self.game.codes[obj].lives -= 1
                        self.game.points += configs.POINTS_ENMY
                else:
                    if self.getSize()[0] == 4:
                        self.resize(0)
                    else:
                        self.lives -= 1

        return contact


class Enemy(Person):

    def __init__(self, game, code, i, j):
        super().__init__(game, i, j, 1, 3)

        self.maxj = 6
        self.jstate = 0

        self.code = code

        self.dir = 2

    def move(self):
        super().move(self.dir)
        if self.collision(self.dir)[0]:
            if self.dir == 1:
                self.dir = 2
            else:
                self.dir = 1

    def collision(self, dir):
        contact = super().collision(dir)

        if contact:
            obj = self.game.screen.map[contact[1][0], contact[1][1]]
            if obj == 5:
                if self.game.codes[5].getSize()[0] == 4:
                    self.game.codes[5].resize(0)
                else:
                    self.game.codes[5].lives -= 1

        return contact


class Boss(Person):
    '''
    Defining behaviour for Boss enemy
    '''

    def __init__(self, game, code, i, j):
        super().__init__(game, i, j, 6, 10)

        self.code = code

    def move(self):
        '''
        Moves so as to track the player
        '''

        # Move to the right if falling short
        if self.j > self.game.player.j:
            super().move(2)
        elif self.j == self.game.player.j:
            pass
        # and to the left if ahead
        else:
            super().move(1)

    def collision(self, dir):
        '''
        Only measures collisions with player for removing
        Doesn't check for other collisions. Kills them all
        '''
        contact = super().collision(dir)
        obj = self.game.screen.map[contact[1][0], contact[1][1]]

        if obj == 5:
            self.game.codes[obj].lives -= 1

        return obj == 5, contact[1]

    def vertical(self):
        '''
        Just goes up and down within given range
        '''
        if self.i >= configs.BOSSLOW:
            self.jstate = configs.BOSSLOW - self.s_i

        super().vertical()


class PowerUp(Person):
    '''
    Not a person, but it's live so
    '''
    def __init__(self, game, i, j):
        super().__init__(game)
        self.code = 7
        self.i = i
        self.j = j

    def getSize(self):
        return 2, 2
