#ifndef BDDATA_H
#define BDDATA_H

#include <QObject>
#include <QList>
#include <QAbstractTableModel>

#include <QtSql>
#include <QSqlRecord>
#include <QFile>
#include<QString>

/**
 * @brief The BDData class
 */
class BDData :public QAbstractTableModel// public QAbctractTableModel {

{
    Q_OBJECT
public:
//    BDData();
BDData(QObject *parent = nullptr);
virtual int rowCount(const QModelIndex &parent) const override;
   virtual int columnCount(const QModelIndex &parent) const override;
 virtual QVariant data(const QModelIndex &index, int role) const override;

public slots:


private:
  QList<QString> column_name; ///имена столбцов таблицы
  QList<QString> type_data; ///типы данных каждого столбца
QList<QList<QString>> data1; ///данные таблицы
//QString file_name;
//QString table_name;
int cols=0,rows=0;

public:
/**
 * @brief load_from_csv загрузчик из файла формата csv
 * @param filename путь к загружаемому файлу
 */
void load_from_csv(QString filename);//имена столбцов из первой строчки
/**
 * @brief output_in_csv выгрузка данных в файл формата csv
 * @param filename путь к сохраняемому файлу
 */
void output_in_csv(QString filename); //заголовки это будет имя таблицы
virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override; //установить имена столбцов в отображении таблицы
/**
 * @brief opred_data_type алгоритм определения типов столбцов таблицы
 */
void opred_data_type();
QList<QString> get_column_name();
QList<QList<QString>> get_data();
int get_row();
int get_col();
void CSVRead(QString _file);
bool writeFromModelToCsv();
/**
 * @brief load_from_sql
 * @param filename путь к файлу
 * @param table_name имя таблицы
 */
void load_from_sql(QString filename, QString table_name);
/**
 * @brief out_to_sql
 * @param filename путь к файлу
 * @param table_name имя таблицы
 */
void out_to_sql(QString filename, QString table_name);
int comparator(QSqlDatabase sd,QString table_name);

void create_table(QString table_name);
/**
 * @brief load_from_sql1
 * @param filename
 * @param name_of_table
 */
void load_from_sql1(QString filename, QString name_of_table);
/**
 * @brief output_in_sql1
 * @param filename
 * @param name_of_table
 */
void output_in_sql1(QString filename, QString name_of_table);


void output_in_sql2(QString filename, QString name_of_table);
void load_from_sql2(QString filename, QString name_of_table);
};

#endif // BDDATA_H
