#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QOpenGLFunctions>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* screen = ui->screenHandler;
    glScreen = new glView(screen);
    glScreen->setGeometry(3, 3, screen->width() - 6, screen->height() - 6);


    setupConfigs();

    connect(ui->backgroundColor, &QPushButton::clicked, this, &MainWindow::backgroundColorChange);
    connect(ui->vertexColor, &QPushButton::clicked, this, &MainWindow::vertexColorChange);
    connect(ui->edgeColor, &QPushButton::clicked, this, &MainWindow::edgeColorChange);
    connect(ui->projectionType, &QComboBox::currentIndexChanged, this, &MainWindow::projectionTypeChange);
    connect(ui->vertexType, &QComboBox::currentIndexChanged, this, &MainWindow::vertexTypeChange);
    connect(ui->vertexThickness, &QComboBox::currentIndexChanged, this, &MainWindow::vertexThicknessChange);
    connect(ui->edgeType, &QComboBox::currentIndexChanged, this, &MainWindow::edgeTypeChange);
    connect(ui->edgeThickness, &QComboBox::currentIndexChanged, this, &MainWindow::edgeThicknessChange);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConfigs() {
    QString newColorS;

    if (glScreen->params.projectionType == "perspective") {
        ui->projectionType->setCurrentIndex(1);
    } else {
        ui->projectionType->setCurrentIndex(0);
    }

    if (glScreen->params.vertexType == "no") {
        ui->vertexType->setCurrentIndex(0);
    } else if (glScreen->params.vertexType == "circle") {
        ui->vertexType->setCurrentIndex(1);
    } else {
        ui->vertexType->setCurrentIndex(2);
    }

    newColorS = QString("\nbackground-color: %1;").arg(glScreen->params.vertexColor);
    ui->vertexColor->setStyleSheet(ui->vertexColor->styleSheet() + newColorS);

    if (glScreen->params.vertexThickness == "1") {
        ui->vertexThickness->setCurrentIndex(0);
    } else if (glScreen->params.vertexThickness == "2") {
        ui->vertexThickness->setCurrentIndex(1);
    } else if (glScreen->params.vertexThickness == "3") {
        ui->vertexThickness->setCurrentIndex(2);
    } else {
        ui->vertexThickness->setCurrentIndex(3);
    }

    if (glScreen->params.edgeType == "solid") {
        ui->edgeType->setCurrentIndex(0);
    } else if (glScreen->params.edgeType == "dashed") {
        ui->edgeType->setCurrentIndex(1);
    } else {
        ui->edgeType->setCurrentIndex(2);
    }

    newColorS = QString("\nbackground-color: %1;").arg(glScreen->params.edgeColor);
    ui->edgeColor->setStyleSheet(ui->edgeColor->styleSheet() + newColorS);

    if (glScreen->params.edgeThickness == "1") {
        ui->edgeThickness->setCurrentIndex(0);
    } else if (glScreen->params.edgeThickness == "2") {
        ui->edgeThickness->setCurrentIndex(1);
    } else if (glScreen->params.edgeThickness == "3") {
        ui->edgeThickness->setCurrentIndex(2);
    } else {
        ui->edgeThickness->setCurrentIndex(3);
    }

}

void MainWindow::backgroundColorChange() {
    QColor color = QColorDialog::getColor();
    glScreen->params.backgroundColor = color.name();
    setupConfigs();
    glScreen->setConf("Background color", glScreen->params.backgroundColor);
    glScreen->update();

}

void MainWindow::vertexColorChange() {
    QColor color = QColorDialog::getColor();
    glScreen->params.vertexColor = color.name();
    setupConfigs();
    glScreen->setConf("Vertex color", glScreen->params.vertexColor);
}

void MainWindow::edgeColorChange() {
    QColor color = QColorDialog::getColor();
    glScreen->params.edgeColor = color.name();
    setupConfigs();
    glScreen->setConf("Edge color", glScreen->params.edgeColor);
}

void MainWindow::projectionTypeChange(int index) {
    switch (index) {
    case 0:
        glScreen->params.projectionType = "orthogonal";
        break;
    case 1:
        glScreen->params.projectionType = "perspective";
        break;
    }
    glScreen->setConf("Projection type", glScreen->params.projectionType);
    glScreen->rebuildPerspectiveMatrix();
}

void MainWindow::vertexTypeChange(int index) {
    switch (index) {
    case 0:
        glScreen->params.vertexType = "no";
        break;
    case 1:
        glScreen->params.vertexType = "circle";
        break;
    case 2:
        glScreen->params.vertexType = "square";
        break;
    }
    glScreen->setConf("Vertex type", glScreen->params.vertexType);

}

void MainWindow::vertexThicknessChange(int index) {
    switch (index) {
    case 0:
        glScreen->params.vertexThickness = "1";
        break;
    case 1:
        glScreen->params.vertexThickness = "2";
        break;
    case 2:
        glScreen->params.vertexThickness = "3";
        break;
    case 3:
        glScreen->params.vertexThickness = "4";
        break;
    }
    glScreen->setConf("Vertex thickness", glScreen->params.vertexThickness);

}

