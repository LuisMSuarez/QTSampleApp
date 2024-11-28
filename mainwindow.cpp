#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sourceImage=new QImage();
    ui->graphicsView->hide();
    ui->labelSourceBitmapFilePath->setText("Select bitmap file.");
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->hide();
}

MainWindow::~MainWindow()
{
    delete sourceImage;
    delete ui;
}


void MainWindow::on_pushButtonFileSelection_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Bitmap files (*.bmp);;All files (*.*)");

    if (dialog.exec() == QDialog::Accepted)
    {
        QString fileName = dialog.selectedFiles().first();
        ui->labelSourceBitmapFilePath->setText(fileName);
        //QMessageBox::information(this, "File selection", fileName);
        qDebug() << "Selected file:" << fileName;
        openImage();
    }
}

void MainWindow::openImage()
{
    sourceImage->load(ui->labelSourceBitmapFilePath->text());
    QGraphicsScene* scene=new QGraphicsScene() ;
    ui->graphicsView->setScene(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*sourceImage));
    scene->addItem(item);
    ui->graphicsView->show();
 }

void MainWindow::on_pushButtonDataFileSelection_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("All files (*.*)");

    if (dialog.exec() == QDialog::Accepted)
    {
        QString fileName = dialog.selectedFiles().first();
        ui->labelDataFileSourcePath->setText(fileName);
        //QMessageBox::information(this, "File selection", fileName);
        qDebug() << "Selected file:" << fileName;
        loadTextFile();
    }
}

void MainWindow::loadTextFile()
{
    QFile file(ui->labelDataFileSourcePath->text());
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    QString content;
    while(!file.atEnd())
    {
        content.append(file.readLine());
    }
    ui->plainTextEdit->setPlainText(content);
    ui->plainTextEdit->show();
    file.close();
}

