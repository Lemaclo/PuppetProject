# Mini Proyecto 1: The Puppet
## Luis Emilio Martínez Capetillo
## Gráficas por Computadora
### Viernes 24 de Octubre del 2025

------------------------------------------------

## Instrucciones de compilación:
Para compilar, se necesita usar el *makefile* del proyecto.
Se usa con `make main`, y el ejecutable que devuelve tiene el
nombre por defecto del compilador (como `a.out`).
No hay parámetros adicionales de compilación.

## Instrucciones de uso
Al inciar el programa, se mostrará la marioneta en su estado inicial (T-pose).
Los controles de cámara son los siguientes:
- w/s: Zoom in, out.
- a/d: Mover arriba, abajo.
- q/e: Mover izquierda, derecha.
- Flecha izquierda / derecha : Girar hacia la izquierda /derecha
- Flecha arrbia / abajo : Girar hacia arriba / abajo
- x: Reiniciar la cámara

En todo momento, una articulación o más se encuentran **seleccionadas**.
Cuando una articulación está seleccionada, todas las articulaciones que dependen (i.e. que 
siguen su movimiento) de ella también lo están. Inicialmente, la articulación seleccionada
es la pelvis, que se considera la **raíz** del modelo.
Para alternar la articulación seleccionada, se usa n (de next) para ir a la siguiente, 
m para ir a la anterior, y b (de base) para regresar a la pelvis. El orden de visita de las
articulaciones no hace mucho sentido, y para cuando me di cuenta, ya era muy tarde para cambiarlo.

Los controles de la articulación seleccionada son los siguientes:
- i / p: Rotación en el eje x
- j / l: Rotación en el eje y
- o / k: Rotación en el eje z
- r: Reiniciar la articulación

Los ejes son relativos a la primitiva. 
El orden de las rotaciones es z-y-x.

Los controles de acciones son los siguientes:
- u: Undo
- r: Redo
- h: Reiniciar toda la marioneta (reinicia las pilas de undo/redo)

## Problemas de implementación
En general, creo que no tuve demasiados problemas implementando el proyecto.
Lo más complicado fue empezar a abstraer en clases y métdos la creación de 
VAOs y VBOs, pero una vez que tenía eso, implementar las ideas se volvió más
sencillo. Manejar el input de manera adecuada (diferenciar entre PRESS y REPEAT, por
ejemplo) me dio algunos problemas. El orden de multiplicación de matrices para las transformaciones
también tuvo sus complicaciones.

## Referencias
[learnopengl.com](Learn OpenGL) Esta página fue de gran ayuda para la parte inicial del proyecto, 
y básicamente la clase de Shaders es la misma que en ahí. Además, me guié en ella para usar las matrices
en el vertex shader. Definitivamente, fue la referencia principal del proyecto.
Canal The Cherno en Youtube.
