#ifndef DIALOGLOSE_H
#define DIALOGLOSE_H

#include <QDialog>

namespace Ui {
class DialogLose;
}

class DialogLose : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLose(QWidget *parent = nullptr);
    ~DialogLose();

private slots:

    void on_pushButtonExit_clicked();

private:
    Ui::DialogLose *ui;
};

#endif // DIALOGLOSE_H
