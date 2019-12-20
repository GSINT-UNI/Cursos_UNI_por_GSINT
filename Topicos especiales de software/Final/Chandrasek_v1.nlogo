turtles-own
[
  fx
  fy
  vx
  vy
  xc     ;; real x-coordinate (in case particle leaves world)
  yc     ;; real y-coordinate (in case particle leaves world)
  mass   ;; the particle's mass
  dir    ;; angulo de direccion
  dist   ;; distancia al centro
]

globals [
  start ;  start center
  g

]
;;;;;;;;;;;;;;;;;;;;;;;;
;;; Setup Procedures ;;;
;;;;;;;;;;;;;;;;;;;;;;;;

to setup
  clear-all
  set-default-shape turtles "circle"
  create-turtles number
  random-initial-setup

  reset-ticks
end

to random-initial-setup
  ask turtles
  [
    set vx ((random-float ((2 * max-initial-speed) - 1)) - max-initial-speed)
    set vy ((random-float ((2 * max-initial-speed) - 1)) - max-initial-speed)
    set mass (random-float max-initial-mass) + 1
    setxy random-xcor random-ycor
    set xc xcor
    set yc ycor
    set heading (random-float 360)     ;direccion de la tortuga
    set size sqrt mass
    set dir 0.1
    set fx 0
    set fy 0
  ]
  create-center
end

to create-center

   set start one-of turtles
   ask start [
      set vx 0
      set vy 0
      set mass mass-start
      setxy 0 0
      set size sqrt mass
      set color red
      set g mass / ( size * size)
  ]

end

to go

  ;; must do all of these steps separately to get correct results
  ;; since all turtles interact with one another
  let max-mass [mass] of start
  ask turtles with [mass < max-mass] [ gravitate ]
  fade-patches
  tick
end

to gravitate

  update-force
  update-velocity
  update-position

end

to update-force ;; Turtle Procedure
  ;; This is recursive over all the turtles, each turtle asks this of all other turtles


  let xd xcor ;- [xcor] of start    la coordenada de start es (0,0)
  let yd ycor ;- [ycor] of start
  set dist sqrt ((xd * xd) + (yd * yd))    ; distancia de la estrella al punto
  let lim_dist [size] of start

  ifelse (dist > lim_dist) [    ; seguir moviendose
    set fx (cos (atan (- yd) (- xd)) * (mass / (dist * dist)))
    set fy (sin (atan (- yd) (- xd)) * (mass / (dist * dist)))
    ;set dir (dir + (f / 30))     ;Modificar este parametro
  ]
  [ ; En caso contrario lo absorve

    let mass-add mass
    ask start [
      set mass mass + mass-add
      set size (size - ((sqrt mass-add) / 100))
      set g (mass / (size * size))
      set color color - (mass-add / 1000)
    ]
    die
  ]

end

to update-velocity ;; Turtle Procedure
  ;; Now we update each particle's velocity, by taking last time-step's velocity
  ;; and adding the effect of the force to it.
  set vx  (vx + (fx * g ))
  set vy  (vy + (fy * g ))

end

to update-position ;; Turtle Procedure
  ;; As our system is closed, we can safely recenter the center of mass to the origin.
  ;right dir       ; cambiar su direncion en 2
  ;forward v     ; mover hacia adelante


  ;let new-dist sqrt ((xcor * xcor) + (ycor * ycor))
  ;if new-dist > dist [
  ;  set dir dir * -1
  ;]

  ;if (fade-rate != 100)
  ;  [ set pcolor color + 3 ]
  set xc (xc + vx)
  set yc (yc + vy)
  ifelse patch-at (xc - xcor) (yc - ycor) != nobody
  [
    setxy xc yc
    show-turtle
    if (fade-rate != 100)
    [ set pcolor color + 3 ]
  ]
  [die]
end

to fade-patches
  ask patches with [pcolor != black]
  [ ifelse (fade-rate = 100)
    [ set pcolor black ]
    [ if (fade-rate != 0)
      [ fade ]
    ]
  ]
end

to fade ;; Patch Procedure
  let new-color pcolor - 8 * fade-rate / 100
  ;; if the new-color is no longer the same shade then it's faded to black.
  ifelse (shade-of? pcolor new-color)
  [ set pcolor new-color ]
  [ set pcolor black ]
end
@#$#@#$#@
GRAPHICS-WINDOW
202
10
612
421
-1
-1
2.0
1
10
1
1
1
0
0
0
1
-100
100
-100
100
0
0
1
ticks
30.0

