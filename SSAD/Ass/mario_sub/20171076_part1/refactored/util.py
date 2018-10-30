'''
File containing utility functions for assorted purposes.
Functions include:
    clearing screen
    taking non-blocking keypresses
'''

import sys
import select
import tty
import termios

import subprocess as sp


def clear():
    '''
    function to clear the terminal screen
    '''
    sp.call('clear', shell=True)


def keypress(keyin):
    '''
    Identifies which key was pressed
    '''

    if keyin in ('Q', 'q'):
        return -1
    if keyin in ('D', 'd'):
        return 1
    if keyin in ('A', 'a'):
        return 2
    if keyin in ('W', 'w'):
        return 3

    return 0


class NBInput:
    '''
    class to deal with non-blocking input
    '''

    def __init__(self):
        '''
        Initializes the object to be used for non-blocking input.
         - Saves original state at time of function call
         - Conversion to new mode has to be manual
        '''
        self.old_settings = termios.tcgetattr(sys.stdin)

    @classmethod
    def nb_term(cls):
        '''
        Sets up the terminal for non-blocking input
        '''
        tty.setcbreak(sys.stdin.fileno())

    def or_term(self):
        '''
        Sets terminal back to original state
        '''
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, self.old_settings)

    @classmethod
    def kb_hit(cls):
        '''
        returns True if keypress has occured
        '''
        return select.select([sys.stdin], [], [], 0) == ([sys.stdin], [], [])

    @classmethod
    def get_ch(cls):
        '''
        returns input character
        '''
        return sys.stdin.read(1)

    @classmethod
    def flush(cls):
        '''
        clears input buffer
        '''
        termios.tcflush(sys.stdin, termios.TCIOFLUSH)
