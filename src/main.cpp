#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <random>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include "Cube.h"
#include "Timer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

static unsigned int Width = 1600;
static unsigned int Height = 900;

static std::string Title = "OpenGL project";
static std::string ShaderPath = "/home/marek/Dev/Examples/OpenGL_training/res/basic.shader";
static std::string TexturePath1 = "/home/marek/Dev/Examples/OpenGL_training/res/textures/hagrid.jpg";

//Background color
static float bgColor[4] = {0.2f,0.2f,0.3f,1.0f};

static bool enableVsync = true;

static Camera camera;

bool firstMouse = true;
static float lastX = static_cast<float>(Width) / 2;
static float lastY = static_cast<float>(Height) / 2;


void FrameBuffer_CallBack(GLFWwindow* window, int width, int height){
    
    glViewport(0, 0, width, height);
    //Save data for future
    Width = width;
    Height = height;   
}

void KeyInput_CallBack(GLFWwindow* window, int key, int scancode, int action, int mods){

    float cameraStep = 2.5f * (1.0f / 60.0f);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window,GLFW_TRUE);

    if (key == GLFW_KEY_W && action == GLFW_REPEAT)
        camera.s_position += cameraStep * camera.s_front;
    if (key == GLFW_KEY_S && action == GLFW_REPEAT)
        camera.s_position -= cameraStep * camera.s_front;
    if (key == GLFW_KEY_D && action == GLFW_REPEAT)
        camera.s_position += cameraStep * glm::normalize(glm::cross(camera.s_front,camera.s_up));
    if (key == GLFW_KEY_A && action == GLFW_REPEAT)
        camera.s_position -= cameraStep * glm::normalize(glm::cross(camera.s_front,camera.s_up));
        
}

