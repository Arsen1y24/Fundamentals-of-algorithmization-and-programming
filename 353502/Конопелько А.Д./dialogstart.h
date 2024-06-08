#ifndef DIALOGSTART_H
#define DIALOGSTART_H

#include <QDialog>
#include <string>
#include <unordered_map>
#include <map>
#include <QFile>
#include <QString>
#include <QChar>
#include <bits/unordered_map.h>
#include "MyHeaders.h"

namespace Ui {
class DialogStart;
}

class DialogStart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStart(QWidget *parent = nullptr);
    ~DialogStart();
signals:
    void signalStart();

public slots:
    void on_pushButtonEnter_clicked();

private slots:

    void on_pushButtonCreateAcc_clicked();

private:
    Ui::DialogStart *ui;
    bool checkAllow();
    bool canAccess = false;
    QString strAnsDecode = "";
    QFile file = (QFile ("PasswordsLogins.txt"));
    struct Node{
        char ch;
        int freq;
        Node *left, *right;
    };
    Node* getNode(char ch, int freq, Node* left, Node* right);
    Node* root;
    struct comp
    {    bool operator()(Node* l, Node* r)
        {
            return l->freq > r->freq;
        }
    };
    void encode(Node* root, QString str,
                std::unordered_map<char, QString> &huffmanCode);
    void decode(Node* root, int &index, QString& str);
    std::unordered_map<char, QString> buildHuffmanTree(QString text);
    QString getHuffmanCode(QString begStr);
   // QString textFromCode(QString codeStr);
    QString hash(QString str);
};

#endif // DIALOGSTART_H
