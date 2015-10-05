#pragma once

#include <QLabel>
#include <QPixmap>


class SpriteArea : public QLabel
{
    Q_OBJECT

public:
    explicit SpriteArea(QWidget* parent);
    ~SpriteArea() final;

    void loadNewSprite(const QSize& size, const QColor& fillColor);
    void loadNewSprite(const QString& absPathToSprite);

    void scaleAndDrawSprite(uint32_t scaleFactor);

private:
    QPixmap _sprite;
};
