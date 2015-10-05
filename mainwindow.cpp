#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


namespace
{
    constexpr auto kDefaultScaleFactor  = uint32_t{8};
}


MainWindow::MainWindow(QWidget* parent /*=0*/)
    : QMainWindow{parent}
    , _ui{std::make_unique<Ui::MainWindow>()}
{
    _ui->setupUi(this);

    _ui->spinnerScale->setValue(kDefaultScaleFactor);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actionOpenSprite_triggered()
{
    const auto selectedFileName = QString{QFileDialog::getOpenFileName(this, "Select Sprite", "", "Images (*.png);;")};
    if (!selectedFileName.isEmpty())
    {
        _ui->labelSpriteArea->loadNewSprite(selectedFileName);
        _ui->spinnerScale->setValue(kDefaultScaleFactor);
    }
}

void MainWindow::on_spinnerScale_valueChanged(int scale)
{
    auto scaleFactor = static_cast<uint32_t>(scale);
    _ui->labelSpriteArea->scaleAndDrawSprite(scaleFactor);
}
