#include "bddata.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDialog>
#include <QTextStream>
#include <QDebug>
#include <QtSql>
#include <QSqlRecord>
#include <QFile>

/*BDData::BDData()
{

}*/
BDData::BDData(QObject *parent): QAbstractTableModel(parent)
{

}
QVariant BDData::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (!index.isValid())
            return QVariant();

        return data1.at(index.row()).at(index.column());
    }

    return QVariant();

}

int BDData::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return rows;
}

int BDData::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    if (rows == 0)
        return 0;
    return cols;
}

QVariant BDData::headerData(int section, Qt::Orientation orientation, int role) const
{ if (role == Qt::DisplayRole)
    { if (orientation == Qt::Horizontal)
        { return column_name[section];
        } }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QString trimCSV(QString item){
    if((!item.isEmpty())&&(item[0] == QChar(34)))
        item.remove(0,1);
    if((!item.isEmpty())&&(!item.isNull())&(item[item.count()-1] == QChar(34)))
        item.remove(item.count()-1,1);
    if(!item.isEmpty())
        item = item.replace("\"\"","\"");
    return item;

}

void BDData::CSVRead(QString _file)
{
    emit beginResetModel();
    if(cols!=0){
        cols=0;rows=0; data1.clear();column_name.clear();type_data.clear();
    }
    QFile file(_file);
    if (!file.open(QIODevice::ReadOnly))
    {
        //  QMessageBox::critical(,tr("Error"),tr("Could not open file"));
        qDebug()<<"error from open file"<<endl;;
        return;
    }

    QTextStream in(&file);
    bool Quote = false;
    QList<QString> ItemList;
    QString item = "";

    QString line(in.readLine().simplified());
    int count = line.count();
    for (int i = 0;i<count;i++){
        if (line[i] == QChar(34)){
            Quote = (Quote) ? false : true;
        }
        if ((Quote != true)&(line[i] == _separator)){
            column_name.append(trimCSV(item));
            cols++;
            item = "";
        }else{
            item += line[i];
        }
        if ((count-1 == i)&(Quote != true)){
            item = trimCSV(item);
            if (item != ""){
                column_name.append(item);
                cols++;}
            item = "";
        }
    }
    qDebug()<<column_name;
    {
        while(!in.atEnd()){
            QString line(in.readLine().simplified());
            int count = line.count();
            rows++;
            //  qDebug()<<rows;
            for (int i = 0;i<count;i++){
                if (line[i] == QChar(34)){
                    Quote = (Quote) ? false : true;
                }
                if ((Quote != true)&(line[i] == _separator)){
                    ItemList.append(trimCSV(item));
                    item = "";
                }else{
                    item += line[i];
                }

                if ((count-1 == i)&(Quote != true)){
                    item = trimCSV(item);
                    if (item != "")
                        ItemList.append(item);
                    //   _lines_list.append(ItemList);
                    data1.append(ItemList);
                    qDebug()<<ItemList;
                    ItemList.clear();
                    item = "";
                }
            }

        }
    }
    file.close();
    emit endResetModel();
}

QString get_elem(QString elem){
    elem.replace("\"","\"\"");
    if (elem.contains('"'))
        return "\""+elem+"\"";
    if (elem.contains(';'))
        return "\""+elem+"\"";
    if(elem.contains('/'))
        return "\""+elem+"\"";
    if(elem.contains("<<"))
        return "\""+elem+"\"";
    if(elem.contains("\n"))
        return "\""+elem+"\"";
    if(elem.contains(", "))
        return "\""+elem+"\"";
    return elem;
}

void BDData::output_in_csv(QString filename){
    if(cols==0){qDebug()<<"No data in prog";}
    //  opred_data_type();
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream text_stream(&file);
        QStringList str;
        for(int k=0;k<cols;k++){
            str<<get_elem(column_name[k]);
        }
        text_stream<<str.join(';')+"\n";
        for (int i=0;i<rows;i++)
        {
            str.clear();
            for (int j =0;j<cols;j++){
                str<<get_elem(data1[i][j]);//temp[j];
            }
            text_stream<<str.join(';')+"\n";
        }

        file.close();
    }
    else qDebug()<<"error open file to write";
}

