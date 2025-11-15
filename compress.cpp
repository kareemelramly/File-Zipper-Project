#include "compress.h"
#include "ui_compress.h"
#include "QFileDialog"
#include "QMessageBox"
#include "huffman_tree.cpp"
compress::compress(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::compress)
{
    ui->setupUi(this);

}

compress::~compress()
{
    delete ui;
}

void compress::on_com_sel_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this, "Select and open file", "C://");
    if (!filename.isEmpty()) {
        // Extract the base name (not full path)
        QFileInfo fileInfo(filename);
        QString baseName = fileInfo.fileName();

        // Set the label (or line edit) text to the file name
        ui->com_sel->setText(baseName);
    }
}


void compress::on_docompression_clicked()
{
    // Get the selected file path from the button text
    QString inputFile = ui->com_sel->text();

    // Check if a file is selected
    if (inputFile.isEmpty() || inputFile == "Select File") {
        QMessageBox::warning(this, "Warning", "Please select a file first!");
        return;
    }

    // Let user choose where to save compressed file
    QString outputFile = QFileDialog::getSaveFileName(
        this,
        "Save Compressed File",
        "C://compressed.huff",
        "All Files (*)"
        );

    if (outputFile.isEmpty()) {
        return; // User cancelled
    }

    try {
        // Use Huffman directly - SIMPLEST APPROACH
        Huffman huffman;
        huffman.CompressToFile(inputFile.toStdString(), outputFile.toStdString());

        QMessageBox::information(this, "Success", "File compressed successfully!");

    } catch (...) {
        QMessageBox::critical(this, "Error", "Compression failed!");
    }
}

