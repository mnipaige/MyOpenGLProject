#pragma once
#include <string>
#include <GL/glew.h>
using namespace std;

static class Utils
{
public:
	Utils();
	~Utils();
	//֧�ֶ�����ɫ����Ƭ����ɫ��
	GLuint createShaderProgram(const char* vp, const char* fp);
	////֧�ֶ�����ɫ����������ɫ����Ƭ����ɫ��
	//GLuint createShaderProgram(const char* vp, const char* gp, const char* fp);
	////֧�ֶ�����ɫ��������ϸ����ɫ����Ƭ����ɫ��
	//GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* fp);
	////֧�ֶ�����ɫ��������ϸ����ɫ����������ɫ���� Ƭ����ɫ��
	//GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* gp, const char* fp);
	string readShaderSource(const char* filePath);
	bool checkOpenGLError();
	void printProgramLog(GLuint prog);
	void printShaderLog(GLuint shader);
private:

};