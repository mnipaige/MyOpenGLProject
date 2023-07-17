#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];
GLint vertCompiled;
GLint fragCompiled;
GLint linked;

//���ı��ж�ȡ��ɫ������
string readShaderSource(const char* filePath)
{
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

//����GLSL����
void printShaderLog(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Shader Info Log: " << log << endl;
		free(log);
	}
}


void printProgramLog(int prog)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}

bool checkOpenGLError()
{
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

GLuint creatShaderProgram()
{
	string vShaderStr = readShaderSource("GLSL/2.1/VectShader.glsl");
	string fShaderStr = readShaderSource("GLSL/2.1/FragShader.glsl");

	const char* vshaderSource = vShaderStr.c_str();
	const char* fshaderSource = fShaderStr.c_str();
	/*const char* vshaderSource = "#version 430 \n"
		"void main(void) \n"
		"{	gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
	const char* fshaderSource = "#version 430 \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ color = vec4(0.0, 1.0, 0.0, 1.0); } ";*/

	//����shader����
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//����shaderԴ�ļ�
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	//����shader
	glCompileShader(vShader);
	//�������shaderʱ�Ĵ���
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1)
	{
		cout << "vertex shader compilation failed" << endl;
		printShaderLog(vShader);
	}

	glCompileShader(fShader);
	//�������shaderʱ�Ĵ���
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1)
	{
		cout << "vertex fragment compilation failed" << endl;
		printShaderLog(fShader);
	}
	//����shader����
	GLuint vfProgram = glCreateProgram();
	//����shader������shader����֮��
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	//���ӳ���
	glLinkProgram(vfProgram);
	//���������ڼ�Ĵ���
	checkOpenGLError();
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		cout << "linking failed" << endl;
		printProgramLog(vfProgram);
	}

	return vfProgram;
}

void init(GLFWwindow* window) {
	renderingProgram = creatShaderProgram();
	//���ɶ����������
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);//2
};
void display(GLFWwindow* window, double currentTime)
{
	//glClearColor(0.0, 1.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//���Ѿ�����ɫ��ɫ���ĳ�������OpenGL���߽׶Σ���GPU��,��û��������ɫ��
	glUseProgram(renderingProgram);
	glDrawArrays(GL_POINTS, 0, 1);
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