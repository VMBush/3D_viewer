#include "glview.h"

// QString readShaderFromFile(QString path) {
//     QFile file(path);
//     if (!file.open(QIODevice::Text, QIODevice::ReadOnly)) {
//         qDebug() << "error opening file " << path;
//         return "";
//     }
//     QTextStream in(&file);
//     return in.readAll();
// }

QVector3D colorToVec(QString color) {
    color.remove(0, 1);
    return QVector3D((color.mid(0, 2).toInt(nullptr, 16) / 255.0f), (color.mid(2, 2).toInt(nullptr, 16) / 255.0f), (color.mid(4, 2).toInt(nullptr, 16) / 255.0f));
}

void glView::initializeGL() {

    QVector3D colorVec = colorToVec(this->params.backgroundColor);
    glClearColor(colorVec.x(), colorVec.y(), colorVec.z(), 1);
    glEnable(GL_DEPTH_TEST);

    initShaderPrograms();
    //object =
}

void glView::initShaderPrograms() {

    programEdge.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/edgeVert");
    if (params.edgeType == "dashed") {
        programEdge.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/edgeDashedGeo");
    }
    programEdge.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/edgeFrag");
    programEdge.link();

    programVertex.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/verVert");
    if (params.edgeType == "circle") {
        programVertex.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/verRoundGeo");
    }
    else if (params.edgeType == "square") {
        programVertex.addShaderFromSourceFile(QOpenGLShader::Geometry, ":/shaders/verSquareGeo");
    }
    programVertex.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/verFrag");
    programVertex.link();
}


void glView::paintGL() {
    QVector3D colorVec = colorToVec(this->params.backgroundColor);
    glClearColor(colorVec.x(), colorVec.y(), colorVec.z(), 1);
    glClear(GL_COLOR_BUFFER_BIT);

}

