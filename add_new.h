#ifndef ADD_NEW_H
#define ADD_NEW_H

#include <QDialog>
#include "Vag.h"

namespace Ui {
class Add_New;
}

class Add_New : public QDialog
{
    Q_OBJECT

public:
    explicit Add_New(QWidget *parent = nullptr);
    int chng = 0;
    int CHNG();
    Vag Get();
    ~Add_New();
    void SetA(const QString &s);
    void SetB(const QString &s);
    void SetC(const QString &s);
    void SetD(const QString &s);
    void SetE(const QString &s);

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_5_textChanged();

    void on_lineEdit_4_textChanged();

    void on_lineEdit_3_textChanged();

    void on_lineEdit_2_textChanged();

    void on_lineEdit_textChanged();

private:
    Ui::Add_New *ui;
};

#endif // ADD_NEW_H
