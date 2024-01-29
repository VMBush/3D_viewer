#include "glview.h"

glView::glView() {

}

glView::glView(QWidget* w) : QOpenGLWidget(w){

}


void glView::initializeGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

}

void glView::resizeGL(int w, int h) {

}

void glView::paintGL() {

}
