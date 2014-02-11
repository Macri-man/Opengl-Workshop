#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "glhelp.h"
#include "VAO.h"

GLuint program;
GLuint outlineProg;
GLuint tex;

vector<Geometry*> geoms;

float yaw,pit;
glm::vec3 playerPos;

void setupGL(){
    glClearColor(.2, .3, .4, 0);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 600, 600);

	program=glCreateProgram();
	GLuint vs=loadShader("main.vert.txt",GL_VERTEX_SHADER);
	GLuint fs=loadShader("main.frag.txt",GL_FRAGMENT_SHADER);

	glAttachShader(program,vs);
	glAttachShader(program,fs);

	glBindAttribLocation(program, 0, "in_Position");
      glBindAttribLocation(program, 1, "in_Color");
      glBindAttribLocation(program, 2, "in_Tex");
      glBindAttribLocation(program, 3, "in_Norms");

      glLinkProgram(program);
      printLog(program);
      
      //load second shader
      outlineProg=glCreateProgram();
	vs=loadShader("outline.vert.txt",GL_VERTEX_SHADER);
	fs=loadShader("outline.frag.txt",GL_FRAGMENT_SHADER);

	glAttachShader(outlineProg,vs);
	glAttachShader(outlineProg,fs);

	glBindAttribLocation(outlineProg, 0, "in_Position");
      glBindAttribLocation(outlineProg, 1, "in_Color");
      glBindAttribLocation(outlineProg, 2, "in_Tex");
      //glBindAttribLocation(outlineProg, 3, "in_Tex");

      glLinkProgram(outlineProg);
      printLog(outlineProg);
      
    glUseProgram(program);
      
    glm::mat4 mainProjMatrix;
    //mainProjMatrix = glm::ortho(-45.0,45.0,-45.0,45.0,-20.0,5000.0);
    mainProjMatrix = glm::perspective(57.0,1.0,.1,5000.0);
    int tempLoc = glGetUniformLocation(program, "Matrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &mainProjMatrix[0][0]);
    
    glm::mat4 temp;
    tempLoc = glGetUniformLocation(program, "modelMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
    
    tempLoc = glGetUniformLocation(program, "Sam");
    glUniform1i(tempLoc,0);
    
    tempLoc = glGetUniformLocation(program, "mode");
    glUniform1i(tempLoc,0);


	glUseProgram(outlineProg);

	tempLoc = glGetUniformLocation(outlineProg, "Matrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &mainProjMatrix[0][0]);

	tempLoc = glGetUniformLocation(outlineProg, "modelMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);



   glGenTextures(1,&tex);
   loadPicture("pic.bmp",tex);

}
bool tog=true;
void input(SDL_Window* w,bool &quit){

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
				if (event.key.keysym.sym == SDLK_w){
						playerPos.z+=2;
				}
				if (event.key.keysym.sym == SDLK_s){
						playerPos.z-=2;
				}
				if (event.key.keysym.sym == SDLK_a){
						playerPos.x+=2;
				}
				if (event.key.keysym.sym == SDLK_d){
						playerPos.x-=2;
				}
				if (event.key.keysym.sym == SDLK_q){
						playerPos.y+=2;
				}
				if (event.key.keysym.sym == SDLK_e){
						playerPos.y-=2;
				}

				break;
			}
			
		case SDL_MOUSEMOTION:
		{
		
		yaw+=((event.motion.x)-300)/10.0;
		pit+=((event.motion.y)-300)/10.0;
		SDL_WarpMouseInWindow(w,300,300);
		
		}
	}
	}
}

void render(SDL_Window* screen, long long count){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    glUseProgram(program);
    
    //setup the view matrix, and the time uniform
    
    glm::mat4 temp;
    
    temp=glm::rotate(temp,pit,glm::vec3(1,0,0));
    temp=glm::rotate(temp,yaw,glm::vec3(0,1,0));
    temp=glm::translate(temp,playerPos);
    
    int tempLoc = glGetUniformLocation(program, "viewMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
    
    tempLoc = glGetUniformLocation(program, "light");
    glUniform3f(tempLoc,playerPos.x,playerPos.y,playerPos.z);
    
    glUseProgram(outlineProg);
    
    tempLoc = glGetUniformLocation(outlineProg, "viewMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
    
    glUseProgram(program);
    
    tempLoc = glGetUniformLocation(program, "time");
    glUniform1i(tempLoc, count);
    
    glLineWidth(8);
    
    //render all our geometry
    for(int x=0;x<geoms.size();x++)
    geoms.at(x)->render(outlineProg,GL_LINE_STRIP);
    
    
    for(int x=0;x<geoms.size();x++)
    geoms.at(x)->render(program);
       
	//clean up our VAO
    glBindVertexArray(0);

	GLenum e=glGetError();
	if(e)
	printf("%s\n",gluErrorString(e));

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
    SDL_ShowCursor(false);
    GLenum err = glewInit();

    if (err != GLEW_OK) fprintf(stderr, "Error: %s", glewGetErrorString(err));

    if (!screen) {
        fprintf(stderr, "Unable to start video: %s\n", SDL_GetError());
    }
    
    setupGL();
    //setup geometry
    geoms.push_back(new CubeVAO(1000,10,1000,glm::vec3(0,-50,0)));
    geoms.push_back(new CubeVAO(50,50,10,glm::vec3(-100,0,0)));
    geoms.push_back(new CubeVAO(10,10,10,glm::vec3(100,70,-100)));
    geoms.push_back(new CubeVAO(100,10,500,glm::vec3(200,50,-100)));
    geoms.push_back(new ImageVAO(tex));
    yaw=0;
    pit=0;

	bool quit=false;
	long long count=0;

	while(!quit){
	
	input(screen,quit);
	
	render(screen,count++);
	
	
	
	}



//cleanup
glUseProgram(0);

for(int x=0;x<geoms.size();x++)
delete geoms.at(x);


glDeleteProgram(program);
glDeleteTextures(1,&tex);
SDL_GL_DeleteContext(glcontext);



}
