#include "importwindow.h"
#include<QFileDialog>
#include<QDebug>
#include<QMessageBox>
ImportWindow::ImportWindow(QWidget *parent, MainWindow* obj) :
        QWidget(parent) {
    this->setWindowTitle("�����ض�����");
    mw = obj;
    /*
     MainWindow* mw;

     QVBoxLayout* vblMain;
     QHBoxLayout* hblRow1;
     QHBoxLayout* hblRow2;
     QHBoxLayout* hblRow3;
     QHBoxLayout* hblRow4;

     QLabel* lbDescribe;
     QLabel* lbFileInfo;

     QPushButton* pbChoseFile;
     QPushButton* pbUseBack;
     QPushButton* pbCancel;

     QCheckBox* cbImportNote;
     QCheckBox* cbInsertExist;

     QString strBackPath;
     */
    vblMain = new QVBoxLayout(this);
    hblRow1 = new QHBoxLayout(this);
    hblRow2 = new QHBoxLayout(this);
    hblRow3 = new QHBoxLayout(this);
    hblRow4 = new QHBoxLayout(this);

    lbDescribe = new QLabel("ѡ��ĵ����ļ�:");
    hblRow1->addWidget(lbDescribe);
    pbChoseFile = new QPushButton("���", this);
    hblRow1->addWidget(pbChoseFile);
    vblMain->addLayout(hblRow1);

    lbFileInfo = new QLabel(" ");
    hblRow2->addWidget(lbFileInfo);
    vblMain->addLayout(hblRow2);
//    lbFileInfo->setGeometry(QRect(328, 240, 329, 27*4));  //�ı��о�
//    lbFileInfo->setWordWrap(true);//�Զ�����
//    lbFileInfo->setAlignment(Qt::AlignTop);

    cbImportNote = new QCheckBox("ͬʱ���뱸ע��Ϣ");
    cbImportNote->setChecked(true);
    hblRow3->addWidget(cbImportNote);
    cbInsertExist = new QCheckBox("�����Ѵ��ڵı���");
    cbInsertExist->setChecked(false);
    hblRow3->addWidget(cbInsertExist);
    vblMain->addLayout(hblRow3);
    QLabel* lbBlank = new QLabel("");
    vblMain->addWidget(lbBlank);

    pbUseBack = new QPushButton("ȷ�ϵ���", this);
    pbUseBack->setDisabled(true);
    hblRow4->addWidget(pbUseBack);
    pbCancel = new QPushButton("����", this);
    hblRow4->addWidget(pbCancel);
    vblMain->addLayout(hblRow4);

    /*
     ��
     */
    //�˳�
    connect(pbCancel, SIGNAL(clicked()), this, SLOT(close()));
    //ѡ���ļ�
    connect(pbChoseFile, SIGNAL(clicked()), this, SLOT(slotChoseFile()));
    //��ԭ����
    connect(pbUseBack, SIGNAL(clicked()), this, SLOT(SlotUseBack()));
}
void ImportWindow::closeEvent(QCloseEvent *event) {
    qDebug() << event;
    mw->setDisabled(false);
}
void ImportWindow::slotChoseFile() {
    strBackPath = QFileDialog::getOpenFileName(this, "ѡ���ض�������env���ļ�",
            "./export", "Files(*.env)");
    if (!strBackPath.isEmpty()) {
        lbFileInfo->setText(strBackPath);
        pbUseBack->setDisabled(false);
    }
}

void ImportWindow::SlotUseBack() {
    if (mw->isAdimin == true) {
        back = new QSettings(strBackPath, QSettings::IniFormat);
        QStringList strlName = back->allKeys();
        qDebug() << strlName[0];
        if (cbInsertExist->isChecked()) {
            for (int i = 0; i < strlName.length(); i++) {
                QString strName = strlName[i];
                QString strNameValue = back->value(strName).toString();
                QStringList strtemp = strNameValue.split("--//");
                QString value = strtemp[0];
                QString note = strtemp[1];
                mw->reg->setValue(strName, value);
                if (cbImportNote->isChecked()) {
                    mw->note->setValue(strName, note);
                }
            }
            QMessageBox::information(NULL, "�����ɹ���", "���л��������ѱ��ɹ����룡");

        } else {
            QString unInsertValue; //��¼δ��ԭ�ı�����
            int count = 0;
            for (int i = 0; i < strlName.length(); i++) {
                QString strName = strlName[i];
                QString strNameValue = back->value(strName).toString();
                QStringList strtemp = strNameValue.split("--//"); //�ָ��Ƿ�
                QString value = strtemp[0];
                QString note = strtemp[1];
                qDebug() << strNameValue;

                if ((mw->key.indexOf(strName)) == -1) //�����key��StringList��û��strName
                        {
                    mw->reg->setValue(strName, value);
                    if (cbImportNote->isChecked()) {
                        mw->note->setValue(strName, note);
                    }
                    count++;
                } else {
                    unInsertValue = unInsertValue + strName + "\n";
                }

            }
            QMessageBox::information(NULL, "�����ɹ���",
                    "���β������ɹ���ԭ��" + QString::number(count) + "����������,����"
                            + QString::number(strlName.length() - count)
                            + "��������Ϊ�����л���������ͻδ�ܳɹ����룬������:\n" + unInsertValue);

        }
        mw->slotRefrehValue(); //ˢ���������������
    } else {
        QMessageBox::information(NULL, "����ʧ�ܣ�", "��ʹ�ù���ԱȨ�������������ٽ��г��ԣ�");
    }
//    QString value=back->value(strlName[0]).toString();
//    qDebug()<<value;
//    int index=mw->key.indexOf("test");
//    qDebug()<<index;
}

