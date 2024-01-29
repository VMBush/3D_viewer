#include "glview.h"


glView::glView() {
    initGlView();
}

glView::glView(QWidget* w) : QOpenGLWidget(w){
    initGlView();
}

void glView::initGlView() {
    projectionType = getFromConf("Projection type");
    backgroundColor = getFromConf("Background color");
    vertexType = getFromConf("Vertex type");
    vertexColor = getFromConf("Vertex color");
    vertexThickness = getFromConf("Vertex thickness");
    edgeType = getFromConf("Edge type");
    edgeColor = getFromConf("Edge color");
    edgeThickness = getFromConf("Edge thickness");

}


void glView::initializeGL() {
    glMatrixMode(GL_PROJECTION);

}


QString glView::getFromConf(QString param) {
    QString executablePath = QCoreApplication::applicationDirPath();
    QFile file(executablePath + "/../../3D_Viewer/options.conf");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString line, result = "";

    QTextStream in(&file);

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList words = line.split(" : ");
        if (words[0] == param) {
            result = words[1];
            break;
        }
    }

    file.close();
    return result;
}

void glView::setConf(QString param, QString value) {
    QString executablePath = QCoreApplication::applicationDirPath();
    QFile configs(executablePath + "/../../3D_Viewer/options.conf");
    configs.open(QIODevice::ReadOnly | QIODevice::Text);
    QFile outConf(executablePath + "/../../3D_Viewer/temp.txt");
    outConf.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream in(&configs);
    QTextStream out(&outConf);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList words = line.split(" : ");
        if (words[0] == param) {
            out << words[0] << " : " << value;
        } else {
            out << line;
        }
        out << Qt::endl;
    }


    configs.close();
    configs.remove();
    outConf.rename(executablePath + "/../../3D_Viewer/options.conf");
    outConf.close();
}

void glView::draw() {

}