void BDData::opred_data_type() //INTEGER -> REAL -> TEXT
{
    QList <QString>temp,d;bool qw[cols];
    for (int i=0;i<cols;i++){
        temp.append("TEXT");
        type_data.append("INTEGER");
        qw[i]=false;
    }
    /* for (int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
        {
            d.clear();
            d=data1[i];
            bool flag;
            d[j].toInt(&flag);
            if(flag) temp[j]="INTEGER";
            else {
                d[j].toDouble(&flag);
                if(flag) {temp[j]="REAL";qw[j]=true;}
                else {temp[j]="TEXT"; type_data[j]="TEXT";}
            }
            for(int i=0;i<cols;i++)
            {
                if(qw[i] &&(type_data[i]!="TEXT")) type_data[i]="REAL";
                // else if(type_data[i]!="TEXT") type_data[i]="INTEGER";
            }
        }*/
    for (int j=0;j<cols;j++)
        for (int i=0;i<rows;i++)
        {
            bool flag;
            data1[i][j].toInt(&flag);
            if(flag) temp[j]="INTEGER";
            else
            {
                data1[i][j].toDouble(&flag);
                if(flag) {temp[j]="REAL";qw[j]=true;}
                else {temp[j]="TEXT"; type_data[j]="TEXT";break;}
            }
        }
    for(int i=0;i<cols;i++)
    {
        if(qw[i] &&(type_data[i]!="TEXT")) type_data[i]="REAL";
        // else if(type_data[i]!="TEXT") type_data[i]="INTEGER";
    }
    //qDebug()<<temp;
    qDebug()<<type_data;
}

void BDData::load_from_sql1(QString filename, QString name_of_table)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if( !db.open() ) {
        qDebug() <<  "Cannot open database:" << db.lastError().text();
        return;
    }
    QSqlRecord rec = db.record(name_of_table);
    if (rec.isEmpty())
    {
        qDebug() << "Cannot found table" + name_of_table;
        return;
    }
    if (cols != 0){
       cols=0;
       rows=0;
       data1.clear();
       column_name.clear();
       type_data.clear();
     }

    beginInsertColumns(QModelIndex(), 0, rec.count()-1);
    for(int j = 0; j < rec.count(); j++)
    column_name.append(rec.fieldName(j));
    endInsertColumns();
    cols = rec.count();

    QList<QString> temp;
    QSqlQuery countRows;
    countRows.exec("SELECT count(*) FROM " + name_of_table);
    countRows.last();
    qDebug() << countRows.value(countRows.at()).toString();
    rows = countRows.value(countRows.at()).toInt();
    //cout << rows;
    QSqlQuery query("SELECT * FROM " + name_of_table);

    emit beginInsertRows(QModelIndex(), 0, rows-1);
    while (query.next())
    {
        for (int j = 0; j < cols; j++)
              temp.append(query.value(j).toString());
              data1.append(temp);
              temp.clear();
     }
     emit endInsertRows();

     db.close();
     return ;
}

void BDData::output_in_sql1(QString filename, QString name_of_table)
{
    opred_data_type();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if (!db.open())
    {
        qDebug() << "Cannot open database:" + db.lastError().text();
        return;
    }
    QSqlRecord columns = db.record(name_of_table);

    if (!columns.isEmpty()) { //create table if not it
        QSqlQuery query2;
        if(!query2.exec( "DROP TABLE '" +name_of_table+"'") )
        { //error of create
            qDebug() << "DataBase: error of delete table" ;
            qDebug() << query2.lastError().text();
            return;
        }
    }
    //PRIMARY KEY NOT NULL
    QSqlQuery queru;
    QString str;
    str = "CREATE TABLE "+ name_of_table + "( ";
    str += "\'" + column_name[0] + "\' " + type_data[0] +" , ";
    for (int j = 1; j < cols-1; j++)
        str += "\'" + column_name[j] + "\' " + type_data[j]+", ";
    str += "\'" + column_name[cols-1] + "\' " + type_data[cols-1] +" );";
    qDebug() << str;
    if (!queru.exec(str)) {
        qDebug() << "Unable to create a table";
    }

    QSqlQuery query;
    QString strt;
    for (int i = 0; i < rows; i++)
    {
    db.transaction();
    strt = "INSERT INTO " + name_of_table+" (";
    for (int j = 0; j < cols-1; j++)
        strt += "\'" + column_name[j] + "\'" + ", ";
    strt += "\'" + column_name[cols-1] + "\'" + ")" + " VALUES (";

    if(type_data[0]=="TEXT")
        strt += "'" + data1[i][0] + "'" + ", ";
    else
        strt += data1[i][0] + ", ";
    //strt += "'" + data1[i][0] + "'" + ", ";
    for (int j = 1; j < cols-1; j++){
        if(type_data[j]=="TEXT")
        //if (data1[i][j] != "")
            strt += "'" + data1[i][j] + "'" + ", ";
        else
            strt = strt  + data1[i][j]  + ", ";
    }
        //qDebug() << data1[i][j] <<" , ";}
    if(type_data[cols-1]=="TEXT")
        strt += "'" + data1[i][cols-1]+ "'" + ");";
    else
        strt +=data1[i][cols-1] + ");";
    qDebug() << strt;
    if (!query.exec(strt)) {
        qDebug() << "Unable to do insert operation";
    }
    db.commit();
    }

    db.close();
}


