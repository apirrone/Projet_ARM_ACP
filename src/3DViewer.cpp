
#include "3DViewer.hpp"

Viewer::Viewer(std::vector<Voxel>* voxels, QWidget *parent)
  : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    _voxels(voxels)
{
}

Viewer::~Viewer(){
  
}

QSize Viewer::minimumSizeHint() const{
  return QSize(50, 50);
}

QSize Viewer::sizeHint() const{
  return QSize(400, 400);
}

void Viewer::initializeGL(){
  // glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
}

void Viewer::paintGL(){
  
  //TODO Récup les voxels et les afficher ici  
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f,0.0f,-5.0f); //move along z-axis
  // glRotatef(45.0,0.0,1.0,0.0); //rotate 30 degress around y-axis
  // glRotatef(45.0,1.0,0.0,0.0); //rotate 15 degress around x-axis

  glBegin(GL_TRIANGLES);

  (*_voxels)[0].paint();
  
  // for(std::vector<Voxel>::iterator it = _voxels->begin() ; it != _voxels->end(); ++it) 
  // 	    it->paint(); 
  
  //   //front
  // glColor3f(1.0,0.0,0.0);

  // glVertex3f(1.0,1.0,1.0);
  // glVertex3f(-1.0,1.0,1.0);
  // glVertex3f(-1.0,-1.0,1.0);
  // glVertex3f(1.0,-1.0,1.0);


  // //back

  // glColor3f(0.0,1.0,0.0);

  // glVertex3f(1.0,1.0,-1.0);
  // glVertex3f(-1.0,1.0,-1.0);
  // glVertex3f(-1.0,-1.0,-1.0);
  // glVertex3f(1.0,-1.0,-1.0);


  // //top
  // //glColor3f(0.0,0.0,1.0);

  // glVertex3f(-1.0,1.0,1.0);
  // glVertex3f(1.0,1.0,1.0);
  // glVertex3f(1.0,1.0,-1.0);
  // glVertex3f(-1.0,1.0,-1.0);


  // //bottom
  // glColor3f(0.0,1.0,1.0);

  // glVertex3f(1.0,-1.0,1.0);
  // glVertex3f(1.0,-1.0,-1.0);
  // glVertex3f(-1.0,-1.0,-1.0);
  // glVertex3f(-1.0,-1.0,1.0);

  // //right
  // glColor3f(1.0,0.0,1.0);

  // glVertex3f(1.0,1.0,1.0);
  // glVertex3f(1.0,-1.0,1.0);
  // glVertex3f(1.0,-1.0,-1.0);
  // glVertex3f(1.0,1.0,-1.0);


  // //left
  // glColor3f(1.0,1.0,0.0);

  // glVertex3f(-1.0,1.0,1.0);
  // glVertex3f(-1.0,-1.0,1.0);
  // glVertex3f(-1.0,-1.0,-1.0);
  // glVertex3f(-1.0,1.0,-1.0);


  glEnd();
}

void Viewer::resizeGL(int width, int height){

  glViewport( 0, 0, (GLint)width, (GLint)height );

  /* create viewing cone with near and far clipping planes */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 30.0);

  glMatrixMode( GL_MODELVIEW );

}

void Viewer::draw(){

}
