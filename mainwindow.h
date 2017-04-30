#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "drawwidget.h"

class MainWindow : public DrawWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSlider *sliderScaleX, *sliderScaleY;
    QLabel *valueSliderX, *valueSliderY;

private slots:
    void slotChangeScaleX(int value);
    void slotChangeScaleY(int value);

};

#endif // MAINWINDOW_H
