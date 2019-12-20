from tkinter import *
import os
 
window = Tk()
 
window.title("AG BC")
 
window.geometry('350x200')
 
lbl = Label(window, text="Moriras gil ;v")
 
lbl.grid(column=0, row=0)
 
def clicked():
 
    lbl.configure(text="Mira fastaselec.fasta en la carpeta ;v")
    os.system('python leer.py')
 
btn = Button(window, text="seleccionar", command=clicked)
 
btn.grid(column=1, row=0)
 
window.mainloop()
