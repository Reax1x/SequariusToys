#include<QDebug>
#include "EiditWindow.h"
//#include<QMainWindow>
#include<QMessageBox>
#include<mainwindow.h>
EiditWindow::EiditWindow(QWidget *parent, MainWindow* obj) :
        QWidget(parent) {
    this->setWindowTitle("�༭��������");
    bCheckBox = false;
    mw = obj;
    cwLayout = new QVBoxLayout(this);
    row1 = new QHBoxLayout;
//    ��ȡѡ�б���
    int row = mw->tvValueList->currentIndex().row();
    QString strName =
            mw->simTable->data(mw->simTable->index(row, 0)).toString(); //��n�е�1�е�����
    QString StrValue =
            mw->simTable->data(mw->simTable->index(row, 1)).toString(); //��n�е�2�е�����
    lbName = new QLabel("��������");
    row1->addWidget(lbName);
    leName = new QLineEdit(strName);
    row1->addWidget(leName);
    cwLayout->addLayout(row1);
    row2 = new QHBoxLayout;
    lbValue = new QLabel("����ֵ��");
    row2->addWidget(lbValue);
    leValue = new QLineEdit(StrValue);
    row2->addWidget(leValue);
    cwLayout->addLayout(row2);
    row3 = new QHBoxLayout;
    lbNote = new QLabel("������ע��");
    row3->addWidget(lbNote);
    leNote = new QLineEdit();
    row3->addWidget(leNote);
    cwLayout->addLayout(row3);
    cbAdd2Path = new QCheckBox("ͬʱ���ñ�����ӵ�Path");
    cwLayout->addWidget(cbAdd2Path);

    row4 = new QHBoxLayout;
    lbToPath = new QLabel(" ");
    lbToPath->hide();
    row4->addWidget(lbToPath);
    leToPath = new QLineEdit("");
    leToPath->hide();
    row4->addWidget(leToPath);
    cwLayout->addLayout(row4);

    row5 = new QHBoxLayout;
    pbConfirm = new QPushButton("ȷ���޸�");
    row5->addWidget(pbConfirm);
    pbCancel = new QPushButton("����");
    row5->addWidget(pbCancel);
    cwLayout->addLayout(row5);

    /*
     ��
     */
    //�˳�ʵ��
    connect(pbCancel, SIGNAL(clicked()), this, SLOT(close()));
    //���Path��ѡ������
    connect(cbAdd2Path,SIGNAL(clicked(bool)),this,SLOT(slotShowAddSetting(bool)));
    //path��ǩ��ȫʵ��
    connect(leName, SIGNAL(textChanged(QString)), this, SLOT(slotPathAdded()));
    //�����޸�ʵ��
    connect(pbConfirm, SIGNAL(clicked()), this, SLOT(slotSaveChange()));
}
void EiditWindow::closeEvent(QCloseEvent *event) {

    mw->setDisabled(false);
    qDebug() << event;
}
void EiditWindow::slotShowAddSetting(bool b) {
    if (b == true) {
        lbToPath->show();
        leToPath->show();
        bCheckBox = true;
    } else {
        lbToPath->hide();
        leToPath->hide();
        bCheckBox = false;
    }
}

void EiditWindow::slotPathAdded() {
    qDebug() << __FUNCTIONW__;
    QString str = leName->text();
    str = "%" + str + "%\\";
    lbToPath->setText(str);
    qDebug() << str;
}

void EiditWindow::slotSaveChange() {
    QString strName = leName->text();
    QString strValue = leValue->text();
    QString strNote = leNote->text();
    mw->reg->setValue(strName, strValue);
    mw->note->setValue(strName, strNote);
    if (bCheckBox == true) {
        QString strpath = mw->reg->value("path").toString();
        QString addPath = leToPath->text();
        strpath = "%" + strName + "%\\" + addPath + ";" + strpath;
        mw->reg->setValue("Path", strpath);
    }
    if (mw->reg->value(strName, false).toBool()) {
        QMessageBox::information(NULL, "�����ɹ�", "����" + strName + "���޸ģ�");
    } else {
        QMessageBox::information(NULL, "����ʧ��",
                "����" + strName + "δ�ɹ�������������������Թ���ԱȨ�����б�����");
    }

    delete mw->reg; //�ͷ�ԭʼreg�ڴ�
    delete mw->simTable; //�ͷ�ԭ����SimTable�ڴ�
    delete mw->note; //�ͷ�note���ڴ�
    mw->slotRefrehValue();
    this->close();
    delete this; //�ͷŴ����ڴ�
}
