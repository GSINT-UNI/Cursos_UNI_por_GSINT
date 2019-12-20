import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext as st
import re

class App:

	def __init__(self):
		#configuracion de ventana
		self.ventana = tk.Tk()		
		self.ventana.title("GUI")
		self.ventana.geometry("440x200")		
		
		#variables         
		self.checkbuttonvar = tk.IntVar()

		#texto
		self.label = tk.Label(text="texto1")
		self.label.grid(row=0,column=0)

		self.cuadrotexto = st.ScrolledText(self.ventana,width=30, height=10)
		self.cuadrotexto.grid(row=1,column=0)	
		self.cuadrotexto.insert('1.0',"texto insertado")
		#self.cuadrotexto.delete('1.0',tk.END)	
		#obtenertexto = self.cuadrotexto.get('1.0',tk.END)

		#boton
		self.boton1 = tk.Button(self.ventana,text="boton1", command=self.accion1 )
		self.boton1.grid(row=1,column=1)

		#checkbutton
		self.checkbutton1 = tk.Checkbutton(self.ventana,text="Checkbutton1", variable=self.checkbuttonvar,command=self.accion1)	
		self.checkbutton1.grid(row=0,column=1)

		

		self.ventana.mainloop()
	
	#acciones para los botones	
	
	def accion1(self):
		pass
		
	

App()