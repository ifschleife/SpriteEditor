#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "spritearea.h"

#include <QFileDialog>
#include <QSpinBox>


namespace
{
    constexpr auto kDefaultScaleFactor  = uint32_t{14};

    // template for overloaded function selection, courtesy of
    // http://stackoverflow.com/a/16795664/578536
    template<typename... Args> struct SELECT
    {
        template<typename C, typename R>
        static constexpr auto OVERLOAD_OF( R (C::*pmf)(Args...) ) -> decltype(pmf)
        {
            return pmf;
        }
    };
}


MainWindow::MainWindow(QWidget* parent /*=0*/)
    : QMainWindow{parent}
    , _ui{std::make_unique<Ui::MainWindow>()}
{
    _ui->setupUi(this);

    _ui->spinnerScale->setValue(kDefaultScaleFactor);

    connect(_ui->spinnerScale, SELECT<int>::OVERLOAD_OF(&QSpinBox::valueChanged),
            _ui->labelSpriteArea, &SpriteArea::scaleAndDrawSprite);
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