BUTTON
18
37
82
70
Setup
setup
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

SLIDER
16
181
188
214
number
number
1
400
105.0
1
1
NIL
HORIZONTAL

BUTTON
110
39
173
72
Go
go
T
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

SLIDER
16
328
188
361
fade-rate
fade-rate
0
100
6.0
1
1
%
HORIZONTAL

SLIDER
16
222
187
255
max-initial-speed
max-initial-speed
0
10
2.18
0.01
1
NIL
HORIZONTAL

SLIDER
16
265
188
298
max-initial-mass
max-initial-mass
10
150
94.0
1
1
NIL
HORIZONTAL

PLOT
642
10
1013
248
Radio
Time
Radio
0.0
10.0
0.0
10.0
true
false
"" ""
PENS
"pen-1" 1.0 0 -13840069 true "" "plot [size] of start"

PLOT
645
258
1015
473
Masa
time
masa
0.0
10.0
0.0
10.0
true
false
"" ""
PENS
"default" 1.0 0 -16777216 true "" "plot [mass] of start"

TEXTBOX
19
158
169
176
Particulas
11
0.0
1

TEXTBOX
18
308
168
326
Trayecto
11
0.0
1

TEXTBOX
20
89
170
107
Estrella\n
11
0.0
1

SLIDER
17
112
189
145
mass-start
mass-start
50
1000
510.0
10
1
Kg
HORIZONTAL

@#$#@#$#@
# Limite de Chandrasekhar
## QUÉ ES ESTO?

(a general understanding of what the model is trying to show or explain)

El límite de Chandrasekhar es la __máxima masa posible de una estrella__ de tipo enana blanca. Si se supera este límite la estrella colapsará para convertirse en un agujero negro o en una estrella de neutrones (la mayoría de veces, en este último astro)

En astrofísica, el límite de Chandrasekhar es el límite de masa más allá del cual la degeneración de electrones no es capaz de contrarrestar la fuerza de gravedad en un remanente estelar, produciéndose un colapso que origina una estrella de neutrones o un agujero negro.

Este límite equivale a aproximadamente 1,44 masas solares, y es la masa máxima posible en una enana blanca. Si ésta superase el límite de Chandrasekhar, se colapsaría para convertirse en una estrella de neutrones o un agujero negro. 

## CÓMO TRABAJA ESTO

(what rules the agents use to create the overall behavior of the model)

Para simular este fenomeno fisico astronomico, realizamos que cada agente sea un esfera con las propiedades basica de la mecanica clasica como peso, velocidad, fuerza.

La esfera central representa la estrella que llegara al limite de Chandrasekhar luego de absorver la candidad suficiente de agentes externos.

La estrella por cada absorción de un agente se le suma la masa de este y se reduce su tamaño proporcional a la masa del agente.

- La gravedad solo es ejercidad por la estrella central, ya que ahí se concentra la mayor
cantidad de masa, por lo tanto las interaciones solo son con la estrella central, mas no entre agentes.

- Para notar que se esta llegando a la masa critica este se tornara cada vez mas claro (estrella de neutrones) incluso hasta llegar colo negro (simularia un agujero negro). 

## CÓMO USAR ESTO

(how to use the model, including a description of each of the items in the Interface tab)

Para iniciar el modelo tenemos que establecer las condiciones iniciales en la interfaz:

- __mass-start__: Representa la masa inicial de la estrella central.

- __number__: La cantidad de agentes externos a la estrella.

- __max-mass-speed__: La maxima velocidad que tendra los agentes, estos seran asignados aletoriamente desde  0 hasta maxima asignada.

- __max-mass-mass__: La maxima mass que tendra los agentes, estos seran asignados aletoriamente desde  10 hasta maxima asignada.

El tamaño de los agente sera proporcional a la raiz cuadrada de su masa.

- __fada_rate__: Duracion de la trayectoria de los agentes, si su valor es 0 la trayectoria se conserva en el tiempo.


__Grafica Radio Estrella__: como varia el radio de la estrella en el tiempo

__Grafica Masa Estrella__: como varia el masa de la estrella en el tiempo



## COSAS POR NOTAR

(suggested things for the user to notice while running the model)
- Antes de iniciar la simulación la masa de la estrella debe ser mayor al de los agentes.
- Detener el modelo cuando en la grafica de la masa esta llega a ser constante en el tiempo


