#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include <QListWidget>
#include<QTableView>
#include <QWidget>
#include<QStandardItem>
#include<QSettings>
#include<createwindow.h>
#include<eiditwindow.h>
#include<pathwindow.h>
#include<getbackwindow.h>
#include<exportwindow.h>
#include<importwindow.h>
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    friend class CreateWindow;
    friend class EiditWindow;
    friend class PathWindow;
    friend class GetBackWindow;
    friend class ExportWindow;
    friend class ImportWindow;


signals:
    
public slots:
    void slotAboutWindow();  //������Ϣ
    void slotExportWindow();//��ʾ��������
    void SlotGetBackWindow();//��ʾ��ԭ����
    void slotSetBack();//��ʾ���ݴ���
    void slotPathWindow();//Path����
    void slotShowPath();//��ʾ·��
    void slotCreateWindow();//�½�����
    void slotEiditWindow();//�༭����
    void slotGetClickedLine();//���ѡ���е���Ϣ
    void slotRefrehValue();//ˢ�±�������
    void slotRemoveValue();//ɾ������
    void slotImportWindow();//��ʾ���봰��
private:
    //����
    QHBoxLayout* hblMain;//��
    QVBoxLayout* vblRight;//��
    QVBoxLayout* vblLeft;//��
    //��ť
    QPushButton* pbShowPath;//��ʾpath
    QPushButton* pbEiditPath;//�޸�path
    QPushButton* pbSetBack;//���ݻ���
    QPushButton* pbUseBack;//��ԭ����
    QPushButton* pbCheckIN;//���뻷��
    QPushButton* pbCheckOut;//��������
    QPushButton* pbNewValue;//�½�����
    QPushButton* pbDelValue;//ɾ������
    QPushButton* pbEiditValue;//�༭����
    QPushButton* pbAbout;//����
    QPushButton* pbExit; //�˳�
    //��ǩ
    QLabel* lbTableView;//��ǰ�����б�
    QLabel* lbDetailTittle;//������Ϣ����
    QLabel* lbPathDetail;//������Ϣ����
    QLabel* lbPathDescribe;//·������
    QLabel* lbBackDescribe;//��������
    QLabel* lbEiditDescribe;//�����༭
    QLabel* lbEiditFunction;//�ָ�
    //������ʾ�ؼ�
    QTableView* tvValueList;
    QStandardItemModel* simTable;
    QSettings* reg;
    QSettings* note;
    QStringList key;
    QSettings* back;

    CreateWindow* wCreate;
    EiditWindow* wEidit;
    PathWindow* wPath;
    GetBackWindow* wBack;
    ExportWindow* wExport;
    ImportWindow* wImport;

    bool isAdimin;

};

#endif // MAINWINDOW_H
