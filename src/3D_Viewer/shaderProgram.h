#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLShaderProgram>

class ShaderProgram {
public:
    ShaderProgram(QString primitive, QString type);
    QOpenGLShaderProgram program;
};

#endif // SHADERPROGRAM_H
