#include "text_search.h"
#include "ui_text_search.h"
#include "Dict.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QProgressBar>
#include <QList>
#include <QMessageBox>
Dict<QString, set<QString>> d;
int x;
Text_Search::Text_Search(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Text_Search)
{
    ui->setupUi(this);
    ui->progressBar->setMaximum(1000);
}

Text_Search::~Text_Search()
{
    delete ui;
}
string remove_punc(string str)
{
    for (int i = 0, len = str.size(); i < len; i++)
    {
        // check whether parsing character is punctuation or not
        if (ispunct(str[i]))
        {
            str.erase(i--, 1);
            len = str.size();
        }
    }
    return str;
}

void Text_Search::on_pushButton_clicked()
{
    ui->progressBar->setValue(0);
    ui->label->setText("Running");
    QString path=QFileDialog::getExistingDirectory(this, "Select Folder");
    QDir mDir(path+"/");
    QStringList filters;
    filters<<"*.txt";
    QFileInfoList l=mDir.entryInfoList(filters);
    ui->progressBar->setMaximum(l.size());
    for(int i=0;i<l.size();i++)
    {
        ui->progressBar->setValue(i+1);
        QFile file(l.at(i).absoluteFilePath());
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
            continue;
        }
        else
        {
            QTextStream in(&file);
            QString word;
            while(!in.atEnd())
            {
                in>>word;
                string tem=word.toUtf8().constData();
                string tem2=remove_punc(tem);
                QString qstr = QString::fromStdString(tem2);
                //string w = word.toUtf8().constData();
                //remove_punc(w);
                d.insert_set(qstr.toLower(),l.at(i).absoluteFilePath());
            }
        }
        file.close();
    }
    ui->label->setText("Finished!");
}

void Text_Search::on_progressBar_valueChanged(int value)
{
 //   ui->progressBar->setValue(value);

}

void Text_Search::on_pushButton_2_clicked()
{
    QString word = ui->lineEdit->text();
    ui->listWidget->clear();
    set<QString>g=d.find(word.toLower());
    if(g.size()!=0)
    {
        for(auto it:g)
        {
            ui->listWidget->addItem(it);
        }
    }
}
void Text_Search::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QList<QListWidgetItem*> l= ui->listWidget->selectedItems();
    for(auto it:l)
    {
    QFile file(it->text());
    if(!file.open(QFile::ReadOnly|QFile::Text))
        {
        QMessageBox t;
        t.setText("Cannot Open File!");
        t.exec();
        continue;
        }
    else
    {
        QTextStream in(&file);
        QString total;
        while(!in.atEnd())
        {
            //in>>word;
            QString line=in.readLine();
            total=total+line+"\n";
            //string w = word.toUtf8().constData();
            //remove_punc(w);
        }
        ui->textEdit->setPlainText(total);

    }
    file.close();
    }
}
