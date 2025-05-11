#ifndef QTOGGLEBUTTON_H
#define QTOGGLEBUTTON_H

#include <QToolButton>
//#include <QPainter>

class QToggleButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(ButtonStyle ButtonStyle READ buttonStyle WRITE setButtonStyle)
public:
    enum ButtonStyle
    {
        PlainStyle,
        TouchStyle
    };
    explicit QToggleButton(QWidget *parent = 0);
    void setButtonStyle(ButtonStyle s) {
        m_Style = s;
        update();
    }
    ButtonStyle buttonStyle() { return m_Style; }
protected:
    void paintEvent(QPaintEvent* event);
private:
    ButtonStyle m_Style;
};

#endif // QTOGGLEBUTTON_H
