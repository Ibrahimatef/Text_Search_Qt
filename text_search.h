#ifndef TEXT_SEARCH_H
#define TEXT_SEARCH_H

#include <QMainWindow>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Text_Search; }
QT_END_NAMESPACE

class Text_Search : public QMainWindow
{
    Q_OBJECT

public:
    Text_Search(QWidget *parent = nullptr);
    ~Text_Search();

private slots:
    void on_pushButton_clicked();

    void on_progressBar_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Text_Search *ui;
};
#endif // TEXT_SEARCH_H
