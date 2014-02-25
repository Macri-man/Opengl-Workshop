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

GLuint frameBuff;
GLuint frameTex;
GLuint frameDepth;

ImageVAO* frame;

vector<Geometry*> geoms;

float yaw,pit;
glm::vec3 playerPos;
glm::vec3 light;

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
      glBindAttribLocation(program, 3, "in_Norm");

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
   
   glGenFramebuffers(1,&frameBuff);
   glBindFramebuffer(GL_FRAMEBUFFER,frameBuff);
   
   glGenTextures(1,&frameTex);
   glGenTextures(1,&frameDepth);
   
   glBindTexture(GL_TEXTURE_2D,frameTex);
   glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,128,128,0,GL_BGRA,GL_FLOAT,0);
   
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
   
   glBindTexture(GL_TEXTURE_2D,frameDepth);
   glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,128,128,0,GL_DEPTH_COMPONENT,GL_FLOAT,0);
   
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
   
   glBindFramebuffer(GL_FRAMEBUFFER,frameBuff);
   glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,frameTex,0);
   glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,frameDepth,0);
   
   if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)cerr<<"frame buffer failed\n";
   glBindFramebuffer(GL_FRAMEBUFFER,0);
   

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
    glUniform3f(tempLoc, light.x,light.y,light.z);
    
    tempLoc = glGetUniformLocation(program, "viewer");
    glUniform3f(tempLoc, playerPos.x,playerPos.y,playerPos.z);
    
    glUseProgram(outlineProg);
    
    tempLoc = glGetUniformLocation(outlineProg, "viewMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
    
    temp=glm::rotate(glm::mat4(),.1f,glm::vec3(0,0,1));
    light=glm::vec3(temp*glm::vec4(light,1));
    
    glUseProgram(program);
    
    tempLoc = glGetUniformLocation(program, "time");
    glUniform1i(tempLoc, count);
    
    glLineWidth(5);
    
    glBindFramebuffer(GL_FRAMEBUFFER,frameBuff);
    glViewport(0,0,128,128);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //render all our geometry
    //for(int x=0;x<geoms.size();x++)
    //geoms.at(x)->render(outlineProg,GL_LINE_STRIP);
    
    
    for(int x=0;x<geoms.size();x++)
    geoms.at(x)->render(program);
   	
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0,0,600,600);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
     //render all our geometry
    for(int x=0;x<geoms.size();x++)
    geoms.at(x)->render(outlineProg,GL_LINE_STRIP);
    
    
    for(int x=0;x<geoms.size();x++)
    geoms.at(x)->render(program);
    frame->render(program);
      
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
    light=glm::vec3(0.0,-100.0,20.0);
    //setup geometry
    geoms.push_back(new CCubeVAO(1000,10,1000,glm::vec3(0,-50,0)));
    geoms.push_back(new CCubeVAO(50,50,10,glm::vec3(-100,0,0)));
    geoms.push_back(new CCubeVAO(10,10,10,glm::vec3(100,70,-100)));
    geoms.push_back(new CCubeVAO(100,10,500,glm::vec3(200,50,-100)));
    //geoms.push_back(new ImageVAO(tex));
    frame= new ImageVAO(frameTex);
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
