#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glhelp.h"
#include "VAO.h"

GLuint program;
GLuint tex;
CubeVAO* square;
CubeVAO* square1;
CubeVAO* square2;
SquareVAO* sq1;

float yaw,pitch;

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

      glLinkProgram(program);
      printLog(program);
      
      
    glUseProgram(program);
      
    glm::mat4 mainProjMatrix;
    mainProjMatrix = glm::ortho(-45.0,45.0,-45.0,45.0,-30.0,5000.0);
    mainProjMatrix = glm::perspective(57.0,1.0,0.1,5000.0);
    int tempLoc = glGetUniformLocation(program, "Matrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &mainProjMatrix[0][0]);
    
    glm::mat4 temp;
    tempLoc = glGetUniformLocation(program, "modelMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
    
    tempLoc = glGetUniformLocation(program, "Sam");
    glUniform1i(tempLoc,0);
    
    tempLoc = glGetUniformLocation(program, "mode");
    glUniform1i(tempLoc,0);
    
    glGenTextures(1,&tex);
    loadPicture("bitmap.bmp",tex);


}

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
						yaw+=2;
				}
				if (event.key.keysym.sym == SDLK_s){
						yaw-=2;
				}
				if (event.key.keysym.sym == SDLK_a){
						pitch-=2;
				}
				if (event.key.keysym.sym == SDLK_d){
						pitch+=2;
				}
				if (event.key.keysym.sym == SDLK_i){
						playerPos.z-=2;
				}
				if (event.key.keysym.sym == SDLK_k){
						playerPos.z+=2;
				}
				if (event.key.keysym.sym == SDLK_j){
						playerPos.x-=2;
				}
				if (event.key.keysym.sym == SDLK_l){
						playerPos.x+=2;
				}
				if (event.key.keysym.sym == SDLK_o){
						playerPos.y+=2;
				}
				if (event.key.keysym.sym == SDLK_u){
						playerPos.y-=2;
				}
				

				break;
			}
		/*case SDL_MOUSEMOTION:
		{
		yaw+=(event.motion.xrel);
		pitch+=(event.motion.xrel);
		SDL_WarpMouseInWindow(w,300,300);
		}*/
	}
	}
}

void render(SDL_Window* screen, long long count){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();
    glUseProgram(program);
    
    
    
    glm::mat4 temp;
    temp=glm::translate(temp,playerPos);
    temp=glm::rotate(temp,yaw,glm::vec3(0,1,0));
    temp=glm::rotate(temp,pitch,glm::vec3(1,0,0));
    //temp=glm::translate(temp,glm::vec3(5,0,-50));
    
    int tempLoc = glGetUniformLocation(program, "viewMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
    
    tempLoc = glGetUniformLocation(program, "time");
    glUniform1i(tempLoc, count);
    
    tempLoc = glGetUniformLocation(program, "mode");
    glUniform1i(tempLoc, 0);
    
    glBindTexture(GL_TEXTURE_2D,tex);
    
    

	if(square){
	
	temp=glm::translate(glm::mat4(),square->off);
	tempLoc = glGetUniformLocation(program, "modelMatrix");
    	glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
	
	glBindVertexArray(square->vao); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,square->elem);
	
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT,NULL);
	
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	//clean up our VAO
    glBindVertexArray(0);
	}
    	if(square1){

	temp=glm::translate(glm::mat4(),square1->off);
	tempLoc = glGetUniformLocation(program, "modelMatrix");
    	glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
	
	glBindVertexArray(square1->vao); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,square1->elem);
	
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT,NULL);
	
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	//clean up our VAO
    glBindVertexArray(0);
	}
	if(square2){
	
	
	temp=glm::translate(glm::mat4(),square2->off);
	tempLoc = glGetUniformLocation(program, "modelMatrix");
    	glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
	
	glBindVertexArray(square2->vao); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,square2->elem);
	
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT,NULL);
	
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	//clean up our VAO
    	glBindVertexArray(0);
	}
	
	if(sq1){

	temp=glm::translate(glm::mat4(),glm::vec3(50,50,-50));
	tempLoc = glGetUniformLocation(program, "modelMatrix");
    	glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
    	
    	 tempLoc = glGetUniformLocation(program, "mode");
   	 glUniform1i(tempLoc, 1);
	
	glBindVertexArray(sq1->vao); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT,NULL);
	glDrawArrays(GL_QUADS,0,4);
	
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	//clean up our VAO
    	glBindVertexArray(0);
	}
   
    
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
    //square=new CubeVAO(100,10,100,glm::vec3(0,-50,0));
    ///square1=new CubeVAO(50,100,10,glm::vec3(-50,-50,0));
    //square2=new CubeVAO(100,10,100,glm::vec3(100,70,-100));
    sq1=new SquareVAO();
	yaw=0;
	pitch=0;
	bool quit=false;
	long long count=0;

	while(!quit){
	
	input(screen,quit);
	
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glViewport(0, 0, 600, 600);
	render(screen,count++);
	//glViewport(550, 550, 40, 40);
	//render(screen,count++);
	
	//SDL_GL_SwapWindow(screen);
	
	
	}



//cleanup
glUseProgram(0);
delete square;
delete square2;
delete square1;
glDeleteProgram(program);
glDeleteTextures(1,&tex);
SDL_GL_DeleteContext(glcontext);



}
