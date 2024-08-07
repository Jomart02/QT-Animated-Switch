#pragma once

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QObject>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class ToggleSwitch : public QWidget
{
        Q_OBJECT
        Q_PROPERTY(double background READ getBackground WRITE setBackground)
        Q_PROPERTY(double sliderPos READ getSliderPos WRITE setSliderPos)
        Q_PROPERTY(double colorHover READ getcolorHover WRITE setcolorHover)
    public:
        ToggleSwitch(QWidget* parent = nullptr) : QWidget(parent), m_toggled(false)
        {
            // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Установим политику изменения размеров виджета
            //  resize(parent->size()); // Установка начального размера равным размеру родительского виджета
            setMouseTracking(true);
        }

        void paintEvent(QPaintEvent* event) override
        {
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);

            // Отображение тени
            QPainterPath path;
            double opacity = background;

            path.addRoundedRect(rect().adjusted(3, 3, -3, -3), height() / 2, height() / 2); // Здесь мы создаем скругленный прямоугольник с небольшим смещением
            QColor shadowColor = QColor(0, 0, 0, 50); // Цвет и прозрачность тени
            painter.fillPath(path, shadowColor);


            // Swhitch
            painter.setPen(Qt::NoPen);  // Добавить обводку можно тут
            double color = colorHover;
            painter.setBrush(QColor(65, 80, colorHover, opacity));
            // painter.setBrush(m_toggled ? QColor("#4150DE") : QColor("#CECECE"));
            painter.drawRoundedRect(rect(), height() / 2, height() / 2);

            // Slider
            int sliderSize = height() - 10;
            int sliderX = slider;
            painter.setBrush(Qt::white);
            painter.drawEllipse(sliderX, 5, sliderSize, sliderSize);
        }

        void mousePressEvent(QMouseEvent* event) override
        {
            if(event->button() == Qt::LeftButton) {
                m_toggled = !m_toggled;
                // update();
                startAnimation();
                emit toggledChanged(m_toggled);
            }
        }


        bool isToggled() const
        {
            return m_toggled;
        }

        QSize sizeHint() const override
        {
            return QSize(50, 30);
        }

    public slots:
        void setToggled(bool toggled)
        {
            if(m_toggled != toggled) {
                m_toggled = toggled;
                update();

                emit toggledChanged(m_toggled);
            }
        }

        void setSize(int width, int height)
        {
            setFixedSize(width, height);
        }

    signals:
        void toggledChanged(bool toggled);

    protected:
        /// @brief Наведение на виджет
        /// @param event
        void enterEvent(QEnterEvent* event) override
        {
            hovered = true;
            startHoverAnimation();
        }
        /// @brief Отведение с виджета
        /// @param event
        void leaveEvent(QEvent* event) override
        {
            hovered = false;
            startHoverAnimation();
        }

        void resizeEvent(QResizeEvent* event) override
        {
            update();  // Обновляем виджет при изменении его размеров
        }
    private:

        void startAnimation()
        {

            QPropertyAnimation* ani = new QPropertyAnimation(this, "background");
            if(m_toggled) {
                ani->setStartValue(0);
                ani->setEndValue(255);
            } else {
                ani->setStartValue(255);
                ani->setEndValue(0);
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

            ani2->setDuration(200);
            connect(ani2, SIGNAL(finished()), ani2, SLOT(deleteLater()));
            connect(ani2, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
            ani2->start();

        }

        void startHoverAnimation()
        {

            if(m_toggled) {
                QPropertyAnimation* ani = new QPropertyAnimation(this, "colorHover");
                if(hovered) {
                    ani->setStartValue(222);
                    ani->setEndValue(180);
                } else {
                    ani->setStartValue(180);
                    ani->setEndValue(222);
                }
                ani->setDuration(120);
                connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
                connect(ani, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
                ani->start();
            } else {
                QPropertyAnimation* ani = new QPropertyAnimation(this, "colorHover");

                if(hovered) {
                    ani->setStartValue(0);
                    ani->setEndValue(222);
                } else {
                    ani->setStartValue(222);
                    ani->setEndValue(0);
                }

                ani->setDuration(20);
                connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
                connect(ani, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));


                QPropertyAnimation* ani2 = new QPropertyAnimation(this, "background");
                if(hovered) {
                    ani2->setStartValue(0);
                    ani2->setEndValue(50);
                } else {
                    ani2->setStartValue(50);
                    ani2->setEndValue(0);
                }

                ani->setDuration(120);
                connect(ani2, SIGNAL(finished()), ani2, SLOT(deleteLater()));
                connect(ani2, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
                ani->start();
                ani2->start();
            }


        }


        double getBackground() const
        {
            return background;
        }
        void setBackground(double background)
        {
            this->background = background;
            update();
        }
        int getSliderPos() const
        {
            return slider;
        }
        void setSliderPos(int slider)
        {
            this->slider = slider;
            update();
        }
        double getcolorHover()
        {
            return colorHover;
        }
        void setcolorHover(double colorHover)
        {
            this->colorHover = colorHover;
            update();
        }
    private:
        double background = 0;
        int slider = 5;
        bool m_toggled;
        bool hovered = false;
        double colorHover = 255;
};