#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QColorDialog>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QFile>
#include <QTextStream>
#include "c_code/cModules.h"
#include "c_code/vectors.h"

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
    vecVert vertices;
    vecInd indices;
    // float* vertices = nullptr;
    // int* indices = nullptr;
    float centMatrix[4][4];
    float rotationMatrix[4][4];
    float offsetMatrix[4][4];
};

class glView : public QOpenGLWidget, protected QOpenGLFunctions
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
    QOpenGLVertexArrayObject vao;

    void initShaderPrograms();
    void initGLView();
    void rebuildObject();
    QString getFromConf(QString param);
protected:
    void initializeGL();
    void paintGL();
};

#endif // GLVIEW_H
