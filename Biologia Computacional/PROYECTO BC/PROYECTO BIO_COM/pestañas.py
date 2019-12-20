# -*- coding: utf-8 -*-


import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext as st
import leerg
import os
import subprocess as sp

opciones=[]
output1='AQUI SE MUESTRAN LAS SECUENCIAS SELECCIONADAS: '+'\n'
output2='AQUI SE MUESTRA EL ALINEAMIENTO: '+'\n'


class Aplicacion:
    def __init__(self):
    
        self.usos=0
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
        self.info_especies={'Iridosornis reinhardti':'Iridosornis_reinhardti.txt',
'Sicalis raimondii':'Sicalis_raimondii.txt',
'Poospiza caesar':'Poospiza_caesar.txt',
'Poospiza rubecula':'Poospiza_rubecula.txt',
'Poospiza alticola':'Poospiza_alticola.txt',
'Incaspiza ortizi':'Incaspiza_ortizi.txt',
'Incaspiza personata':'Incaspiza_personata.txt',
'Incaspiza pulchra':'Incaspiza_pulchra.txt',
'Piezorhina cinerea':'Piezorhina_cinerea.txt',
'Tangara phillipsi':'Tangara_phillipsi.txt'}
        self.ventana1=tk.Tk()
        self.ventana1.title("Prueba del control Notebook")
        self.cuaderno1 = ttk.Notebook(self.ventana1)
        
        self.pagina1 = ttk.Frame(self.cuaderno1)
        self.cuaderno1.add(self.pagina1, text="Button")
        self.label1=ttk.Label(self.pagina1, text="Seleccione las especies \na analizar una por una:")
        self.label1.grid(column=0, row=0)
        self.opcion=tk.StringVar()

        self.fastalist=open('fastaselec.fasta','w')
        diassemana=[]
        for a in self.especies.keys():
            diassemana.append(a)

        self.combobox1=ttk.Combobox(self.pagina1, 
                                  width=30, 
                                  textvariable=self.opcion, 
                                  values=diassemana)
        self.combobox1.current(0)
        self.combobox1.grid(column=0, row=1)
        self.boton1=ttk.Button(self.pagina1, text="Seleccionar", command=self.recuperar)
        self.boton1.grid(column=0, row=5)
        self.boton1=ttk.Button(self.pagina1, text="Realizar alineamiento",command=self.alinear)
        self.boton1.grid(column=1, row=5)
        self.scrolledtext1=st.ScrolledText(self.pagina1,width=34,state = tk.NORMAL)
        self.scrolledtext1.grid(column=0,row=2,rowspan=3)
        self.scrolledtext1.insert(tk.INSERT,output1)
        self.scrolledtext1.config(state=tk.DISABLED)
        self.scrolledtext2=st.ScrolledText(self.pagina1,state = tk.NORMAL)
        self.scrolledtext2.grid(column=1,row=0,rowspan=5)
        self.scrolledtext2.insert(tk.INSERT,output2)
        self.scrolledtext2.config(state=tk.DISABLED)
        

        self.pagina2 = ttk.Frame(self.cuaderno1)
        self.cuaderno1.add(self.pagina2, text="Label")
        self.label2=ttk.Label(self.pagina2, text="Seleccione la especies para ver su info")
        self.label2.grid(column=0, row=0)
        self.label3=ttk.Label(self.pagina2, text="con los caracteres \\n podemos hacer un salto de línea dentro de la Label")
        self.combobox2=ttk.Combobox(self.pagina2, 
                                  width=30, 
                                  textvariable=self.opcion, 
                                  values=diassemana)
        self.combobox2.current(0)
        self.combobox2.grid(column=0, row=1)        
        self.boton2=ttk.Button(self.pagina2, text="Info", command=self.info)
        self.boton2.grid(column=0, row=5)
        self.scrolledtext3=st.ScrolledText(self.pagina2,state = tk.NORMAL)
        self.scrolledtext3.grid(column=0,row=2,rowspan=3)
        self.scrolledtext3.config(state=tk.DISABLED)


        self.cuaderno1.grid(column=0, row=0)        
        self.ventana1.mainloop()

    def recuperar(self):
        leerg.leer(self.especies[self.combobox1.get()])
        self.scrolledtext1.config(state=tk.NORMAL)
        opciones.append(self.opcion.get())
        self.scrolledtext1.insert(tk.INSERT,self.opcion.get()+'\n')
        print(opciones)  
        self.scrolledtext1.config(state=tk.DISABLED)
        self.scrolledtext2.config(state=tk.NORMAL) 
        self.scrolledtext2.delete("1.0",tk.END)
        self.scrolledtext2.config(state=tk.DISABLED)

    def alinear(self):
        output = sp.getoutput('clustalo --infile=fastaselec.fasta')
        self.scrolledtext2.config(state=tk.NORMAL) 
        self.scrolledtext2.delete("1.0",tk.END)
        self.scrolledtext2.insert(tk.INSERT,output)              
        self.scrolledtext2.config(state=tk.DISABLED)
        opciones=[]
        output=''
        self.scrolledtext1.config(state=tk.NORMAL)
        self.scrolledtext1.delete("1.0",tk.END)
        self.scrolledtext1.insert(tk.INSERT,output1)
        self.scrolledtext1.config(state=tk.DISABLED)
        print("usos= "+str(self.usos))
        self.fastalist=open('fastaselec.fasta','w')

    def info(self):
        infotext = "info de: " + self.combobox2.get() + "\n"
        info_especie = open(self.info_especies[self.combobox2.get()],'r')
        for line in info_especie.readlines():
	        infotext = infotext + line
        self.scrolledtext3.config(state=tk.NORMAL)
        self.scrolledtext3.delete("1.0",tk.END)
        self.scrolledtext3.insert(tk.INSERT,infotext)
        self.scrolledtext3.config(state=tk.DISABLED)

aplicacion1=Aplicacion()
aplicacion1.fastalist.close()
os.system("rm fastaselec.fasta")





