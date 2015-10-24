#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QLabel>
#include <QPixmap>


namespace
{
    constexpr auto kDefaultScaleFactor = uint32_t{8};
    constexpr auto kMaximumScaleFactor = uint32_t{20};
    constexpr auto kDefaultSpriteSize  = QSize{64, 64};
    const auto kDefaultSpriteColor     = QColor{255, 255, 255, 255};
}


MainWindow::MainWindow(QWidget* parent /*=0*/)
    : QMainWindow{parent}
    , _ui{std::make_unique<Ui::MainWindow>()}
    , _sprite{kDefaultSpriteSize, QImage::Format_ARGB32_Premultiplied}
{
    _ui->setupUi(this);
    _ui->spinnerScale->setValue(kDefaultScaleFactor);

    _sprite.fill(kDefaultSpriteColor);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actionOpenSprite_triggered()
{
    const auto selectedFileName = QString{QFileDialog::getOpenFileName(this, "Select Sprite", "", "Images (*.png);;")};
    if (!selectedFileName.isEmpty())
    {
        _sprite.load(selectedFileName);

        const auto width  = int{_sprite.width()};
        const auto height = int{_sprite.height()};

        _ui->tableSprite->setColumnCount(width);
        _ui->tableSprite->setRowCount(height);
        _ui->tableSprite->horizontalHeader()->setDefaultSectionSize(kDefaultScaleFactor);
        _ui->tableSprite->verticalHeader()->setDefaultSectionSize(kDefaultScaleFactor);

        auto brush = QBrush{Qt::SolidPattern};

        for (int x=0; x < width; ++x)
        {
            for (int y=0; y < height; ++y)
            {
                const auto pixelColor = QRgb{_sprite.pixel(x, y)};
                brush.setColor(pixelColor);

                auto widget = new QTableWidgetItem;
                widget->setBackground(brush);
                _ui->tableSprite->setItem(y, x, widget);
            }
        }

        _ui->spinnerScale->setValue(kDefaultScaleFactor);
    }
}

void MainWindow::on_spinnerScale_valueChanged(int scale)
{
    _ui->tableSprite->horizontalHeader()->setDefaultSectionSize(scale);
    _ui->tableSprite->verticalHeader()->setDefaultSectionSize(scale);

    const auto spriteWidth  = int{_sprite.width()};
    const auto spriteHeight = int{_sprite.height()};
    constexpr auto framePadding = int{2};

    const auto tableWidth  = int{spriteWidth*scale + framePadding};
    const auto tableHeight = int{spriteHeight*scale + framePadding};

    _ui->tableSprite->setMinimumSize(tableWidth, tableHeight);
}

