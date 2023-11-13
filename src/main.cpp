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
#include "Timer.h"

#include "Cube.h"


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

void FrameBuffer_CallBack(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    //Save data for future
    Width = width;
    Height = height;   
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
    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(0); //VSYNC - off

    glfwSetFramebufferSizeCallback(window, FrameBuffer_CallBack);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }


    //Blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

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
        /*
        Data from nowhere
        */


        Cube c1;
        //Background color
        float bgColor[4] = {0.2f,0.2f,0.3f,1.0f};

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

        glm::mat4 model; 

        //View matrix
        float cameraTrans[3] = {0.0f,0.0f,-5.0f}; //IMGUI data

        glm::mat4 view; 

        //Projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

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

            unsigned int total = c1.HowMany();
            Timer.onAttach();
            if(Timer.GetDeltaTime() >= 1.0 / 30.0){

                TimerCalculation calc = Timer.onUpdate();
                UpdateTitleFPS(window,Title,calc);
            }
        
            glClearColor(bgColor[0],bgColor[1],bgColor[2],bgColor[3]);
            renderer.Clear();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwPollEvents();

            // (Your code calls glfwPollEvents())
            // ...
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


            ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
            ImGui::Begin("Debug");

                ImGui::Text("Platform");
                ImGui::NewLine();
                ImGui::Text("[GLFW]: %s", glfwGetVersionString());
                ImGui::Text("[OpenGL]: %s", glGetString(GL_VERSION));
                ImGui::Separator();
                
       

                ImGui::Text("Window control");
                ImGui::ColorEdit4("Background",bgColor);
                ImGui::Separator();

                ImGui::Text("Objects control");
                ImGui::Text("Entities number: %d",total);
                ImGui::Separator();

                ImGui::Text("Model Matrix (OBJECT)");
                ImGui::SliderFloat3("Translation",translationA,-1.0f,1.0f);
                ImGui::SliderFloat3("Scale",scaleA,0.0f,1.0f);
                ImGui::SliderFloat("X axis rotation",&rotationA[0],-360.0f,360.0f);
                ImGui::SliderFloat("Y axis rotation",&rotationA[1],-360.0f,360.0f);
                ImGui::SliderFloat("Z axis Rotation",&rotationA[2],-360.0f,360.0f);
                ImGui::Separator();


                ImGui::Text("View Matrix (CAMERA)");
                ImGui::SliderFloat3("Translation",cameraTrans,-10.0f,10.0f);
                ImGui::Separator();


            ImGui::End();

            shader1.Bind();

            //View Matrix
            view = glm::translate(glm::mat4(1.0f), glm::vec3(cameraTrans[0],cameraTrans[1],cameraTrans[2]));
          
            //Object 1 
            {
                //Model Matrix
                model = glm::translate(glm::mat4(1.0f), glm::vec3(translationA[0],translationA[1],translationA[2]));
                model = glm::scale(model, glm::vec3(scaleA[0],scaleA[1],scaleA[2]));
                model = glm::rotate(model, glm::radians(rotationA[0]), glm::vec3(1.0f,0.0f,0.0f)); //X rotation
                model = glm::rotate(model, glm::radians(rotationA[1]), glm::vec3(0.0f,1.0f,0.0f)); //Y rotation
                model = glm::rotate(model, glm::radians(rotationA[2]), glm::vec3(0.0f,0.0f,1.0f)); //Z rotation
            
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

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