#ifndef PHOTOEDIT_H
#define PHOTOEDIT_H

#include <QDialog>
#include <QImageReader>

namespace Ui {
class Photoedit;
}

class Photoedit : public QDialog
{
    Q_OBJECT

public:
    explicit Photoedit(QWidget *parent = nullptr);
    Photoedit(QWidget *parent, const QString &image);
    ~Photoedit();

public slots:
    void Save();
    void cut();
    void backImage();

protected:
    void paintEvent(QPaintEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

private:
    Ui::Photoedit *ui;

    QPainter *mPainter;
    QImageReader *mImg;
    QImage *mImage;
    QImage *mCutImage;
    QImage *mImagePrev;
    QPoint mBegin;
    QPoint mEnd;
    QPoint offset;
    QPen *pen;
    QString *pathImage;
    bool mEnabled;

    void cleanWindow();

    void checkEndPoint(QPoint &end);
    void checkOffset(QPoint &point);
    void refreshOffset();
};
#endif // PHOTOEDIT_H
