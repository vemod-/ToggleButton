#include "qtogglebutton.h"
#include <QPainter>
//#include <QPixmap>

QToggleButton::QToggleButton(QWidget *parent)
    : QToolButton(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_NoSystemBackground);
    m_Style = PlainStyle;
    setCheckable(true);
}

void QToggleButton::paintEvent(QPaintEvent* /*event*/)
{
    QPainter p(this);
    p.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0,0,0,80));

    if (m_Style == PlainStyle)
    {
        QRectF backRect = rect().adjusted(3,3,-3,-3);

        if (isChecked() || isDown()) p.drawRoundedRect(backRect.translated(1,1),5,5);
        else p.drawRoundedRect(backRect.translated(3,3),5,5);
        p.setBrush(QColor(0x11,0x11,0x11));
        p.drawRoundedRect(backRect,5,5);
        if (isChecked() || isDown()) p.setBrush(QColor(0x55,0x55,0x55));
        else p.setBrush(QColor(0xaa,0xaa,0xaa));
        p.drawRoundedRect(backRect.adjusted(1,1,-1,-1),5,5);

        QLinearGradient lg(0,backRect.top()+2,0,backRect.bottom()-1);
        if (isChecked() || isDown())
        {
            lg.setColorAt(0,QColor(0x44,0x44,0x44));
            lg.setColorAt(0.4,QColor(0x33,0x33,0x22));
            lg.setColorAt(0.8,QColor(0x11,0x11,0x11));
        }
        else
        {
            lg.setColorAt(0,QColor(0x55,0x55,0x55));
            lg.setColorAt(0.4,QColor(0x44,0x44,0x44));
            lg.setColorAt(0.8,QColor(0x22,022,0x22));
        }

        p.setBrush(lg);
        p.drawRoundedRect(backRect.adjusted(1,2,-1,-1),5,5);

        p.setFont(font());
        backRect=rect();
        p.setBrush(Qt::NoBrush);
        if (isChecked() || isDown())
        {
            p.setPen(QColor(0x66,0x66,0));
            p.drawText(backRect,text(),QTextOption(Qt::AlignCenter));
            p.setPen(QColor(0xFF,0xFF,0x80));
            p.drawText(backRect.translated(-1,-1),text(),QTextOption(Qt::AlignCenter));
        }
        else
        {
            p.setPen(QColor(0xee,0xee,0xee));
            p.drawText(backRect,text(),QTextOption(Qt::AlignCenter));
        }
    }
    else if (m_Style == TouchStyle)
    {
        QRectF ButtonRect = rect();
        ButtonRect.setHeight(width()/6);
        if (ButtonRect.height() < 14) ButtonRect.setHeight(14);
        ButtonRect.moveBottom(rect().bottom());
        QRectF TextRect = rect();
        TextRect.setHeight((height()-ButtonRect.height())*0.5);
        TextRect.adjust(2,2,-2,-2);
        QPointF LedPoint(width()/2,(height()-ButtonRect.height())*0.75);
        ButtonRect.adjust(3,3,-3,-3);

        if (isDown())
        {
            p.drawRoundedRect(ButtonRect.translated(1,1),3,3);
        }
        else
        {
            p.drawRoundedRect(ButtonRect.translated(3,3),3,3);
        }

        p.setBrush(QColor(0x11,0x11,0x11));
        p.drawRoundedRect(ButtonRect,3,3);

        if (isDown())
        {
            p.setBrush(QColor(0x99,0x99,0x9));
        }
        else
        {
            if (isChecked())
            {
                QLinearGradient lg(ButtonRect.left()+1,0,ButtonRect.right()-1,0);
                lg.setColorAt(0.1,QColor(0xdd,0xdd,0xdd));
                lg.setColorAt(0.5,QColor(0xFF,0xFF,0xA0));
                lg.setColorAt(0.9,QColor(0xdd,0xdd,0xdd));
                p.setBrush(lg);

            }
            else
            {
                p.setBrush(QColor(QColor(0xdd,0xdd,0xdd)));
            }
        }
        p.drawRoundedRect(ButtonRect.adjusted(1,1,-1,-1),3,3);

        QLinearGradient lg(0,ButtonRect.top()+2,0,ButtonRect.bottom()-1);
        lg.setColorAt(0,QColor(0x8,0x88,0x88));
        lg.setColorAt(0.1,QColor(0x33,0x33,0x33));
        lg.setColorAt(0.4,QColor(0x22,0x22,0x22));
        lg.setColorAt(0.8,Qt::black);
        p.setBrush(lg);
        p.drawRoundedRect(ButtonRect.adjusted(1,2,-1,-1),3,3);

        p.setBrush(QColor(0,0,0,80));
        p.drawEllipse(LedPoint+QPointF(1,1),height()/12,height()/12);
        if (isChecked())
        {
            p.setBrush(QColor(0xFF,0xFF,0x80));
        }
        else
        {
            p.setBrush(QColor(0x33,0x33,0x33));
        }
        p.drawEllipse(LedPoint,height()/12,height()/12);

        p.setBrush(Qt::NoBrush);
        p.setPen(Qt::white);
        p.drawText(TextRect.translated(0,-1),text(),QTextOption(Qt::AlignCenter));
        p.setPen(Qt::black);
        p.drawText(TextRect,text(),QTextOption(Qt::AlignCenter));

    }
}
