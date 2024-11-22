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
 

# *Práctica 3*
### Ejercicio 5
Responde a esta pregunta. Si redimensionas la ventana de la aplicación, verás que el triángulo
no permanece igual, sino que se deforma al mismo tiempo que la ventana. ¿A qué crees que se
debe este comportamiento?
<br></br>
Esto es causa de la vista de la cámara, ya que es uniforme con respecto al tamaño de la ventana y por ende del viewport, para implementar 
dicha característica, solo tendríamos que modificar las dimensiones de la visión de la cámara en proporción de las dimensiones del viewport.

### Cambios realizados
Todos los cambios realizados en esta práctica han tenido lugar en la clase Renderer, además de que ha sido añadido 
un directorio para los shaders, en el que hay dos ficheros uno para los vertex shaders y el otro para los fragment shaders.
#### Renderer
Se ha añadido un atributo booleano "problemaShader" que si es verdad hace que en la función de refrescar no se carge nada respectivo al shader. Esta variable
está por defecto en falso, y si en las funciones de "void creaShaderProgram()" y  "void cargarShader(const std::string& ruta)" ocurre
un error en las comprobaciones se vuelve verdadera.
Se comprueban errores:
- Al crear el vertex shader y al compilarlo.
- Al crear el fragment shader y al compilarlo.
- Al crear el programa de shaders y al enlazarlo con los anteriores shaders.

En el caso de ocurrir un error se lanza una excepción indicando a que clase y función pertenece. Estas excepciones son capturadas en el 
main cuando se carga los shaders e inicializa los shaders y el modelo, y son añadidas a los mensajes de la ventana de mensajes.
  <br></br>
Para cargar los ficheros con los fragment y vertex shaders se ha creado la función cargarShader(const std::string& ruta), en la que por 
parámetro se le pasa la ruta del archivo sin la extensión. El código de los shader se almacenan en dos atributos de la clase, "std::string codigoVS"
"string codigoFS" y estos son utilizados en la función de crear los shaders.

Con el objetivo de implementar un color distinto para cada arista del triángulo, se ha modificado el codigo de los shaders añadiendo
un vec3 vertexColor a ambos y un atributo color en el vertex shader.

Para el idVBO no entrelazado ha sido necesario añadir un atributo que sea un vector de dos de tamaño, por tanto se ha tenido que añadir al destructor esta variable.
El idVBO entrelazado resulta más sencillo de manejar asi que es el que he decidido utilizar.

# *Práctica 4*
El objetivo de esta práctica era desacoplar la gestión de los shader de la clase Renderer. Para ello he creado dos
clases: shader y shaderPrograms.
- La clase shader se encarga de cargar los fragment y vertex shaders.
- La clase shaderProgram se encarga de enlazar los shaders con el programa, es decir es la clase
que se comunica con el renderer.
Ambas clases están constituidas por lo que previamente se encontraba en el renderer, y simplemente 
se ha añadido un booleano para no cargar los shaders en el shaderProgram si ha habido algún error
y para ver si ha habido algún error al enlazar el shaderProgram.

<br></br>
La representación en UML tras los cambios realizados en esta práctica:
<br></br>
<img src=img\UML-prac04.png>

# *Práctica 5*
#### Cámara
Se han creado los siguientes atributos:
- glm::vec3 ptoPos, ptoMiraA, vecArriba;
- float aspecto, zNear, zFar, angulo;
  <br></br>
Un enum ha sido utilizado para saber el tipo de movimiento de la cámara:
- enum movimientoCamara{PAN, TILT, DOLLY, CRANE, ORBIT, ZOOM};
  <br></br>
  Se han creado las siguientes funciones:
- const glm::mat4 TransformacionMVision() const;
- const glm::mat4 TransformacionMProyeccion() const;
- void MatrizTranslacion();
- void visionInicial();
- void perspectivaInicial();
- void pan(float angulo);
- void tilt(float angulo);
- void dolly(float anguloX, float diffZ);
- void crane(float anguloY);
- void orbit(float anguloX, float anguloY);
- void zoom(float angulo);
- std::string switchCamara(PAG::movimientoCamara x);
- void setAspecto(float aspecto);
- void setAngulo(float angulo);
- float getAngulo();
<br></br>
Las funciones que son llamadas como los distintos tipos de movimientos, son las que se
encargan de calcular como debería moverse la cámara, para corresponder con dichos movimientos.

#### Renderer
Se han añadido los siguientes atributos:
- Camara* camara
- bool clickIzquierdo
- double *ratonPosX, *ratonPosY
- movimientoCamara TipoMovCamara
  <br></br>
Se han añadido las siguientes funciones:
- void moverRaton(GLFWwindow* window,double xoffset, double yoffset);
- void setClickIzquierdo(bool clickIzquierdo);
- void setTipoMovCamara(movimientoCamara tipoMovCamara);
- void setDireccionCamara(direccionCamara dir);
- Camara& getCamara();
<br></br>
Tres setters, uno para el tipo de movimiento de la cámara, otro para saber si se está pulsando el botón izquierdo del ratón y otro para la 
dirección del movimiento de la cámara.
La función moverRaton calcula la posición del ratón con respecto a la anterior para elegir la dirección del movimiento de la cámara. 
Se ha modificado la función cambioTamViewport(GLFWwindow *window, int width, int height) para que la cámara se ajuste al tamaño de la pantalla.
#### GUI
Se han añadido los siguientes atributos:
- movimientoCamara movimientoCam = TILT;
- direccionCamara direccionMovimiento = reset;
- float barraZoom;
<br></br>
Además se ha creado un enum de las direcciones que se puede mover la cámara:
- enum direccionCamara {izquierda = 0,derecha,arriba,abajo,reset};
<br></br>
Se han añadido las siguientes funciones:
- void seleccionarCamara(const std::string& movimiento);
- movimientoCamara getMovimientoCamara();
- void panVentana();
- void tiltVentana();
- void dollyVentana();
- void craneVentana();
- void orbitVentana();
- void zoomVentana();
- direccionCamara getDireccionCamara();
- void setBarraZoom(float barraZoom);
- void resetBotonCamara();
- float getBarraZoom();
<br></br>
Las diferentes funciones Ventana() se encargan de añadirle la dirección a la que se va a mover la cámara
a las teclas de la interfaz de cada tipo de cámara.
La función manejarVentana() ha sido modificada para añadir la nueva ventana de selección de tipo de cámara.
#### main
Se ha modificado el callback void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) para que ahora 
capture el movimiento del ratón con ImGui::GetIO(), se escoja el tipo de movimiento de cámara y tenga en cuenta si se está pulsando el botón izquierdo del ratón; además
 se ha añadido la función void cursor_pos_callback(GLFWwindow *window, double xPos, double yPos), que es llamada cada vez
que el ratón cambie de posición y le comunica al Renderer la posición del ratón para poder interactuar con la cámara.

#### Instrucciones
- En primer lugar se debe cargar el shader para poder ver los cambios en la cámara.
- En la ventana que aparece el nombre de uno de lo movimientos de la cámara, por defecto tilt, se puede
seleccionar el tipo de movimiento que realiza la cámara pinchando en el recuadro del nombre.
- La cámara se puede mover de dos maneras:

    - Pinchando con el botón izquierdo del ratón en los botones de la ventana en la que se puede seleccionar el tipo
  de movimiento; por ejemplo en tilt aparecen los botones UP(arriba) y DOWN(abajo).
    - Pinchando en la pantalla con el botón izquierdo del ratón y arrastrando manteniendo el click, por ejemplo,
  teniendo tilt como el movimiento seleccionado si se pincha y arrastra hacia arriba se mueve la cámara hacia arriba, si 
  se arrastrase horizontalmente no ocurriría nada puesto que tilt es un desplazamiento solo en vertical.