## COSAS POR TRATAR

(suggested things for the user to try to do (move sliders, switches, etc.) with the model)

- Reducir la velocidad de la silumación cada vez que la estrella se va reduciendo ya que como la gravedad aumenta y por ente la velocidad de las particulas tambien aumentaran brustamente, por lo cual no se podra visualizar.

- Preferible poner el __fade-rate__ en 1% para ver como es la trayectoria de las particulas.

## EXTENDIENDO EL MODELO

(suggested things to add or change in the Code tab to make the model more complicated, detailed, accurate, etc.)

El modelo solo esta basado el la fisica clasica sin tomar en cuenta fuerzas como la electrica, electromagnetica entre cada agente, si se quiere un mayor realismo se tiene que agregar propiedades como la cantidad de electrones, neutrones, protones, la masa molecular, etc.


## MODELOS RELACIONADOS

(models in the NetLogo Models Library and elsewhere which are of related interest)

El modelo esta basado en otros dos que se encuentran en Sample models - Physics - Mechanics - (unverified):

- Gravitation 
- N-Bodies

## REFERENCIAS

(a reference to the model's URL on the web if it has one, as well as any other necessary credits, citations, and links)

https://en.wikipedia.org/wiki/Chandrasekhar_limit

Chandrasekhar Limit:
https://www.sciencedirect.com/topics/physics-and-astronomy/chandrasekhar-limit

Para hacer un modelo mas realista:
https://homepages.bluffton.edu/~bergerd/NSC_111/stars.html

### CREDITOS 

Desarrollado en la Universidad Nacional de Ingenieria de la Facultad de Ciencias en la especialidad de Computer Science

Curso: Topicos Especiales de Software

Profesor: Miguel Arrunategui 

Autores:

- Lazaro Camasca Edson
- Victor Ponce Pinedo
- Josias Ruegg Yupa
- Carlos Espinoza Mansilla
@#$#@#$#@
default
true
0
Polygon -7500403 true true 150 5 40 250 150 205 260 250

airplane
true
0
Polygon -7500403 true true 150 0 135 15 120 60 120 105 15 165 15 195 120 180 135 240 105 270 120 285 150 270 180 285 210 270 165 240 180 180 285 195 285 165 180 105 180 60 165 15

arrow
true
0
Polygon -7500403 true true 150 0 0 150 105 150 105 293 195 293 195 150 300 150

box
false
0
Polygon -7500403 true true 150 285 285 225 285 75 150 135
Polygon -7500403 true true 150 135 15 75 150 15 285 75
Polygon -7500403 true true 15 75 15 225 150 285 150 135
Line -16777216 false 150 285 150 135
Line -16777216 false 150 135 15 75
Line -16777216 false 150 135 285 75

bug
true
0
Circle -7500403 true true 96 182 108
Circle -7500403 true true 110 127 80
Circle -7500403 true true 110 75 80
Line -7500403 true 150 100 80 30
Line -7500403 true 150 100 220 30

butterfly
true
0
Polygon -7500403 true true 150 165 209 199 225 225 225 255 195 270 165 255 150 240
Polygon -7500403 true true 150 165 89 198 75 225 75 255 105 270 135 255 150 240
Polygon -7500403 true true 139 148 100 105 55 90 25 90 10 105 10 135 25 180 40 195 85 194 139 163
Polygon -7500403 true true 162 150 200 105 245 90 275 90 290 105 290 135 275 180 260 195 215 195 162 165
Polygon -16777216 true false 150 255 135 225 120 150 135 120 150 105 165 120 180 150 165 225
Circle -16777216 true false 135 90 30
Line -16777216 false 150 105 195 60
Line -16777216 false 150 105 105 60

car
false
0
Polygon -7500403 true true 300 180 279 164 261 144 240 135 226 132 213 106 203 84 185 63 159 50 135 50 75 60 0 150 0 165 0 225 300 225 300 180
Circle -16777216 true false 180 180 90
Circle -16777216 true false 30 180 90
Polygon -16777216 true false 162 80 132 78 134 135 209 135 194 105 189 96 180 89
Circle -7500403 true true 47 195 58
Circle -7500403 true true 195 195 58

circle
false
0
Circle -7500403 true true 0 0 300

circle 2
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240

cow
false
0
Polygon -7500403 true true 200 193 197 249 179 249 177 196 166 187 140 189 93 191 78 179 72 211 49 209 48 181 37 149 25 120 25 89 45 72 103 84 179 75 198 76 252 64 272 81 293 103 285 121 255 121 242 118 224 167
Polygon -7500403 true true 73 210 86 251 62 249 48 208
Polygon -7500403 true true 25 114 16 195 9 204 23 213 25 200 39 123

cylinder
false
0
Circle -7500403 true true 0 0 300

dot
false
0
Circle -7500403 true true 90 90 120

face happy
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 255 90 239 62 213 47 191 67 179 90 203 109 218 150 225 192 218 210 203 227 181 251 194 236 217 212 240

face neutral
false
0
Circle -7500403 true true 8 7 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Rectangle -16777216 true false 60 195 240 225

face sad
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 168 90 184 62 210 47 232 67 244 90 220 109 205 150 198 192 205 210 220 227 242 251 229 236 206 212 183

fish
false
0
Polygon -1 true false 44 131 21 87 15 86 0 120 15 150 0 180 13 214 20 212 45 166
Polygon -1 true false 135 195 119 235 95 218 76 210 46 204 60 165
Polygon -1 true false 75 45 83 77 71 103 86 114 166 78 135 60
Polygon -7500403 true true 30 136 151 77 226 81 280 119 292 146 292 160 287 170 270 195 195 210 151 212 30 166
Circle -16777216 true false 215 106 30

flag
false
0
Rectangle -7500403 true true 60 15 75 300
Polygon -7500403 true true 90 150 270 90 90 30
Line -7500403 true 75 135 90 135
Line -7500403 true 75 45 90 45

flower
false
0
Polygon -10899396 true false 135 120 165 165 180 210 180 240 150 300 165 300 195 240 195 195 165 135
Circle -7500403 true true 85 132 38
Circle -7500403 true true 130 147 38
Circle -7500403 true true 192 85 38
Circle -7500403 true true 85 40 38
Circle -7500403 true true 177 40 38
Circle -7500403 true true 177 132 38
Circle -7500403 true true 70 85 38
Circle -7500403 true true 130 25 38
Circle -7500403 true true 96 51 108
Circle -16777216 true false 113 68 74
Polygon -10899396 true false 189 233 219 188 249 173 279 188 234 218
Polygon -10899396 true false 180 255 150 210 105 210 75 240 135 240

house
false
0
Rectangle -7500403 true true 45 120 255 285
Rectangle -16777216 true false 120 210 180 285
Polygon -7500403 true true 15 120 150 15 285 120
Line -16777216 false 30 120 270 120

leaf
false
0
Polygon -7500403 true true 150 210 135 195 120 210 60 210 30 195 60 180 60 165 15 135 30 120 15 105 40 104 45 90 60 90 90 105 105 120 120 120 105 60 120 60 135 30 150 15 165 30 180 60 195 60 180 120 195 120 210 105 240 90 255 90 263 104 285 105 270 120 285 135 240 165 240 180 270 195 240 210 180 210 165 195
Polygon -7500403 true true 135 195 135 240 120 255 105 255 105 285 135 285 165 240 165 195

line
true
0
Line -7500403 true 150 0 150 300

line half
true
0
Line -7500403 true 150 0 150 150

pentagon
false
0
Polygon -7500403 true true 150 15 15 120 60 285 240 285 285 120

person
false
0
Circle -7500403 true true 110 5 80
Polygon -7500403 true true 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90
Rectangle -7500403 true true 127 79 172 94
Polygon -7500403 true true 195 90 240 150 225 180 165 105
Polygon -7500403 true true 105 90 60 150 75 180 135 105

plant
false
0
Rectangle -7500403 true true 135 90 165 300
Polygon -7500403 true true 135 255 90 210 45 195 75 255 135 285
Polygon -7500403 true true 165 255 210 210 255 195 225 255 165 285
Polygon -7500403 true true 135 180 90 135 45 120 75 180 135 210
Polygon -7500403 true true 165 180 165 210 225 180 255 120 210 135
Polygon -7500403 true true 135 105 90 60 45 45 75 105 135 135
Polygon -7500403 true true 165 105 165 135 225 105 255 45 210 60
Polygon -7500403 true true 135 90 120 45 150 15 180 45 165 90

sheep
false
15
Circle -1 true true 203 65 88
Circle -1 true true 70 65 162
Circle -1 true true 150 105 120
Polygon -7500403 true false 218 120 240 165 255 165 278 120
Circle -7500403 true false 214 72 67
Rectangle -1 true true 164 223 179 298
Polygon -1 true true 45 285 30 285 30 240 15 195 45 210
Circle -1 true true 3 83 150
Rectangle -1 true true 65 221 80 296
Polygon -1 true true 195 285 210 285 210 240 240 210 195 210
Polygon -7500403 true false 276 85 285 105 302 99 294 83
Polygon -7500403 true false 219 85 210 105 193 99 201 83

square
false
0
Rectangle -7500403 true true 30 30 270 270

square 2
false
0
Rectangle -7500403 true true 30 30 270 270
Rectangle -16777216 true false 60 60 240 240

star
false
0
Polygon -7500403 true true 151 1 185 108 298 108 207 175 242 282 151 216 59 282 94 175 3 108 116 108

target
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240
Circle -7500403 true true 60 60 180
Circle -16777216 true false 90 90 120
Circle -7500403 true true 120 120 60

tree
false
0
Circle -7500403 true true 118 3 94
Rectangle -6459832 true false 120 195 180 300
Circle -7500403 true true 65 21 108
Circle -7500403 true true 116 41 127
Circle -7500403 true true 45 90 120
Circle -7500403 true true 104 74 152

triangle
false
0
Polygon -7500403 true true 150 30 15 255 285 255

triangle 2
false
0
Polygon -7500403 true true 150 30 15 255 285 255
Polygon -16777216 true false 151 99 225 223 75 224

truck
false
0
Rectangle -7500403 true true 4 45 195 187
Polygon -7500403 true true 296 193 296 150 259 134 244 104 208 104 207 194
Rectangle -1 true false 195 60 195 105
Polygon -16777216 true false 238 112 252 141 219 141 218 112
Circle -16777216 true false 234 174 42
Rectangle -7500403 true true 181 185 214 194
Circle -16777216 true false 144 174 42
Circle -16777216 true false 24 174 42
Circle -7500403 false true 24 174 42
Circle -7500403 false true 144 174 42
Circle -7500403 false true 234 174 42

turtle
true
0
Polygon -10899396 true false 215 204 240 233 246 254 228 266 215 252 193 210
Polygon -10899396 true false 195 90 225 75 245 75 260 89 269 108 261 124 240 105 225 105 210 105
Polygon -10899396 true false 105 90 75 75 55 75 40 89 31 108 39 124 60 105 75 105 90 105
Polygon -10899396 true false 132 85 134 64 107 51 108 17 150 2 192 18 192 52 169 65 172 87
Polygon -10899396 true false 85 204 60 233 54 254 72 266 85 252 107 210
Polygon -7500403 true true 119 75 179 75 209 101 224 135 220 225 175 261 128 261 81 224 74 135 88 99

wheel
false
0
Circle -7500403 true true 3 3 294
Circle -16777216 true false 30 30 240
Line -7500403 true 150 285 150 15
Line -7500403 true 15 150 285 150
Circle -7500403 true true 120 120 60
Line -7500403 true 216 40 79 269
Line -7500403 true 40 84 269 221
Line -7500403 true 40 216 269 79
Line -7500403 true 84 40 221 269

wolf
false
0
Polygon -16777216 true false 253 133 245 131 245 133
Polygon -7500403 true true 2 194 13 197 30 191 38 193 38 205 20 226 20 257 27 265 38 266 40 260 31 253 31 230 60 206 68 198 75 209 66 228 65 243 82 261 84 268 100 267 103 261 77 239 79 231 100 207 98 196 119 201 143 202 160 195 166 210 172 213 173 238 167 251 160 248 154 265 169 264 178 247 186 240 198 260 200 271 217 271 219 262 207 258 195 230 192 198 210 184 227 164 242 144 259 145 284 151 277 141 293 140 299 134 297 127 273 119 270 105
Polygon -7500403 true true -1 195 14 180 36 166 40 153 53 140 82 131 134 133 159 126 188 115 227 108 236 102 238 98 268 86 269 92 281 87 269 103 269 113

x
false
0
Polygon -7500403 true true 270 75 225 30 30 225 75 270
Polygon -7500403 true true 30 75 75 30 270 225 225 270
@#$#@#$#@
NetLogo 6.0.4
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
default
0.0
-0.2 0 0.0 1.0
0.0 1 1.0 0.0
0.2 0 0.0 1.0
link direction
true
0
Line -7500403 true 150 150 90 180
Line -7500403 true 150 150 210 180
@#$#@#$#@
0
@#$#@#$#@
