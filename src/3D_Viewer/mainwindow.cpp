#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    if (glScreen->projectionType == "perspective") {
        ui->projectionType->setCurrentIndex(1);
    } else {
        ui->projectionType->setCurrentIndex(0);
    }

    if (glScreen->vertexType == "no") {
        ui->vertexType->setCurrentIndex(0);
    } else if (glScreen->vertexType == "circle") {
        ui->vertexType->setCurrentIndex(1);
    } else {
        ui->vertexType->setCurrentIndex(2);
    }

    newColorS = QString("\nbackground-color: %1;").arg(glScreen->vertexColor);
    ui->vertexColor->setStyleSheet(ui->vertexColor->styleSheet() + newColorS);

    if (glScreen->vertexThickness == "1") {
        ui->vertexThickness->setCurrentIndex(0);
    } else if (glScreen->vertexThickness == "2") {
        ui->vertexThickness->setCurrentIndex(1);
    } else if (glScreen->vertexThickness == "3") {
        ui->vertexThickness->setCurrentIndex(2);
    } else {
        ui->vertexThickness->setCurrentIndex(3);
    }

    if (glScreen->edgeType == "solid") {
        ui->edgeType->setCurrentIndex(0);
    } else {
        ui->edgeType->setCurrentIndex(1);
    }

    newColorS = QString("\nbackground-color: %1;").arg(glScreen->edgeColor);
    ui->edgeColor->setStyleSheet(ui->edgeColor->styleSheet() + newColorS);

    if (glScreen->edgeThickness == "1") {
        ui->edgeThickness->setCurrentIndex(0);
    } else if (glScreen->edgeThickness == "2") {
        ui->edgeThickness->setCurrentIndex(1);
    } else if (glScreen->edgeThickness == "3") {
        ui->edgeThickness->setCurrentIndex(2);
    } else {
        ui->edgeThickness->setCurrentIndex(3);
    }

}

void MainWindow::backgroundColorChange() {
    QColor color = QColorDialog::getColor();
    glScreen->backgroundColor = color.name();
    setupConfigs();
    glScreen->draw();
    glScreen->setConf("Background color", color.name());

}

void MainWindow::vertexColorChange() {
    QColor color = QColorDialog::getColor();
    glScreen->vertexColor = color.name();
    setupConfigs();
    glScreen->draw();
    glScreen->setConf("Vertex color", color.name());
}

void MainWindow::edgeColorChange() {
    QColor color = QColorDialog::getColor();
    glScreen->edgeColor = color.name();
    setupConfigs();
    glScreen->draw();
    glScreen->setConf("Edge color", color.name());
}

void MainWindow::projectionTypeChange(int index) {
    switch (index) {
    case 0:
        glScreen->projectionType = "orthogonal";
        break;
    case 1:
        glScreen->projectionType = "perspective";
        break;
    }
    glScreen->draw();
    glScreen->setConf("Projection type", glScreen->projectionType);
}

void MainWindow::vertexTypeChange(int index) {
    switch (index) {
    case 0:
        glScreen->vertexType = "no";
        break;
    case 1:
        glScreen->vertexType = "circle";
        break;
    case 2:
        glScreen->vertexType = "square";
        break;
    }
    glScreen->draw();
    glScreen->setConf("Vertex type", glScreen->vertexType);

}

void MainWindow::vertexThicknessChange(int index) {
    switch (index) {
    case 0:
        glScreen->vertexThickness = "1";
        break;
    case 1:
        glScreen->vertexThickness = "2";
        break;
    case 2:
        glScreen->vertexThickness = "3";
        break;
    case 3:
        glScreen->vertexThickness = "4";
        break;
    }
    glScreen->draw();
    glScreen->setConf("Vertex thickness", glScreen->vertexThickness);

}

void MainWindow::edgeTypeChange(int index) {
    switch (index) {
    case 0:
        glScreen->edgeType = "solid";
        break;
    case 1:
        glScreen->edgeType = "dashed";
        break;
    }
    glScreen->draw();
    glScreen->setConf("Edge type", glScreen->edgeType);

}

void MainWindow::edgeThicknessChange(int index) {
    switch (index) {
    case 0:
        glScreen->edgeThickness = "1";
        break;
    case 1:
        glScreen->edgeThickness = "2";
        break;
    case 2:
        glScreen->edgeThickness = "3";
        break;
    case 3:
        glScreen->edgeThickness = "4";
        break;
    }
    glScreen->draw();
    glScreen->setConf("Edge thickness", glScreen->edgeThickness);

}

