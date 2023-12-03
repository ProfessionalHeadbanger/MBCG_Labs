#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void drawGradientSquare() {
    //буфер вершин
    GLuint vbo = 0;
    //массив вершин
    GLuint vao = 0;

    //задаем координаты точек для двух треугольников
    float points[] = {
        //верхний левый треугольник
        -0.5f,  0.5f, 0.0f, //верхний левый угол
         0.5f,  0.5f, 0.0f, //правый верхний угол
        -0.5f, -0.5f, 0.0f, //левый нижний угол
        //нижний правый треугольник
        -0.5f, -0.5f, 0.0f, //левый нижний угол
         0.5f,  0.5f, 0.0f, //верхний правый угол
         0.5f, -0.5f, 0.0f  //нижний правый угол
    };

    //прописываем вершинный и фрагментный шейдеры
    const char* vertex_shader =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "out vec4 vertexColor;\n"
        "void main() {\n"
        "  gl_Position = vec4(aPos, 1.0);\n"
        "  vertexColor = vec4(0.5 + aPos.x * 0.5, 0.5 + aPos.y * 0.5, 0.5, 1.0);\n"
        "}\0";
    const char* fragment_shader =
        "#version 330 core\n"
        "in vec4 vertexColor;\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "  FragColor = vertexColor;\n"
        "}\0";

    //создаем объекты шейдеров
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint shader_programme = glCreateProgram();

    //генерируем буфер и массив вершин
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    //привязываем буфер и массив
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    //настраиваем атрибуты вершин
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //компилируем шейдеры
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    //прикрепляем шейдеры к программному объекту
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    //устанавливаем текущую программу рендера
    glUseProgram(shader_programme);
    //отрисовываем
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //очищаем
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_programme);
}

int main() {
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Gradient Square", NULL, NULL);
    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawGradientSquare();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
