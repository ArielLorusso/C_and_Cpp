#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cliente = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Enviar_clicked()
{
    if(cliente)
    {
         cliente->write(ui->plainTextEnviar->toPlainText().toUtf8());
    }
}

void MainWindow::on_conectar_clicked()
{
    if( !cliente )
    {
        cliente = new QTcpSocket;
        QHostAddress addr(ui->lineEdit->text());
        cliente->connectToHost(addr,ui->lineEditPort->text().toUInt());
        connect(cliente, SIGNAL(disconnected()), this, SLOT(disconnected()));
        connect(cliente, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(cliente,SIGNAL(connected()), this, SLOT(connected()));
    }
    else
    {
        cliente->close ();
        cliente = NULL;
        ui->conectar->setText("Conectar");
        ui->conectar->setStyleSheet("background-color: rgb(255,0,0);");
    }
}

void MainWindow::connected()
{
    ui->conectar->setText("Conectado");
    ui->conectar->setStyleSheet("background-color: rgb(0,255,0);");
}

void MainWindow::readyRead()
{

    ui->plainTextRecibir->appendPlainText( cliente->read(cliente->bytesAvailable()) );
}

void MainWindow::disconnected()
{
    cliente->close();
    cliente = NULL;
}
