from tkinter import *

class MyFirstGUI:
    def __init__(self, root):
        self.root = root
        root.title("A simple GUI")

        self.label = Label(root, text="TEXTO")
        self.label.pack()
        
        self.Rvar = IntVar()
        self.Vvar = IntVar()
        self.Avar = IntVar()
        self.red_button = Checkbutton(self.root, text="rojo", variable=self.Rvar, command=self.redd)
        self.red_button.pack()
    
        
    def redd():
    	self.root.configure(background='red')
    	
    def bluee():
    	root.configure(background='blue')
    	
    def greenn():
    	root.configure(background='green')

root = Tk()
my_gui = MyFirstGUI(root)
root.mainloop()
