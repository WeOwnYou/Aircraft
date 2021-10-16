#include "mainwindow.h"

#include <QApplication>
#include <QtSql>
#include <iostream>

int main(int argc, char *argv[])
{
//    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");//QSQLITE//QODBC//QMYSQL
//    db.setDatabaseName("DRIVER={SQL Server};SERVER=LAPTOP-OEHOFDO1\\SQLEXPRESS;DATABASE=test;Trusted_Connection=yes;");
//    db.setUserName("admin");
//    db.setPassword("admin");
//    db.open();
//    db.exec("DROP TABLE id;");
//    db.commit();
//    db.exec("CREATE TABLE id (a int);");
//    db.commit();
//        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");//QSQLITE//QODBC//QMYSQL
//        db.setDatabaseName("DRIVER={SQL Server};SERVER=LAPTOP-OEHOFDO1\\SQLEXPRESS;DATABASE=test;Trusted_Connection=yes;");
//        db.setUserName("admin");
//        db.setPassword("admin");
//        db.open();
//        db.exec("DROP TABLE Airplanes");
//        db.commit();
//        db.exec("CREATE TABLE Airplane0 (t int, x double, y double, v double);");
//        db.commit();
//    db.exec("TRUNCATE TABLE Targets;");
//   db.commit();
//    db.exec("INSERT INTO Targets (idTarget, idTargetType) VALUES (1, 1);");
//    db.commit();
    //db.close();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
