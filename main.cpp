#include <iostream>
#include <fstream>
#include <vector>
#include <GLFW/glfw3.h>

using namespace std;

void getwav(const char* filename)
{
    std::ofstream ofs;
    ofs.open("output.txt",std::ofstream::out);

    FILE * inputfile;
    inputfile = fopen(filename,"rw");

    while (!feof(inputfile))
    {
        int data;
        fread(&data, sizeof(uint8_t),1,inputfile);
        ofs << data << std::endl;
    }
    int fclose(FILE* inputfile);
}

std::vector<int> filerw(std::vector<int> vector)
{
    int x;
    x = 0;
    int number;
    std::string inp;
    std::ifstream in("output.txt");
    while(std::getline(in,inp))
    {
        if(inp.size() > 0)
        {
            number = stoi(inp);
            vector.push_back(number);
        }
    }
    return vector;
}

void datacorrect(std::vector<int> vector)
{
    std::ofstream ofs;
    ofs.open("RGB.txt",std::ofstream::out);

    int width = 429;
    int height = 595;
    int pixels = width*height;
    int r;
    int none = r+1;
    int state;
    int a;
    int fvr, fvg, fvb; 
    std::vector<float> vr; int vrs = vr.size();
    std::vector<float> vg; int vgs = vg.size();
    std::vector<float> vb; int vbs = vb.size();

    int size = vector.size();
    for (int i = 0; i < size; i++)
    {
     int current = i;
     if(vector[i] == 255){r = current;cout<<"it's 255"<<endl; state = 0;}
     else if(state == 0){cout <<"it's 1 "<<vector[i]<<endl; state = state+1; fvr=vector[i]; vr.push_back(fvr);}
     else if(state == 1){cout <<"it's 2 "<<vector[i]<<endl; state = state+1; fvg=vector[i]; vg.push_back(fvg);}
     else if(state == 2){cout <<"it's 3 "<<vector[i]<<endl; state = 0;       fvb=vector[i]; vb.push_back(fvb);}
    }

    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window2 = glfwCreateWindow(width,height,"graph",NULL,NULL);
    glfwMakeContextCurrent(window2);
    glfwSwapBuffers(window2);
    glfwShowWindow(window2);
    while (!glfwWindowShouldClose(window2)) {
        int width, height;
        glfwGetFramebufferSize(window2, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
        for(float y = -height; y<height; y++){
          for(float x = -width; x<width; x++)
          {
            GLfloat ya = (y/height)/1.05;
            GLfloat xa = (x/width)/1.05;
            glVertex2f(xa,ya);
          }
        }
        glEnd();
        glFlush();
        glfwSwapBuffers(window2);
        glfwWaitEvents();
        glfwPollEvents();
    }
    glfwDestroyWindow(window2);
    glfwTerminate();
}

int main()
{
    std::vector<int> vec;
    std::vector<int> vec2;
    vec2 = filerw(vec);
    datacorrect(vec2);
}