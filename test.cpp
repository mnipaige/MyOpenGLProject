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

//从文本中读取着色器代码
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

//捕获GLSL错误
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

	//定义shader类型
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//设置shader源文件
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	//编译shader
	glCompileShader(vShader);
	//捕获编译shader时的错误
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1)
	{
		cout << "vertex shader compilation failed" << endl;
		printShaderLog(vShader);
	}

	glCompileShader(fShader);
	//捕获编译shader时的错误
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1)
	{
		cout << "vertex fragment compilation failed" << endl;
		printShaderLog(fShader);
	}
	//创建shader程序
	GLuint vfProgram = glCreateProgram();
	//附加shader附加在shader程序之上
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	//链接程序
	glLinkProgram(vfProgram);
	//捕获链接期间的错误
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
	//生成顶点对象数组
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);//2
};
void display(GLFWwindow* window, double currentTime)
{
	//glClearColor(0.0, 1.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//将已经编译色着色器的程序载入OpenGL管线阶段，在GPU上,并没有运行着色器
	glUseProgram(renderingProgram);
	glDrawArrays(GL_POINTS, 0, 1);
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