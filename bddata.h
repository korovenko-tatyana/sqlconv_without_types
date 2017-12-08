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
    QChar _separator=';'; ///разделить столбцов в файле
    int cols=0,rows=0;

public:

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
    /**
     * @brief CSVRead Чтение из файла формата  csv
     * @param _file путь к файлу
     */
    void CSVRead(QString _file);
    /**
 * @brief load_from_sql1 Загрузка даных из базы
 * @param filename путь к файлу
 * @param name_of_table имя таблицы
 */
    void load_from_sql1(QString filename, QString name_of_table);
    /**
 * @brief output_in_sql1 Вызрузка данных в базу
 * @param filename путь к файлу
 * @param name_of_table имя таблицы
 */
    void output_in_sql1(QString filename, QString name_of_table);
};

#endif // BDDATA_H
