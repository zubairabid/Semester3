'''
File defining basic Background object classes
'''

from objects import Generic


class Background(Generic):
    '''
    Defines the background, aka Sky
    '''

    def __init__(self):
        super().__init__()
        self.code = 0


class Cloud(Background):
    '''
    Defines Clouds
    '''

    def __init__(self):
        super().__init__()
        self.code = 1
