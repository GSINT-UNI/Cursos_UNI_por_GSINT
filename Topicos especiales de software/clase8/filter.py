import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext as st
import re

class FiltroAbstracto:
	def filtro(self,cadena): 
		pass

class Capitalizar(FiltroAbstracto):	
	def filtro(self,cadena):
		return cadena.upper()

class Reverse(FiltroAbstracto):
	def filtro(self,cadena):
		return cadena[::-1]

class FiltrarEspacio(FiltroAbstracto):
	def filtro(self,cadena):
		return " ".join(cadena.split())

class DolaraSoles(FiltroAbstracto):
	def filtro(self,cadena):		
		numero = re.findall(r"([+-]?\d+(\.\d+)?)",cadena)
		#[print(a[0]) for a in numero]
		numero = ["{0:.2f}".format(float(a[0])*3.38) for a in numero]
		#print(numero)			
		cadena = re.sub("\d+(\.\d+)?",
		lambda match: str(numero.pop(0)),
		cadena)		
		#self.cadena = re.sub("(dolar)|(dólar)","sol",self.cadena)
		#self.cadena = re.sub("(dolares|dólares)","soles",self.cadena)
		return cadena.replace("$","S")

class SolesaDolares(FiltroAbstracto):
	def filtro(self,cadena):
		numero = re.findall(r"([+-]?\d+(\.\d+)?)",cadena)
		numero = ["{0:.2f}".format(float(a[0])*0.2958579881656805) for a in numero]
		cadena = re.sub("\d+(\.\d+)?",
		lambda match: str(numero.pop(0)),
		cadena)		
		return cadena.replace("$","S")

class CuentaPalabras(FiltroAbstracto):
	def filtro(self,cadena):
		return len(re.findall(r'\w+',cadena))

class App:

	def __init__(self):
		#configuracion de ventana
		self.ventana = tk.Tk()		
		self.ventana.title("Patron filtro")
		self.ventana.geometry("500x420")		
		
		#variables         
		self.entradavar = tk.StringVar()
		self.salidavar = tk.StringVar()	

		#botones para el cambio 
		self.capitalbutton = tk.Button(self.ventana,text="Capitalizar", command=self.capital )
		self.capitalbutton.grid(row=1,column=1)		
		self.revesbutton = tk.Button(self.ventana,text="Al reves", command=self.voltear )
		self.revesbutton.grid(row=2,column=1)			
		self.quitarespaciobutton = tk.Button(self.ventana,text="Quitar espacio", command=self.quitar )
		self.quitarespaciobutton.grid(row=3,column=1)	

		self.soladolbutton = tk.Button(self.ventana,text="Soles a Dolares", command=self.soladolar )
		self.soladolbutton.grid(row=1,column=2)		
		self.dolasolbutton = tk.Button(self.ventana,text="Dolares a Soles", command=self.dolarasol )
		self.dolasolbutton.grid(row=2,column=2)			
		self.cuentapalbutton = tk.Button(self.ventana,text="Cuenta Palabras", command=self.contar )
		self.cuentapalbutton.grid(row=3,column=2)		
				
		#texto precio total
		self.label = tk.Label(text="Entrada:")
		self.label.grid(row=0,column=0)
		self.entrada = st.ScrolledText(self.ventana,width=30, height=10)
		self.entrada.grid(row=1,column=0)
		self.label = tk.Label(text="Salida:")
		self.label.grid(row=2,column=0)
		self.salida = st.ScrolledText(self.ventana,width=30, height=10)
		self.salida.grid(row=3,column=0)
		self.ventana.mainloop()
	
	#acciones para los botones	
	
	def capital(self):
		self.salida.delete('1.0',tk.END)		
		cadena = self.entrada.get('1.0',tk.END)
		objeto = Capitalizar()
		filtrado = objeto.filtro(cadena)
		self.salida.insert('1.0',filtrado)
	
	def voltear(self):
		self.salida.delete('1.0',tk.END)		
		cadena = self.entrada.get('1.0',tk.END)
		objeto = Reverse()
		filtrado = objeto.filtro(cadena)
		self.salida.insert('1.0',filtrado)
	
	def quitar(self):
		self.salida.delete('1.0',tk.END)		
		cadena = self.entrada.get('1.0',tk.END)
		objeto = FiltrarEspacio()
		filtrado = objeto.filtro(cadena)
		self.salida.insert('1.0',filtrado)
		
	def dolarasol(self):
		self.salida.delete('1.0',tk.END)		
		cadena = self.entrada.get('1.0',tk.END)
		objeto = DolaraSoles()
		filtrado = objeto.filtro(cadena)
		self.salida.insert('1.0',filtrado)
		
	def soladolar(self):
		self.salida.delete('1.0',tk.END)		
		cadena = self.entrada.get('1.0',tk.END)
		objeto = SolesaDolares()
		filtrado = objeto.filtro(cadena)
		self.salida.insert('1.0',filtrado)
	
	def contar(self):
		self.salida.delete('1.0',tk.END)		
		cadena = self.entrada.get('1.0',tk.END)
		objeto = CuentaPalabras()
		filtrado = objeto.filtro(cadena)
		self.salida.insert('1.0',filtrado)
		


	

App()