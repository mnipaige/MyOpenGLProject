#pragma once
#include <string>
#include <GL/glew.h>
using namespace std;

static class Utils
{
public:
	Utils();
	~Utils();
	//支持顶点着色器，片段着色器
	GLuint createShaderProgram(const char* vp, const char* fp);
	////支持顶点着色器，几何着色器，片段着色器
	//GLuint createShaderProgram(const char* vp, const char* gp, const char* fp);
	////支持顶点着色器，曲面细分着色器，片段着色器
	//GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* fp);
	////支持顶点着色器，曲面细分着色器，几何着色器， 片段着色器
	//GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* gp, const char* fp);
	string readShaderSource(const char* filePath);
	bool checkOpenGLError();
	void printProgramLog(GLuint prog);
	void printShaderLog(GLuint shader);
private:

};