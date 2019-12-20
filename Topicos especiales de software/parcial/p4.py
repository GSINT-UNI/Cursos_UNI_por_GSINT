import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext as st
from random import shuffle
import re

class FiltroAbstracto:
	def filtro(self,cadena): 
		pass

class tuberia:
	def __init__(self):
		self.lista = []
	def agregarfiltro(self, filtro):
		self.objeto = filtro()
		self.lista.append(self.objeto)		

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
		#numerocoma = re.findall(r"([\+-]?(\d+)(,)?(\d+)(\.\d+)?)(\s*)"	,cadena)
		#cadena = re.sub(r"([\+-]?(\d+)(,)?(\d+)(\.\d+)?)(\s*)",str(float(numerocoma[1])*1000+float(numerocoma[3])+float(numerocoma[4])	),cadena))
        
		numero = re.findall(r"([\+-]?\d+(\.\d+)?)(\s*)(dolares|dólares|dolar|dólar)",cadena)		
		numero = ["{0:.2f}".format(float(a[0])*3.34) for a in numero]			
		cadena = re.sub(r"([\+-]?\d+(\.\d+)?)(\s*)(dolares|dólares|dolar|dólar)",
		lambda match: str(numero.pop(0)+" soles"),
		cadena)		

		numero = re.findall(r"\$\s*([\+-]?\d+(\.\d+)?)",cadena)
		numero = ["{0:.2f}".format(float(a[0])*3.34) for a in numero]		
		cadena = re.sub(r"\$\s*([\+-]?\d+(\.\d+)?)",
		lambda match: str("S./ "+numero.pop(0)),
		cadena)
		
		return cadena

class SolesaDolares(FiltroAbstracto):
	def filtro(self,cadena):
		numero = re.findall(r"([\+-]?\d+(\.\d+)?)(\s*)(soles|sol|nuevo sol)",cadena)		
		numero = ["{0:.2f}".format(float(a[1])*0.2958579881656805) for a in numero]		
		cadena = re.sub(r"([\+-]?\d+(\.\d+)?)(\s*)(soles|sol|nuevo sol)",
		lambda match: str(numero.pop(0)+" dólares"),
		cadena)		

		numero = re.findall(r"(S\/\.|s\/\.)\s*([+-]?\d+(\.\d+)?)",cadena)
		numero = ["{0:.2f}".format(float(a[1])*0.2958579881656805) for a in numero]			
		cadena = re.sub(r"(S\/\.|s\/\.)\s*([+-]?\d+(\.\d+)?)",
		lambda match: str("US$ "+numero.pop(0)),
		cadena)

		return cadena

class CuentaPalabras(FiltroAbstracto):
	def filtro(self,cadena):
		return len(re.findall(r'\w+',cadena))

class DesordenarCodigo(FiltroAbstracto):
	def filtro(self,cadena):
		codigo = re.findall(r"\n?.+\n?",cadena)
		shuffle(codigo)
		cadena = "".join(codigo)
		return cadena

class Total(FiltroAbstracto):
	def filtro(self,cadena):
		#cadena = DolaraSoles.filtro(cadena)  
        
		numero = re.findall(r"([\+-]?\d+(\.\d+)?)(\s*)(dolares|dólares|dolar|dólar)",cadena)		
		numero = ["{0:.2f}".format(float(a[0])*3.34) for a in numero]			
		cadena = re.sub(r"([\+-]?\d+(\.\d+)?)(\s*)(dolares|dólares|dolar|dólar)",
		lambda match: str(numero.pop(0)+" soles"),
		cadena)		

		numero = re.findall(r"\$\s*([\+-]?\d+(\.\d+)?)",cadena)
		numero = ["{0:.2f}".format(float(a[0])*3.34) for a in numero]		
		cadena = re.sub(r"\$\s*([\+-]?\d+(\.\d+)?)",
		lambda match: str("S./ "+numero.pop(0)),
		cadena)

		listado = [
            r"((E|e)nero):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((F|f)ebrero):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((M|m)arzo):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((A|a)bril):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((M|m)ayo):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((J|j)unio):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((J|j)ulio):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((A|a)gosto):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((S|s)ep?tiembre):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((O|o)ctubre):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((N|n)oviembre):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
            r"((D|d)iciembre):?\s*(S|s)\.\/\s*([+-]?\d+(\.\d+)?)",
        ]
		mes=[
            "Enero",
            "Febrero",
            "Marzo",
            "Abril",
            "Mayo",
            "Junio",
            "Julio",
            "Agosto",
            "Septiembre",
            "Octubre",
            "Noviembre",
            "Diciembre"
        ]
		totalcadena = str("\n\nTOTALES\n ")
		cadena = cadena + totalcadena
		for j in range(len(listado)):                
			numero = re.findall(listado[j],cadena)
			totalnum = 0
			for i in range(len(numero)):	
			    totalnum = totalnum + float(numero[i][3])		  
			totalcadena = str( mes[j]+" S/. " + str("{0:.2f}".format(totalnum)) + "\n" )    
			cadena = cadena + totalcadena

		return cadena


    
    




