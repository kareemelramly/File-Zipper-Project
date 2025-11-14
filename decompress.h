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

private:
    Ui::Decompress *ui;
};

#endif // DECOMPRESS_H
