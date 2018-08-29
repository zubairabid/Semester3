import configs

from random import random
from random import randrange


def genlevel(num):
    '''
    generates a map for level num
    '''
    map = []

    pipes = 0.03
    staircase = 0.001
    gaps = 0.01
    pipegap = 0.4
    stairgap = 0.2
    clouds = 0.08
    platform1 = 0.02
    platformcoins = 0.7
    platform2 = 0.7
    coins = 0
    powerup = 0.2

    if num == 0:
        gaps = 0.02
        pipes = 0.01
        platformcoins = 1
        coins = 0.03

    if num == 2:
        pipes = 0.05
        gaps = 0.03
        pipegap = 0.6
        platform1 = 0.05

    # a floor
    map.append([32, 0, 4, configs.MAX_J - 100, 6])

    # Coins on floor
    for j in range(configs.LEV_J):
        if random() < coins:
            map.append([30, j, 2, 2, 9])
            map.append([30, j+3, 2, 2, 9])
            map.append([30, j+6, 2, 2, 9])
            map.append([30, j+9, 2, 2, 9])

    # Adding pipe
    for j in range(30, configs.LEV_J):
        if random() < pipes:
            map.append([28, j-4, 4, 4, 6])

    # Adding staircase
    for j in range(30, configs.LEV_J):
        if random() < staircase or j == 380 or j == 40:
            map.append([31, j, 1, 16, 6])
            map.append([30, j+4, 1, 12, 6])
            map.append([29, j+8, 1, 8, 6])
            map.append([28, j+12, 1, 4, 6])

    # Adding gaps
    for j in range(20, configs.LEV_J):
        if random() < gaps:
            map.append([24, j, 12, 5, 0])

            # Adding pipe before gap
            if random() < pipegap:
                map.append([28, j-4, 4, 4, 6])

            # Adding a staircase before a gap
            if random() < stairgap:
                map.append([31, j-12, 1, 16, 6])
                map.append([30, j-8, 1, 12, 6])
                map.append([29, j-4, 1, 8, 6])
                map.append([28, j, 1, 4, 6])

    # Adding clouds
    for j in range(configs.LEV_J):
        if random() < clouds:
            map.append([2, j, 4, 4, 1])
            map.append([4, j-1, 2, 6, 1])

    # Adding platform 1
    for j in range(configs.LEV_J):
        if random() < platform1:
            map.append([23, j, 2, 4, 6])
            map.append([23, j+5, 2, 4, 6])
            map.append([23, j+10, 2, 4, 6])

            # Powerup
            if random() < powerup:
                map.append([23, j, 2, 4, 8])

            # Add coins on platform
            if random() < platformcoins:
                map.append([17, j, 2, 2, 9])
                map.append([17, j+3, 2, 2, 9])
                map.append([17, j+6, 2, 2, 9])
                map.append([17, j+9, 2, 2, 9])

            # Adding platform 2:
            if random() < platform2:
                map.append([12, j, 2, 4, 6])
                map.append([12, j+5, 2, 4, 6])
                map.append([12, j+10, 2, 4, 6])

                # PowerUp on platform 2
                if random() < 0.2:
                    map.append([12, j+5, 2, 4, 8])

    # mandatory powerup
    map.append([23, 60, 2, 4, 8])

    # Level ender
    map.append([0, 402, 35, 1, 6])

    return map
