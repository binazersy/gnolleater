# snake.py
#
# issue:
# vertical direction speed problem.
# move faster than horizontal direction cause it has diffrent resolution
#
# input reverse direction yields immediate quit

import random
import curses

s = curses.initscr()
curses.curs_set(0)
sh, sw = s.getmaxyx()
w = curses.newwin(sh, sw, 0, 0)
w.keypad(1)
w.timeout(100)

# snake position
snake_x = sw/4
snake_y = sh/2

# snake initial length = 3
snake = [
    [snake_y, snake_x],
    [snake_y, snake_x-1],
    [snake_y, snake_x-2]
]

# food
food = [sh/2, sw/2]
w.addch(food[0], food[1], curses.ACS_PI)

key = curses.KEY_RIGHT

while True:
    next_key = w.getch()
    key = key if next_key == -1 else next_key

    # out of screen or bite itself
    if snake[0][0] in [1, sh-1] or snake[0][1] in [1, sw-1] or snake[0] in snake[1:]:
        curses.endwin()
        quit()

    # seems like to move by
    # adding new head forward current head by direction and remove tail
    # if eats food, leave tail(grow) and make new food

    # new head
    new_head = [snake[0][0], snake[0][1]]

    if key == curses.KEY_DOWN:
        new_head[0] += 1
    if key == curses.KEY_UP:
        new_head[0] -= 1
    if key == curses.KEY_LEFT:
        new_head[1] -= 1
    if key == curses.KEY_RIGHT:
        new_head[1] += 1

    snake.insert(0, new_head)

    if snake[0] == food:
        food = None
        while food is None:
            # new food except snake's position
            nf = [random.randint(1, sh-1), random.randint(1, sw-1)]
            food = nf if nf not in snake else None
        
        w.addch(food[0], food[1], curses.ACS_PI)
    else:
        # remove tail
        tail = snake.pop()
        w.addch(tail[0], tail[1], ' ')
    
    w.addch(snake[0][0], snake[0][1], curses.ACS_CKBOARD)