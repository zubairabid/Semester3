from gamestate import Game
from testutil import mario_exists_in_bounds

# Tests are done only for the Mario class as it's the same template
# As all the other movement functions due to Inheritance

def test_mario_move_right():
    GAME = Game(0, 100, 1)
    mario = GAME.player
    oldloc = mario.get_loc()
    mario.move(1)
    newloc = mario.get_loc()

    assert oldloc[1] == newloc[1] - 1

    mario_exists_in_bounds(GAME)

def test_mario_move_left():
    GAME = Game(0, 100, 1)
    mario = GAME.player
    oldloc = mario.get_loc()
    mario.move(2)
    newloc = mario.get_loc()

    assert oldloc[1] == newloc[1] + 1

    mario_exists_in_bounds(GAME)

def test_mario_jump():
    GAME = Game(0, 100, 1)
    mario = GAME.player

    mario.move(3)
    # Check jump up
    assert mario.jstate == mario.maxj
    while mario.jstate > 0:
        pjstate = mario.jstate
        mario.vertical()
        if pjstate == 1:
            assert mario.jstate == -1
        else:
            assert mario.jstate == pjstate - 1
        mario_exists_in_bounds(GAME)
