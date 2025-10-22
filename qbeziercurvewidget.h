#pragma once

#include <QWidget>
#include <QMouseEvent>


struct QBezierCurvePoint
{
    int x = 0;
    int y = 0;
};

class QBezierCurveWidget: public QWidget
{
public:
    explicit QBezierCurveWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QBezierCurvePoint m_points[3];
    int m_pointSize = 0;
    int m_selectedPoint = -1;
    int m_steps = 0;
};
