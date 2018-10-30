from gamestate import Game
from testutil import mario_exists_in_bounds

# Tests are done on all objects with atomic initialization sequences

def test_game_init_with_proper_params():
    '''
    Checks for proper initialization of Game
    '''

    GAME = Game(0, 100, 1)
    # Check time allocated is correct
    assert GAME.etime - GAME.stime == 100
    # Check for object inconsistencies
    assert GAME.screen.game == GAME
    assert len(GAME.codes) == 1007

def test_mario_init_with_default_params():
    '''
    Check for proper initialization of Mario in default
    '''
    GAME = Game(0, 100, 1)

    PLAYER_POS_I = GAME.player.i
    PLAYER_POS_J = GAME.player.j
    PLAYER_SIZE_I = GAME.player.get_size()[0]
    PLAYER_SIZE_J = GAME.player.get_size()[1]

    assert GAME.player.lives == 1
    assert GAME.player.get_size() == (3, 3)

    mario_exists_in_bounds(GAME)
    test_mario_resize_to_large()

def test_mario_resize_to_large():
    GAME = Game(0, 100, 1)

    # Assert changes on resize
    GAME.player.resize(1)
    assert GAME.player.get_size() == (4, 3);
    assert GAME.player.maxj == 11

    mario_exists_in_bounds(GAME)
