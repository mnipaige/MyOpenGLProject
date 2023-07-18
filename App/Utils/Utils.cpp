#include "Utils.h";
#include<iostream>
#include<fstream>


GLuint Utils::createShaderProgram(const char* vp, const char* fp)
{
	string vShaderStr = readShaderSource(vp);
	string fShaderStr = readShaderSource(fp);

	const char* vshaderSource = vShaderStr.c_str();
	const char* fshaderSource = fShaderStr.c_str();

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
	GLint vertCompiled;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1)
	{
		cout << "vertex shader compilation failed" << endl;
		printShaderLog(vShader);
	}

	glCompileShader(fShader);
	//捕获编译shader时的错误
	checkOpenGLError();
	GLint fragCompiled;
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
	GLint linked;
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		cout << "linking failed" << endl;
		printProgramLog(vfProgram);
	}

	return vfProgram;
}

string Utils::readShaderSource(const char* filePath)
{
	string content;
	ifstream fileStream(filePath, ios::in);
	//todo 错误处理
	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

bool Utils::checkOpenGLError()
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

void Utils::printProgramLog(GLuint prog)
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

void Utils::printShaderLog(GLuint shader)
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

Utils::Utils()
{
}

Utils::~Utils()
{
}