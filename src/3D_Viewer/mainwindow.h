#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include "glview.h"
//#include "c_code/vectors.h"
#include "3rdparty/gif.h"


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
    QTimer* timer;
    int gifElCount;

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
    void on_dial_sliderMoved(int position);
    void on_saveImg_clicked();
    void on_saveGif_clicked();

    void oneGif();
    void createGif();



};
#endif // MAINWINDOW_H
