def mario_exists_in_bounds(GAME):
    PLAYER_POS_I = GAME.player.i
    PLAYER_POS_J = GAME.player.j
    PLAYER_SIZE_I = GAME.player.get_size()[0]
    PLAYER_SIZE_J = GAME.player.get_size()[1]

    # Checking that Mario exists within bounds
    for i in range(PLAYER_POS_I+1-PLAYER_SIZE_I, PLAYER_POS_I+1):
        for j in range(PLAYER_POS_J-1, PLAYER_POS_J-1+PLAYER_SIZE_J):
            assert GAME.screen.gmap[i, j] == 5
