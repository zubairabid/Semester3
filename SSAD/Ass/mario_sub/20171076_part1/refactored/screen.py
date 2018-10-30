'''
File managing the screen: printing, adding to a map, loading map. etc.
'''

import numpy as np
from colorama import Fore, Back, Style

import maps
import configs


class Screen:
    '''
    An object of class represents a single screen
    Contains helper functions to carry out simple operations based on screen.
    '''

    def __init__(self, dim_i, dim_j, level, game):
        '''
        Initializes screen with dimensions j (x-axis), i (y-axis)
        '''

        self.game = game

        # Set up map
        self.gmap = np.array([[0 for col in range(configs.MAX_J)]
                              for row in range(dim_i)])
        self.load_map(level)

        # offset from where map starts displaying on screen
        self.offset = 0

        # height, width of map
        self.dim_i = dim_i
        self.dim_j = dim_j

    def load_map(self, level):
        '''
        Calls the random map generator to get a map for level specified
        '''
        print('Loading level ' + str(level))
        for component in maps.genlevel(level):
            vst = component[0]
            vh = component[2]
            hst = component[1]
            hh = component[3]
            self.gmap[vst:vst + vh, hst:hst + hh] = component[4]

    def position(self, obj):
        '''
        Given an object, it places it on the map's[i,j] as defined by object's
        i, j and get_size()
        '''
        size = obj.get_size()

        from_i = obj.i+1-size[0]
        to_i = obj.i+1
        from_j = obj.j-1
        to_j = obj.j-1+size[1]

        self.gmap[from_i:to_i, from_j:to_j] = obj.code

    def add(self, obj, from_i, to_i, from_j, to_j):
        '''
        Places obj.code within range specified
        '''
        self.gmap[from_i:to_i, from_j:to_j] = obj.code

    def render(self):
        '''
        Generates the screen
        '''

        # Used to render Mario's character properly
        trackc = 0
        sky = Back.BLUE
        brick = Back.GREEN

        if self.game.level == 2:
            sky = Back.BLACK
            brick = Back.MAGENTA

        for i in self.gmap:
            for j in range(self.offset, self.offset + self.dim_j):

                char = ''

                # Sky
                if i[j] == 0:
                    char = sky + Fore.BLACK + ' '

                # Clouds
                if i[j] == 1:
                    char = Back.WHITE + '0'

                # Mario
                if i[j] == 5:
                    if trackc in (0, 2):
                        char = 'O'
                    else:
                        char = '|'
                    trackc += 1
                    char = sky + Fore.RED + char

                # Brick
                if i[j] == 6:
                    char = brick + '.'

                # PowerUp
                if i[j] == 7:
                    char = Back.CYAN + '*'

                # Hidden Brick
                if i[j] == 8:
                    char = Back.YELLOW + 'X'

                # Coins
                if i[j] == 9:
                    char = sky + Fore.YELLOW + 'O'

                # Enemy
                if i[j] >= 20:
                    char = Back.RED + Fore.BLACK + '^'

                print(char, end='')

            print(Style.RESET_ALL+'')
