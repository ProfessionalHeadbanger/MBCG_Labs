#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Шейдеры вершин и фрагмента
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    out vec3 ourColor;
    void main() {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor;
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 ourColor;
    out vec4 FragColor;
    void main() {
        FragColor = vec4(ourColor, 1.0);
    }
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Установка версии OpenGL и профиля (Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создание окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "Gradient Square", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Инициализация GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Установка размеров окна
    glViewport(0, 0, 800, 600);

    // Установка обратного вызова изменения размера окна
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Компиляция и линковка шейдеров
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Определение вершин квадрата
    float vertices[] = {
        // Первый треугольник
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Левая нижняя вершина (x, y, z, r, g, b)
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Правая нижняя вершина
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Левая верхняя вершина

        // Второй треугольник
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Правая нижняя вершина
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Правая верхняя вершина
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Левая верхняя вершина
    };

    // Создание буфера вершин и массива вершин
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Привязка массива вершин
    glBindVertexArray(VAO);

    // Привязка буфера вершин и передача данных
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Атрибуты вершин
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Разбинд буфера и массива вершин
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Основной цикл рендеринга
    while (!glfwWindowShouldClose(window)) {
        // Опрос событий и обработка клавиш/мыши
        glfwPollEvents();

        // Очистка буфера цвета
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Активация шейдерной программы
        glUseProgram(shaderProgram);

        // Рисование квадрата
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Связывание массива вершин
        glBindVertexArray(0);

        // Переключение буферов и отображение результата
        glfwSwapBuffers(window);
    }

    // Очистка ресурсов
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Завершение работы GLFW
    glfwTerminate();
    return 0;
}
