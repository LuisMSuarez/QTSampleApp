#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "steganography.h"
#include <QtWidgets>
#include <filesystem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sourceImage=new QImage();
    ui->labelSourceBitmapFilePath->setText("Select bitmap file");
    ui->plainTextEdit->setReadOnly(true);
    ui->gridLayout->setColumnStretch( 0, 0 ) ; // Give column 0 no stretch ability
    ui->gridLayout->setColumnStretch( 1, 1 ) ; // Give column 1 stretch ability of ratio 1
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
        selectedBitmapFilePath = dialog.selectedFiles().first();
        std::string fileName = std::filesystem::path(selectedBitmapFilePath.toStdString()).filename();
        ui->labelSourceBitmapFilePath->setText(QString::fromStdString(fileName));
        qDebug() << "Selected file:" << fileName;
        openImage();
    }
}

void MainWindow::openImage()
{
    sourceImage->load(selectedBitmapFilePath);
    QGraphicsScene* scene=new QGraphicsScene() ;
    ui->graphicsView->setScene(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(
                QPixmap::fromImage(*sourceImage).scaled(
                    ui->graphicsView->width(),
                    ui->graphicsView->height(),
                    Qt::KeepAspectRatio));
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
        selectedDataFilePath = dialog.selectedFiles().first();
        std::string fileName = std::filesystem::path(selectedDataFilePath.toStdString()).filename();
        ui->labelDataFileSourcePath->setText(QString::fromStdString(fileName));
        qDebug() << "Selected file:" << fileName;
        loadTextFile();
    }
}

void MainWindow::loadTextFile()
{
    QFile file(selectedDataFilePath);
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

void MainWindow::on_pushButtonEmbed_clicked()
{
    if (selectedBitmapFilePath == "")
    {
        QMessageBox::critical(this, "Error", "Must select bitmap file first", QMessageBox::Ok);
        return;
    }

    steganographyLib::Steganography steg;
    steg.embed(selectedBitmapFilePath.toStdString(),
               selectedDataFilePath.toStdString(),
               selectedBitmapFilePath.toStdString() + ".enc.bmp",
               ui->spinBoxBitsPerPixel->value());
}


void MainWindow::on_pushButtonExtract_clicked()
{
    steganographyLib::Steganography steg;
    steg.extract(selectedBitmapFilePath.toStdString(),
               selectedBitmapFilePath.toStdString() + ".extracted",
               ui->spinBoxBitsPerPixel->value());
}

