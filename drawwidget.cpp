#include "drawwidget.h"

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    prevoffsetx = offsetx = 0;
    scalex = scaley = 1;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
    timer->start(500);
}

void DrawWidget::drawPoints(const std::vector<__int16_t> &points)
{
    pts = std::move(points);
    repaint();
}

inline int normalPoint(const int &h, const int &scale, int value) {

    if (value >= 16777216 / 2)
        value = -(16777216 - value);

    return value / scale;
}

void DrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    QSize sz = size();

    p.drawLine(QPoint(0, sz.height() * 0.25), QPoint(sz.width(), sz.height() * 0.25));
    p.drawLine(QPoint(0, sz.height() * 0.75), QPoint(sz.width(), sz.height() * 0.75));

    int offset = sz.height() * 0.25;

    QPoint prevl(-1000, -1000);
    QPoint prevr(-1000, -1000);

    for (float i = 0; i < sz.width()*scalex; ++i) {

        std::pair<value_type, value_type> lr = std::move(getOffsetSample(i - offsetx));

        QPoint currl(i/scalex, lr.first / (-500.f / scaley) + offset);
        if (prevl.x() > -1000)
            p.drawLine(prevl, currl);

        prevl = currl;

        QPoint currr(i/scalex, lr.second / (-500.f / scaley) + offset*3);
        if (prevr.x() > -1000)
            p.drawLine(prevr, currr);

        prevr = currr;

    }

}

void DrawWidget::setFxbody(const WaveParser::FXBody &value)
{
    fxbody = value;
}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    prevoffsetx = event->pos().x();
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    offsetx += (event->pos().x() - prevoffsetx)*scalex;
    prevoffsetx = event->pos().x();
    repaint();
}

std::pair<DrawWidget::value_type, DrawWidget::value_type> DrawWidget::getOffsetSample(size_t offset)
{
    size_t currentPosSample = 0;
    for (const auto &obj : fxbody) {
        currentPosSample += obj.first.size();
        if (offset < currentPosSample)
            return std::make_pair(obj.first [offset % fxbody.front().first .size()],
                                  obj.second[offset % fxbody.front().second.size()]);
    }

    return std::make_pair(0, 0);
}

void DrawWidget::slotTimer()
{
}

