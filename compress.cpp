#include "compress.h"
#include "ui_compress.h"
#include "QFileDialog"

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

