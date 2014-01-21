#ifndef _glhelp_h_
#define _glhelp_h_
#include <string>
#include <fstream>

using namespace std;

void printLog(GLuint obj)
{
    int infologLength = 0;
    int maxLength;

    if(glIsShader(obj))
        glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
    else
        glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);

    char infoLog[maxLength];

    if (glIsShader(obj))
        glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
    else
        glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);

    if (infologLength > 0)
        fprintf(stderr,"%s\n",infoLog);

}

GLuint loadShader(string s,GLenum type)
{
    string shad;

    ifstream in(s.c_str());
    string line;
    while ( in.good() ) {
        getline (in,line);
        shad+=line+"\n";
    }
    in.close();

    GLchar* vShad = new char [shad.length()+1];
    strcpy (vShad, shad.c_str());

    GLuint vs;
    vs = glCreateShader(type);
    glShaderSource(vs, 1, (const GLchar**)(&vShad), NULL);
    glCompileShader(vs);
    printLog(vs);

    delete[] vShad;

    return vs;
}


#endif