<br></br>
La representación en UML tras los cambios realizados en esta práctica:
<br></br>
<img src=img\UML-prac05.png>
# *Práctica 6*

#### Modelo
En la clase modelo se ha transferido los identificadores del vertex array object (VAO), del vertex buffer object (VBO) y 
 del index buffer object (IBO), asi como los métodos que los crean y destruyen de la clase renderer a esta. 
Para cada transformación (escalado, transalación y rotación) se ha creado una función que modifica el atributo glm::mat4 mTransformacion.
Con el objetivo de facilitar la asignación de los atributos de los vertices se ha creado un struct Vertice que contiene todos esos atributos.
ProcesarMalla y procesarNodo utilizan la librería assimp para definir el modelo en la aplicación a partir de un fichero de extensión .obj.
#### Renderer
El renderer maneja ahora el número de modelos que hay junto con la selección de las transformaciones a aplicar. 
Se han añadido los siguientes atributos
- std::vector<Modelo> modelos: Vector que contiene todos los modelos
- int modeloSeleccionado = -1: Sirve para identificar cual es el modelo seleccionado
- modeloMovimiento movimientoModelo: Sirve para identificar cual es la transformación ha aplicar en el modelo seleccionado.
#### GUI
Se han creado dos ventanas nuevas, una para el explorador de archivos que permite seleccionar un fichero de extensión .obj, que es el modelo, y 
otra ventana que permite aplicar transformaciones(utiliza un enum nuevo llamado modeloMovimiento para saber la transformación y un enum llamado direccionMovimientoModelo para saber en que eje realizar la transformación)
y destruir a un modelo seleccionado desde esta misma ventana.
Para el explorador de archivos se ha añadido un fichero de cabecera en el directorio GUI llamado imfilebrowser.
#### Shaders
En el vertex shader se ha añadido el modelo
#### Instrucciones
- Ventana de explorador de archivos: Simplemente se busca por los directorios hasta seleccionar un archivo .obj
- Ventana  de transformaciones:Cuando se añade un objeto aparece uno recuadro con numeración(el primer objeto tendrá el recuadro con el número uno, el segundo con el número dos), seleccionando
estos recuadros seleccionas al objeto al que se le aplican las transformaciones o destrucción. Para destruir un objeto se pincha el botón destruir modelo.

<br></br>
La representación en UML tras los cambios realizados en esta práctica:
<br></br>
<img src=img\UML-prac06.png>
# *Práctica 7*
#### Material
Tiene los siguientes atributos
- glm::vec3 difusa, ambiente, especular: Los colores del material con respecto a la iluminación
- float expBrillo: el exponente del brillo del material
  <br></br>
Las funciones de esta clase son simplemente los setters y getters de sus atributos.
#### Modelo
Se ha añadido un puntero al material con su getter y setter correspondiente.
#### Renderer
Se añade dos modos de dibujado de un modelo, dibujo de la malla y dibujo relleno.
El renderer aplica a los modelos el material si se selecciona el modo de dibujado relleno.
#### GUI
Añade a la ventana de transformación de modelos las propiedades del material del modelo
#### ShaderPrograms
Tiene una nueva función llamada void aplicarSubrutina(const std::string &subrutina, GLuint tipo) que procesa las subrutinas de los shaders
#### Shaders
Se han añadido nuevos shaders con subrutinas
#### Instrucciones
- Ventana de transformaciones: Se ha añadido una subventana que permite alterar las propiedades del material del modelo con unas barras de desplazamiento
vertical(arriba el valor máximo, abajo el mínimo)
- Ventana de propiedades de renderizado: Contiene una caja de verificación (checkbox) que permite cambiar el modo de visualización
del modelo (malla o relleno); por defecto está en modo relleno.

<br></br>
La representación en UML tras los cambios realizados en esta práctica:
<br></br>
<img src=img\UML-prac07.png>