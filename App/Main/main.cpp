#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include "../Utils/Utils.h"

using namespace std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];
Utils utils;

float x = 0.0f;
float inc = 0.01f;


void init(GLFWwindow* window) {
	renderingProgram = utils.createShaderProgram("App/GLSL/2.4/VectShader.glsl", "App/GLSL/2.4/FragShader.glsl");
	//生成顶点对象数组
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);//2
};
void display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);//确保深度对比不受旧的深度值的影响
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//将已经编译色着色器的程序载入OpenGL管线阶段，在GPU上,并没有运行着色器
	glUseProgram(renderingProgram);

	x += inc;
	if (x > 1.0f || x < -1.0f)
	{
		inc = -inc;
	}
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
	glProgramUniform1f(renderingProgram, offsetLoc, x);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}



int main(void)
{
	//初始化GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//设置版本号,必须与OpenGL4.3兼容
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//创建GLFWwindow
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2-program1", NULL, NULL);
	//创建的window并不会自动的和OpenGL上下文关联起来，所以要手动调用此函数关联起来
	glfwMakeContextCurrent(window);

	//初始话GLEW
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}

	//用来设置垂直同步
	glfwSwapInterval(1);
	init(window);

	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		//用来设置垂直同步
		glfwSwapBuffers(window);
		//处理window事件相关
		glfwPollEvents();
	}

	//销毁窗口
	glfwDestroyWindow(window);
	//停止运行
	glfwTerminate();
	exit(EXIT_SUCCESS);
}