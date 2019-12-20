#Python 3, Tkinter 8.6
# Sizing and Positioning
 
from tkinter import * 
 
root = Tk()
 
root.geometry("500x100+300+300")
 
def callback():
    print("click!")

def redd():
	root.configure(background='red')
	
def bluee():
	root.configure(background='blue')
	
def greenn():
	root.configure(background='green')
			
b = Button(root, text="CTRL Z", command=callback)
b.pack()

Rvar = IntVar()
c = Checkbutton(
        root, text="rojo", variable=Rvar,
        command=redd)
c.pack()

Vvar = IntVar()
d = Checkbutton(
        root, text="verde", variable=Vvar,
        command=greenn)
d.pack()

Avar = IntVar()
e = Checkbutton(
        root, text="azul", variable=Avar,
        command=bluee)
e.pack()

root.mainloop()

