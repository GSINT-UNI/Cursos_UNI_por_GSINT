import tkinter as tk
from abc import ABC, abstractmethod


class Paquete:

    def __init__(self,precio,millas_a_recorrer,millas_acumuladas):
        self.precio=precio
        self.millas_acumuladas=millas_acumuladas
        self.millas_a_recorrer=millas_a_recorrer

class AbstractHandler():
    """
    The default chaining behavior can be implemented inside a base handler
    class.
    """
    

    def siguiente_manejador(self, handler) :
        self._next_handler = handler
        return handler

    @abstractmethod
    def calcular_paquete(self, paquete) :
        if self._next_handler:
            return self._next_handler.calcular_paquete(paquete)

        return None



class Normal(AbstractHandler):
    def calcular_paquete(self, paquete) :
        if paquete.millas_acumuladas <= 10000:
            print(f"Normal manejara esto")
            return [paquete.precio,paquete.millas_a_recorrer,paquete.millas_acumuladas]
        else:
            return super().calcular_paquete(paquete)


class Silver(AbstractHandler):
    def calcular_paquete(self, paquete) :
        if paquete.millas_acumuladas >= 10001 and paquete.millas_acumuladas <= 25000:
            print(f"Silver manejara esto")
            return [5,paquete.precio*0.95,paquete.millas_a_recorrer*1.1]
        else:
            return super().calcular_paquete(paquete)


class Gold(AbstractHandler):
    def calcular_paquete(self, paquete) :
        if paquete.millas_acumuladas >= 25001 and paquete.millas_acumuladas <= 50000:
            print(f"Gold manejara esto")
            return [10,paquete.precio*0.9,paquete.millas_a_recorrer*2]
        else:
            return super().calcular_paquete(paquete)


class Platino(AbstractHandler):
    def calcular_paquete(self, paquete) :
        if paquete.millas_acumuladas > 50000:
            print(f"Platino manejara esto")
            return [20,paquete.precio*0.8,paquete.millas_a_recorrer*3]







class Aplicacion:
    def __init__(self):
        self.ventana1=tk.Tk()

        self.normal = Normal()
        self.silver = Silver()
        self.gold = Gold()
        self.platino = Platino()
        self.normal.siguiente_manejador(self.silver).siguiente_manejador(self.gold).siguiente_manejador(self.platino)

        
        self.label1=tk.Label(text="Precio normal:")
        self.label1.grid(column=0, row=0)
        self.label2=tk.Label(text="Millas acumuladas:")
        self.label2.grid(column=0, row=1)
        self.label3=tk.Label(text="Millas a recorrer:")
        self.label3.grid(column=3, row=0)

        self.label4=tk.Label(text="Descuento:")
        self.label4.grid(column=0, row=4)
        self.label5=tk.Label(text="Precio a pagar:")
        self.label5.grid(column=0, row=5)
        self.label6=tk.Label(text="Millas a acumular:")
        self.label6.grid(column=3, row=4)

        
        self.dato1=tk.StringVar()
        self.dato2=tk.StringVar()
        self.dato3=tk.StringVar()
        
        self.dato4=tk.StringVar()
        self.dato5=tk.StringVar()
        self.dato6=tk.StringVar()
        
        self.entry1=tk.Entry(self.ventana1, width=20, textvariable=self.dato1)  #precio normal
        self.entry1.grid(column=1, row=0)
        self.entry2=tk.Entry(self.ventana1, width=20, textvariable=self.dato2) #millas acumuladas
        self.entry2.grid(column=1, row=1)
        self.entry3=tk.Entry(self.ventana1, width=20, textvariable=self.dato3) #millas a recorrer
        self.entry3.grid(column=4, row=0)
        
        self.label7=tk.Label(text="") #descuento
        self.label7.grid(column=1, row=4)
        self.label8=tk.Label(text="")  #precio a pagar
        self.label8.grid(column=1, row=5)
        self.label9=tk.Label(text="") # millas a acumular
        self.label9.grid(column=4, row=4)        

        self.boton1=tk.Button(self.ventana1, text="Calcular", command=self.ingresar)
        self.boton1.grid(column=2, row=2)
        
        self.ventana1.mainloop()

    def ingresar(self):
        mi_paquete=Paquete(int(self.dato1.get()),int(self.dato3.get()),int(self.dato2.get()))
        print(f"Dato 1 es {mi_paquete.precio}")
        print(f"Dato 2, milla acumulada es {mi_paquete.millas_acumuladas}")
        print(f"Dato 3, millas_a_recorrer es {mi_paquete.millas_a_recorrer}")
        result = self.normal.calcular_paquete(mi_paquete)
        self.label7.configure(text=str(result[0]))
        self.label8.configure(text=str(result[1]))
        self.label9.configure(text=str(result[2]))

        print(result)


aplicacion1=Aplicacion()      
