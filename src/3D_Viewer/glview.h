#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLWidget>
#include <QWidget>


class glView : public QOpenGLWidget
{
public:
    glView();
    glView(QWidget* w);

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QString projectionType;
    QString backgroundColor;
    QString vertexType;
    QString vertexColor;
    QString vertexThickness;
    QString edgeType;
    QString edgeColor;
    QString edgeThickness;

};

#endif // GLVIEW_H
