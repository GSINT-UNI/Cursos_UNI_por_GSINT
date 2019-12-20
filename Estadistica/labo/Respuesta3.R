# Nombre : Carlos Alberto Espinoza Mansilla 20162187C

#(a)vamos a crear 2 vectores uno llamado sexo y otro llamado partido, 

sexo=rep("M",20) #crea un array de 20 "M"

sexo[c(1,5:7,12,14:16)]="F" #reemplaza en dichas posiciones con el carater "F"


partido=rep("Nacional",20) #repetimos el proceso con el vector partido

partido[c(1,4,12,15,16,19)]="Laborista"
partido[c(6,9,11)]="Verdes"
partido[c(10,20)]="Otro"

#(b)
#creamos factores para cada vector
factorsexo=factor(sexo)
factorpartido=factor(partido)
#no tiene sentido usar ordered=TRUE puesto que ninguno de
#los niveles tiene un sentido de orden lógico
#para el caso sexo no hay un sentido de orden entre hombre y mujer
#para el caso partido tampoco hay un sentido de orden entre los nombres de los partidos
#R por defecto organiza los "levels" en orden del alfabeto
#esto se ve mejor en el segundo vector:
as.numeric(factorpartido)
as.numeric(factorsexo)
#donde vemos que asigna 1,2,3,4 a los partidos en orden alfabético

#(c)
#indicamos aquellos partidos quie han elegido los hombres
#con la sintaxis vector[condicion]
factorpartido[factorsexo=="M"]
#de igual forma para mostrar los generos de quienes eligen el partido Nacional
factorsexo[factorpartido=="Nacional"]

#(d)
#concatenamos los nuevos datos a los vectores iniciales
partido=c(partido,"Nacional","Maori","Maori","Laborista","Verdes","Laborista")
sexo=c(sexo,"M","M","F","F","F","M")
#ya que hemos ingresado mas valores debemos volver a crear o actualizar nuestros factores
factorsexo=factor(sexo)
factorpartido=factor(partido)
#ahgora agregamos el vector confiabilidadLN
ConfiabilidadLN=c(93,55,29,100,52,84,56,0,33,52,35,53,55,46,40,56,45,64,31,10,29,40,95,18,61,75)
#ahora vamos a establecer niveles dado que la confiabilidad 
#esta medida en porcentaje y este si posee un orden logico
#los niveles se distribuiran en bajo [0:30], medio (30:70] y alto (70:100]
factorCLN=factor(ConfiabilidadLN)#establezco un factor para ConfiabilidadLN
#paso a renombrar los niveles de acuerdo a los intervalos
levels(factorCLN)[ levels(factorCLN) %in% 0:30 ]="Bajo"
levels(factorCLN)[ levels(factorCLN) %in% 30:70 ]="Medio"
levels(factorCLN)[ levels(factorCLN) %in% 70:100 ]="Alto"
factorCLN[factorpartido=="Laborista"]
factorCLN[factorpartido=="Nacional"]
#se puede notar que aquellos que botan por el partido Laborista creen con un nivel "Alto"
#de confianza en que estos ganaran mas escaños que el rival
#mientras que el rival opina que los Laboristas tienen "medias" o "bajas" oportunidades de ganarles