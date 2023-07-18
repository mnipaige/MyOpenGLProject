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
	//���ɶ����������
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);//2
};
void display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);//ȷ����ȶԱȲ��ܾɵ����ֵ��Ӱ��
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//���Ѿ�����ɫ��ɫ���ĳ�������OpenGL���߽׶Σ���GPU��,��û��������ɫ��
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
	//��ʼ��GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//���ð汾��,������OpenGL4.3����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//����GLFWwindow
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2-program1", NULL, NULL);
	//������window�������Զ��ĺ�OpenGL�����Ĺ�������������Ҫ�ֶ����ô˺�����������
	glfwMakeContextCurrent(window);

	//��ʼ��GLEW
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}

	//�������ô�ֱͬ��
	glfwSwapInterval(1);
	init(window);

	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		//�������ô�ֱͬ��
		glfwSwapBuffers(window);
		//����window�¼����
		glfwPollEvents();
	}

	//���ٴ���
	glfwDestroyWindow(window);
	//ֹͣ����
	glfwTerminate();
	exit(EXIT_SUCCESS);
}