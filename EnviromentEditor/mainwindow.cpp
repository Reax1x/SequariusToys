#include "mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include<QDateTime>
#include<QDir>
MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent) {
    this->setWindowTitle("���������༭��");
    /***************************************************
     ȫ�ֲ��ֿ���
     */
    hblMain = new QHBoxLayout(this);
    vblRight = new QVBoxLayout(this);
    vblLeft = new QVBoxLayout(this);
    hblMain->addLayout(vblLeft);
    hblMain->addLayout(vblRight);
    /*******************************************************
     ��಼��
     */
    lbTableView = new QLabel("��ǰϵͳ����������", this);
    vblLeft->addWidget(lbTableView);
    tvValueList = new QTableView();
    vblLeft->addWidget(tvValueList);
    lbDetailTittle = new QLabel("������Ϣ��", this);
    vblLeft->addWidget(lbDetailTittle);
    lbPathDetail = new QLabel("������Ϣ��", this);
    vblLeft->addWidget(lbPathDetail);
    lbPathDetail->setGeometry(QRect(328, 240, 329, 27 * 4));  //�ı��о�
    lbPathDetail->setWordWrap(true);  //�Զ�����
    lbPathDetail->setAlignment(Qt::AlignTop);
    /*******************************************************
     �Ҳ಼��
     */
    lbPathDescribe = new QLabel("Path���ã�", this);
    vblRight->addWidget(lbPathDescribe);
    pbShowPath = new QPushButton("��ʾPath��Ϣ");  //��ʾpath
    vblRight->addWidget(pbShowPath);
    pbEiditPath = new QPushButton("�༭Path·��");  //�޸�path
    vblRight->addWidget(pbEiditPath);

    //*****************************************************************

    lbBackDescribe = new QLabel("��������:");
    vblRight->addWidget(lbBackDescribe);
    pbSetBack = new QPushButton("���ݵ�ǰ����");  //���ݻ���
    vblRight->addWidget(pbSetBack);
    pbUseBack = new QPushButton("��ԭ��ָ������");  //��ԭ����
    vblRight->addWidget(pbUseBack);
    pbCheckIN = new QPushButton("�����ض���������");  //���뻷��
    vblRight->addWidget(pbCheckIN);
    pbCheckOut = new QPushButton("����ָ����������"); //��������
    vblRight->addWidget(pbCheckOut);

    //*****************************************************************

    lbEiditDescribe = new QLabel("����������");
    vblRight->addWidget(lbEiditDescribe);
    pbNewValue = new QPushButton("�½���������");  //�½�����
    vblRight->addWidget(pbNewValue);
    pbEiditValue = new QPushButton("�༭ѡ�б���");  //�༭����
    vblRight->addWidget(pbEiditValue);
    pbDelValue = new QPushButton("ɾ��ѡ�б���");  //ɾ������
    vblRight->addWidget(pbDelValue);

    //*****************************************************************
    lbEiditFunction = new QLabel(" ");
    vblRight->addWidget(lbEiditFunction);
    pbAbout = new QPushButton("���ڡ�");//����
    vblRight->addWidget(pbAbout);
    pbExit = new QPushButton("�˳�"); //�˳�
    vblRight->addWidget(pbExit);

    /******************************************
     //        ����������
     */
    //��ʾ����
    slotRefrehValue();

    //ͨ���Ƿ�����½����������ж��Ƿ��Թ���Ա�������
    reg->setValue("testAdminPermissions", "test");
    if (reg->value("testAdminPermissions", false).toBool()) {

        reg->remove("testAdminPermissions");
        isAdimin = true;
        //�ж�backĿ¼�Ƿ���ڣ���û����ʾ�û����ݣ�
        QDir dir;
        if (!dir.exists("./back/")) {
            switch (QMessageBox::information(this, "��������",
                    "����ǰĿ¼���Ҳ���back�ļ��У������ܴ�δ�Ի����������б��ݣ�Ϊ�˱�֤������ȫ,ǿ�ҽ��������ݵ�ǰ���������Լ�������������������ţ�",
                    "�������ݣ�", "�ݲ���Ҫ��", 0, 1)) {
            case 0:
                slotSetBack();
                break;
            case 1:
                break;

            }

        }
    } else {
        QMessageBox::information(NULL, "δ���UAC����ԱȨ��",
                "δʹ��UAC����ԱȨ�޿�������������Windowsϵͳ�����ƣ������ֻ�ܲ鿴�������ݶ��޷�����༭");
        isAdimin = false;

    }

    //��ʾѡ�б�����Ҫ
    connect(tvValueList, SIGNAL(clicked(QModelIndex)), this,
            SLOT(slotGetClickedLine()));

    //��
    //��ʾPath��Ϣ
    connect(pbShowPath, SIGNAL(clicked()), this, SLOT(slotShowPath()));
    //��Ӱ�ť��
    connect(pbNewValue, SIGNAL(clicked()), this, SLOT(slotCreateWindow()));
    connect(pbEiditValue, SIGNAL(clicked()), this, SLOT(slotEiditWindow()));
    connect(pbEiditPath, SIGNAL(clicked()), this, SLOT(slotPathWindow()));

    //ɾ����ť��
    connect(pbDelValue, SIGNAL(clicked()), this, SLOT(slotRemoveValue()));
    //����
    connect(pbSetBack, SIGNAL(clicked()), this, SLOT(slotSetBack()));
    //��ԭ
    connect(pbUseBack, SIGNAL(clicked()), this, SLOT(SlotGetBackWindow()));
    //����
    connect(pbCheckOut, SIGNAL(clicked()), this, SLOT(slotExportWindow()));
    //����
    connect(pbCheckIN, SIGNAL(clicked()), this, SLOT(slotImportWindow()));
    //�˳�
    connect(pbExit, SIGNAL(clicked()), this, SLOT(close()));
    //����
    connect(pbAbout, SIGNAL(clicked()), this, SLOT(slotAboutWindow()));
}

