
import tkinter as tk
import tkinter.scrolledtext as tkscrolledtext
from tkinter import *
from tkinter import filedialog
import serial_rx_tx
import _thread
import time
import webbrowser
from tkinter import messagebox

# globals
serialPort = serial_rx_tx.SerialPort()
logFile = None

root = tk.Tk() # create a Tk root window
root.title( "Moore Specialty Brewing Can Filler" )
# set up the window size and position
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
window_width = screen_width/2
window_height = screen_width/3
window_position_x = screen_width/2 - window_width/2
window_position_y = screen_height/2 - window_height/2
root.geometry('%dx%d+%d+%d' % (window_width, window_height, window_position_x, window_position_y))
root.state('zoomed')

# scrolled text box used to display the serial data
frame = tk.Frame(root, bg='cyan')
frame.pack(side="bottom", fill='both', expand='no')
textbox = tkscrolledtext.ScrolledText(master=frame, wrap='word', width=screen_width, height=25) #width=characters, height=lines
textbox.pack(side='bottom', fill='y', expand=True, padx=0, pady=0)
textbox.config(font="bold")

#COM Port label
label_comport = Label(root,width=10,height=2,text="COM Port:")
label_comport.place(x=10,y=26)
label_comport.config(font="bold")

#COM Port entry box
comport_edit = Entry(root,width=10)
comport_edit.place(x=100,y=36)
comport_edit.config(font="bold")
comport_edit.insert(END,"/dev/ttyACM0")

# serial data callback function
def OnReceiveSerialData(message):
    str_message = message.decode("utf-8")
    textbox.insert('1.0', str_message)

# Register the callback above with the serial port object
serialPort.RegisterReceiveCallback(OnReceiveSerialData)

def sdterm_main():
    root.after(200, sdterm_main)  # run the main loop once each 200 ms

#
#  commands associated with button presses
#
def OpenCommand():
    if button_openclose.cget("text") == 'Open COM Port':
        comport = comport_edit.get()
        baudrate = baudrate_edit.get()
        serialPort.Open(comport,baudrate)
        button_openclose.config(text='Close COM Port')
        textbox.insert('1.0', "COM Port Opened\r\n")
    elif button_openclose.cget("text") == 'Close COM Port':
        if button_replaylog.cget('text') == 'Stop Replay Log':
            textbox.insert('1.0',"Stop Log Replay first\r\n")
        else:
            serialPort.Close()
            button_openclose.config(text='Open COM Port')
            textbox.insert('1.0',"COM Port Closed\r\n")


def ClearDataCommand():
    textbox.delete('1.0',END)

def SendDataCommand():
    message = senddata_edit.get()
    if serialPort.IsOpen():
        message += '\r\n'
        serialPort.Send(message)
        textbox.insert('1.0',message)
    else:
        textbox.insert('1.0', "Not sent - COM port is closed\r\n")

def Lower_Head():
    
    lower = "c0"
    if serialPort.IsOpen():
        lower += '\r\n'
        serialPort.Send(lower)
        textbox.insert('1.0',lower)
    else:
        textbox.insert('1.0', "Not sent - COM port is closed\r\n")

def PurgeFill():
    purge = "c1"
    if serialPort.IsOpen():
        purge += '\r\n'
        serialPort.Send(purge)
        textbox.insert('1.0',purge)
        
    else:
        textbox.insert('1.0', "Not sent - COM port is closed\r\n")

def Raise_Head():
    raise_ = "c2"
    if serialPort.IsOpen():
        raise_ += '\r\n'
        serialPort.Send(raise_)
        textbox.insert('1.0',raise_)
    else:
        textbox.insert('1.0', "Not sent - COM port is closed\r\n")

# COM Port open/close button
button_openclose = Button(root,text="Open COM Port",width=20,command=OpenCommand)
button_openclose.config(font="bold")
button_openclose.place(x=210,y=30)

#Clear Rx Data button
button_cleardata = Button(root,text="Clear Rx Data",width=20,command=ClearDataCommand)
button_cleardata.config(font="bold")
button_cleardata.place(x=210,y=72)

#Manual Command button
button_command = Button(root,text="Manual Command",width=20,command=SendDataCommand)
button_command.config(font="bold")
button_command.place(x=210,y=114)

#Lower button
button_lower = Button(root,text="Lower",width=16,height=5,bg="red",command=Lower_Head)
button_lower.config(font="bold")
button_lower.place(x=(screen_width/2)-80,y=30)

#Purge/Fill button
button_fill = Button(root,text="Purge/Fill",width=16,height=5,bg="green",command=PurgeFill)
button_fill.config(font="bold")
button_fill.place(x=(screen_width/2)-80,y=150)

#Raise Button
button_raise = Button(root,text="Raise",width=16,height=5,bg="blue",command=Raise_Head)
button_raise.config(font="bold")
button_raise.place(x=(screen_width/2)-80,y=270)

#
# data entry labels and entry boxes
#

#Send Command entry box
senddata_edit = Entry(root,width=21)
senddata_edit.place(x=210,y=156)
senddata_edit.config(font="bold")
senddata_edit.insert(END,"Command")

#Baud Rate label
label_baud = Label(root,width=10,height=2,text="Baud Rate:")
label_baud.place(x=10,y=70)
label_baud.config(font="bold")

#Baud Rate entry box
baudrate_edit = Entry(root,width=10)
baudrate_edit.place(x=100,y=80)
baudrate_edit.config(font="bold")
baudrate_edit.insert(END,"115200")

#
# The main loop
#
root.after(200, sdterm_main)
root.mainloop()
#


