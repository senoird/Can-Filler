import serial as s
import time as t
from tkinter import *
import tkinter as tk



class Action:
    def __init__(self):
        

        def on():
            ser.write(b'7')

        def exit():
            ser.close() # close serial port
            quit()

        self.window = Tk()
        self.window.title("Moore Speciality Brewing")
        self.window.geometry('640x480')
        self.lbl = Label(self.window, text="Can Filler",fg='black',font=(None, 15))
        self.lbl.place(relx=0.24, rely=0.10, height=50, width=350)
        bo = Button(self.window, text="Fill Can", width=10 ,bg='red' ,command=on)
        bo.place(relx=0.34, rely=0.30, height=40, width=200)
        ext = Button(self.window, text="Exit", width=10, bg='white', command=exit)
        ext.place(relx=0.34, rely=0.50, height=40, width=200)

class Prompt(tk.Tk):
    def __init__(self):
        global comm
        comm = None               
        tk.Tk.__init__(self)
        self.geometry('640x480')
        self.label = tk.Label(self, text="Comm Port",fg='black',font=(None, 15))
        self.entry = tk.Entry(self)
        self.button = tk.Button(self, text="Get", command=self.on_button)
        
        self.entry.place(relx=.5, rely=.5,anchor="center" )
        self.label.place(relx=.5, rely=.44,anchor="center")
        self.button.place(relx=.5, rely=.56,anchor="center")

    def on_button(self):
        comm = self.entry.get()
        global ser
        ser = s.Serial(comm, 9600, timeout=0)   # check your com port
        t.sleep(2)
        Action()
        self.destroy()

if __name__ == "__main__":
    prm = Prompt()
    prm.mainloop()
