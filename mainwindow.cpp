#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    DrawWidget(parent),
    valueSliderY(nullptr),
    valueSliderX(nullptr)
{
    setStyleSheet("Background: gray");
    WaveParser p(QFileDialog::getOpenFileName().toStdString().c_str());

    setFxbody(std::move(p.getAllShanels()));

    sliderScaleX = new QSlider(Qt::Orientation::Horizontal, this);
    sliderScaleY = new QSlider(Qt::Orientation::Horizontal, this);

    connect(sliderScaleX, &QAbstractSlider::valueChanged, this, &MainWindow::slotChangeScaleX);
    connect(sliderScaleY, &QAbstractSlider::valueChanged, this, &MainWindow::slotChangeScaleY);

    sliderScaleX->setRange(1, 10000);
    sliderScaleX->setValue(10);

    sliderScaleY->setRange(1, 100);
    sliderScaleY->setValue(10);

    valueSliderX = new QLabel(QString::number((float)sliderScaleX->value() / 10.f), this);
    valueSliderY = new QLabel(QString::number((float)sliderScaleY->value() / 10.f), this);

    QHBoxLayout *lx = new QHBoxLayout;
    QHBoxLayout *ly = new QHBoxLayout;

    lx->addWidget(valueSliderX);
    lx->addWidget(sliderScaleX);

    ly->addWidget(valueSliderY);
    ly->addWidget(sliderScaleY);

    QVBoxLayout *lv = new QVBoxLayout;

    lv->addSpacerItem(new QSpacerItem(65536, 65536, QSizePolicy::Maximum, QSizePolicy::Maximum));
    lv->addLayout(lx);
    lv->addLayout(ly);

    setLayout(lv);

}

MainWindow::~MainWindow()
{
}

void MainWindow::slotChangeScaleX(int value)
{
    scalex = (float)value / 10;

    if (valueSliderX)
        valueSliderX->setText(QString::number(scalex));

    repaint();
}

void MainWindow::slotChangeScaleY(int value)
{
    scaley = (float)value / 10;

    if (valueSliderY)
        valueSliderY->setText(QString::number(scaley));

    repaint();
}
