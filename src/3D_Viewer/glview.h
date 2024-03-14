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
#include <QMouseEvent>
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



struct Matrices {
    // При создании объекта оцентровывает его и укладывает в масштаб от -0.7 до 0.7 по всем осям
    // При повороте мышью поворачивает (rebuildObject, mouseMoveEvent)
    float centMatrix[4][4];
    // Смещает объект при взаимодействии с мышью (rebuildObject, mouseMoveEvent)
    float offsetMatrix[4][4];
    // Отображает объект в перспективе (initializeGL,
    float perspectiveMatrix[4][4];
    // Масштабирует объект под экран (initializeGL)
    float screenMatrix[4][4];
};



class glView : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    glView();
    glView(QWidget* w);
    QString fname;

    void setConf(QString param, QString value);
    void initShaderPrograms();
    void rebuildPerspectiveMatrix();
    void rebuildObject();
    void rescale(float newScale);
    void initializeGL();


    Params params;
    Object object;

private:

    QOpenGLShaderProgram programVertex;
    QOpenGLShaderProgram programEdge;
    QOpenGLVertexArrayObject* vao;
    QOpenGLBuffer* vbo;
    QOpenGLBuffer* ebo;
    int freezing = 0;

    Matrices matrices;
    int mousePos[2];
    float scaleVal;

    void initGLView();
    QString getFromConf(QString param);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
protected:
    void paintGL();
};

#endif // GLVIEW_H
