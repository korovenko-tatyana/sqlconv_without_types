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
    QString file_name_load; ///путь к файлу импорта
    QString file_name_out; ///путь к файлу экспорта
    BDData table;
    QString table_name_from; ///имя таблицы для базы

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    /**
 * @brief choose_napr1 выполняется, если нажата первая радио кнопка (из csv)
 * @param checked
 */
    void choose_napr1(bool checked);
    /**
 * @brief choose_napr2 выполняется, если нажата вторая радио кнопка (из базы)
 */
    void choose_napr2(bool);
    /**
 * @brief choose_file_click нажатие на выбор файла экспорта
 */
    void choose_file_click();
    /**
 * @brief go_click начать преобразование
 */
    void go_click();
    /**
 * @brief path_click нажатие на выбор файла для сохранения
 */
    void path_click();

    /**
 * @brief set_table_name_in слот для принятия сигнала об вводе/изменении имени таблицы
 */
    void set_table_name_in();

};

#endif // MAINWINDOW_H
