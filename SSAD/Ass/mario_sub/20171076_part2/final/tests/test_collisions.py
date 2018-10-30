from gamestate import Game
from people import Enemy, PowerUp

def test_mario_collision_with_ground():
    GAME = Game(0, 100, 1)
    mario = GAME.player

    assert mario.collision(4) == (True, (mario.i+1, mario.j-1))
    oldloc = mario.get_loc()
    mario.vertical()
    newloc = mario.get_loc()
    assert oldloc == newloc

def test_mario_collision_with_enemy_side():
    GAME = Game(0, 100, 1)
    mario = GAME.player

    enemy = Enemy(GAME, 33, 31, 6)
    GAME.codes[33] = enemy
    enemy.dir = 0
    GAME.screen.position(enemy)

    mario.move(1)
    assert mario.lives == 0

def test_mario_collision_with_enemy_top():
    GAME = Game(0, 100, 1)
    mario = GAME.player

    mario.move(3)
    mario.vertical()
    mario.vertical()
    mario.vertical()
    mario.vertical()
    mario.vertical()
    mario.vertical()
    mario.vertical()
    print(mario.jstate)
    enemy = Enemy(GAME, 33, 31, 4)
    GAME.codes[33] = enemy
    GAME.screen.position(enemy)
    mario.vertical()
    mario.vertical()
    mario.vertical()
    mario.vertical()
    mario.vertical()
    mario.vertical()
    mario.vertical()
    print(mario.get_loc())

    assert enemy.lives <= 0
    assert GAME.points > 0

def test_large_mario_collision_with_enemy():
    GAME = Game(0, 100, 1)
    mario = GAME.player
    mario.resize(1)

    enemy = Enemy(GAME, 33, 31, 6)
    GAME.codes[33] = enemy
    enemy.dir = 0
    GAME.screen.position(enemy)

    mario.move(1)
    assert mario.get_size() == (3,3)

def test_large_mario_double_collision_with_enemy():
    GAME = Game(0, 100, 1)
    mario = GAME.player
    mario.resize(1)

    enemy = Enemy(GAME, 33, 31, 6)
    GAME.codes[33] = enemy
    enemy.dir = 0
    GAME.screen.position(enemy)

    mario.move(1)
    assert mario.get_size() == (3,3)
    mario.move(1)
    assert mario.lives == 0

def test_mario_collision_with_coin():
    GAME = Game(0, 100, 1)
    mario = GAME.player
    GAME.screen.gmap[30:32, 6:8] = 9

    mario.move(1)
    mario.move(1)
    mario.move(1)
    assert GAME.points > 0

def test_mario_collision_with_powerup():
    GAME = Game(0, 100, 1)
    mario = GAME.player
    powerup = PowerUp(GAME, 31, 6)
    GAME.screen.position(powerup)

    mario.move(1)
    mario.move(1)
    mario.move(1)

    assert mario.get_size() == (4, 3)

def test_enemy_collision_with_brick():
    GAME = Game(0, 100, 1)
    enemy = Enemy(GAME, 33, 31, 6)
    GAME.screen.gmap[30:33, 2:4] = 6
    enemy.move()
    enemy.move()
    enemy.move()
    enemy.move()
    assert enemy.dir == 1
