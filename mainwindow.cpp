#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_new.h"
#include "Vag.h"
#include <QFile>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QStatusBar>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText(QString("Поиск"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

Cont <Vag> v;

bool saved = true;

bool c = false;

QString File = "";

int String_To_Int(QString s)
{
    int a;
    bool ok;
    a = s.toInt(&ok, 10);
    return a;
}

void MainWindow::on_action_triggered()
{
    if (ui->tableWidget->rowCount() < 1)
    {
        QMessageBox::about(this, "Информация", "Таблица пуста     ");
        return;
    }
    QMessageBox Mes;
    Mes.setWindowTitle("Очистка");
    Mes.setText("Вы уверены, что хотите очистить таблицу? Все несохраненные данные будут утеряны");
    Mes.setIcon(QMessageBox::Question);
    Mes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (Mes.exec() == QMessageBox::Yes)
    {
        ui->tableWidget->setRowCount(0);
        v.Delete();
        statusBar()->showMessage(tr("Таблица очищена"));
    }
    else
    {
        return;
    }
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox Mes;
    Mes.setWindowTitle("Выход");
    Mes.setText("Вы уверены, что хотите выйти? Все несохраненные данные будут утеряны");
    Mes.setIcon(QMessageBox::Question);
    Mes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (Mes.exec() == QMessageBox::Yes)
    {
        QCoreApplication::quit();
    }
    else
    {
        return;
    }
}

void MainWindow::on_action_3_triggered()
{
    QMessageBox Mes;
    Mes.setWindowTitle("Создание новой базы данных");
    Mes.setText("Вы уверены, что хотите создать новую таблицу? Все несохраненные данные будут утеряны");
    Mes.setIcon(QMessageBox::Question);
    Mes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (Mes.exec() == QMessageBox::Yes)
    {
        ui->tableWidget->setRowCount(0);
        v.Delete();
        statusBar()->showMessage(tr("Новая таблица"));
        saved = true;
    }
    else
    {
        return;
    }
}

void MainWindow::on_action_4_triggered()
{
    QMessageBox Mes;
    Mes.setWindowTitle("Открыть файл");
    Mes.setText("Вы уверены, что хотите открыть файл? Все несохраненные данные будут утеряны");
    Mes.setIcon(QMessageBox::Question);
    Mes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (Mes.exec() == QMessageBox::Yes)
    {
        auto filename = QFileDialog::getOpenFileName(this, "Открыть", QDir::rootPath(), "CSV file (*.csv)");
        QFile file(filename);
        File = filename;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }
        QTextStream in(&file);
        int x = 0;
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        while(!in.atEnd())
        {
            auto line = in.readLine();
            auto val = line.split(";");
            Vag v1;
            v1.a = String_To_Int(val[0]);
            v1.b = String_To_Int(val[1]);
            v1.c = val[2];
            v1.d = val[3];
            v1.e = val[4];
            v.Push_Back(v1);
            for (int i = 0; i < 5; i++)
            {
                ui->tableWidget->setItem(x, i, new QTableWidgetItem(QString(val.at(i))));
            }
            if (!in.atEnd())
            ui->tableWidget->insertRow(x + 1);
            x++;
        }
        file.flush();
        file.close();
        saved = false;
        statusBar()->showMessage(tr("Файл открыт"));
    }
    else
    {
        return;
    }
}

void MainWindow::on_action_5_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this, "Сохранить", QDir::rootPath(), "CSV File (*.csv)");
    QFile file(filename);
    File = filename;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream out(&file);
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            out << ui->tableWidget->item(i, j)->text() << ";";
        }
        out << "\n";
    }
    file.flush();
    file.close();
    saved = false;
    statusBar()->showMessage(tr("Таблица сохранена"));
}

void MainWindow::on_action_6_triggered()
{
    QMessageBox Mes;
    Mes.setWindowTitle("Объединение");
    Mes.setText("Вы уверены, что хотите объединить таблицы? Все несохраненные данные будут утеряны");
    Mes.setIcon(QMessageBox::Question);
    Mes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (Mes.exec() == QMessageBox::Yes)
    {
        auto filename = QFileDialog::getOpenFileName(this, "Открыть", QDir::rootPath(), "CSV file (*.csv)");
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }
        QTextStream in(&file);
        if (ui->tableWidget->rowCount() < 1)
        {
            int x = 0;
            ui->tableWidget->setColumnCount(5);
            ui->tableWidget->setRowCount(1);
            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            while(!in.atEnd())
            {
                auto line = in.readLine();
                auto val = line.split(";");
                Vag v1;
                v1.a = String_To_Int(val[0]);
                v1.b = String_To_Int(val[1]);
                v1.c = val[2];
                v1.d = val[3];
                v1.e = val[4];
                v.Push_Back(v1);
                for (int i = 0; i < 5; i++)
                {
                    ui->tableWidget->setItem(x, i, new QTableWidgetItem(QString(val.at(i))));
                }
                if (!in.atEnd())
                ui->tableWidget->insertRow(x + 1);
                x++;
            }
        }
        else
        {
            int x = ui->tableWidget->rowCount() + 1;
            while(!in.atEnd())
            {
                auto line = in.readLine();
                auto val = line.split(";");
                Vag v1;
                v1.a = String_To_Int(val[0]);
                v1.b = String_To_Int(val[1]);
                v1.c = val[2];
                v1.d = val[3];
                v1.e = val[4];
                v.Push_Back(v1);
                ui->tableWidget->insertRow(x - 1);
                for (int i = 0; i < 5; i++)
                {
                    ui->tableWidget->setItem(x - 1, i, new QTableWidgetItem(QString(val.at(i))));
                }
                x++;
            }
        }
        file.flush();
        file.close();
        statusBar()->showMessage(tr("Таблицы объединены"));
    }
    else
    {
        return;
    }
}