void Mouse_CallBack(GLFWwindow* window, double xposIn, double yposIn){

    printf("Cursor Pos: %f, %f \n",xposIn,yposIn);

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.yaw += xoffset;
    camera.pitch += yoffset;

    camera.yaw   += xoffset;
    camera.pitch += yoffset;

    if(camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    if(camera.pitch < -89.0f)
        camera.pitch = -89.0f;


    glm::vec3 direction;
    direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    direction.y = sin(glm::radians(camera.pitch));
    direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    camera.s_front = glm::normalize(direction);

}  

void Scroll_CallBack(GLFWwindow* window, double xpos2, double ypos2){


    printf("Scroll values: %f, %f \n",xpos2,ypos2);
        camera.fov -= (float)ypos2;
    if (camera.fov < 1.0f)
        camera.fov = 1.0f;
    if (camera.fov > 90.0f)
        camera.fov = 90.0f; 
}  

int main()
{
    /*
        GLFW Init
    */
    if(glfwInit() == false)
    {
        std::cout<<"[GLFW] Initialization Error\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 


    GLFWwindow* window = glfwCreateWindow(Width,Height,Title.c_str(),NULL, NULL);

    if(window == nullptr)
    {
        std::cout<<"[GLFW] Window creation Error\n";
        glfwTerminate();
        return -1;  
    }

    glfwSetWindowPos(window,1080 - (Width/2),720 - (Height/2)); //Central position
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // FPS coursor mode
    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(0); //VSYNC - off

    glfwSetFramebufferSizeCallback(window, FrameBuffer_CallBack); //Resizing handler
    glfwSetKeyCallback(window,KeyInput_CallBack); //Keys input handler
    glfwSetCursorPosCallback(window, Mouse_CallBack);//Mouse handler
    glfwSetScrollCallback(window, Scroll_CallBack);//Mouse handler

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }


    //Blending
    // GLCall(glEnable(GL_BLEND));
    // GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

    //Z-buffer
    GLCall(glEnable(GL_DEPTH_TEST));


    GLCall(glViewport(0,0,Width,Height));

    //IMGUI INIT
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.FontGlobalScale = 1.25f;


    // Setup Platform/Renderer backends 
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
 
    {
        Cube c1;

        VertexArray VAO;
        VertexBuffer VBO(c1.GetVerticesArrayData(), c1.GetVerticesArraySize());
        IndexBuffer EBO(c1.GetIndicatesArrayData(),c1.GetIndicatesArraySize());

        //VERTEX ATTRIBUTES 
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);

        //Adding VBO and sense of data (Vertex Attributes)
        VAO.AddBuffer(VBO,layout);

        /*
        -------------------------------------------------------------
                            Starting MVP 
        -------------------------------------------------------------
        
        */

        //Model matrix
        float translationA[3] = {-0.0f,0.0f,0.0f};  //IMGUI DATA
        float scaleA[3] = {1.0f,1.0f,1.0f};
        float rotationA[3] = {};


     
  
        //Model matrix
        glm::mat4 model; 
        
        //Camera rotation
    
       
        //Projection matrix
        

        //MVP matrix
        glm::mat4 mvp;

        //SHADERS
        Shader shader1(ShaderPath);
        shader1.Bind();

        //Renderer
        Renderer renderer;

        //Texture
        Texture texture1(TexturePath1);
        texture1.Bind();
        shader1.SetUniform1i("u_texture1",0);

        VAO.UnBind();
        VBO.UnBind();
        EBO.UnBind();
        shader1.UnBind();
      
        //Timer
        Timer Timer;
        
    while(!glfwWindowShouldClose(window))
    {          


        if(enableVsync == true)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

            Timer.onAttach();
            if(Timer.GetDeltaTime() >= 1.0 / 30.0){

                TimerCalculation calc = Timer.onUpdate();
                UpdateTitleFPS(window,Title,calc);
            }
        
            glClearColor(bgColor[0],bgColor[1],bgColor[2],bgColor[3]);
            renderer.Clear();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwPollEvents();


            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

        {
            ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
            ImGui::Begin("Debug");

                ImGui::Text("Platform");
                ImGui::NewLine();
                ImGui::Text("[GLFW]: %s", glfwGetVersionString());
                ImGui::Text("[OpenGL]: %s", glGetString(GL_VERSION));
                ImGui::Separator();
                ImGui::Checkbox("Vsync",&enableVsync);
                
       

                ImGui::Text("Window control");
                ImGui::ColorEdit4("Background",bgColor);
                ImGui::Separator();

                ImGui::Text("Objects control");
                ImGui::Text("Entities number: %d",c1.HowMany());
                ImGui::Separator();

                ImGui::PushID(0);
                ImGui::Text("Object");
                ImGui::SliderFloat3("Translation",translationA,-1.0f,1.0f);
                ImGui::SliderFloat3("Rotation",rotationA,-360.0f,360.0f);
                ImGui::SliderFloat3("Scale",scaleA,0.0f,1.0f); //Actual - OFF
                ImGui::PopID();
                ImGui::Separator();


                ImGui::PushID(1);
                ImGui::Text("Camera");
                ImGui::Text("Position:  X: %f, Y: %f, Z: %f",camera.s_position.x ,camera.s_position.y ,camera.s_position.z );
                ImGui::Text("Angle: Pitch: %f, Yaw: %f , Fov: %f",camera.pitch,camera.yaw,camera.fov);
                ImGui::Separator();
                ImGui::PopID();


            ImGui::End();
        }
           

            shader1.Bind();
            //View Matrix
             glm::mat4 view = glm::lookAt(camera.s_position,               //position
                                            camera.s_position +  camera.s_front,//target
                                            camera.s_up                //up
                                            );


            //Object 1 
            {

                c1.SetPosition(translationA[0],translationA[1],translationA[2]);
               // c1.SetScaleVec(scaleA[0],scaleA[1],scaleA[2]);
                //Model Matrix
                model = glm::translate(glm::mat4(1.0f), c1.GetPosition());
                model = glm::scale(model, glm::vec3( c1.GetSize() ));
                model = glm::rotate(model, glm::radians(rotationA[0]), glm::vec3(1.0f,0.0f,0.0f)); //X rotation
                model = glm::rotate(model, glm::radians(rotationA[1]), glm::vec3(0.0f,1.0f,0.0f)); //Y rotation
                model = glm::rotate(model, glm::radians(rotationA[2]), glm::vec3(0.0f,0.0f,1.0f)); //Z rotation
            
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(55.0f), glm::vec3(0.5f, 0.5f, 0.0f));

                glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)Width / (float)Height, 0.1f, 1000.0f);
                //Update MVP matrix
                mvp = projection * view * model;

                shader1.SetUniformMat4f("u_MVP",mvp);
                renderer.Draw(VAO,EBO,shader1);

            }



        //ImGui renderign
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }


    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}