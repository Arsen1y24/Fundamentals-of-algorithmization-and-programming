#include "dialogstart.h"
#include "ui_dialogstart.h"

DialogStart::DialogStart(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogStart)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint);
}

DialogStart::~DialogStart()
{
    delete ui;
}

void DialogStart::on_pushButtonEnter_clicked()
{
    QString passwordEnter = getHuffmanCode(ui->lineEdit_password->text());
    QString passwordHashEnter = hash(ui->lineEdit_password->text());
    QString loginEnter = getHuffmanCode(ui->lineEdit_login->text());
    QString loginHashEnter = hash(ui->lineEdit_login->text());
    qDebug() << loginEnter  + loginHashEnter << '\n' << passwordEnter + passwordHashEnter;
    if(file.open(QIODevice::ReadOnly)){
        qDebug() << "проверка пароля";
        QTextStream stream(&file);
        int numOfLine = 0;
        bool checkOnOk = false;
        while(stream.atEnd() == false){
            QString strInFile = stream.readLine();
            if(numOfLine % 2 == 1){
                if(passwordEnter + passwordHashEnter == strInFile && checkOnOk == true){
                    qDebug() << " you may enter";
                    file.close();
                    emit signalStart();
                    return;
                }
            }
            if(loginEnter + loginHashEnter == strInFile && numOfLine % 2 == 0){
                checkOnOk = true;
            }
            else{
                checkOnOk = false;
            }
            numOfLine++;
        }
        ui->lineEdit_Info->setText("Неверный пароль");
    }
    else{
        ui->lineEdit_Info->setText("Неверный пароль");
    }
    file.close();
}

void DialogStart::on_pushButtonCreateAcc_clicked()
{
    if(file.open(QIODevice::Append | QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << getHuffmanCode(ui->lineEdit_login->text()) + hash(ui->lineEdit_login->text()) << '\n';
        stream << getHuffmanCode(ui->lineEdit_password->text()) + hash(ui->lineEdit_password->text())<< '\n';
    }
    file.close();
    emit signalStart();
}

bool DialogStart::checkAllow()
{
    return false;
}

DialogStart::Node *DialogStart::getNode(char ch, int freq, Node *left, Node *right)
{
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

void DialogStart::encode(Node *root, QString str, std::unordered_map<char, QString> &huffmanCode)
{
    if (root == nullptr){
        return;
    }
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void DialogStart::decode(Node *root, int &index, QString& str)
{
    if (root == nullptr) {
        return;
    }
    if (!root->left && !root->right)
    {
        strAnsDecode += root->ch;
        return;
    }
    index++;
    if (str[index] =='0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

std::unordered_map<char, QString> DialogStart::buildHuffmanTree(QString text)
{
    std::unordered_map<char, int> freq;
    for (QChar ch: text) {
        int chI = ch.QChar::unicode();
        freq[(char)chI]++;
    }
    std::priority_queue<Node*, std::vector<Node*>, comp> pq;
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
    while (pq.size() != 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
    root = pq.top();
    std::unordered_map<char, QString> huffmanCode;
    encode(root, "", huffmanCode);
     /*
    qDebug() << "Huffman Codes are :\n" << '\n';
    for (auto pair: huffmanCode) {
        qDebug() << pair.first << " " << pair.second << '\n';
    }
    */
    return huffmanCode;
}

QString DialogStart::getHuffmanCode(QString begStr)
{
    std::unordered_map<char, QString> huffmanCode = buildHuffmanTree(begStr);
    QString str = "";
    for (QChar ch: begStr) {
        int charI = ch.QChar::unicode();
        str += huffmanCode[(char)charI];
    }
    return str;
}

// QString DialogStart::textFromCode(QString codeStr)
// {
//     strAnsDecode.clear();
//     int index = -1;
//     while (index < (int)codeStr.size() - 1) {
//         decode(root, index, codeStr);
//     }
//     return codeStr;
// }

QString DialogStart::hash(QString str)
{
    const int k = 329, mod = (int)1e8 + 7;
    long long res = 0;
    for(QChar c: str){
        long long x = c.QChar::unicode();
        res += (res * k + x) % mod;
    }
    return (QVariant(res).toString());
}

