#include "pathwindow.h"

#include "PathWindow.h"
#include<mainwindow.h>
#include<QDebug>
PathWindow::PathWindow(QWidget *parent, MainWindow* obj) :
        QWidget(parent) {
    this->setWindowTitle("�༭Path");
    mw = obj;
    /*
     //����
     QHBoxLayout* hblMain;
     QVBoxLayout* vblLeft;
     QVBoxLayout* vblRight;

     //��ǩ
     QLabel* lbDescribe;
     QLabel* lbPathDetail;

     //��ť
     QPushButton* pbNewPath;
     QPushButton* pbDelPath;
     QPushButton* pbEiditPath;
     QPushButton* pbExit;


     */
    hblMain = new QHBoxLayout(this);
    vblLeft = new QVBoxLayout(this);
    vblRight = new QVBoxLayout(this);

    lbDescribe = new QLabel("��ǰ�����е�Path��");
    vblLeft->addWidget(lbDescribe);
    tvPathList = new QTableView(this);
    vblLeft->addWidget(tvPathList);

    hblMain->addLayout(vblLeft);

    pbNewPath = new QPushButton("�½�Path", this);
    vblRight->addWidget(pbNewPath);
    pbEiditPath = new QPushButton("�༭ѡ��Path", this);
    vblRight->addWidget(pbEiditPath);
    pbDelPath = new QPushButton("ɾ��ѡ��Path", this);
    vblRight->addWidget(pbDelPath);
    lbPathDetail = new QLabel(" ");
    lbPathDetail->setGeometry(QRect(328, 240, 329, 27 * 4));  //�ı��о�
    lbPathDetail->setWordWrap(true);  //�Զ�����
    lbPathDetail->setAlignment(Qt::AlignTop);
    vblRight->addWidget(lbPathDetail);
    /*
     �ı���������
     */
    lbPathValue = new QLabel("Path��");
    vblRight->addWidget(lbPathValue);
    lePathValue = new QLineEdit();
    vblRight->addWidget(lePathValue);
    lbPathNote = new QLabel("��ע");
    vblRight->addWidget(lbPathNote);
    lePathNote = new QLineEdit();
    vblRight->addWidget(lePathNote);
    hblEidit = new QHBoxLayout(this);
    pbSavaPath = new QPushButton("����", this);
    hblEidit->addWidget(pbSavaPath);
    pbCancel = new QPushButton("ȡ��", this);
    hblEidit->addWidget(pbCancel);
    vblRight->addLayout(hblEidit);

    lbPathValue->hide();
    lbPathNote->hide();
    lePathValue->hide();
    lePathNote->hide();
    pbSavaPath->hide();
    pbCancel->hide();

    pbExit = new QPushButton("�˳�", this);
    vblRight->addWidget(pbExit);

    hblMain->addLayout(vblRight);

    slotRefreshPath();

    /*
     **    ��
     */
    //��ʾѡ�б�����Ҫ
    connect(tvPathList, SIGNAL(clicked(QModelIndex)), this,
            SLOT(slotGetClickedInfo()));
    //�½�����
    connect(pbNewPath, SIGNAL(clicked()), this, SLOT(slotCreatePath()));
    //����Path
    connect(pbSavaPath, SIGNAL(clicked()), this, SLOT(slotSavePath()));
    //�޸�Path
    connect(pbEiditPath, SIGNAL(clicked()), this, SLOT(slotEditPath()));
    //ɾ��Path
    connect(pbDelPath, SIGNAL(clicked()), this, SLOT(slotDelPath()));
    //ȡ���޸�
    connect(pbCancel, SIGNAL(clicked()), this, SLOT(slotCancel()));
    //����
    connect(pbExit, SIGNAL(clicked()), this, SLOT(close()));
}
void PathWindow::closeEvent(QCloseEvent *event) {
    qDebug() << event;
    mw->setDisabled(false);
}
void PathWindow::slotRefreshPath() {
    pathNote = new QSettings("./note/PathNote.ini", QSettings::IniFormat);
    QString strPath = mw->reg->value("path").toString();
    QStringList strPath_s = strPath.split(";");

    simTable = new QStandardItemModel();
    simTable->setColumnCount(2);
    simTable->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("·����"));
    simTable->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("·����ע"));
    tvPathList->setModel(simTable);
    tvPathList->setSelectionBehavior(QAbstractItemView::SelectRows);  //��������ѡ��
    tvPathList->setEditTriggers(QAbstractItemView::NoEditTriggers);    //�����޷��༭
    tvPathList->setSortingEnabled(true);    //����
    for (int i = 0; i < strPath_s.length(); i++) {
        simTable->setItem(i, 0, new QStandardItem(strPath_s[i]));
        QString strNote = pathNote->value(strPath_s[i]).toString();
        simTable->setItem(i, 1, new QStandardItem(strNote));
    }
}
void PathWindow::slotGetClickedInfo() {
    int row = tvPathList->currentIndex().row();
    QString str1 = simTable->data(simTable->index(row, 0)).toString(); //��n�е�1�е�����
    QString str2 = simTable->data(simTable->index(row, 1)).toString(); //��n�е�2�е�����
//    qDebug()<<str1;
    lbPathDetail->setText("·������" + str1 + "\n��ע��" + str2 + "\n");
}

void PathWindow::slotCreatePath() {
    lbPathValue->show();
    lbPathNote->show();
    lePathValue->show();
    lePathNote->show();
    pbSavaPath->show();
    pbCancel->show();
    lePathValue->clear();
    lePathNote->clear();

}
void PathWindow::slotSavePath() {
    QString strpath = mw->reg->value("path").toString();
    QString addPath = lePathValue->text();
    QString note = lePathNote->text();
    QStringList strPath_s = strpath.split(";");
    int temp = strPath_s.indexOf(addPath);
    if (temp == -1)    //���path·���²�������ӵ�path
            {
        //    pathNote->setValue(addPath,note);
        strpath = addPath + ";" + strpath;
        mw->reg->setValue("Path", strpath);
    }
    pathNote->setValue(addPath, note);
    lbPathValue->hide();
    lbPathNote->hide();
    lePathValue->hide();
    lePathNote->hide();
    pbSavaPath->hide();
    pbCancel->hide();
    slotRefreshPath();
}

void PathWindow::slotEditPath() {
    slotCreatePath();
    int row = tvPathList->currentIndex().row();
    QString str1 = simTable->data(simTable->index(row, 0)).toString(); //��n�е�1�е�����
    QString str2 = simTable->data(simTable->index(row, 1)).toString(); //��n�е�2�е�����
    lePathValue->setText(str1);
    lePathNote->setText(str2);
}

void PathWindow::slotDelPath() {
    int row = tvPathList->currentIndex().row();
    QString str1 = simTable->data(simTable->index(row, 0)).toString(); //��n�е�1�е�����
    QString strPath = mw->reg->value("path").toString();
    QStringList strPath_s = strPath.split(str1 + ";");
    QString finalPath;
    for (int i = 0; i < strPath_s.length(); i++) {
        finalPath = finalPath + strPath_s[i];
    }
    qDebug() << finalPath;
    mw->reg->setValue("Path", finalPath);    //ȥ��Path�ַ�����ı��·��
    pathNote->remove(str1);    //ȡ�����ü�¼�еı�ע��Ϣ
    slotRefreshPath();

}

void PathWindow::slotCancel() {
    lbPathValue->hide();
    lbPathNote->hide();
    lePathValue->hide();
    lePathNote->hide();
    pbSavaPath->hide();
    pbCancel->hide();
    lePathValue->clear();
    lePathNote->clear();

}

