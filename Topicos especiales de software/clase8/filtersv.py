import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext as st
import re

class Abstract_filter:

	def __init__(self,texto):
		self.texto = texto

	def filter(self,cadena):
		pass



class Capitalize(Abstract_filter):
	
	def filter(self,cadena):
		return cadena.upper()


class Reverse(Abstract_filter):
	
	def filter(self,cadena):
		return cadena[::-1]


class FiltraSpace(Abstract_filter):
	
	def filter(self,cadena):
		return re.sub(r'[\t ]+',' ',cadena)


class DolarToSoles(Abstract_filter):
	
	def filter(self,cadena):
		pass


class SolesToDolar(Abstract_filter):
	
	def filter(self,cadena):
		pass



class Contador(Abstract_filter):
	
	def filter(self,cadena):
		return str(len(re.findall(r'\w+',cadena)))


class Aplicacion:
	def __init__(self):
		self.ventana1=tk.Tk()
		self.scrolledtext1=st.ScrolledText(self.ventana1, width=50, height=10)
		self.scrolledtext1.grid(column=0,row=0, columnspan=3,padx=10, pady=10)

		self.boton1=ttk.Button(self.ventana1, text="Capitalize", command=self.capital)
		self.boton1.grid(column=0, row=1, padx=10, pady=10)

		self.boton2=ttk.Button(self.ventana1, text="Reverse", command=self.reverse)
		self.boton2.grid(column=1, row=1, padx=10, pady=10)

		self.boton3=ttk.Button(self.ventana1, text="Filter Spaces", command=self.space)
		self.boton3.grid(column=2, row=1, padx=10, pady=10)

		self.boton4=ttk.Button(self.ventana1, text="Dolar a sol", command=self.dolarToSol)
		self.boton4.grid(column=0, row=2, padx=10, pady=10)

		self.boton5=ttk.Button(self.ventana1, text="Sol a dolar", command=self.solToDolar)
		self.boton5.grid(column=1, row=2, padx=10, pady=10)

		self.boton6=ttk.Button(self.ventana1, text="Contador", command=self.contar)
		self.boton6.grid(column=2, row=2, padx=10, pady=10)


		self.scrolledtext2=st.ScrolledText(self.ventana1, width=50, height=10)
		self.scrolledtext2.grid(column=0,row=4, columnspan=3, padx=10, pady=10)
		self.ventana1.mainloop()


	def capital(self):
		self.scrolledtext2.delete('1.0',tk.END)
		filtro= Capitalize(self.scrolledtext1.get('1.0',tk.END))
		print(filtro.filter(filtro.texto))
		self.scrolledtext2.insert("1.0",filtro.filter(filtro.texto))

	def reverse(self):	
		self.scrolledtext2.delete('1.0',tk.END)
		filtro= Reverse(self.scrolledtext1.get('1.0',tk.END))
		print(filtro.filter(filtro.texto))
		self.scrolledtext2.insert("1.0",filtro.filter(filtro.texto))

	def space(self):
		self.scrolledtext2.delete('1.0',tk.END)		
		filtro= FiltraSpace(self.scrolledtext1.get('1.0',tk.END))
		print(filtro.filter(filtro.texto))
		self.scrolledtext2.insert("1.0",filtro.filter(filtro.texto))


	def dolarToSol(self):
		pass


	def solToDolar(self):
		pass


	def contar(self):
		self.scrolledtext2.delete('1.0',tk.END)		
		filtro= Contador(self.scrolledtext1.get('1.0',tk.END))
		print(filtro.filter(filtro.texto))
		self.scrolledtext2.insert("1.0",filtro.filter(filtro.texto))




aplicacion1=Aplicacion() 
