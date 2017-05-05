#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    DrawWidget(parent),
    valueSliderY(nullptr),
    valueSliderX(nullptr)
{
    setStyleSheet("Background: gray");

    sliderScaleX = new QSlider(Qt::Orientation::Horizontal, this);
    sliderScaleY = new QSlider(Qt::Orientation::Horizontal, this);

    connect(sliderScaleX, &QAbstractSlider::valueChanged, this, &MainWindow::slotChangeScaleX);
    connect(sliderScaleY, &QAbstractSlider::valueChanged, this, &MainWindow::slotChangeScaleY);

    sliderScaleX->setRange(1, 10000);
    sliderScaleX->setValue(10);

    sliderScaleY->setRange(1, 10000);
    sliderScaleY->setValue(10);

    valueSliderX = new QLabel(QString("Scale width  1/") + QString::number((float)sliderScaleX->value() / 10.f) + (sliderScaleX->value() % 10 ? "" : ".0"), this);
    valueSliderY = new QLabel(QString("Scale heigth 1/") + QString::number((float)sliderScaleY->value() / 10.f) + (sliderScaleY->value() % 10 ? "" : ".0"), this);

    QFont font;
    font.setFamily("monospace");

    valueSliderX->setFont(font);
    valueSliderY->setFont(font);

    QHBoxLayout *lx = new QHBoxLayout;
    QHBoxLayout *ly = new QHBoxLayout;


    lx->addWidget(sliderScaleX);
    lx->addWidget(valueSliderX);


    ly->addWidget(sliderScaleY);
    ly->addWidget(valueSliderY);

    QVBoxLayout *lv = new QVBoxLayout;

    lv->addSpacerItem(new QSpacerItem(65536, 65536, QSizePolicy::Maximum, QSizePolicy::Maximum));
    lv->addLayout(lx);
    lv->addLayout(ly);

    setLayout(lv);

    QTimer::singleShot(500, this, SLOT(slotSelectAndReadFromFile()));

}

MainWindow::~MainWindow()
{
}

void MainWindow::slotChangeScaleX(int value)
{
    scalex = (float)value / 10;

    if (valueSliderX)
        valueSliderX->setText(QString("Scale width  1/") + QString::number(scalex) + (value % 10 ? "" : ".0"));

    repaint();
}

void MainWindow::slotChangeScaleY(int value)
{
    scaley = (float)value / 10;

    if (valueSliderY)
        valueSliderY->setText(QString("Scale heigth 1/") + QString::number(scaley) + (value % 10 ? "" : ".0"));

    repaint();
}

void MainWindow::slotSelectAndReadFromFile()
{
    WaveParser parser(QFileDialog::getOpenFileName().toStdString().c_str());
    setFxbody(std::move(parser.getAllShanels()));
    repaint();
}
