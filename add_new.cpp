#include "add_new.h"
#include "ui_add_new.h"
#include <QMessageBox>
#include <QIntValidator>

Add_New::Add_New(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_New)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0, 10000000000, this));
    ui->lineEdit_2->setValidator(new QIntValidator(0, 10000000000, this));
}

Add_New::~Add_New()
{
    delete ui;
}

Vag Add_New::Get()
{
    Vag vag(ui->lineEdit->text().toInt(), ui->lineEdit_2->text().toInt(), ui->lineEdit_3->text(), ui->lineEdit_4->text(), ui->lineEdit_5->text());
    return vag;
}

int Add_New::CHNG()
{
    return chng;
}

void Add_New::on_pushButton_2_clicked()
{
    ui->label->setStyleSheet("color : rgb(0, 0, 0)");
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty() || ui->lineEdit_5->text().isEmpty())
    {
        QMessageBox::about(this, "Информация", "Все поля должы быть заполнены");
        if (ui->lineEdit->text().isEmpty())
        {
            ui->label_5->setStyleSheet("color : rgb(205, 92, 92)");
        }
        if (ui->lineEdit_2->text().isEmpty())
        {
            ui->label_4->setStyleSheet("color : rgb(205, 92, 92)");
        }
        if (ui->lineEdit_3->text().isEmpty())
        {
           ui->label_3->setStyleSheet("color : rgb(205, 92, 92)");
        }
        if (ui->lineEdit_4->text().isEmpty())
        {
           ui->label_2->setStyleSheet("color : rgb(205, 92, 92)");
        }
        if (ui->lineEdit_5->text().isEmpty())
        {
            ui->label->setStyleSheet("color : rgb(205, 92, 92)");
        }
        return;
    }
    else
    {
        chng = 1;
        this->close();
    }
}

void Add_New::on_pushButton_clicked()
{
    chng = -1;
    this->close();
}

void Add_New::SetA(const QString &s)
{
    ui->lineEdit->setText(s);
}

void Add_New::SetB(const QString &s)
{
    ui->lineEdit_2->setText(s);
}

void Add_New::SetC(const QString &s)
{
    ui->lineEdit_3->setText(s);
}

void Add_New::SetD(const QString &s)
{
    ui->lineEdit_4->setText(s);
}

void Add_New::SetE(const QString &s)
{
    ui->lineEdit_5->setText(s);
}

void Add_New::on_lineEdit_5_textChanged()
{
    ui->label->setStyleSheet("color : rgb(0, 0, 0)");
}

void Add_New::on_lineEdit_4_textChanged()
{
    ui->label_2->setStyleSheet("color : rgb(0, 0, 0)");
}

void Add_New::on_lineEdit_3_textChanged()
{
    ui->label_3->setStyleSheet("color : rgb(0, 0, 0)");
}

void Add_New::on_lineEdit_2_textChanged()
{
    ui->label_4->setStyleSheet("color : rgb(0, 0, 0)");
}

void Add_New::on_lineEdit_textChanged()
{
    ui->label_5->setStyleSheet("color : rgb(0, 0, 0)");
}

