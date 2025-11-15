#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <QDialog>

namespace Ui {
class Decompress;
}

class Decompress : public QDialog
{
    Q_OBJECT

public:
    explicit Decompress(QWidget *parent = nullptr);
    ~Decompress();

private slots:
    void on_decom_sel_clicked();

    void on_Dodecompression_clicked();

private:
    Ui::Decompress *ui;
    QString selectedFilePath;
};

#endif // DECOMPRESS_H
