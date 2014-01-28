#ifndef VAO_HEADER
#define VAO_HEADER

class SquareVAO{
public:
SquareVAO();
~SquareVAO();



GLuint vao;
GLuint vbo[2];

};

SquareVAO::SquareVAO(){

float size =10;
    GLfloat vertexCoords[12]= {size,size,-50,
                               size,-size,-50,
                               -size,-size,-50,
                               -size,size,-50
                              };
                              
    GLfloat colors[8]= {1,1,
    				0,1,
    				1,1,
    				1,0
    				};

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(2,vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*12,vertexCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*8,colors,GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);

}

	SquareVAO::~SquareVAO(){
	
	glBindVertexArray(0);
   	glDeleteVertexArrays(1,&vao);
    	glDeleteBuffers(2,vbo);
	
	}
	
class CubeVAO{
public:
CubeVAO(int length,int width,int depth,glm::vec3 off);
~CubeVAO();



GLuint vao;
GLuint vbo[2];
GLuint elem;
glm::vec3 off;
};

CubeVAO::CubeVAO(int length,int width,int depth,glm::vec3 o){
off=o;
float size =10;
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
    GLushort elems[24]= {0,1,2,3,4,5,6,7,
    				0,4,7,3,1,5,6,2,
    				0,1,5,4,3,2,6,7
                              };


    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(2,vbo);
    glGenBuffers(1,&elem);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*24,vertexCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*32,colors,GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*24,elems,GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

}

	CubeVAO::~CubeVAO(){
	
	glBindVertexArray(0);
   	glDeleteVertexArrays(1,&vao);
    	glDeleteBuffers(2,vbo);
    	glDeleteBuffers(1,&elem);
	
	}
	
	
	
	
	
	
#endif
