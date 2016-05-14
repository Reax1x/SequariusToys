#include "exportwindow.h"
#include<QDebug>
#include<QLabel>
#include<QDateTime>
#include<QMessageBox>
ExportWindow::ExportWindow(QWidget *parent, MainWindow* obj) :
        QWidget(parent) {
    this->setWindowTitle("����ѡ����������");
    mw = obj;
    int row = mw->key.length() / 5;
    vblROW = new QVBoxLayout(this);
    hblLine = new QHBoxLayout[row + 1];
    cbValue = new QCheckBox[(mw->key.length())];
    QLabel* _discribe = new QLabel("ѡ����Ҫ�����Ļ���������");
    vblROW->addWidget(_discribe);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < 5; j++) {
            QString strValue = (mw->key[i * 5 + j]);
//           qDebug()<<strValue;
            (cbValue + i * 5 + j)->setText(strValue);
            (hblLine + i)->addWidget((cbValue + i * 5 + j));
        }
        vblROW->addLayout((hblLine + i));
        if (i == (row - 1)) {
            for (int j = 0; j < ((mw->key.length()) - row * 5); j++) {
                QString strValue = (mw->key[row * 5 + j]);
                (cbValue + row * 5 + j)->setText(strValue);
                (hblLine + row)->addWidget((cbValue + row * 5 + j));
            }
            vblROW->addLayout(hblLine + row);
        }
    }
    hblButton = new QHBoxLayout;
    pbComfirm = new QPushButton("ȷ�ϵ���", this);
    hblButton->addWidget(pbComfirm);
    pbCancel = new QPushButton("ȡ��", this);
    hblButton->addWidget(pbCancel);
    vblROW->addLayout(hblButton);
    /*
     **��
     */
    connect(pbComfirm, SIGNAL(clicked()), this, SLOT(slotExport()));
    connect(pbCancel, SIGNAL(clicked()), this, SLOT(close()));
}
void ExportWindow::closeEvent(QCloseEvent *event) {
    delete[] cbValue;
    delete[] hblLine;
    qDebug() << event;
    mw->setDisabled(false);
}
void ExportWindow::slotExport() {
    QString strTime = (QDateTime::currentDateTime()).toString("yyyyMMddhhmmss");
    QString strFileName = "back" + strTime + ".env";
    QString strPath = "./export/" + strFileName;
    back = new QSettings(strPath, QSettings::IniFormat);
    for (int i = 0; i < mw->key.length(); i++) {
        if ((cbValue + i)->isChecked()) {
//            QString Name=(cbValue+1)->text();
//            QString Value=mw->reg->value(Name).toString()+"--//"+mw->note->value(Name).toString();
//            back->setValue(Name,Value);
            QString Name = mw->key[i];
            QString Value = mw->reg->value(Name).toString() + "--//"
                    + mw->note->value(Name).toString();
            back->setValue(Name, Value);
            qDebug() << Name;
        }

    }
    if (!mw->isAdimin) {
        QMessageBox::information(NULL, "����ʧ��", "������δ��ɣ����Թ���ԱȨ�����б��������ԣ�");
    } else {

        QMessageBox::information(NULL, "�����ɹ�",
                "�ѳɹ������л���������Ϣ��" + strFileName + "������������Ŀ¼\\export�ļ�����");

    }

}

