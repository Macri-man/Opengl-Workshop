#ifndef _glhelp_h_
#define _glhelp_h_
#include <string>
#include <fstream>
#include <iostream>

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

void loadPicture(std::string file, GLuint tex)
{
    if(file.find(".bmp")==string::npos)
        return;

    std::cout<<"Loaded: "<<file<<endl;

    SDL_Surface *image;
    SDL_Surface *fixed;
    image = SDL_LoadBMP(file.c_str());

    if(!image) {
        std::cerr<<"error loading:"<<file;
        return;
    }

    fixed=SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ABGR8888,0);

    //SDL_SetColorKey(fixed,SDL_TRUE,0xFF00FF00);
   /* SDL_Color color;
  for (int y = 0; y < fixed->h; y++)
  {
   for (int x = 0; x < fixed->w; x++)
   {
     unsigned int pix = ((unsigned int*)fixed->pixels)[y*(fixed->pitch/sizeof(unsigned int)) + x];
    //if (color.r == 255 && color.b == 255)
    if(pix==0xFFFF00FF)
    {((unsigned int*)fixed->pixels)[y*(fixed->pitch/sizeof(unsigned int)) + x] = SDL_MapRGBA(fixed->format, 0, 0, 0,0);}
   }
  }*/

    if(!fixed) {
        std::cerr<<"error loading:"<<file;
        return;
    }

    /*if(!(is2Pwr(image->w)&&is2Pwr(image->h)))
        cerr<<"image is not power of 2 it may render incorrectly"<<endl;*/
    // not actually an error here to handle

    glBindTexture(GL_TEXTURE_2D,tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0,GL_RGBA, GL_UNSIGNED_BYTE, fixed->pixels );

    if (image) 
        SDL_FreeSurface(image);
    if (fixed) 
        SDL_FreeSurface(fixed);
    
}


#endif
