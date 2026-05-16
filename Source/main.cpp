#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <chrono>

#include <windows.h>
#include <commdlg.h>

#include <glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Text.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int WPM = 150;
int charIndex = 0;
bool pause = false;
bool fileSelection = false;
bool fileSelected = false;
std::string filePath;
std::string text;
std::string currentWord = "sample";
std::string WPMtext = "150";


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* init_opengl();
std::string OpenTextFileDialog();
std::string OpenFontFileDialog();
void input(GLFWwindow* window, int key, int scancode, int action, int mods);
void CheckFile(std::string (*SelectFile)(), std::string TypeExtension);
void ReadFile();

void NextWord();
void JumpForward(int words);
void JumpBackwards(int words);

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

int main(){
	HideConsole();
	
    print("TextReader start point\n");

    GLFWwindow* window = init_opengl();
    if(window == nullptr){
        println("failed to initialize opengl");
        return -1;
    }

    // compile and setup the shader
    // ----------------------------
    Shader shader("../../Shaders/vertexTexture.shader", "../../Shaders/fragmentTexture.shader");
    glm::mat4 projectionText = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT);
    shader.Use();
    glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projectionText));

    //float deltaTime= 0;
    //float currTime = 0, prevTime = glfwGetTime();

    Text::InitClass();
    Text text(&shader);

    glUseProgram(0);

    CheckFile(OpenFontFileDialog, ".ttf");
    if(fileSelected == false){
        return 1;
    }
    text.LoadFont(filePath.c_str(), 50);

    CheckFile(OpenTextFileDialog, ".txt");
    if(fileSelected){
        ReadFile();
        NextWord();
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[µs]" << std::endl;

    //zanka se izvaja toliko casa dokler ne zapremo okna
    while (!glfwWindowShouldClose(window))
    {
        //prevTime = currTime;
        //currTime = glfwGetTime();
        //deltaTime = currTime - prevTime;

        //dolocimo barvo s katero bomo pobrisali zaslon
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //pobrisemo zaslon
        glClear(GL_COLOR_BUFFER_BIT);

        if(fileSelected && pause == false){
            std::chrono::steady_clock::time_point elapsed = std::chrono::steady_clock::now();

            //println(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed - begin).count());

            if(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed - begin).count() > 60000/WPM){
                begin = std::chrono::steady_clock::now();
                NextWord();
                println(charIndex);
            }
        }
        text.Render(currentWord, {270, 160}, 1.5f, ColorRGB(255,255,255));
        text.Render("Words Per Minute: " + WPMtext, {0,0}, 1, ColorRGB(255,255,255));

        //zamenjamo buffer
        glfwSwapBuffers(window);
        //preverimo za evente
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
void CheckFile(std::string (*SelectFileDialog)(), std::string TypeExtension){
    fileSelection = true;

    filePath = SelectFileDialog();

    if (!filePath.empty()) {
        std::cout << "Selected file: " << filePath << std::endl;
        std::string extension;
        for(int i = filePath.size()-2;i>0;i--){
            if(filePath[i] =='.'){
                for(int j=i;j<filePath.size();j++){
                    extension.push_back(filePath[j]);
                }
                break;
            }
        }
        if(extension.compare(TypeExtension) == 0){
            println("Selected file is a txt file!");
            fileSelected = true;
        }
        else{
            for(int i=0;i<TypeExtension.size();i++){
                if(TypeExtension[i] >= 'a' && TypeExtension[i] <= 'z'){
                    TypeExtension[i] -= 32;
                }
                else if(TypeExtension[i] >= 'A' && TypeExtension[i] <= 'Z'){
                    TypeExtension[i] += 32;
                }
            }
            if(extension.compare(TypeExtension) == 0){
                println("Selected file is a txt file!");
                fileSelected = true;
            }
            else{
                println("Selected file is not a txt file!");
                fileSelected = false;
            }
        }
    }
    else{
        std::cout << "Selection canceled\n";
        fileSelected = false;
    }

    fileSelection = false;
    charIndex = 0;
}
void ReadFile(){
    std::ifstream data;
    data.open(filePath.c_str());

    text.clear();
    text = "";
    
    if(!data.is_open()){
        println("ERROR OPENING FILE");
        return;
    }

    std::string line;
    while(getline(data, line)){
        text += line;
        text +='\n';
    }
    data.close();
    charIndex = 0;
}

void NextWord(){
    currentWord.clear();
    //std::cout<<"Text position: " << charIndex << std::endl;
    for(int i=charIndex;i<text.size();i++){
        if(text[i] == ' ' || text[i] == '\n'){
            charIndex = i+1;
            break;
        }
        currentWord.push_back(text[i]);
    }
    //std::cout<<"Current word is: " << currentWord << std::endl;
}
void JumpForward(int words){
    currentWord.clear();

    int wordsToSkip=words;

    for(int i=charIndex;i<text.size();i++){
        if(wordsToSkip > 0){
            if(text[i] == ' ' || text[i] == '\n'){
                wordsToSkip--;
            }
        }
        else {
            if(text[i] == ' ' || text[i] == '\n'){
                charIndex = i;
                break;
            }
            currentWord.push_back(text[i]);
        }
    }
}
void JumpBackwards(int words){

    for(int i=charIndex;i>=0;i--){
        charIndex = i;
        if(words > 0){
            if(text[i] == ' ' || text[i] == '\n'){
                words--;
            }
        }
        else{
            break;
        }
    }
    NextWord();
}

void input(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_UP && action == GLFW_PRESS){
        WPM += 10;
        WPMtext = std::to_string(WPM);
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        WPM -= 10;
        if(WPM <= 0)
            WPM = 10;
        WPMtext = std::to_string(WPM);
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
        JumpForward(10);
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
        JumpBackwards(10);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        pause = !pause;
    }
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS){
        if(fileSelection == false){
            CheckFile(OpenTextFileDialog, ".txt");
            if(fileSelected){
                ReadFile();
                NextWord();
            }
        }
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.

    glViewport(0, 0, width, height);
}
GLFWwindow* init_opengl(){


    //Inicializacija GLFW knjiznjice
    glfwInit();
    //Dolocimo verzijo opengl-a : 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //ustvarimo okno
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TextReader", NULL, NULL);
    if(window == nullptr){
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetKeyCallback(window, input);

    //inicializiramo glew
    glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW INIT ERROR\n";
		glfwTerminate();
		return nullptr;
	}
    //tukaj povemo opengl-u velikost nasega okna za pravilno renderanje
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST); // Optional for 2D

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetWindowAspectRatio(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}

std::string OpenTextFileDialog() {
    char filename[MAX_PATH] = "";

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt = "txt";

    if (GetOpenFileName(&ofn)) {
        return std::string(filename);
    }

    return ""; // user cancelled
}
std::string OpenFontFileDialog() {
    char filename[MAX_PATH] = "";

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = "True Type Font Files (*.ttf)\0*.ttf\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt = "ttf";

    if (GetOpenFileName(&ofn)) {
        return std::string(filename);
    }

    return ""; // user cancelled
}