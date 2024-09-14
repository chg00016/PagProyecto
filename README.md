# **Proyecto de programación de aplicaciones gráficas**

# *Práctica 1*

## Ejercicio 2
  Una buena práctica que puedes aplicar es crear un espacio de nombres (llamado
“PAG”, por ejemplo) para tus clases. Así te aseguras no tener conflictos con otros
nombres de clases o tipos de las bibliotecas que utilices.
  En nuestra aplicación debería haber una clase PAG::Renderer que se encargue de
encapsular todo lo relativo al dibujado de la escena 3D en el contexto gráfico OpenGL.
Esa clase debería tener un método llamado refrescarVentana() que debería llamarse
cada vez que la ventana deba redibujarse. El problema es que no podemos registrar
como callback para el evento window_refresh al método
PAG::Renderer::refrescarVentana(), ya que no podemos registrar como
callbacks métodos de clases, sino funciones sencillas de C.
¿Cómo solucionar este problema? ¿Cómo podemos llamar desde nuestras funciones
callback en C a los métodos de la clase PAG::Renderer que responden a los distintos
eventos? Todo ello habría de hacerse de la forma más encapsulada (es decir menos
acoplada) posible.

### Solución
  Puesto que solo queremos que exista una única instancia de la clase PAG::Renderer y esta
clase debe ser accedida por el resto de clases del programa podríamos hacer uso del patrón
de diseño singleton.
  <br></br>
  La representación en UML del patrón sería de la siguiente manera:
  <br></br>
  <img src=img\UMLSingleton.png>

  El atributo tipo puntero privado hace refencia a la única instancia de la calse y este estaría 
compartido con el resto de clases a través de  los métodos públicos. Para que las funciones callback 
puedan llamar a los métodos de la clase PAG::Renderer se debe instanciar la clase primero. Se podría 
realizar de dos maneras:
- Llamando al constructor al principio del fichero main.
- Llamando al método getRenderer() cuando sea necesario crear la instancia.

