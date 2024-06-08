#ifndef DIALOGWIN_H
#define DIALOGWIN_H

#include <QDialog>

namespace Ui {
class DialogWin;
}

class DialogWin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWin(QWidget *parent = nullptr);
    ~DialogWin();

private slots:

    void on_pushButton_clicked();

private:
    Ui::DialogWin *ui;
};

#endif // DIALOGWIN_H
