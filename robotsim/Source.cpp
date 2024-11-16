#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"AllMyInclude.h"
#include "Wheel.h"
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

float g_Scale = 1.0f;

void ScrollCallback(GLFWwindow* window, double x, double y)
{
    g_Scale =(float)y;
}

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
      -0.2f, 0.2f,0,1,//0
      -0.2f, -0.2f,0,0,//1
       0.2f, 0.2f,1,1,//2
       0.2f, -0.2f,1,0,//3
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

    Textur robottex("rob.png");
    map map("map.map");
    Renderer renderer(map);
    inputmanager inpmanager;
    Robot robot({ 0,0,0 });
    float offsetx=0, offsety=0;
    float zoom=1;
    vec3 move = { 0,0 ,0};
    vec2 camerapos = { 0,0 };
    std::string text;
    double robspeed = 0;
    vec3 deltarobpos = { 0,0,0 };
    vec3 robpos = {0,0,0};

    wheel FR(&robot, { 1,1 });
    wheel FL(&robot, { 1,0 });
    wheel BR(&robot, { 0,1 });
    wheel BL(&robot, { 0,0 });
    while (!glfwWindowShouldClose(window))
    {
        deltarobpos.x = robot.GetPos().x - robpos.x;
        deltarobpos.y = robot.GetPos().y - robpos.y;
        deltarobpos.z = robot.GetPos().z - robpos.z;
        robpos = robot.GetPos();
        robspeed = sqrt(deltarobpos.x* deltarobpos.x+ deltarobpos.y* deltarobpos.y);
        move = { 0,0 ,0 };
        deltatime = time2 - time1;
        time1 = glfwGetTime();
        
        //move rob + input
        
        if (inpmanager.press('W'))move.y += 0.01f;
        if (inpmanager.press('S'))move.y -= 0.01f;
        if (inpmanager.press('A'))move.x -= 0.01f;
        if (inpmanager.press('D'))move.x += 0.01f;
        if (inpmanager.press('E'))
            move.z += 0.1;
        if (inpmanager.press('Q'))
            move.z -= 0.1;
        if (inpmanager.press(VK_UP))camerapos.y += 0.01f*10/zoom;
        if (inpmanager.press(VK_DOWN))camerapos.y -= 0.01f*10/zoom;
        if (inpmanager.press(VK_RIGHT))camerapos.x += 0.01f * 10 / zoom;
        if (inpmanager.press(VK_LEFT))camerapos.x -= 0.01f * 10 / zoom;
        glfwSetScrollCallback(window, ScrollCallback);
        if (g_Scale > 0) {
            g_Scale = 0;
            if (zoom <= 19.0f)
                zoom += 1.0f;
            else
                zoom = 20.0f;
        }
        if (g_Scale < 0) {
            g_Scale = 0;
            if (zoom >= 2.0f)
                zoom -= 1.0f;
            else
                zoom = 1.0f;
        }
        
        double PowerVector[] = {0, 0, 0, 0, 0};

        PowerVector[4] = fabs(move.y) + fabs(move.x) + fabs(move.z);

        PowerVector[0] = move.y - move.x + move.z;
        PowerVector[1] = move.y + move.x - move.z;
        PowerVector[2] = move.y + move.x + move.z;
        PowerVector[3] = move.y - move.x - move.z;

        if (PowerVector[4] > 1) {
            PowerVector[4] /= 1;

            PowerVector[0] *= PowerVector[4];
            PowerVector[1] *= PowerVector[4];
            PowerVector[2] *= PowerVector[4];
            PowerVector[3] *= PowerVector[4];
        }

        FL.setPower(PowerVector[0]);
        FR.setPower(PowerVector[1]);
        BL.setPower(PowerVector[2]);
        BR.setPower(PowerVector[3]);
        
        robot.UpdateWheels();
        if (inpmanager.press(VK_TAB)) robot.ResetPos({ 0,0,0 });

        //drawrobot
        renderer.ClearScreen();
        ImGui_ImplGlfwGL3_NewFrame();
        GetCursorPos(&mousepos);
        robottex.Bind(0);
        TextureShader.Bind();
        TextureShader.SetUniform1f("offsetx", offsetx + robot.GetPos().x - 0.5 - camerapos.x);
        TextureShader.SetUniform1f("offsety", offsety + robot.GetPos().y - 0.5 - camerapos.y);
        TextureShader.SetUniform1f("zoom", zoom);
        TextureShader.SetUniform2f("sincos", (float)sin(robot.GetPos().z), (float)cos(robot.GetPos().z));
        TextureShader.SetUniform1i("u_Texture", GL_TEXTURE0);
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        //draw console
        std::stringstream textss;
        textss << "camerapos:  " << camerapos.x<<"  " << camerapos.y << "\nrobotpos:" << robot.GetPos().x << "  " << robot.GetPos().y << " \n zoom:" << zoom<<"\n speed:"<< robspeed;

        text = textss.str();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text(text.c_str());
        textss.clear();
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

