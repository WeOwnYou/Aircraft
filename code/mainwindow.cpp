#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->setText("Add targets");
    ui->listWidget->hide();
    ui->pushButton_4->hide();
    ui->listWidget_2->hide();
    ui->listWidget_3->hide();
    ui->plainTextEdit->hide();
    ui->pushButton_3->hide();
    ui->textBrowser->hide();
    ui->label->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();

    ui->listWidget_4->hide();
    ui->listWidget_6->hide();
    ui->listWidget_5->hide();
    ui->listWidget_7->hide();
    ui->plainTextEdit_2->hide();
    ui->plainTextEdit_3->hide();

    //ui->label->hide();

    //ui->result->setReadOnly(true);
    //ui->result->hide();
    simulator = new TSimulator(0, 0.01, 12);
    init_insert_screen();
}

MainWindow::~MainWindow()
{
    //delete rls;
    delete ui;
    sprites.clear();
    sprites.shrink_to_fit();
    data_of_text.clear();
    aircrafts.clear();
    missiles.clear();
    db.close();
}

QStringList remove_all_non_elements(QStringList q)
{
    for(int i = 0;i < q.length();i++)
    {
        if(q[i] == QString::fromStdString(""))
            q.removeAt(i);
    }
    return q;
}

void MainWindow::init_insert_screen()
{
    int y = 50;
    for(int i = 0;i < 5;i++)
    {
        int x = 10, w = 25, h = 35;
        ql[i] = new QLabel(this);
        qpt[i] = new QPlainTextEdit(this);
        ql[i]->setGeometry(x, y, w, h);
        qpt[i]->setGeometry(x + 20,y,w + 20,h);
        y+=50;
        qpt[i]->show();
        ql[i]->show();
    }

    ql[0]->setText("X:");
    ql[1]->setText("Y:");
    ql[2]->setText("V:");
    ql[3]->setText("K:");
    ql[4]->setText("N:");

    db.setDatabaseName("DRIVER={SQL Server};SERVER=LAPTOP-OEHOFDO1\\SQLEXPRESS;DATABASE=FullLr;Trusted_Connection=yes;");
    db.setUserName("admin");
    db.setPassword("admin");
    db.open();
}

void MainWindow::add_to_track(QString t, QString x, QString y, QString v)
{
    QSqlQuery qry = db.exec("SELECT * FROM Exp");
    qry.last();
    QString idExp = "1";
    if(!qry.value(0).isNull())
        idExp = QString::number(qry.value(0).toInt());

    qry = db.exec("SELECT * FROM Aircrafts");
    qry.last();
    QString idAC = "1";
    if(!qry.value(0).isNull())
        idAC = QString::number(qry.value(0).toInt());

    QString temp = "INSERT INTO Track (idExp, idAC, t, x, y, v) VALUES (";
    temp = temp + idExp + "," + idAC + "," + t + "," + x + "," + y + "," + v + ")";
    db.exec(temp);
    db.commit();


}


