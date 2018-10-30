'''
File defining basic non-background object classes
'''


class Generic:
    '''
    Every object in the game inherits from here.
    '''

    def __init__(self):
        pass

    def get_size(self):
        '''
        Generic
        '''
        pass

    def get_loc(self):
        '''
        Generic
        '''
        pass


class Thing(Generic):
    '''
    Generic object
    '''

    def __init__(self):
        super().__init__()


class Brick(Thing):
    '''
    Defines the generic brick
    '''

    def __init__(self):
        super().__init__()
        self.code = 6


class HidBrick(Brick):
    '''
    Defines the brick hiding powerup
    '''

    def __init__(self):
        super().__init__()
        self.code = 8


class Coin(Thing):
    '''
    Defines coin
    '''

    def __init__(self):
        super().__init__()
        self.code = 9
