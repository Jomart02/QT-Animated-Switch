#include "ToggleSwitch.h"

ToggleSwitch::ToggleSwitch(QWidget* parent ) : QWidget(parent)
{
    setMouseTracking(true);
}
ToggleSwitch::~ToggleSwitch(){

}

void ToggleSwitch::paintEvent(QPaintEvent* event) 
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Отображение тени
    QPainterPath path;

    path.addRoundedRect(rect().adjusted(3, 3, -3, -3), height() / 2, height() / 2); // Здесь мы создаем скругленный прямоугольник с небольшим смещением
    QColor shadowColor = QColor(0, 0, 0, 50); // Цвет и прозрачность тени
    painter.fillPath(path, shadowColor);


    // Swhitch
    painter.setPen(Qt::NoPen);  // Добавить обводку можно тут
    colorSwitch.setBlue(colorHover);
    colorSwitch.setAlpha(opacity);
    painter.setBrush(colorSwitch);

    // painter.setBrush(m_toggled ? QColor("#4150DE") : QColor("#CECECE"));
    painter.drawRoundedRect(rect(), height() / 2, height() / 2);

    // Slider
    int sliderSize = height() - 10;
    int sliderX = slider;
    painter.setBrush(Qt::white);
    painter.drawEllipse(sliderX, 5, sliderSize, sliderSize);
}

void ToggleSwitch::mousePressEvent(QMouseEvent* event) 
{
    if(event->button() == Qt::LeftButton) {
        setToggled(!m_toggled);
    }
}


bool ToggleSwitch::isToggled() const
{
    return m_toggled;
}

QSize ToggleSwitch::sizeHint() const 
{
    return QSize(50, 30);
}


void ToggleSwitch::setToggled(bool toggled)
{
    if(m_toggled != toggled) {
        m_toggled = toggled;
        startAnimation();

        emit toggledChanged(m_toggled);
    }
}

void ToggleSwitch::setSize(int width, int height)
{
    setFixedSize(width, height);
}

/// @brief Наведение на виджет
/// @param event
void ToggleSwitch::enterEvent(QEnterEvent* event) 
{
    hovered = true;
    startHoverAnimation();
}
/// @brief Отведение с виджета
/// @param event
void ToggleSwitch::leaveEvent(QEvent* event) 
{
    hovered = false;
    startHoverAnimation();
}

void ToggleSwitch::resizeEvent(QResizeEvent* event) 
{
    update();  // Обновляем виджет при изменении его размеров
}


