import curses


class MainScreen:

    def __init__(self, screen):
        self.screen = screen
        self.last_pressed_key = None
        # dummy, connection, speed
        self.view_state_index = 0
        self.speed = 100
        self.connected = False
        return

    def draw(self):
        # Clear screen
        # stdscr.clear()
        # stdscr.border(0)
        self.screen.box()

        # static text 
        curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK) 

        # warning text 
        curses.init_pair(2, curses.COLOR_RED, curses.COLOR_BLUE)  

        # info text
        curses.init_pair(3, curses.COLOR_MAGENTA, curses.COLOR_WHITE)

        curses.init_color(100, 30, 100, 30)
        curses.init_pair(4, 100, curses.COLOR_BLACK)

        self.screen.bkgdset(' ', curses.color_pair(1))
        self.draw_connection_line(False, self.connected)
        self.draw_speed_line(False, self.speed)

        self.screen.addstr(4, 1, "K1 chng", curses.color_pair(4))
        self.screen.addstr(5, 1, "K2 sel", curses.color_pair(4))
        self.screen.addstr(6, 1, "K3 exit", curses.color_pair(4))

    def update(self):
        self.draw_connection_line(self.view_state_index is 1, self.connected)
        self.draw_speed_line(self.view_state_index is 2, self.speed)
        if self.last_pressed_key is not None:
            self.screen.addstr(8, 1, "key pressed %s" % self.last_pressed_key, curses.color_pair(4))
            self.last_pressed_key = None
        return 
    
    def change_speed(self):
        self.speed += 10
        if self.speed > 255:
            self.speed = 10

    def reconnect(self):
        self.connected = True
        return

    def draw_connection_line(self, selected, connected):
        self.screen.addstr(1, 1, "Connected", curses.color_pair(1))
        if connected:
            conn_state_txt = "Y"
        else:
            conn_state_txt = "N"

        if selected:                                 
            text = "-%s-"
        else:
            text = " %s "
        self.screen.addstr(1, 12, text % conn_state_txt, curses.color_pair(3))

    def draw_speed_line(self, selected, speed): 
        self.screen.addstr(2, 1, "Speed", curses.color_pair(1))
        if selected:
            text = "-%+3s-"
        else:
            text = " %+3s "
        self.screen.addstr(2, 12, text % speed, curses.color_pair(3))

    def on_key_pressed(self, key):
        self.last_pressed_key = key
        if key is '2':
            self.view_state_index+= 1
            if self.view_state_index > 2: 
                self.view_state_index = 0                
        elif key is '3':
            self.view_state_index = 0
        elif key is '1' and self.view_state_index > 0:
            if self.view_state_index is 1:
                self.reconnect()
            else: 
                self.change_speed()
        return



def main(stdscr):
    screen = MainScreen(stdscr)

    screen.draw()
    
    while True:
        stdscr.refresh()
        key = stdscr.getkey()
        if key == 'q': 
            exit(0)

        screen.on_key_pressed(key)
        screen.update()

curses.initscr()
curses.start_color()
curses.use_default_colors()
curses.wrapper(main)