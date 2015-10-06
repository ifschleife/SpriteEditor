#include "spritearea.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>


namespace
{
    constexpr auto kDefaultScaleFactor  = uint32_t{8};
    constexpr auto kDefaultSpriteSize   = QSize{64, 64};
    constexpr auto kMinimumScaleForGrid = uint32_t{4};
    const     auto kDefaultSpriteColor  = QColor{255, 255, 255, 255};

    QPixmap scaleSprite(const QPixmap& sprite, uint32_t scaleFactor)
    {
        const auto newSize = QSize{scaleFactor * sprite.size()};
        return sprite.scaled(newSize, Qt::KeepAspectRatio, Qt::FastTransformation); // don't user bilinear filtering
    }

    void drawGridOnSprite(QPixmap& sprite, uint32_t pixelScale)
    {
        const int width  = sprite.width();
        const int height = sprite.height();

        QPainter painter(&sprite);
        painter.setPen(QColor(0, 0, 0, 255));

        painter.drawRect(0, 0, width-1, height-1);

        for (int x=0; x < width; x+=pixelScale)
        {
            painter.drawLine(x, 0, x, height);
        }
        for (int y=0; y < width; y+=pixelScale)
        {
            painter.drawLine(0, y, width, y);
        }
    }
}


SpriteArea::SpriteArea(QWidget* parent)
    : QLabel(parent)
    , _scaleFactor(kDefaultScaleFactor)
{
    loadNewSprite(kDefaultSpriteSize, kDefaultSpriteColor);
}

SpriteArea::~SpriteArea()
{

}

void SpriteArea::loadNewSprite(const QSize& size, const QColor& fillColor)
{
    _sprite = QPixmap{size};
    _sprite.fill(fillColor);
    scaleAndDrawSprite(kDefaultScaleFactor);
}

void SpriteArea::loadNewSprite(const QString& absPathToSprite)
{
    _sprite = QPixmap{absPathToSprite};
    scaleAndDrawSprite(kDefaultScaleFactor);
}

void SpriteArea::scaleAndDrawSprite(uint32_t scaleFactor)
{
    auto scaledSprite = scaleSprite(_sprite, scaleFactor);
    if (scaleFactor >= kMinimumScaleForGrid)
    {
        drawGridOnSprite(scaledSprite, scaleFactor);
    }
    setPixmap(scaledSprite);

    _scaleFactor = scaleFactor;
}


void SpriteArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->type() == QEvent::MouseButtonRelease && event->button() == Qt::MouseButton::LeftButton)
    {
        const QPoint cursorPosition = event->pos();
        translateCursorPositionToSpritePixel(cursorPosition);

        event->accept();
    }
    else
    {
        event->ignore();
    }
}

uint32_t SpriteArea::translateCursorPositionToSpritePixel(const QPoint& cursorPosition)
{
    qDebug() << cursorPosition.x() << ", " << cursorPosition.y();

    auto x = int{std::div(cursorPosition.x(), _scaleFactor).quot};
    auto y = int{std::div(cursorPosition.y(), _scaleFactor).quot};

//    const QPoint scaledPixelTopLeft(x*_scaleFactor, y*_scaleFactor);
//    const QPoint scaledPixelBottomRight(scaledPixelTopLeft.x() + _scaleFactor, scaledPixelTopLeft.y() + _scaleFactor);
//    const QRect(scaledPixelTopLeft, scaledPixelBottomRight);

    QImage spriteImage = _sprite.toImage();
    spriteImage.setPixel(x, y, qRgba(255,0,0,255));

    _sprite.convertFromImage(spriteImage);

    scaleAndDrawSprite(_scaleFactor);

    return 0;
}

