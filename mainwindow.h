#pragma once

#include <QImage>
#include <QMainWindow>
#include <memory>


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

private slots:
    void on_spinnerScale_valueChanged(int scale);
    void on_actionOpenSprite_triggered();

private:
    std::unique_ptr<Ui::MainWindow> _ui;
    QImage _sprite;
};

