#include <iostream>
// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include "./Renderer/Renderer.h"
#include "GUI/GUI.h"
#include "Shader/Shader.h"
#include "Shader/ShaderPrograms.h"

// - Esta función callback será llamada cuando GLFW produzca algún error
void error_callback ( int errno, const char* desc ){
    std::string aux (desc);
    std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
}

// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void window_refresh_callback ( GLFWwindow *window ){
    PAG::Renderer::getInstancia().refrescar();
// - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
// intercambia el buffer back (que se ha estado dibujando) por el
// que se mostraba hasta ahora front. Debe ser la última orden de
// este callback
    glfwSwapBuffers ( window );
    PAG::GUI::getInstancia().addmensaje("Refresh callback call");
}

// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void framebuffer_size_callback ( GLFWwindow *window, int width, int height ){
    PAG::Renderer::getInstancia().cambioTamViewport(window, width, height);
    PAG::GUI::getInstancia().addmensaje("Resize callback called");

}

// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    PAG::GUI::getInstancia().addmensaje("Key callback called");
}

// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    ImGuiIO &io = ImGui::GetIO();

    if (!io.WantCaptureMouse) {
        PAG::Renderer::getInstancia().setTipoMovCamara(PAG::GUI::getInstancia().getMovimientoCamara());
        if(action == GLFW_PRESS){
            PAG::Renderer::getInstancia().setClickIzquierdo(true);
            PAG::GUI::getInstancia().addmensaje("Pulsado el boton: ");
        }else if(action == GLFW_RELEASE) {
            PAG::Renderer::getInstancia().setClickIzquierdo(false);
            PAG::GUI::getInstancia().addmensaje("Soltado el boton: ");
        }
    } else
        PAG::Renderer::getInstancia().setClickIzquierdo(false);
}

// -Esta función será llamada cada vez que el ratón cambie de posición
void cursor_pos_callback(GLFWwindow *window, double xPos, double yPos) {
    ImGuiIO& io = ImGui::GetIO();
    if(!io.WantCaptureMouse) {
        PAG::Renderer::getInstancia().moverRaton(window,xPos, yPos);
    }

}

// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void scroll_callback ( GLFWwindow *window, double xoffset, double yoffset ){
    PAG::GUI::getInstancia().addmensaje("Movida la rueda del raton " + std::to_string(xoffset) +
        " Unidades en horizontal y " + std::to_string(yoffset) + " unidades en vertical");
    PAG::Renderer::getInstancia().ruedaRaton(window, xoffset, yoffset);
}


int main(){
std::cout << "Starting Application PAG - Prueba 01" << std::endl;

// - Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback ( (GLFWerrorfun) error_callback );

// - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    if ( glfwInit () != GLFW_TRUE ){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

// - Definimos las características que queremos que tenga el contexto gráfico
// OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
// modo Core Profile.
    glfwWindowHint ( GLFW_SAMPLES, 4 ); // - Activa antialiasing con 4 muestras.
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // - Esta y las 2
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 4 ); // siguientes activan un contexto
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 1 ); // OpenGL Core Profile 4.1.

// - Definimos el puntero para guardar la dirección de la ventana de la aplicación y
// la creamos
    GLFWwindow *window;

// - Tamaño, título de la ventana, en ventana y no en pantalla completa,
// sin compartir recursos con otras ventanas.
    window = glfwCreateWindow ( 1024, 576, "PAG Introduction", nullptr, nullptr );

// - Comprobamos si la creación de la ventana ha tenido éxito.
    if ( window == nullptr ){
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }

// - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
// ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent ( window );

// - Ahora inicializamos GLAD.
    if ( !gladLoadGLLoader ( (GLADloadproc) glfwGetProcAddress ) ){
        std::cout << "GLAD initialization failed" << std::endl;
        glfwDestroyWindow ( window ); // - Liberamos los recursos que ocupaba GLFW.
        window = nullptr;
        glfwTerminate ();
        return -3;
    }

// - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
// 3D construido.
    PAG::GUI::getInstancia().addmensaje(PAG::Renderer::getInstancia().getInforme());


    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback ( window, window_refresh_callback );
    glfwSetFramebufferSizeCallback ( window, framebuffer_size_callback );
    glfwSetKeyCallback ( window, key_callback );
    glfwSetMouseButtonCallback ( window, mouse_button_callback );
    glfwSetScrollCallback ( window, scroll_callback );
    //PR5
    glfwSetCursorPosCallback ( window, cursor_pos_callback );
    //
    //Inicializar ImGUI
    PAG::GUI::getInstancia().inicializarImGUI(window);

    //Inicializamos opengl
    PAG::Renderer::getInstancia().inicializarOpenGL();
    //PR4
    PAG::Shader *shader = new PAG::Shader;
    PAG::ShaderPrograms *shaderPrograms = new PAG::ShaderPrograms;
    PAG::Renderer::getInstancia().setShaderProgram(*shaderPrograms);
    PAG::Renderer::getInstancia().creaModelo();


// - Ciclo de eventos de la aplicación. La condición de parada es que la
// ventana principal deba cerrarse. Por ejemplo, si el usuario pulsa el
// botón de cerrar la ventana (la X).
    while ( !glfwWindowShouldClose ( window ) ){
        //Borra los buffers (color y profundidad)
        glm::vec4 color = PAG::Renderer::getInstancia().getClearColor();
        PAG::GUI::getInstancia().setColor(color.r, color.g, color.b, color.a);


        //Se crea un nuevo frame en el que renderizar
        PAG::GUI::getInstancia().newFrame();

        //Se crean las ventanas
        PAG::GUI::getInstancia().setVentana();
        PAG::GUI::getInstancia().manipularVentana();
        //La escena se dibuja
        PAG::Renderer::getInstancia().setClearColor(
            PAG::GUI::getInstancia().getColor().x, PAG::GUI::getInstancia().getColor().y,
            PAG::GUI::getInstancia().getColor().z, PAG::GUI::getInstancia().getColor().w);

        //PR3 y PR4
        if(PAG::GUI::getInstancia().getbuttonPressed()) {
            try{
                // Cargamos los shaders e inicializamos los shaders y el modelo
                shader->cargarShader("..\\Shaders\\" + PAG::GUI::getInstancia().getNombreShader());
                shader->crearShader();
                shaderPrograms->linkShader(*shader);

                PAG::Renderer::getInstancia().setShaderProgram(*shaderPrograms);
            }catch(std::exception& e) {
                PAG::GUI::getInstancia().addmensaje(e.what());
                PAG::GUI::getInstancia().addmensaje("\n");
                shaderPrograms->setExito(false);
            }
            PAG::GUI::getInstancia().setButtonPressed(false);
        }

        PAG::Renderer::getInstancia().render();
        PAG::Renderer::getInstancia().refrescar();
        // - se dibuja la interfaz con imgui
        PAG::GUI::getInstancia().render();
        // - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
        // intercambia el buffer back (en el que se ha estado dibujando) por el
        // que se mostraba hasta ahora (front).
        glfwSwapBuffers ( window );

        // - Obtiene y organiza los eventos pendientes, tales como pulsaciones de
        // teclas o de ratón, etc. Siempre al final de cada iteración del ciclo
        // de eventos y después de glfwSwapBuffers(window);
        glfwPollEvents ();
    }

// - Una vez terminado el ciclo de eventos, liberar recursos, etc.

    std::cout << "Finishing application pag prueba" << std::endl;
    //PR4
    delete shader;
    shader = nullptr;
    delete shaderPrograms;
    shaderPrograms = nullptr;
    //---
    PAG::GUI::getInstancia().liberarRecursos();
    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
}
