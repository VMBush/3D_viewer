#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include "glview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupConfigs();
    Ui::MainWindow *ui;
    glView* glScreen;
    QString selectedFilePath; // Путь к выбранному файлу

private slots:
    void backgroundColorChange();
    void projectionTypeChange(int index);
    void vertexTypeChange(int index);
    void vertexColorChange();
    void vertexThicknessChange(int index);
    void edgeTypeChange(int index);
    void edgeColorChange();
    void edgeThicknessChange(int index);
    void on_pushButton_clicked(); // Обработчик нажатия на кнопку
};
#endif // MAINWINDOW_H
