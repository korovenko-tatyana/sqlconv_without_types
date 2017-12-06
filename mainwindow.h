#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "tabledata.h"
#include <QString>
#include <bddata.h>
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
int napr=0;
bool set_label=0;
//TableData table1;
QString file_name_load; ///путь к файлу импорта
QString file_name_out; ///путь к файлу экспорта
BDData table;
QStandardItemModel *model;
QStandardItem *item;
QString table_name_from; ///имя таблицы для базы

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
int get_napr();
//QString get_file_name();


private slots:

/**
 * @brief choose_napr1 если нажата первая радио кнопка
 * @param checked
 */
void choose_napr1(bool checked);
void choose_napr2(bool);
/**
 * @brief choose_file_click нажатие на выбор файла экспорта
 */
void choose_file_click();
/**
 * @brief go_click начать
 */
void go_click();
/**
 * @brief path_click нажатие на выбор файла для сохранения
 */
void path_click();

//void download_click();
/**
 * @brief set_table_name_in слот для принятия сигнала об вводе/изменении имна таблицы
 */
void set_table_name_in();

};

#endif // MAINWINDOW_H
