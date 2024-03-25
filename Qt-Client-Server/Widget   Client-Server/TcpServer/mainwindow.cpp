#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = NULL;
    cliente = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_conectar_clicked()
{
    socket = new QTcpServer(this);
    connect(socket, SIGNAL(newConnection()),this, SLOT(newConnection()) );
    socket->listen(QHostAddress::Any, ui->lineEditPort->text().toUInt());

    ui->conectar->setText("Conectado");
    ui->conectar->setStyleSheet("background-color: rgb(0,255,0);");
}

void MainWindow::on_Enviar_clicked()
{
    if(cliente)
    {
        cliente->write(ui->plainTextEnviar->toPlainText().toUtf8());
    }
}

void MainWindow::newConnection(void)
{
    if(!cliente)
    {
        cliente = new QTcpSocket;
        cliente = socket->nextPendingConnection();
        connect(cliente, SIGNAL(disconnected()), this, SLOT(disconnected()));
        connect(cliente, SIGNAL(readyRead()), this, SLOT(readyRead()));
    }
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
