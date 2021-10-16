#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include <QtDebug>
#include <QThread>
#include <QImage>
#include <QPlainTextEdit>
#include <QtSql>
#include <QListWidgetItem>
#include "tsimulator.h"
#include "Rls.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum INPUT_CONDITION {BASE, PELENG_TIME, NUMBER_OF_AIRCRAFTS, AIRCRAFTS, NUMBER_OF_MISSILES, MISSILES};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void paint();
    void init_insert_screen();
    void on_pushButton_clicked();
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_toggled(bool checked);
    void on_pushButton_2_released();
    void destroy_interface();
    void transport_data_to_bd(vector <Target*> objs);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_pushButton_3_clicked();
    void add_to_track(QString t, QString x, QString y, QString v);

    void on_pushButton_4_clicked();

private:
    int n = 0, m = 0;
    INPUT_CONDITION input_condition;
    bool is_runable = false;
    QStringList aircrafts, missiles;
    Ui::MainWindow *ui;
    //Rls *rls;
    TSimulator *simulator;

    vector<QLabel*> sprites;
    QStringList data_of_text;
    QImage aircraftImg, missileImg;
    QLabel **ql = new QLabel* [5];
    QPlainTextEdit **qpt = new  QPlainTextEdit* [5];
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");//QSQLITE//QODBC//QMYSQL
};
#endif // MAINWINDOW_H