class App:

	def __init__(self):
		#configuracion de ventana
		self.ventana = tk.Tk()		
		self.ventana.title("Patron filtro")
		self.ventana.geometry("550x410")		
		
		#variables
		self.tubo = tuberia()
		self.indexvar = [0,0,0,0,0,0,0,0,0,0,0,0,0,0]
		self.index = 0
		self.entradavar = tk.StringVar()
		self.salidavar = tk.StringVar()	
		self.capitalvar = tk.IntVar()
		self.capitalvar = tk.IntVar()
		self.revesvar = tk.IntVar()
		self.quitarvar = tk.IntVar()
		self.sadvar = tk.IntVar()
		self.dasvar = tk.IntVar()
		self.contarvar = tk.IntVar()   
		self.desordenarvar = tk.IntVar()     
		self.totalvar = tk.IntVar()  

		#botones para el cambio
		self.capitalbutton = tk.Checkbutton(self.ventana,text="Capitalizar", variable=self.capitalvar,command=self.capital)
		self.capitalbutton.grid(row=1,column=1,sticky="")		
		self.revesbutton = tk.Checkbutton(self.ventana,text="Al reves", variable=self.revesvar, command=self.voltear )
		self.revesbutton.grid(row=2,column=1,sticky="")			
		self.quitarespaciobutton = tk.Checkbutton(self.ventana,text="Quitar espacio", variable=self.quitarvar, command=self.quitar_espacio )
		self.quitarespaciobutton.grid(row=3,column=1,sticky="")

		self.soladolbutton = tk.Checkbutton(self.ventana,text="Soles a Dolares", variable=self.sadvar, command=self.soladolar )
		self.soladolbutton.grid(row=1,column=2,sticky="")		
		self.dolasolbutton = tk.Checkbutton(self.ventana,text="Dolares a Soles", variable=self.dasvar, command=self.dolarasol )
		self.dolasolbutton.grid(row=2,column=2,sticky="")			
		self.cuentapalbutton = tk.Checkbutton(self.ventana,text="Cuenta Palabras", variable=self.contarvar, command=self.contar )
		self.cuentapalbutton.grid(row=3,column=2,sticky="")
		self.desordenarbutton = tk.Checkbutton(self.ventana,text="Desordenar Codigo", variable=self.desordenarvar, command=self.desordenar )
		self.desordenarbutton.grid(row=4,column=1,sticky="")

		self.totalbutton = tk.Checkbutton(self.ventana,text="total", variable=self.totalvar, command=self.total )
		self.totalbutton.grid(row=4,column=2,sticky="")        

		self.ponerfiltrobutton = tk.Button(self.ventana,text="Aplicar Filtros", command=self.aplicar )
		self.ponerfiltrobutton.grid(row=6,column=1,columnspan=2)

		self.limpiarfiltrobutton = tk.Button(self.ventana,text="Limpiar Filtros", command=self.limpiar )
		self.limpiarfiltrobutton.grid(row=8,column=1,columnspan=2)
		
				
		#texto 
		self.label = tk.Label(text="Entrada:")
		self.label.grid(row=0,column=0)
		self.entrada = st.ScrolledText(self.ventana,width=30, height=10)
		self.entrada.grid(row=1,column=0,rowspan=4)
		self.label = tk.Label(text="Salida:")
		self.label.grid(row=5,column=0)
		self.salida = st.ScrolledText(self.ventana,width=30, height=10)
		self.salida.grid(row=6,column=0,rowspan=4)
		self.ventana.mainloop()
	
	#acciones para los botones	
	def action(self,variable,number,nombre_objeto):
		if(variable.get() == 1):
			self.index +=1
			#self.indexvar = [a + 1 for a in self.indexvar]
			self.indexvar[number] = self.index
			self.tubo.agregarfiltro(nombre_objeto)
			#print(str("index = "+ str(self.index)))
			#print(str("indexvar = "+ str(self.indexvar)))
			#print(str("numero de indice = "+ str(number)))
			#print(str("lista de objetos = "+ str(self.tubo.lista)+ "\n"))           


		if(variable.get() == 0):						
			self.tubo.lista.pop(self.indexvar[number]-1)			
			#self.indexvar = [a -1 for a in self.indexvar]
			for i in range(len(self.indexvar)):
			    if(self.indexvar[i]>self.indexvar[number]):
			        self.indexvar[i] -= 1
			self.index -=1
			#print(str("index = "+str(self.index)))
			#print(str("indexvar = "+str(self.indexvar)))
			#print(str("numero de indice = "+str(number)))
			#print(str("lista de objetos = "+ str(self.tubo.lista)+"\n")) 

	def capital(self):
		self.action(self.capitalvar,1,Capitalizar)
	
	def voltear(self):	
		self.action(self.revesvar,2,Reverse)
	
	def quitar_espacio(self):
		self.action(self.quitarvar,3,FiltrarEspacio)

	def desordenar(self):
		self.action(self.desordenarvar,4,DesordenarCodigo)

	def soladolar(self):
		self.action(self.sadvar,5,SolesaDolares)

	def dolarasol(self):
		self.action(self.dasvar,6,DolaraSoles)
	
	def contar(self):
		self.action(self.contarvar,7,CuentaPalabras)

	def total(self):        
		self.action(self.totalvar,8,Total)        

	def aplicar(self): 
		self.salida.delete('1.0',tk.END)		
		cadena = self.entrada.get('1.0',tk.END)
		for a in self.tubo.lista:
			cadena = a.filtro(cadena) 
		self.salida.insert('1.0',cadena)

	def limpiar(self):
		self.tubo.lista = []
		self.capitalbutton.deselect()		
		self.revesbutton.deselect()		
		self.quitarespaciobutton.deselect()
		self.soladolbutton.deselect()	
		self.dolasolbutton.deselect()		
		self.cuentapalbutton.deselect()
		self.desordenarbutton.deselect()
		self.index = 0

App()