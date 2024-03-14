#include "glview.h"




glView::glView() {
    initGLView();
}

glView::glView(QWidget* w) : QOpenGLWidget(w){
    initGLView();
    this->fname = fname;
}

void glView::initGLView() {
    params.projectionType = getFromConf("Projection type");
    params.backgroundColor = getFromConf("Background color");
    params.vertexType = getFromConf("Vertex type");
    params.vertexColor = getFromConf("Vertex color");
    params.vertexThickness = getFromConf("Vertex thickness");
    params.edgeType = getFromConf("Edge type");
    params.edgeColor = getFromConf("Edge color");
    params.edgeThickness = getFromConf("Edge thickness");

}

QString glView::getFromConf(QString param) {
    QString executablePath = QCoreApplication::applicationDirPath();
    QFile file(QString(SRCDIR) + "options.conf");
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
    QFile configs(QString(SRCDIR) + "options.conf");
    configs.open(QIODevice::ReadOnly | QIODevice::Text);
    QFile outConf(QString(SRCDIR) + "temp.conf");
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
    outConf.rename(QString(SRCDIR) + "options.conf");
    outConf.close();
}
