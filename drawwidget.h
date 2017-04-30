#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QtWidgets>
#include <vector>
#include "waveparser.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    typedef WaveParser::Channel::value_type value_type;
    explicit DrawWidget(QWidget *parent = 0);

    void drawPoints(const std::vector<__int16_t> &points);
    virtual void paintEvent(QPaintEvent *event);

    std::vector<value_type> pts;

    WaveParser::FXBody fxbody;

    int offsetx, prevoffsetx;

    float scalex, scaley;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    std::pair<value_type, value_type> getOffsetSample(size_t offset);

public:
    void setFxbody(const WaveParser::FXBody &value);

public slots:
    void slotTimer();
};

#endif // DRAWWIDGET_H
