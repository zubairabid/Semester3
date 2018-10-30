from objects import Generic
from colorama import Fore, Back, Style


class Back(Generic):
    '''
    Defines the background, aka Sky
    '''

    def __init__(self):
        super().__init__()
        self.code = 0


class Cloud(Back):
    '''
    Defines Clouds
    '''

    def __init__(self):
        super().__init__()
        self.code = 1
