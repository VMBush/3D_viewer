#include "glview.h"

QVector3D colorToVec(QString color) {
    color.remove(0, 1);
    return QVector3D((color.mid(0, 2).toInt(nullptr, 16) / 255.0f), (color.mid(2, 2).toInt(nullptr, 16) / 255.0f), (color.mid(4, 2).toInt(nullptr, 16) / 255.0f));
}

void glView::initializeGL() {
    QVector3D colorVec = colorToVec(this->backgroundColor);
    glClearColor(colorVec.x(), colorVec.y(), colorVec.z(), 1);
    glEnable(GL_DEPTH_TEST);
}


void glView::paintGL() {
    QVector3D colorVec = colorToVec(this->backgroundColor);
    glClearColor(colorVec.x(), colorVec.y(), colorVec.z(), 1);
    glClear(GL_COLOR_BUFFER_BIT);

}

