#pragma once

#include <QMainWindow>
#include <memory>


class QPixmap;

namespace Ui
{
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void drawCurrentSprite();
    //void mousePressEvent(QMouseEvent* event);

private slots:
    void on_spinnerScale_valueChanged(int i);
    void on_actionOpenSprite_triggered();

private:
    QPixmap scaleSprite(const QPixmap& sprite) const;
    void drawGridOnSprite(QPixmap& sprite) const;

private:
    QPixmap _currentSprite;
    QSize    _originalSpriteSize;
    uint32_t _scaleFactor;

    std::unique_ptr<Ui::MainWindow> _ui;
};