void MainWindow::edgeTypeChange(int index) {
    switch (index) {
    case 0:
        glScreen->params.edgeType = "solid";
        break;
    case 1:
        glScreen->params.edgeType = "dashed";
        break;
    case 2:
        glScreen->params.edgeType = "no";
        break;
    }

    glScreen->setConf("Edge type", glScreen->params.edgeType);
}

void MainWindow::edgeThicknessChange(int index) {
    switch (index) {
    case 0:
        glScreen->params.edgeThickness = "1";
        break;
    case 1:
        glScreen->params.edgeThickness = "2";
        break;
    case 2:
        glScreen->params.edgeThickness = "3";
        break;
    case 3:
        glScreen->params.edgeThickness = "4";
        break;
    }
    glScreen->setConf("Edge thickness", glScreen->params.edgeThickness);

}

void MainWindow::on_pushButton_clicked()
{
    clearVecInd(&(glScreen->object.indices));
    clearVecVert(&(glScreen->object.vertices));
    QString folderPath = QString(SRCDIR) + "obj_files";
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл"), folderPath, tr("Files (*.obj)"));

    if (!filePath.isEmpty()) {
        // Преобразуем QString filePath в char* file_name
        QByteArray byteArray = filePath.toLocal8Bit();
        char* file_name = byteArray.data();

        // Вызываем наш парсер для чтения файла
        loadObj(file_name, &(glScreen->object));

        ui->label_2->setText("Количество вершин: " + QString::number(glScreen->object.vertices.size));
        ui->label_3->setText("Количество ребер: " + QString::number(glScreen->object.indices.size));
        for (int i = 0; i < glScreen->object.indices.size; i++) {
            qDebug() << "\n" << i << ": " << glScreen->object.indices.data[2*i] <<  glScreen->object.indices.data[2*i + 1];
        }

        // Извлекаем имя файла из полного пути
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();

        // Выводим имя файла в label
        ui->label->setText("Имя объекта: " + fileName);
        glScreen->rebuildObject();
    }
}


void MainWindow::on_dial_sliderMoved(int position)
{
    glScreen->rescale(position);
}




void MainWindow::on_saveImg_clicked()
{
    QString initialPath = QString(SRCDIR) + "generated_media";
    QString selectedFilter;
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Сохранить изображение", initialPath, "Images (*.bmp *.jpg)", &selectedFilter);
    if (!filePath.isEmpty()) {
        QImage image = glScreen->grabFramebuffer();
        image.save(filePath);
    }
}



void MainWindow::on_saveGif_clicked() {
    ui->saveGif->setEnabled(false);
    ui->recordInd->setStyleSheet(ui->recordInd->styleSheet() + "\n	background: #00ff00;");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(oneGif()));
    timer->start(100);
    gifElCount = 0;
    QDir().mkdir(QString(SRCDIR) + "generated_media/tmp");
}

void MainWindow::oneGif() {
    glScreen->grab().scaled(640, 480, Qt::IgnoreAspectRatio).save(QString(SRCDIR) + "generated_media/tmp/" + QString::number(gifElCount) + ".bmp");
    gifElCount++;


    if (gifElCount == 50) {
        timer->stop();
        createGif();
        gifElCount = 0;
        QDir dir(QString(SRCDIR) + "generated_media/tmp");
        dir.removeRecursively();
    }

}

void MainWindow::createGif() {
    QString selectedFilter;
    QString gif_name = QFileDialog::getSaveFileName(nullptr, "Сохранить gif", QString(SRCDIR) + "generated_media", "GIF (*.gif)", &selectedFilter);
    QByteArray ga = gif_name.toLocal8Bit();
    GifWriter writer = {};
    int err = 0;
    if (GifBegin(&writer, ga.data(), 640, 480, 10, 8, false)) {
        for (int i = 0; i < 50; i++) {
            if (err == 1) {
                break;
            }
            QImage img(QString(SRCDIR) + "generated_media/tmp/" + QString::number(i) + ".bmp");
            if (!img.isNull()) {
                if (GifWriteFrame(&writer,
                                  img.convertToFormat(QImage::Format_Indexed8)
                                      .convertToFormat(QImage::Format_RGBA8888)
                                      .constBits(),
                                  640, 480, 10, 8, false)) {
                } else {
                    QMessageBox::critical(0, "Error", "Gif file can not be created! 1");
                    err = 1;
                }
            } else {
                QMessageBox::critical(0, "Error", "Gif file can not be created! 2");
                err = 1;
            }
        }
        if (err == 0) {
            GifEnd(&writer);
        }
    } else {
        err = 1;
        QMessageBox::critical(0, "Error", "Gif file can not be created! 3");
    }

    if (err == 1) {
        if (QFile::exists(gif_name)) {
            QFile::remove(gif_name);
        }
    }

    ui->saveGif->setEnabled(true);
    ui->recordInd->setStyleSheet(ui->recordInd->styleSheet() + "\n	background: #ff0000;");

}

