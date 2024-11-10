#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"AllMyInclude.h"

#define fov 30.0f
#define degres 0.0174f
#define ScreenHeight 768
#define ScreenLenght 1366
float spaceing = 2.0f/fov;
const float pi = 3.14f;

float startor;
float deltatime;

float quality =3;

float time1, time2;
vec2 mousep;
POINT mousepos;

int main(void)
{
    GLFWwindow* window;
    
   
    if (!glfwInit())
        return -1;

   
    window = glfwCreateWindow(ScreenLenght, ScreenHeight, "robsim", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

   
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR not glew!!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    

    shader Shader("Basic.shader");
    shader TextureShader("texture.shader");
    

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    
    float startspace = (float)(spaceing-1.00f);
    float pos[] = {
      -1.0f, 1.0f,//0
      -1.0f,-1.0f,//1
      startspace, 1.0f,//2
      startspace,-1.0f//3
    };

    unsigned int indices[] = {
        0,1,2,2,3,1
    };
    unsigned int VAO, VAB, IBO;

    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VAB);
    glBindBuffer(GL_ARRAY_BUFFER, VAB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6  * 2, pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,(void*)0);
    
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    float postop[] = {
      -0.1125f, 0.2f,0,1,//0
      -0.1125f, -0.2f,0,0,//1
       0.1125f, 0.2f,1,1,//2
       0.1125f, -0.2f,1,0,//3
    };

    
    unsigned int  VAO1, VAB1, IBO1;

    glCreateVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    glGenBuffers(1, &VAB1);
    glBindBuffer(GL_ARRAY_BUFFER, VAB1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4, postop, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &IBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    Textur robot("rob.png");
    map map("map.map");
    Renderer renderer(map);
    inputmanager inpmanager;
    float offsetx=0, offsety=0;
    float mx=0;
    while (!glfwWindowShouldClose(window))
    {
        
        mx += 1.0f;
        deltatime = time2 - time1;
        time1 = glfwGetTime();
        renderer.ClearScreen();
        ImGui_ImplGlfwGL3_NewFrame();
        GetCursorPos(&mousepos);
        robot.Bind(0);
        TextureShader.Bind();
        if (inpmanager.press('W'))offsety += 0.01f;
        if (inpmanager.press('S'))offsety -= 0.01f;
        if (inpmanager.press('A'))offsetx -= 0.01f;
        if (inpmanager.press('D'))offsetx += 0.01f;
        TextureShader.SetUniform1f("offsetx", offsetx);

       TextureShader.SetUniform1f("offsety", offsety);

        TextureShader.SetUniform1i("u_Texture", GL_TEXTURE0);
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

       
        glfwSwapBuffers(window);

        glfwPollEvents();
        time2 = glfwGetTime();
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}

