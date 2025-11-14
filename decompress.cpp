#include "decompress.h"
#include "ui_decompress.h"
#include "QFileDialog"

Decompress::Decompress(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Decompress)
{
    ui->setupUi(this);
}

Decompress::~Decompress()
{
    delete ui;
}

void Decompress::on_decom_sel_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this, "Select and open file", "C://");
    if (!filename.isEmpty()) {
        // Extract the base name (not full path)
        QFileInfo fileInfo(filename);
        QString baseName = fileInfo.fileName();

        // Set the label (or line edit) text to the file name
        ui->decom_sel->setText(baseName);
    }
}

