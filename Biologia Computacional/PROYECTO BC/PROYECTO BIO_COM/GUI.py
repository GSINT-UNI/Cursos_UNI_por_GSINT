import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext as st

especies={'Iridosornis reinhardti':'Iridosornis_reinhardti.fasta',
'Sicalis raimondii':'Sicalis_raimondii.fasta',
'Poospiza caesar':'Poospiza_caesar.fasta',
'Poospiza rubecula':'Poospiza_rubecula.fasta',
'Poospiza alticola':'Poospiza_alticola.fasta',
'Incaspiza ortizi':'Incaspiza_ortizi.fasta',
'Incaspiza personata':'Incaspiza_personata.fasta',
'Incaspiza pulchra':'Incaspiza_pulchra.fasta',
'Piezorhina cinerea':'Piezorhina_cinerea.fasta',
'Tangara phillipsi':'Tangara_phillipsi.fasta'}
opciones=[]

class Aplicacion:
    def __init__(self):
        self.especies={'Iridosornis reinhardti':'Iridosornis_reinhardti.fasta',
'Sicalis raimondii':'Sicalis_raimondii.fasta',
'Poospiza caesar':'Poospiza_caesar.fasta',
'Poospiza rubecula':'Poospiza_rubecula.fasta',
'Poospiza alticola':'Poospiza_alticola.fasta',
'Incaspiza ortizi':'Incaspiza_ortizi.fasta',
'Incaspiza personata':'Incaspiza_personata.fasta',
'Incaspiza pulchra':'Incaspiza_pulchra.fasta',
'Piezorhina cinerea':'Piezorhina_cinerea.fasta',
'Tangara phillipsi':'Tangara_phillipsi.fasta'}
        self.ventana1=tk.Tk()
        self.label1=ttk.Label(self.ventana1, text="Seleccione las especies \na analizar una por una:")
        self.label1.grid(column=0, row=0)
        self.opcion=tk.StringVar()
        diassemana=[]
        for a in self.especies.keys():
            diassemana.append(a)
        self.combobox1=ttk.Combobox(self.ventana1, 
                                  width=30, 
                                  textvariable=self.opcion, 
                                  values=diassemana)
        self.combobox1.current(0)
        self.combobox1.grid(column=0, row=1)
        self.boton1=ttk.Button(self.ventana1, text="Seleccionar", command=self.recuperar)
        self.boton1.grid(column=0, row=5)
        self.boton1=ttk.Button(self.ventana1, text="Realizar alineamiento")
        self.boton1.grid(column=1, row=5)
        self.scrolledtext1=st.ScrolledText(self.ventana1,width=34,state = tk.NORMAL)
        self.scrolledtext1.grid(column=0,row=2,rowspan=3)
        self.scrolledtext1.insert(tk.INSERT,'AQUI SE MUESTRAN LAS SECUENCIAS SELECCIONADAS: '+'\n')
        self.scrolledtext1.config(state=tk.DISABLED)
        self.scrolledtext2=st.ScrolledText(self.ventana1,state = tk.NORMAL)
        self.scrolledtext2.grid(column=1,row=0,rowspan=5)
        self.scrolledtext2.insert(tk.INSERT,'AQUI SE MUESTRA EL ALINEAMIENTO: '+'\n')
        self.scrolledtext2.config(state=tk.DISABLED)
        self.ventana1.mainloop()

    def recuperar(self):
        self.scrolledtext1.config(state=tk.NORMAL)
        opciones.append(self.opcion.get())
        self.scrolledtext1.insert(tk.INSERT,self.opcion.get()+'\n')
        print(opciones)  
        self.scrolledtext1.config(state=tk.DISABLED)
aplicacion1=Aplicacion()

