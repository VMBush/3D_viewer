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

}

MainWindow::~MainWindow()
{
    delete ui;
}