void MainWindow::paint()
{
    vector <Target*> objs = simulator->get_targets();
    int n = objs.size();
    transport_data_to_bd(objs);

    for(int i = 0;i < n;i++)
    {
        QLabel *temp = new QLabel(this);
        QPixmap *img;
        if(objs[i]->getType() == 1)
            img = new QPixmap("airplane.jpg");
        else
            img = new QPixmap("raketa.jpg");
        temp->setPixmap(*img);
        temp->setGeometry(objs[i]->get_x(),objs[i]->get_y(), img->width(),img->height());
        sprites.push_back(temp);
    }

    QLabel *temp = new QLabel(this);
    QPixmap *img;
    img = new QPixmap("rls.jpg");
    temp->setPixmap(*img);
    temp->setGeometry(0,0, img->width(), img->height());
    sprites.push_back(temp);
    n = sprites.size();

    for(double j = 0;j < 5;j += 0.01)
    {
        for(int i = 0;i < n;i++)
        {
            if(i != n-1)
            {

                sprites[i]->setGeometry(objs[i]->get_x(), objs[i]->get_y(), sprites[i]->width(), sprites[i]->height());
                add_to_track(QString::number(j*100), QString::number(objs[i]->get_x()),
                             QString::number(objs[i]->get_y()), QString::number(objs[i]->get_v()));
            //QString name = "Airplane" + QString::number(i+1);
            //objs[i]->get_x();
            //if(j==0)
                //create_bd(name);
            //transport_data_to_bd(name, QString::number(j*100), QString::number(objs[i]->get_x()), QString::number(objs[i]->get_y()), QString::number(objs[i]->get_v()));
            }
            sprites[i]->show();
            repaint();
        }
        simulator->run(j);
    }
    for(int i = 0; i < n;i++)
        sprites[i]->hide();
    //n = db.tables().size();
    for(int i = 0;i < 4; i++)
        ui->listWidget->addItem(db.tables()[i].toLocal8Bit().data());
    ui->listWidget->addItem(db.tables()[5].toLocal8Bit().data());
    //ui->listWidget->

    ui->listWidget->show();
    ui->listWidget_2->show();
    ui->listWidget_3->show();
    //ui->result->show();
    ui->plainTextEdit->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();
}

void MainWindow::on_pushButton_clicked()
{
    if (!(ui->radioButton->isChecked() || ui->radioButton_2->isChecked()))
    {
        ui->label_2->setText("Incorrect. Please fill the gapes");
        return;
    }
    //cout<<ui->listWidget->item(2)->isSelected()<<"!"<<endl;
    int n = 5;
    if(ui->radioButton->isChecked())
        n = 4;
    if(!is_runable)
    {
        for(int i = 0;i < n;i++)
        {
            if(qpt[0]->toPlainText().length() == 0)
            {
                ui->label_2->setText("Incorrect. Please fill the gapes");
                return;
            }
        }
        is_runable = true;
    }

    vector<double> target;

    for(int i = 0;i < n;i++)
        target.push_back(qpt[i]->toPlainText().simplified().toDouble());

    if(n == 4)
        simulator->createAircraft(target);
    else
        simulator->createMissile(target);

    for(int i = 0;i < n;i++)
        qpt[i]->setPlainText("");
    ui->label_2->setText("Add target or run programm");
    return;

}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if(checked)
    {
        ql[4]->setVisible(true);
        qpt[4]->setVisible(true);
    }

}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked)
    {
        ql[4]->setVisible(false);
        qpt[4]->setVisible(false);
    }
}

void MainWindow::on_pushButton_2_released()
{

    if(!is_runable)
        return;
    destroy_interface();
    paint();
}


void MainWindow::destroy_interface()
{
    ui->label_2->~QLabel();
    ui->pushButton->~QPushButton();
    ui->pushButton_2->~QPushButton();
    ui->radioButton->~QRadioButton();
    ui->radioButton_2->~QRadioButton();
    for(int i = 0;i < 5;i++)
    {
        qpt[i]->~QPlainTextEdit();
        ql[i]->~QLabel();
    }
}

