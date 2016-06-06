import serial
from tkinter import *

pressed = 0b00000000
prev = pressed

keysymToBitmask = {
    'Alt_L'     : 0b10000000, # A
    'Control_L' : 0b01000000, # B
    'Shift_R'   : 0b00100000, # SELECT
    'Return'    : 0b00010000, # START
    'Up'        : 0b00001000, # UP
    'Down'      : 0b00000100, # DOWN
    'Left'      : 0b00000010, # LEFT
    'Right'     : 0b00000001  # RIGHT
}

def onKeyDown(e) :
    global pressed
    pressed |= keysymToBitmask.get(e.keysym, 0b00000000)

def onKeyUp(e) :
    global pressed
    pressed -= keysymToBitmask.get(e.keysym, 0b00000000)

########################################################

port = '/dev/ttyACM0'
baud = 9600

ser = serial.Serial(port, baud, timeout=1)

root = Tk()
frame = Frame(root, width=100, height=100)
frame.bind("<KeyPress>", onKeyDown)
frame.bind("<KeyRelease>", onKeyUp)
frame.pack()
frame.focus_set()

while True :
    root.update_idletasks()
    root.update()
    if prev != pressed :
        prev = pressed
        ser.write(bytes(chr(pressed), 'utf-8'))
        ser.flush()
        """
        print('pressed: ' + str(pressed))
        res = ser.readline().strip().decode('utf-8')
        #print('{0:08b}'.format(res))
        print(res)
        """
