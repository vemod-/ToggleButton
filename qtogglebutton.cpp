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
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0,0,0,80));

    if (m_Style == PlainStyle)
    {
        QRectF backRect = rect().adjusted(3,3,-3,-3);

        if (isChecked() || isDown()) p.drawRoundedRect(backRect.translated(1,1),5,5);
        else p.drawRoundedRect(backRect.translated(3,3),5,5);
        p.setBrush(QColor("#111"));
        p.drawRoundedRect(backRect,5,5);
        if (isChecked() || isDown()) p.setBrush(QColor("#555"));
        else p.setBrush(QColor("#AAA"));
        p.drawRoundedRect(backRect.adjusted(1,1,-1,-1),5,5);

        QLinearGradient lg(0,backRect.top()+2,0,backRect.bottom()-1);
        if (isChecked() || isDown())
        {
            lg.setColorAt(0,"#444");
            lg.setColorAt(0.4,"#332");
            lg.setColorAt(0.8,"#111");
        }
        else
        {
            lg.setColorAt(0,"#555");
            lg.setColorAt(0.4,"#444");
            lg.setColorAt(0.8,"#222");
        }

        p.setBrush(lg);
        p.drawRoundedRect(backRect.adjusted(1,2,-1,-1),5,5);

        p.setFont(font());
        backRect=rect();
        p.setBrush(Qt::NoBrush);
        if (isChecked() || isDown())
        {
            p.setPen("#660");
            p.drawText(backRect,text(),QTextOption(Qt::AlignCenter));
            p.setPen("#FFFF80");
            p.drawText(backRect.translated(-1,-1),text(),QTextOption(Qt::AlignCenter));
        }
        else
        {
            p.setPen("#EEE");
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

        p.setBrush(QColor("#111"));
        p.drawRoundedRect(ButtonRect,3,3);

        if (isDown())
        {
            p.setBrush(QColor("#999"));
        }
        else
        {
            if (isChecked())
            {
                QLinearGradient lg(ButtonRect.left()+1,0,ButtonRect.right()-1,0);
                lg.setColorAt(0.1,"#DDD");
                lg.setColorAt(0.5,"#FFFFA0");
                lg.setColorAt(0.9,"#DDD");
                p.setBrush(lg);

            }
            else
            {
                p.setBrush(QColor("#DDD"));
            }
        }
        p.drawRoundedRect(ButtonRect.adjusted(1,1,-1,-1),3,3);

        QLinearGradient lg(0,ButtonRect.top()+2,0,ButtonRect.bottom()-1);
        lg.setColorAt(0,"#888");
        lg.setColorAt(0.1,"#333");
        lg.setColorAt(0.4,"#222");
        lg.setColorAt(0.8,"#000");
        p.setBrush(lg);
        p.drawRoundedRect(ButtonRect.adjusted(1,2,-1,-1),3,3);

        p.setBrush(QColor(0,0,0,80));
        p.drawEllipse(LedPoint+QPointF(1,1),height()/12,height()/12);
        if (isChecked())
        {
            p.setBrush(QColor("#FFFF80"));
        }
        else
        {
            p.setBrush(QColor("#333"));
        }
        p.drawEllipse(LedPoint,height()/12,height()/12);

        p.setBrush(Qt::NoBrush);
        p.setPen(Qt::white);
        p.drawText(TextRect.translated(0,-1),text(),QTextOption(Qt::AlignCenter));
        p.setPen("#000");
        p.drawText(TextRect,text(),QTextOption(Qt::AlignCenter));

    }
}
