#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QColorDialog>
#include <QVector3D>


class glView : public QOpenGLWidget
{
public:
    glView();
    glView(QWidget* w);


    QString projectionType;
    QString backgroundColor;
    QString vertexType;
    QString vertexColor;
    QString vertexThickness;
    QString edgeType;
    QString edgeColor;
    QString edgeThickness;

    void setConf(QString param, QString value);

private:
    void initGlView();
    QString getFromConf(QString param);
protected:
    void initializeGL();
    void paintGL();
};

#endif // GLVIEW_H
