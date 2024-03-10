#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QColorDialog>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QFile>
#include <QTextStream>
#include "c_code/3D_Viewer.h"

struct Params
{
    QString projectionType;
    QString backgroundColor;
    QString vertexType;
    QString vertexColor;
    QString vertexThickness;
    QString edgeType;
    QString edgeColor;
    QString edgeThickness;
};

struct Object {
    float* vertices = nullptr;
    int* indices = nullptr;
    float centMatrix[4][4];
    float rotationMatrix[4][4];
    float offsetMatrix[4][4];
};

class glView : public QOpenGLWidget
{
public:
    glView();
    glView(QWidget* w);

    void setConf(QString param, QString value);

    Params params;
    Object object;

private:

    QOpenGLShaderProgram programVertex;
    QOpenGLShaderProgram programEdge;

    GLfloat* vertices;
    GLint* indices;

    void initShaderPrograms();
    void initGLView();
    QString getFromConf(QString param);
protected:
    void initializeGL();
    void paintGL();
};

#endif // GLVIEW_H
