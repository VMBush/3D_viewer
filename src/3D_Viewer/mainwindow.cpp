#include "mainwindow.h"
#include "ui_mainwindow.h"

// Qstring qcolorToSlashed(QColor color) {
//    return  QString::number(color.redF()) + "/" + QString::number(color.greenF()) + "/" + QString::number(color.blueF());
// }

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
    } else {
        ui->edgeType->setCurrentIndex(1);
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

void MainWindow::setVertexCountLabel() {
    ui->label_2->setText("Количество вершин: " + QString::number(Data->amount_coord));
}


void MainWindow::on_pushButton_clicked()
{
    QString folderPath = QString(SRCDIR) + "obj_files";
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл"), folderPath, tr("Files (*.*)"));
    

    if (!filePath.isEmpty()) {
        selectedFilePath = filePath;

        // Преобразуем QString filePath в char* file_name
        QByteArray byteArray = filePath.toLocal8Bit();
        char* file_name = byteArray.data();


        work_struct Data;


        int error = fileReading(&Data, file_name);

        if (error != OK) {
    
            QString errorMessage = QString("Ошибки страшнные, переделывай");
            qDebug() << errorMessage;
            QMessageBox::critical(this, "Ошибка", errorMessage);
        } else {

            qDebug() << "Файл прочтен" << filePath;
            setVertexCountLabel();

        }
        
    }
}