void MainWindow::transport_data_to_bd(vector <Target*> objs)
{
    QString temp = "INSERT INTO Exp (id, Time) VALUES (";
    QDateTime time;
    QSqlQuery qry = db.exec("SELECT * FROM Exp");
    qry.last();
    time = time.currentDateTime();
    QString idExp = "1";
    if(!qry.value(0).isNull())
        idExp = QString::number(qry.value(0).toInt()+1);
    temp += idExp + ", '" + time.toString() + "')";
    db.exec(temp);
    db.commit();

    temp = "INSERT INTO Rls (id, x, y) VALUES (";
    temp += idExp;
    temp += ",0,0)";
    db.exec(temp);
    db.commit();

    temp = "INSERT INTO CP (id, x, y) VALUES (";
    temp += idExp;
    temp += ",600,600)";
    db.exec(temp);
    db.commit();

    for(int i = 0; i < objs.size();i++)
    {
        temp = "INSERT INTO Aircrafts(id, idExp, x, y, v) VALUES (";
        qry = db.exec("SELECT * FROM Aircrafts");
        qry.last();
        QString id = "1";
        if(!qry.value(0).isNull())
            id = QString::number(qry.value(0).toInt()+1);
        temp += id + ", " + idExp + ", " + QString::number(objs[i]->get_x()) + ", " + QString::number(objs[i]->get_y()) + ", " +
                QString::number(objs[i]->get_v()) + ");";
        cout<<temp.toLocal8Bit().data()<<endl;
        db.exec(temp);
        db.commit();
    }
    //cout<<endl<<temp.toLocal8Bit().data()<<endl;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString text = item->text();
    if(text == "Aircrafts")
    {
        ui->listWidget_2->clear();
        ui->listWidget_2->addItem("id");
        ui->listWidget_2->addItem("idExp");
        ui->listWidget_2->addItem("x");
        ui->listWidget_2->addItem("y");
        ui->listWidget_2->addItem("v");

        ui->listWidget_4->clear();
        ui->listWidget_4->addItem("id");
        ui->listWidget_4->addItem("idExp");
        ui->listWidget_4->addItem("x");
        ui->listWidget_4->addItem("y");
        ui->listWidget_4->addItem("v");

        ui->listWidget_6->clear();
        ui->listWidget_6->addItem("id");
        ui->listWidget_6->addItem("idExp");
        ui->listWidget_6->addItem("x");
        ui->listWidget_6->addItem("y");
        ui->listWidget_6->addItem("v");
    }
    else if(text == "Exp")
    {
        ui->listWidget_2->clear();
        ui->listWidget_2->addItem("id");
        ui->listWidget_2->addItem("Time");

        ui->listWidget_4->clear();
        ui->listWidget_4->addItem("id");
        ui->listWidget_4->addItem("Time");

        ui->listWidget_6->clear();
        ui->listWidget_6->addItem("id");
        ui->listWidget_6->addItem("Time");
    }else if(text == "Rls")
    {
        ui->listWidget_2->clear();
        ui->listWidget_2->addItem("id");
        ui->listWidget_2->addItem("x");
        ui->listWidget_2->addItem("y");

        ui->listWidget_4->clear();
        ui->listWidget_4->addItem("id");
        ui->listWidget_4->addItem("x");
        ui->listWidget_4->addItem("y");

        ui->listWidget_6->clear();
        ui->listWidget_6->addItem("id");
        ui->listWidget_6->addItem("x");
        ui->listWidget_6->addItem("y");
    }else if(text == "CP")
    {
        ui->listWidget_2->clear();
        ui->listWidget_2->addItem("id");
        ui->listWidget_2->addItem("x");
        ui->listWidget_2->addItem("y");

        ui->listWidget_4->clear();
        ui->listWidget_4->addItem("id");
        ui->listWidget_4->addItem("x");
        ui->listWidget_4->addItem("y");

        ui->listWidget_6->clear();
        ui->listWidget_6->addItem("id");
        ui->listWidget_6->addItem("x");
        ui->listWidget_6->addItem("y");
    }else if(text == "Track")
    {
        ui->listWidget_2->clear();
        ui->listWidget_2->addItem("idExp");
        ui->listWidget_2->addItem("idAC");
        ui->listWidget_2->addItem("t");
        ui->listWidget_2->addItem("x");
        ui->listWidget_2->addItem("y");
        ui->listWidget_2->addItem("v");

        ui->listWidget_4->clear();
        ui->listWidget_4->addItem("idExp");
        ui->listWidget_4->addItem("idAC");
        ui->listWidget_4->addItem("t");
        ui->listWidget_4->addItem("x");
        ui->listWidget_4->addItem("y");
        ui->listWidget_4->addItem("v");

        ui->listWidget_6->clear();
        ui->listWidget_6->addItem("idExp");
        ui->listWidget_6->addItem("idAC");
        ui->listWidget_6->addItem("t");
        ui->listWidget_6->addItem("x");
        ui->listWidget_6->addItem("y");
        ui->listWidget_6->addItem("v");
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    QString column, column2 = NULL, column3 = NULL;
    QString table;
    QString operation, operation2 = NULL, operation3 = NULL;
    QString temp;
    QSqlQuery qry;
    if(ui->listWidget->item(0)->isSelected())
    {
        cout<<"??";
        table = "Aircrafts";
        if(ui->listWidget_2->item(0)->isSelected())
            column = "id";
        else if(ui->listWidget_2->item(1)->isSelected())
            column = "idExp";
        else if(ui->listWidget_2->item(2)->isSelected())
            column = "x";
        else if(ui->listWidget_2->item(3)->isSelected())
            column = "y";
        else if(ui->listWidget_2->item(4)->isSelected())
            column = "v";


        if(ui->listWidget_4->item(0)->isSelected())
            column2 = "id";
        else if(ui->listWidget_4->item(1)->isSelected())
            column2 = "idExp";
        else if(ui->listWidget_4->item(2)->isSelected())
            column2 = "x";
        else if(ui->listWidget_4->item(3)->isSelected())
            column2 = "y";
        else if(ui->listWidget_4->item(4)->isSelected())
            column2 = "v";

        if(ui->listWidget_6->item(0)->isSelected())
            column3 = "id";
        else if(ui->listWidget_6->item(1)->isSelected())
            column3 = "idExp";
        else if(ui->listWidget_6->item(2)->isSelected())
            column3 = "x";
        else if(ui->listWidget_6->item(3)->isSelected())
            column3 = "y";
        else if(ui->listWidget_6->item(4)->isSelected())
            column3 = "v";
    }

    else if(ui->listWidget->item(2)->isSelected())
    {
        cout<<"?";
        table = "Exp";
        if(ui->listWidget_2->item(0)->isSelected())
            column = "id";
        if(ui->listWidget_4->item(0)->isSelected())
            column2 = "id";
        if(ui->listWidget_6->item(0)->isSelected())
            column3 = "id";
    }


    else if(ui->listWidget->item(1)->isSelected())
    {

        cout<<"!!!";
        table = "CP";
        if(ui->listWidget_2->item(0)->isSelected())
            column = "id";
        if(ui->listWidget_4->item(0)->isSelected())
            column2 = "id";
        if(ui->listWidget_6->item(0)->isSelected())
            column3 = "id";
    }

    else if(ui->listWidget->item(3)->isSelected())
    {

        cout<<"!!";
        table = "Rls";
        if(ui->listWidget_2->item(0)->isSelected())
            column = "id";
        if(ui->listWidget_4->item(0)->isSelected())
            column2 = "id";
        if(ui->listWidget_6->item(0)->isSelected())
            column3 = "id";
    }

    else
    {
        cout<<"!";
        table = "Track";
        if(ui->listWidget_2->item(0)->isSelected())
            column = "idExp";
        else if(ui->listWidget_2->item(1)->isSelected())
            column = "idAC";
        else if(ui->listWidget_2->item(2)->isSelected())
            column = "t";
        else if(ui->listWidget_2->item(3)->isSelected())
            column = "x";
        else if(ui->listWidget_2->item(4)->isSelected())
            column = "y";
        else if(ui->listWidget_2->item(5)->isSelected())
            column = "v";

        if(ui->listWidget_4->item(0)->isSelected())
            column2 = "idExp";
        else if(ui->listWidget_4->item(1)->isSelected())
            column2 = "idAC";
        else if(ui->listWidget_4->item(2)->isSelected())
            column2 = "t";
        else if(ui->listWidget_4->item(3)->isSelected())
            column2 = "x";
        else if(ui->listWidget_4->item(4)->isSelected())
            column2 = "y";
        else if(ui->listWidget_4->item(5)->isSelected())
            column2 = "v";

        if(ui->listWidget_6->item(0)->isSelected())
            column3 = "idExp";
        else if(ui->listWidget_6->item(1)->isSelected())
            column3 = "idAC";
        else if(ui->listWidget_6->item(2)->isSelected())
            column3 = "t";
        else if(ui->listWidget_6->item(3)->isSelected())
            column3 = "x";
        else if(ui->listWidget_6->item(4)->isSelected())
            column3 = "y";
        else if(ui->listWidget_6->item(5)->isSelected())
            column3 = "v";
    }

    if(ui->listWidget_3->item(0)->isSelected())
        operation = ui->listWidget_3->item(0)->text();
    else if(ui->listWidget_3->item(1)->isSelected())
        operation = ui->listWidget_3->item(1)->text();
    else if(ui->listWidget_3->item(2)->isSelected())
        operation = ui->listWidget_3->item(2)->text();

    if(ui->listWidget_5->item(0)->isSelected())
        operation2 = ui->listWidget_5->item(0)->text();
    else if(ui->listWidget_5->item(1)->isSelected())
        operation2 = ui->listWidget_5->item(1)->text();
    else if(ui->listWidget_5->item(2)->isSelected())
        operation2 = ui->listWidget_5->item(2)->text();

    if(ui->listWidget_7->item(0)->isSelected())
        operation3 = ui->listWidget_7->item(0)->text();
    else if(ui->listWidget_7->item(1)->isSelected())
        operation3 = ui->listWidget_7->item(1)->text();
    else if(ui->listWidget_7->item(2)->isSelected())
        operation3 = ui->listWidget_7->item(2)->text();


    //qpt[i]->toPlainText().simplified().toDouble()
    temp = "SELECT * FROM " + table + " WHERE " + column + operation + ui->plainTextEdit->toPlainText().simplified();
    if(operation2 != NULL)
        temp = temp + " and " + column2 + operation2 + ui->plainTextEdit_2->toPlainText().simplified();
    if(operation3 != NULL)
        temp = temp + " and " + column3 + operation3 + ui->plainTextEdit_3->toPlainText().simplified();

    cout<<temp.toLocal8Bit().data()<<endl;
    qry = db.exec(temp);
    int n = 5;
    qry.next();
    ui->label->show();
    if(qry.value(3).isNull()){
        n = 2;
        ui->label_7->show();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();
        ui->label_6->hide();
    }else if (qry.value(6).isNull()){
        ui->label_7->hide();
        ui->label_3->show();
        ui->label_4->show();
        ui->label_5->show();
        ui->label_6->show();
        n = 6;
    }
    else
        n = 6;
    cout<<"n="<<n<<endl;
    temp = "";
    do{
        //cout<<qry.value(4).toString().toLocal8Bit().data();
        for(int i = 0;i < n;i++){
            int value = qry.value(i).toInt();
            int k = 0;
            while(value != 0){
                value /= 10;
                k++;
            }
            cout<<endl<<value<<" "<<k<<endl;
            temp += qry.value(i).toString().toLocal8Bit().data();
            for(int j = 0; j <= 15-k;j++)
                temp += " ";
        }
        temp += "\n";
    }while(qry.next());
    ui->textBrowser->show();
    ui->textBrowser->setText(temp);
   // ui->label->setText(temp);
    //ui->label->show();
    //ui->result->toPlainText().
    //cout<<temp.toLocal8Bit().data()<<"??"<<endl;
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->listWidget_4->isHidden()){
        ui->listWidget_4->show();
        ui->listWidget_5->show();
        ui->plainTextEdit_2->show();
        ui->label_8->show();
    }else if (ui->listWidget_6->isHidden()){
        ui->listWidget_6->show();
        ui->listWidget_7->show();
        ui->plainTextEdit_3->show();
        ui->label_9->show();
    }
}