void ToggleSwitch::startAnimation()
{

    QPropertyAnimation* ani = new QPropertyAnimation(this, "opacity");
    if(m_toggled) {
        ani->setStartValue(minOpacity);
        ani->setEndValue(maxOpacity);
    } else {
        ani->setStartValue(maxOpacity);
        ani->setEndValue(minOpacity);
    }

    ani->setDuration(300);
    connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
    connect(ani, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
    ani->start();

    QPropertyAnimation* ani2 = new QPropertyAnimation(this, "sliderPos");
    if(m_toggled) {
        ani2->setStartValue(5);
        ani2->setEndValue(width() - (height() - 10) - 5);
    } else {
        ani2->setStartValue(width() - (height() - 10) - 5);
        ani2->setEndValue(5);
    }

    ani2->setDuration(durationToggledProcces_sliderPos);
    connect(ani2, SIGNAL(finished()), ani2, SLOT(deleteLater()));
    connect(ani2, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
    ani2->start();

}

void ToggleSwitch::startHoverAnimation()
{

    if(m_toggled) {
        QPropertyAnimation* ani = new QPropertyAnimation(this, "colorHover");
        if(hovered) {
            ani->setStartValue(mincolorHover);
            ani->setEndValue(maxcolorHover);
        } else {
            ani->setStartValue(maxcolorHover);
            ani->setEndValue(mincolorHover);
        }
        ani->setDuration(durationToggledHovered);
        connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
        connect(ani, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
        ani->start();
    } else {
        QPropertyAnimation* ani = new QPropertyAnimation(this, "colorHover");

        if(hovered) {
            ani->setStartValue(mincolorHover);
            ani->setEndValue(maxcolorHover);
        } else {
            ani->setStartValue(maxcolorHover);
            ani->setEndValue(mincolorHover);
        }

        ani->setDuration(durationUnToggledHovered);
        connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
        connect(ani, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));


        QPropertyAnimation* ani2 = new QPropertyAnimation(this, "opacity");
        if(hovered) {
            ani2->setStartValue(0);
            ani2->setEndValue(maxHoverOpacity);
        } else {
            ani2->setStartValue(maxHoverOpacity);
            ani2->setEndValue(0);
        }

        ani2->setDuration(durationToggledHovered_opacity);
        connect(ani2, SIGNAL(finished()), ani2, SLOT(deleteLater()));
        connect(ani2, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
        ani->start();
        ani2->start();
    }


}


double ToggleSwitch::getOpacity() const
{
    return opacity;
}
void ToggleSwitch::setOpacity(double background)
{
    this->opacity = background;
    update();
}
int ToggleSwitch::getSliderPos() const
{
    return slider;
}
void ToggleSwitch::setSliderPos(int slider)
{
    this->slider = slider;
    update();
}
double ToggleSwitch::getcolorHover()
{
    return colorHover;
}
void ToggleSwitch::setcolorHover(double colorHover)
{
    this->colorHover = colorHover;
    update();
}

QColor ToggleSwitch::getcolorSwitch()
{
    return colorSwitch;
}
void ToggleSwitch::setcolorSwitch(QColor colorSwitch)
{
    this->colorSwitch = colorSwitch;
    update();
}

double ToggleSwitch::getmaxOpacity()
{
    return maxOpacity;
}
void ToggleSwitch::setmaxOpacity(double maxOpacity)
{
    this->maxOpacity = maxOpacity;
    update();
}

double ToggleSwitch::getminOpacity()
{
    return minOpacity;
}
void ToggleSwitch::setminOpacity(double minOpacity)
{
    this->minOpacity = minOpacity;
    update();
}
double ToggleSwitch::getmaxHoverOpacity()
{
    return maxHoverOpacity;
}
void ToggleSwitch::setmaxHoverOpacity(double maxHoverOpacity)
{
    this->maxHoverOpacity = maxHoverOpacity;
    update();
}
double ToggleSwitch::getmaxcolorHover()
{
    return maxcolorHover;
}
void ToggleSwitch::setmaxcolorHover(double maxcolorHover)
{
    this->maxcolorHover = maxcolorHover;
    update();
}
double ToggleSwitch::getmincolorHover()
{
    return mincolorHover;
}
void ToggleSwitch::setmincolorHover(double mincolorHover)
{
    this->mincolorHover = mincolorHover;
    update();
}


///================================================================


int ToggleSwitch::getDurationToggledHovered()
{
    return durationToggledHovered;
}
void ToggleSwitch::setDurationToggledHovered(int durationToggledHovered)
{
    this->durationToggledHovered = durationToggledHovered;
}

int ToggleSwitch::getDurationUnToggledHovered()
{
    return durationUnToggledHovered;
}
void ToggleSwitch::setDurationUnToggledHovered(int durationUnToggledHovered)
{
    this->durationUnToggledHovered = durationUnToggledHovered;
}

int ToggleSwitch::getDurationToggledProcces_opacity()
{
    return durationToggledProcces_opacity;
}
void ToggleSwitch::setDurationToggledProcces_opacity(int durationToggledProcces_opacity)
{
    this->durationToggledProcces_opacity = durationToggledProcces_opacity;
}

int ToggleSwitch::getDurationToggledProcces_sliderPos()
{
    return durationToggledProcces_sliderPos;
}
void ToggleSwitch::setDurationToggledProcces_sliderPos(int durationToggledProcces_sliderPos)
{
    this->durationToggledProcces_sliderPos = durationToggledProcces_sliderPos;
}

int ToggleSwitch::getDurationToggledHovered_opacity()
{
    return durationToggledHovered_opacity;
}
void ToggleSwitch::setDurationToggledHovered_opacity(int durationToggledHovered_opacity)
{
    this->durationToggledHovered_opacity = durationToggledHovered_opacity;
}