void MainWindow::slotRefrehValue() {
    reg =
            new QSettings(
                    "HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment",
                    QSettings::NativeFormat);
    key = reg->allKeys();
    note = new QSettings("./note/ValueNote.ini", QSettings::IniFormat);
    simTable = new QStandardItemModel();
    simTable->setColumnCount(3);
//    simTable->setColumnCount(3);
    simTable->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("������"));
    simTable->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("����ֵ"));
    simTable->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("��ע"));
    tvValueList->setModel(simTable);
    tvValueList->setSelectionBehavior(QAbstractItemView::SelectRows);   //��������ѡ��
    tvValueList->setEditTriggers(QAbstractItemView::NoEditTriggers);    //�����޷��༭
    tvValueList->setSortingEnabled(true);    //����
    for (int i = 0; i < key.length(); i++) {
        simTable->setItem(i, 0, new QStandardItem(key[i]));
        simTable->setItem(i, 1,
                new QStandardItem(reg->value(key[i]).toString()));
        simTable->setItem(i, 2,
                new QStandardItem(note->value(key[i]).toString()));
    }
}
void MainWindow::slotGetClickedLine() {
    int row = tvValueList->currentIndex().row();
    QString str1 = simTable->data(simTable->index(row, 0)).toString(); //��n�е�1�е�����
    QString str2 = simTable->data(simTable->index(row, 1)).toString(); //��n�е�2�е�����
    QString str3 = simTable->data(simTable->index(row, 2)).toString();
    qDebug() << str1;
    lbPathDetail->setText(
            "��������" + str1 + "\nֵ��" + str2 + "\n" + "��ע��" + str3 + "\n");
}
void MainWindow::slotShowPath() {
    QString str = reg->value("path").toString();
    QStringList str2 = str.split(";");
    QString str3;
    int count = 0;
    for (int i = 0; i < str2.length(); i++) {
        str3 = str3 + str2[i] + "\n";
        count++;
    }

    qDebug() << str2[3];
    QMessageBox::information(NULL, "��ǰPath·��",
            "��ǰPathһ������" + QString::number(count) + "��Path���������£�\n" + str3);
}

