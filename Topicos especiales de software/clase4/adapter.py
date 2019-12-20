from tkinter import *

class Vector():
    def __init__(self,vector):
        self.vectordata = vector
    def get(self,i):
        return self.vectordata[i]

    def seteo(self,i,value):
        self.vectordata[i] = value
        return self.vectordata

class AbstractAdapter():    
    def getElement(self,x,y):pass
    def setElement(self,x,y,value):pass

class Adapter(AbstractAdapter):
    def __init__(self,fila,columna,vector):
        self.fila = fila
        self.columna = columna
        self.vector = vector
    def getElement(self,x,y):
        return self.vector[x+(y-1)*self.columna-1] 
    def setElement(self,x,y,value):
        self.vector = self.vector[x+(y-1)*self.columna] = value
        return self.vector    

class App:
    def __init__(self,vector):
        #configuracion de ventana
        self.ventana = Tk()		
        self.ventana.title("vector to matrix: Adapter")
        self.ventana.geometry("250x100")
        self.vector = vector
		#variables 
        self.getbuttonvar = IntVar()
        self.entradax = StringVar()	
        self.entraday = StringVar()	

        #texto
        self.labelx = Label(text="X"  )
        self.labelx.grid(row=0,column=0)
        #entradas de texto 
        self.entrx = Entry(self.ventana, textvariable=self.entradax,width=10)
        self.entrx.grid(row=0,column=1)
        #texto 
        self.labely = Label(text="Y"  )
        self.labely.grid(row=0,column=2)
        #entradas de texto 
        self.entry = Entry(self.ventana, textvariable=self.entraday,width=10)
        self.entry.grid(row=0,column=3)
        #texto
        self.labelresul = Label(text="El resultado es: "  )
        self.labelresul.grid(row=1,column=1)
		#boton get 
        self.getbutton = Button(self.ventana,text="Get", command=self.getaction )
        self.getbutton.grid(row=1,column=3)				
        
        self.ventana.mainloop()
		
    #acciones para los botones
    def getaction(self):
        try:            
            intx = int(self.entradax.get())
            inty = int(self.entraday.get())
            #intx = 4
            #inty = 3
            ob = Adapter(3,4,self.vector)
            resultado = ob.getElement( intx,inty )            
            self.labelresul.configure(text="El resultado es:" + str(resultado)  )
        except ValueError:
            pass



vector = [1,2,3,4,5,6,7,8,9,10,11,12]

App(vector)