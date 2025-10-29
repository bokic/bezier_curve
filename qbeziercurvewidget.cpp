#include "qbeziercurvewidget.h"
#include <QPainter>


static QBezierCurvePoint calcBezierCurve(const QBezierCurvePoint points[3], float pos)
{
    QBezierCurvePoint ret;

    if (pos < 0.) pos = 0.; else if (pos > 1.) pos = 1.;

    int dx12 = points[1].x - points[0].x;
    int dy12 = points[1].y - points[0].y;

    float middlePoint_x = points[0].x + (dx12 * pos);
    float middlePoint_y = points[0].y + (dy12 * pos);

    float dxm3 = points[2].x - middlePoint_x;
    float dym3 = points[2].y - middlePoint_y;

    ret.x = qRound(middlePoint_x + (dxm3 * pos));
    ret.y = qRound(middlePoint_y + (dym3 * pos));

    return ret;
}

static int calcSteps(const QBezierCurvePoint points[3])
{
    int minx, maxx;
    int miny, maxy;


    minx = qMin(points[0].x, points[1].x);
    minx = qMin(minx, points[2].x);
    maxx = qMax(points[0].x, points[1].x);
    maxx = qMax(maxx, points[2].x);

    miny = qMin(points[0].y, points[1].y);
    miny = qMin(miny, points[2].y);
    maxy = qMax(points[0].y, points[1].y);
    maxy = qMax(maxy, points[2].y);

    return ((maxx - minx) + (maxy - miny)) * 2;
}

QBezierCurveWidget::QBezierCurveWidget(QWidget* parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{

}

void QBezierCurveWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->position().x();
    int y = event->position().y();


    if (m_pointSize < 3)
    {
        m_points[m_pointSize].x = x;
        m_points[m_pointSize].y = y;
        m_pointSize++;

        if (m_pointSize >= 3)
        {
            m_steps = calcSteps(m_points);
        }

        update();
    }
    else
    {
        for (int c = 0; c < 3; c++)
        {
            if (
                (x >= m_points[c].x - 4)&&
                (x <= m_points[c].x + 4)&&
                (y >= m_points[c].y - 4)&&
                (y <= m_points[c].y + 4)
               )
            {
                m_selectedPoint = c;
                update();
                break;
            }
        }
    }
}

void QBezierCurveWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_selectedPoint = -1;
    update();
}

void QBezierCurveWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_selectedPoint != -1)
    {
        m_points[m_selectedPoint].x = event->position().x();
        m_points[m_selectedPoint].y = event->position().y();

        m_steps = calcSteps(m_points);

        update();
    }
}

void QBezierCurveWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    if (m_pointSize > 0)
    {
        for(int c = 0; c < m_pointSize; c++)
        {
            if (c == m_selectedPoint)
            {
                p.setPen(Qt::blue);
            } else
            {
                p.setPen(Qt::yellow);
            }

            p.drawRect(m_points[c].x - 2, m_points[c].y - 2, 4, 4);
        }

        if (m_pointSize == 3)
        {
            p.setPen(Qt::green);

            for(int s = 0; s < m_steps; s++)
            {
                auto bezier_point = calcBezierCurve(m_points, static_cast<float>(s) / m_steps);
                p.drawPoint(bezier_point.x, bezier_point.y);
            }
        }
    }
}