void MainWindow::slotRemoveValue() {
    int row = tvValueList->currentIndex().row();
    QString strName = simTable->data(simTable->index(row, 0)).toString(); //��n�е�1�е�����
    QString strNotification = "ȷ��ɾ��" + strName + "?\n";
    if (strName.isNull()) {
        QMessageBox::information(NULL, "����", "δѡ���κ���Ч�Ļ���������");
    } else {
        switch (QMessageBox::information(this, "ɾ��ȷ��", strNotification, "ȷ��ɾ��",
                "ȡ������", 0, 1)) {
        case 0:
            if (isAdimin == false) {
                QMessageBox::information(NULL, "����ʧ��",
                        "����" + strName + "δ�ɹ�ɾ��������UCA����ԱȨ�����б�����");
            } else {
                reg->remove(strName);
                note->remove(strName);
                delete reg;    //�ͷ�ԭʼreg�ڴ�
                delete simTable;    //�ͷ�ԭ����SimTable�ڴ�
                slotRefrehValue();
                QMessageBox::information(NULL, "�����ɹ�",
                        "����" + strName + "�ѳɹ�ɾ����");
            }
            break;
        case 1:
            break;

        }

    }
}

void MainWindow::slotEiditWindow() {
    qDebug() << __FUNCTIONW__;
    wEidit = new EiditWindow(0, this);
    wEidit->show();
    this->setDisabled(true);
    wEidit->setAttribute(Qt::WA_DeleteOnClose, true);    //����������close()����ʱ�ͷſռ�
}
void MainWindow::slotCreateWindow() {
    qDebug() << __FUNCTIONW__;
    wCreate = new CreateWindow(0, this);
    wCreate->setAttribute(Qt::WA_DeleteOnClose, true);
    wCreate->show();
    this->setDisabled(true);

}
void MainWindow::slotPathWindow() {
    wPath = new PathWindow(0, this);
    wPath->show();
    this->setDisabled(true);
    wPath->setAttribute(Qt::WA_DeleteOnClose, true);
    wPath->setGeometry(350, 250, 400, 340);
}
void MainWindow::slotSetBack() {
    QString strTime = (QDateTime::currentDateTime()).toString("yyyyMMddhhmmss");
    QString strFileName = "back" + strTime + ".back";
    QString strPath = "./back/" + strFileName;
    back = new QSettings(strPath, QSettings::IniFormat);
    for (int i = 0; i < key.length(); i++) {
        QString Name = key[i];
        QString Value = reg->value(key[i]).toString() + "--//"
                + note->value(key[i]).toString();
        back->setValue(Name, Value);
    }
    if (!isAdimin) {
        QMessageBox::information(NULL, "����ʧ��", "������δ��ɣ�����UCA����ԱȨ�����б��������ԣ�");
    } else {

        QMessageBox::information(NULL, "�����ɹ�",
                "�ѳɹ������л���������Ϣ��" + strFileName + "������������Ŀ¼\\back�ļ�����");

    }

}
void MainWindow::SlotGetBackWindow() {
    wBack = new GetBackWindow(0, this);
    wBack->show();
    this->setDisabled(true);
    wBack->setAttribute(Qt::WA_DeleteOnClose, true);

}
void MainWindow::slotExportWindow() {
    wExport = new ExportWindow(0, this);
    wExport->show();
    this->setDisabled(true);
    wExport->setAttribute(Qt::WA_DeleteOnClose, true);
}
void MainWindow::slotImportWindow() {
    wImport = new ImportWindow(0, this);
    wImport->show();
    this->setDisabled(true);
    wImport->setAttribute(Qt::WA_DeleteOnClose, true);
}
void MainWindow::slotAboutWindow() {
    QMessageBox::about(NULL, "���ڳ���",
            "���ߣ�Sequarius\n�汾��1.10\n����BUG���º���sequarius@gmail.com\nллʹ�ã�");

}
