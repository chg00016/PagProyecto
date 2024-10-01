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

# *Práctica 2*
  Tal y como indica el guión, se ha implementado el patrón singleton para las nuevas clases del renderer
y para imgui, cuya librería ha sido incluida. Además, ambas clases se encuentran dentro del espacio de nombres PAG.
  <br></br>
### Clase Renderer
  Para mayor encapsulación todos las funciones de la biblioteca glad que se utilizaban en los callbacks del main han sido 
agregados a dsitintas funciones en el renderer, asi pues, en los callbacks se llama a la única instancia del renderer y este a su vez
llamará a la función correspondiente.
  Se ha modificado la función para cambiar de color con la rueda del ratón, haciendo uso de un atributo de la clase, un
vector "vec4" de color.
  <br></br>
### Clase GUI
Al crear una ventana lo primero que se debe hacer es indicar la posición en la que se va a crear. Para ello, en la función "ImGui::SetNextWindowPos()" se pasa por parametro un vector de 
dos elementos, siendo cada uno x e y, asimismo se añade la siguiente flag:
- ImGuiCond_Once: Solo se incializa la posición de la ventana una vez durante la ejecución de la aplicación, esto te permite cambiar la poscion de la ventana.
He decidido utilizar un vector de string para los mensajes que se escriben en los callbacks
  del main, un atributo privado  "std::vector<std::string> mensajes". Este vector de mensajes es pasado como parámetro en la función imgui::text() para así poder
  sacar los mensajes por la ventana.
  Para poder hacer la ventana con una rueda de colores, he creado otro atributo, "ImVec4 color", este es pasado como parametro 
en la función "ImGui::ColorPicker4()", junto con los flags necesarios que definiré a continuación:
-  ImGuiColorEditFlags_PickerHueWheel: Por defecto se genera un cuadrado de color, esto lo cambia a triangulo.
-   ImGuiColorEditFlags_DisplayRGB: Muestra los valores numéricos rgb del color seleccionado.
-   ImGuiColorEditFlags_DisplayHSV: Muestra los valores numéricos hsv del color seleccionado.
-   ImGuiColorEditFlags_DisplayHex: Muestra el color seleccionado en hexadecimal.
-   ImGuiColorEditFlags_NoAlpha: No muestra el valor de transparencia.
  Importante que cuando se crean ventanas distintas tengan nombres distintos en ImGui::Begin ( "Nombre" ). 

### Main
Antes del ciclo de eventos de la aplicación se inicializan imgui y opengl.
Durante el ciclo de eventos, explicaré en orden lo que ocurre:
- Se borra los buffers de color y profundidad.
- Se crea un nuevo frame en el que renderizar.
- Se crean las ventanas.
- Se dibuja la escena con renderer.
- Se dibuja la escena con gui.
-

# *Práctica 3*
### Ejercicio 5
Responde a esta pregunta. Si redimensionas la ventana de la aplicación, verás que el triángulo
no permanece igual, sino que se deforma al mismo tiempo que la ventana. ¿A qué crees que se
debe este comportamiento?
<br></br>
Esto es causa de la vista de la cámara, ya que es uniforme con respecto al tamaño de la ventana y por ende del viewport, para implementar 
dicha característica, solo tendríamos que modificar las dimensiones de la visión de la cámara en proporción de las dimensiones del viewport.
