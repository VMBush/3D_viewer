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

class glView : public QOpenGLWidget
{
public:
    glView();
    glView(QWidget* w);

    void setConf(QString param, QString value);

    Params params;
    QOpenGLShaderProgram programVertex;
    QOpenGLShaderProgram programEdge;




private:
    void initShaderPrograms();
    void initGLView();
    QString getFromConf(QString param);
protected:
    void initializeGL();
    void paintGL();
};

#endif // GLVIEW_H
