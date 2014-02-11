#ifndef VAO_HEADER
#define VAO_HEADER


class Geometry{
public:
Geometry();
virtual ~Geometry();

virtual void render(GLuint shad,GLenum r = GL_QUADS)=0;
virtual int getType()=0;

};

Geometry::Geometry(){}
Geometry::~Geometry(){}




class ImageVAO:public Geometry{
public:
ImageVAO(GLuint t);
virtual ~ImageVAO();
virtual void render(GLuint shad,GLenum r = GL_QUADS);
virtual int getType();


GLuint vao;
GLuint vbo[3];
GLuint tex;
glm::vec3 trans;
};

ImageVAO::ImageVAO(GLuint t):Geometry(){
tex=t;
trans=glm::vec3(30,70,0);
float size =10;
    GLfloat vertexCoords[12]= {size,size,-50,
                               size,-size,-50,
                               -size,-size,-50,
                               -size,size,-50
                              };
                              
    GLfloat colors[8]= {-1,-1,
                        -1,1,
                        1,1,
                        1,-1
                              };

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(3,vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*12,vertexCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*8,colors,GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*12,vertexCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

}

ImageVAO::~ImageVAO(){
	
	glBindVertexArray(0);
   	glDeleteVertexArrays(1,&vao);
    	glDeleteBuffers(3,vbo);
	
}
	
void ImageVAO::render(GLuint shad,GLenum mode){

	if(mode==GL_LINE_STRIP)
	mode=GL_LINE_LOOP;

	glUseProgram(shad);
	glBindTexture(GL_TEXTURE_2D,tex);
	
	glm::mat4 temp=glm::translate(glm::mat4(),trans);
	int tempLoc = glGetUniformLocation(shad, "modelMatrix");
      glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
      
      tempLoc = glGetUniformLocation(shad, "mode");
    	glUniform1i(tempLoc, 1);
	
	
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
    glDrawArrays(mode,0,4);
}

int ImageVAO::getType(){return 1;}	
	
	
	
	
	
	
	
	
	
	
	
	
class CubeVAO:public Geometry{
public:
CubeVAO(int length, int width, int depth, glm::vec3 off);
~CubeVAO();

virtual void render(GLuint shad,GLenum r = GL_QUADS);
virtual int getType();


GLuint vao;
GLuint vbo[3];
GLuint elem;
glm::vec3 off;
};

CubeVAO::CubeVAO(int length, int width, int depth, glm::vec3 o):Geometry(){
off=o;
//float size =10;
    GLfloat vertexCoords[24]= {length,width,-depth,
                               length,-width,-depth,
                               -length,-width,-depth,
                               -length,width,-depth,
                               length,width,depth,
                               length,-width,depth,
                               -length,-width,depth,
                               -length,width,depth
                              };
                              
    GLfloat colors[32]= {1,1,1,.2,
                               0,.5,0,0,
                               .5,.5,1,0,
                               .5,0,0,1,
                               0,0,0,1,
                               1,0,1,0,
                               1,.1,.5,0,
                               0,1,0,.3
                              };
    GLushort elems[24]= {0,1,2,3,7,4,5,6,//z
    				7,3,0,4,5,6,2,1,//y
    				0,1,5,4,7,3,2,6//x
                              };


    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(3,vbo);
    glGenBuffers(1,&elem);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*24,vertexCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*32,colors,GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*24,vertexCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*24,elems,GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(3);

}

CubeVAO::~CubeVAO(){
	
	glBindVertexArray(0);
   	glDeleteVertexArrays(1,&vao);
    	glDeleteBuffers(3,vbo);
    	glDeleteBuffers(1,&elem);
	
}
	
void CubeVAO::render(GLuint shad, GLenum mode){

    glUseProgram(shad);

    int tempLoc = glGetUniformLocation(shad, "mode");
    glUniform1i(tempLoc, 0);

    glm::mat4 temp=glm::translate(glm::mat4(),off);
    tempLoc = glGetUniformLocation(shad, "modelMatrix");
    glUniformMatrix4fv(tempLoc, 1, GL_FALSE, &temp[0][0]);
	
	
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,elem);
    
    glDrawElements(mode, 24, GL_UNSIGNED_SHORT,NULL);
	
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

int  CubeVAO::getType(){return 2;}
	
	
	
#endif
