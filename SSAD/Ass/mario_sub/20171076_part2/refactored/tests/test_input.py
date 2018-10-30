from util import keypress
import pytest

def test_keypress():

    for i in range(65536):
        character = chr(i)

        if character == 'Q':
            assert keypress('Q') == -1;
        elif character == 'q':
            assert keypress('q') == -1;
        elif character == 'W':
            assert keypress('W') == 3;
        elif character == 'w':
            assert keypress('w') == 3;
        elif character == 'A':
            assert keypress('A') == 2;
        elif character == 'a':
            assert keypress('a') == 2;
        elif character == 'D':
            assert keypress('D') == 1;
        elif character == 'd':
            assert keypress('d') == 1;
        else:
            assert keypress(character) == 0
