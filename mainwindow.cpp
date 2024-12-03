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
    if (selectedBitmapFilePath.isNull() ||
        selectedBitmapFilePath.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Must select bitmap file first", QMessageBox::Ok);
        return;
    }

    if (selectedDataFilePath.isNull() ||
        selectedDataFilePath.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Must select data file first", QMessageBox::Ok);
        return;
    }

    try
    {
        steganographyLib::Steganography steg;
        steg.embed(selectedBitmapFilePath.toStdString(),
                   selectedDataFilePath.toStdString(),
                   selectedBitmapFilePath.toStdString() + ".enc.bmp",
                   ui->spinBoxBitsPerPixel->value());
        ui->statusbar->showMessage("Embed operation complete", 5000);
    }
    catch (std::runtime_error &e)
    {
        QMessageBox::critical(this, "Encoding error", QString("Error during encoding operation\n") + e.what(), QMessageBox::Ok);
    }
}


void MainWindow::on_pushButtonExtract_clicked()
{
    if (selectedBitmapFilePath.isNull() ||
        selectedBitmapFilePath.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Must select bitmap file first", QMessageBox::Ok);
        return;
    }

    try
    {
        steganographyLib::Steganography steg;
        steg.extract(selectedBitmapFilePath.toStdString(),
                   selectedBitmapFilePath.toStdString() + ".extracted",
                   ui->spinBoxBitsPerPixel->value());
        ui->statusbar->showMessage("Extract operation complete", 5000);
    }
    catch (std::runtime_error &e)
    {
        QMessageBox::critical(this, "Extract error", QString("Error during extract operation\n") + e.what(), QMessageBox::Ok);
    }
}