void MainWindow::on_action_7_triggered()
{
    auto a = ui->tableWidget->selectedItems();
    if (a.size() < 5 && ui->tableWidget->rowCount() > 0 || c)
    {
        c = false;
        QMessageBox::about(this, "Информация", "Выберите запись для удаления     ");
        return;
    }
    if (ui->tableWidget->rowCount() < 1)
    {
        QMessageBox::about(this, "Информация", "Таблица пуста     ");
        return;
    }
    QMessageBox Mes;
    Mes.setWindowTitle("Удаление записи");
    Mes.setText("Вы уверены, что хотите удалить запись?");
    Mes.setIcon(QMessageBox::Question);
    Mes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (Mes.exec() == QMessageBox::Yes)
    {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        v.Del_Num(ui->tableWidget->currentRow() + 1);
        statusBar()->showMessage(tr("Строка удалена"));
    }
    else
    {
        return;
    }
}

void MainWindow::on_action_8_triggered()
{
    Add_New wind;
    wind.setModal(true);
    wind.exec();
    int c = wind.chng;
    if (c > 0)
    {
        Vag vag(wind.Get());
        if (ui->tableWidget->rowCount() < 1)
        {

            v.Push_Back(vag);
            ui->tableWidget->setColumnCount(5);
            ui->tableWidget->setRowCount(1);
            ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1 , 0, new QTableWidgetItem(QString::number(vag.a)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(vag.b)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString(vag.c)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(QString(vag.d)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(QString(vag.e)));

        }
        else
        {
            v.Push_Back(vag);
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1 , 0, new QTableWidgetItem(QString::number(vag.a)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(vag.b)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString(vag.c)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(QString(vag.d)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(QString(vag.e)));
        }
        statusBar()->showMessage(tr("Запись добавлена"));
    }
}

void MainWindow::on_action_9_triggered()
{
    Add_New wind;
    wind.setModal(true);
    auto a = ui->tableWidget->selectedItems();
    if (a.size() < 5 && ui->tableWidget->rowCount() > 0 || c)
    {
        c = false;
        ui->tableWidget->clearSelection();
        QMessageBox::about(this, "Информация", "Выберите запись для редактирования");
        return;
    }
    if (ui->tableWidget->rowCount() > 0)
    {
        wind.SetA(a.at(0)->text());
        wind.SetB(a.at(1)->text());
        wind.SetC(a.at(2)->text());
        wind.SetD(a.at(3)->text());
        wind.SetE(a.at(4)->text());
        wind.exec();
    }
    else
    {
        QMessageBox::about(this, "Информация", "Нет записей          ");
        return;
    }
    int c = wind.chng;
    if (c > 0)
    {
        Vag vag(wind.Get());
        v.Change(vag, ui->tableWidget->currentRow());
        ui->tableWidget->setItem(ui->tableWidget->currentRow(), 0, new QTableWidgetItem(QString::number(vag.a)));
        ui->tableWidget->setItem(ui->tableWidget->currentRow(), 1, new QTableWidgetItem(QString::number(vag.b)));
        ui->tableWidget->setItem(ui->tableWidget->currentRow(), 2, new QTableWidgetItem(QString(vag.c)));
        ui->tableWidget->setItem(ui->tableWidget->currentRow(), 3, new QTableWidgetItem(QString(vag.d)));
        ui->tableWidget->setItem(ui->tableWidget->currentRow(), 4, new QTableWidgetItem(QString(vag.e)));
        statusBar()->showMessage(tr("Строка отредактирована"));
    }
}

void MainWindow::on_action_10_triggered()
{
    if (!saved)
    {
        QFile file(File);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }
        QTextStream out(&file);
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            for (int j = 0; j < 5; j++)
            {
                out << ui->tableWidget->item(i, j)->text() << ";";
            }
            out << "\n";
        }
        file.flush();
        file.close();
        saved = false;
        statusBar()->showMessage(tr("Таблица сохранена"));
    }
    else
    {
        MainWindow::on_action_5_triggered();
    }
}

void MainWindow::on_action_11_triggered()
{
    QMessageBox::about(this, "О программе", "Курсовая работа, Иванов А.С. ПИБ-11з, Вариант №8");
}

void MainWindow::on_action_12_triggered()
{
    QMessageBox::aboutQt(this, "О программе");
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        ui->tableWidget->clearSelection();
        return;
    }
    ui->tableWidget->clearSelection();
    if (!ui->lineEdit->text().isEmpty())
    {
        ui->tableWidget->clearSelection();
        auto find = ui->tableWidget->findItems(arg1, Qt::MatchContains);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        c = true;
        for (int i = 0; i < find.size(); i++)
        {
            ui->tableWidget->setCurrentItem(find.at(i), QItemSelectionModel::Select);
        }
    }
}

void MainWindow::on_tableWidget_cellDoubleClicked()
{
    MainWindow::on_action_9_triggered();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox Mes;
    Mes.setWindowTitle("Выход");
    Mes.setText("Вы уверены, что хотите выйти? Все несохраненные данные будут утеряны");
    Mes.setIcon(QMessageBox::Question);
    Mes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (Mes.exec() == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
