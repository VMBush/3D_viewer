#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QColorDialog>


class glView : public QOpenGLWidget
{
public:
    glView();
    glView(QWidget* w);

    void draw();

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
    void initializeGL() override;

    QString getFromConf(QString param);

};

#endif // GLVIEW_H
