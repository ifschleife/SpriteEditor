#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cassert>
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>


namespace
{
    constexpr auto kDefaultScaleFactor  = uint32_t{8};
    constexpr auto kDefaultSpriteSize   = QSize{64, 64};
    constexpr auto kMaximumScaleForGrid = uint32_t{4};
}


MainWindow::MainWindow(QWidget* parent /*=0*/)
    : QMainWindow{parent}
    , _currentSprite{kDefaultSpriteSize}
    , _originalSpriteSize{kDefaultSpriteSize}
    , _scaleFactor{kDefaultScaleFactor}
    , _ui{std::make_unique<Ui::MainWindow>()}
{
    _ui->setupUi(this);

    _ui->spinnerScale->setValue(_scaleFactor);

    _currentSprite.fill(QColor(255, 255, 255, 255));
    drawCurrentSprite();
}

MainWindow::~MainWindow()
{

}

void MainWindow::drawCurrentSprite()
{
    auto scaledSprite = scaleSprite(_currentSprite);
    if (_scaleFactor >= kMaximumScaleForGrid)
    {
        drawGridOnSprite(scaledSprite);
    }
    _ui->labelSpriteArea->setPixmap(scaledSprite);
}

QPixmap MainWindow::scaleSprite(const QPixmap& sprite) const
{
    const auto newSize = QSize{_scaleFactor * sprite.size()};
    return sprite.scaled(newSize, Qt::KeepAspectRatio, Qt::FastTransformation); // don't user bilinear filtering
}

void MainWindow::drawGridOnSprite(QPixmap& sprite) const
{
    assert(_scaleFactor >= kMaximumScaleForGrid);

    QPainter painter(&sprite);
    painter.setPen(QColor(0, 0, 0, 255));

    painter.drawRect(0, 0, sprite.width()-1, sprite.height()-1);

    for (int x=0; x < sprite.width(); x+=_scaleFactor)
    {
        painter.drawLine(x, 0, x, sprite.height());
    }
    for (int y=0; y < sprite.width(); y+=_scaleFactor)
    {
        painter.drawLine(0, y, sprite.width(), y);
    }
}

void MainWindow::on_actionOpenSprite_triggered()
{
    const auto selectedFileName = QString{QFileDialog::getOpenFileName(this, "Select Sprite", "", "Images (*.png);;")};
    if (!selectedFileName.isEmpty())
    {
        _currentSprite = QPixmap{selectedFileName};
        _originalSpriteSize = _currentSprite.size();
        _scaleFactor = kDefaultScaleFactor;
        _ui->spinnerScale->setValue(_scaleFactor);

        drawCurrentSprite();
    }
}

void MainWindow::on_spinnerScale_valueChanged(int i)
{
    _scaleFactor = static_cast<uint32_t>(i);
    drawCurrentSprite();
}

//void MainWindow::mousePressEvent(QMouseEvent* event)
//{
//}
