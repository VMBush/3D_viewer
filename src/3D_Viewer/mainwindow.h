#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
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

    void backgroundColorChange();
    void projectionTypeChange(int index);
    void vertexTypeChange(int index);
    void vertexColorChange();
    void vertexThicknessChange(int index);
    void edgeTypeChange(int index);
    void edgeColorChange();
    void edgeThicknessChange(int index);
};
#endif // MAINWINDOW_H
