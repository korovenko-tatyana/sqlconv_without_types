#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->go->setEnabled(false);
    //ui->download->setEnabled(false);

    connect (ui->csv_sql, SIGNAL(clicked(bool)), this, SLOT(choose_napr1(bool)));
    connect (ui->sql_csv, SIGNAL(clicked(bool)), this, SLOT(choose_napr2(bool)));
    connect (ui->choose_file, SIGNAL(clicked(bool)), this, SLOT(choose_file_click()));
    connect (ui->go, SIGNAL(clicked(bool)), this, SLOT(go_click()));
    connect (ui->path, SIGNAL(clicked(bool)), this, SLOT(path_click()));
    //connect (ui->download, SIGNAL(clicked(bool)), this, SLOT(download_click()));
    connect(ui->table_name, SIGNAL(editingFinished()),this,SLOT(set_table_name_in()));
    ui->tableView->setModel(&table);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::choose_napr1(bool checked){
    if (checked)
    {
        napr=1;
        //  ui->groupBox_4->show();
        // ui->label->hide();
        ui->label->setEnabled(false);
        // ui->table_name->hide();
        ui->table_name->setEnabled(false);
        // ui->label_2->show();
        // ui->table_name_out->show();
        ui->label_2->setEnabled(true);
        ui->table_name_out->setEnabled(true);
         ui->choose_file->setEnabled(true);
        table_name_from="";
    }
}
void MainWindow::choose_napr2(bool checked){
    if (checked)
    {
        napr=-1;

        ui->label->setEnabled(true);
        ui->table_name->setEnabled(true);
        ui->choose_file->setEnabled(false);
        ui->label_2->setEnabled(false);
        ui->table_name_out->setEnabled(false);
        table_name_from="";
    }
}
//  if(napr==1){ui->label_2->show();ui->table_name_out->show();}{ui->label_2->hide();ui->table_name_out->hide();}


int MainWindow::get_napr() {return napr;}
//QString MainWindow::get_file_name(){return file_name_load;}

void MainWindow::path_click(){ //choose 2 in
    // ui->go->show();
    ui->go->setEnabled(true);

    // ui->groupBox_2->show();
    QString filename=//QFileDialog::getOpenFileName(this, tr("Save File"),"","");
      QFileDialog::getSaveFileName(this,
                                QString::fromUtf8("Сохранить файл"),
                                QDir::currentPath(),
                                "Fiels (*.db *.csv *.*);;All files (*.*)");
    if (filename!=""){
        /*  QFile file(filename);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
            return;
        }else*/

        /*      if(napr==1){
            //   if( filename.indexOf(".db")==-1)
                   if(!filename.contains(".db"))
                filename+=".db";}
            else {*/
        if(napr==-1)
            if(!filename.contains(".csv"))

                filename+=".csv";
        ui->path_label->setText(filename);
        file_name_out=filename;
        //  file.close();
        //}
    }

}

void MainWindow::set_table_name_in(){
    ui->choose_file->setEnabled(true);
     table_name_from=  ui->table_name->text();
}

void MainWindow::choose_file_click(){ //сhoose 1 from

    //ui->download->setEnabled(true);
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"),"","");

    if(!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
            return;
        }
        file.close();
    }

    ui->path_label_in->setText(filename);
    file_name_load=filename;
    switch (napr) {
    case 1: //from csv
        if(file_name_load!=""){
           // table.load_from_csv(file_name_load);
            table.CSVRead(filename);
        }
        else  QMessageBox::critical(this,tr("Error"),tr("Not a file name to open"));
        break;
    case -1:
        //download from sql
        if(table_name_from=="")
        {QMessageBox::critical(this,tr("Error"),tr("Not a table name")); break;}
        else{
            table.load_from_sql1(file_name_load,table_name_from);
        }
      //  table.load_from_sql(file_name_load,table_name_from);
        break;
    default:
        QMessageBox::critical(this,tr("Error"),tr("Not a napravlenie convertachii"));
        break;
    }
}

/*void MainWindow::download_click(){
    if (file_name_load=="")
    {
        QMessageBox::critical(this,tr("Error"),tr("Not a file name"));
        return;
    }
    else{
        //зависи от логики или в функции загрузчика делать выбор по направлению или в интерфейсе
        switch (napr) {
        case 1: //in sql
            if(file_name_load!=""){
                table.load_from_csv(file_name_load);;
                //отобразить в модели
            }
            else  QMessageBox::critical(this,tr("Error"),tr("Not a file name to open"));
            break;
        case -1:
            //download from sql
            table_name_from=  ui->table_name->text();
            if(table_name_from==""){QMessageBox::critical(this,tr("Error"),tr("Not a table name")); break;}
          //  table.load_from_sql(file_name_load,table_name_from);
            table.load_from_sql1(file_name_load,table_name_from);
            break;
        default:
            QMessageBox::critical(this,tr("Error"),tr("Not a napravlenie convertachii"));
            break;
        }
    }
}*/


void MainWindow::go_click(){
    if (file_name_load=="")
    {
        QMessageBox::critical(this,tr("Error"),tr("Not a file name to open"));
        return;
    }
    if (file_name_out=="")
    {
        QMessageBox::critical(this,tr("Error"),tr("Not a file name to save"));
        return;
    }
    switch (napr) {
    case 1: //in sql
        //download from csv
        table_name_from=  ui->table_name_out->text();
        if(table_name_from==""){QMessageBox::critical(this,tr("Error"),tr("Not a table name")); break;}
      //  table.load_from_csv(file_name_load);;
       // table.out_to_sql(file_name_out,table_name_from);
        table.output_in_sql1(file_name_out,table_name_from);
        //table.out_to_sql("/home/student/qt_project/convec/basa_sql_out",table_name_from);
        break;

    case -1: //in csv
        table_name_from=  ui->table_name->text();
        if(table_name_from==""){QMessageBox::critical(this,tr("Error"),tr("Not a table name")); break;}
      //  table.load_from_sql(file_name_load, table_name_from);
     //   table.load_from_sql1(file_name_load, table_name_from);
        table.output_in_csv(file_name_out);
        break;
    default:
        QMessageBox::critical(this,tr("Error"),tr("Not a napravlenie")); return;
        break;
    }
}



