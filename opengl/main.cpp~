#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glhelp.h"

GLuint program;

void setupGL(){
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);

    glViewport(0, 0, 600, 600);

	program=glCreateProgram();
	GLuint vs=loadShader("main.vert.txt",GL_VERTEX_SHADER);
	GLuint fs=loadShader("main.frag.txt",GL_FRAGMENT_SHADER);

	glAttachShader(program,vs);
	glAttachShader(program,fs);

	glBindAttribLocation(program, 0, "in_Position");
      glBindAttribLocation(program, 1, "in_color");

      glLinkProgram(program);
      printLog(program);
      
    glUseProgram(program);  
    
    glm::mat4 mainProjMatrix;
    mainProjMatrix = glm::ortho(-45.0,45.0,-45.0,45.0,-5.0,5000.0);
    int tempLoc = glGetUniformLocation(program, "Matrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &mainProjMatrix[0][0]);

}

void input(bool &quit){

SDL_Event event;

while (SDL_PollEvent(&event)) {
switch (event.type){
		
		case SDL_QUIT:
			quit=true;
			break;
		
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			{
				// exit if ESCAPE is pressed
				if (event.key.keysym.sym == SDLK_ESCAPE){
						quit=true;
				}
				

				break;
			}
	}
	}
}

void render(SDL_Window* screen,float count){
//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glUseProgram(program);
    
    
    glm::mat4 temp;
    temp=glm::rotate(glm::mat4(),count,glm::vec3(0,0,1));
    
    int tempLoc = glGetUniformLocation(program, "viewMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
    
    tempLoc = glGetUniformLocation(program, "time");
    glUniform1i(tempLoc,count);
    
    GLuint vao;
    GLuint vbo[2];
    
    float size =10;
    GLfloat vertexCoords[12]= {size,size,-50,
                               size,-size,-50,
                               -size,-size,-50,
                               -size,size,-50
                              };
                              
                              
    GLfloat vertexcolor[16]={1,0,0,.2,
   					0,1,0,.2,
   					 0,0,1,.5,
  					  0,0,0,1,};

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(2,vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*12,vertexCoords,GL_STREAM_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*16,vertexcolor,GL_STREAM_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    //glBindVertexArray(0);
    
    glDrawArrays(GL_QUADS, 0, 4);

    /*glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex3f(0,0,0);
    glVertex3f(.5,0,0);
    glVertex3f(.5,.5,0);
    glVertex3f(0,.5,0);
	glEnd();*/
	
	
	//clean up our VAO
    glBindVertexArray(0);
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(2,vbo);

	GLenum e=glGetError();
	if(e)
	printf("%s/n",gluErrorString(e));

    SDL_GL_SwapWindow(screen);
    }

int main(int argc, char **argv)
{

if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Error: Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
	SDL_Window* screen;
	SDL_GLContext glcontext;
    screen = SDL_CreateWindow("Window Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               600, 600,SDL_WINDOW_OPENGL);

    glcontext = SDL_GL_CreateContext(screen);
    //SDL_ShowCursor(false);
    GLenum err = glewInit();

    if (err != GLEW_OK) fprintf(stderr, "Error: %s", glewGetErrorString(err));

    if (!screen) {
        fprintf(stderr, "Unable to start video: %s\n", SDL_GetError());
    }
    
    setupGL();

	bool quit=false;
	float count=0;

	while(!quit){
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	input(quit);
	render(screen,count++);
	//glViewport(0, 0, 600, 600);
	//SDL_GL_SwapWindow(screen);
	
	//glViewport(0, 0, 600, 600);
	//SDL_GL_SwapWindow(screen);
	
	}



//cleanup
glUseProgram(0);
glDeleteProgram(program);
SDL_GL_DeleteContext(glcontext);



}
