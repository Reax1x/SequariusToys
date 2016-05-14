#ifndef PATHWINDOW_H
#define PATHWINDOW_H

#include <QWidget>
#include<mainwindow.h>
#include<QTableView>
#include<QPushButton>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QStandardItemModel>
#include<QLineEdit>
#include<QSettings>
class PathWindow : public QWidget
{
    Q_OBJECT
public:
    friend class MainWindow;
    explicit PathWindow(QWidget *parent = 0,MainWindow* obj=0);

signals:

public slots:
    void slotRefreshPath();//ˢ��Path��Ϣ
    void slotGetClickedInfo();//���ѡ������Ϣ
    void slotCreatePath();//�½�Path����
    void slotSavePath();//����Path
    void slotEditPath();//��ʾ�༭����
    void slotDelPath();//ɾ��Path
    void slotCancel();//ȡ���޸�

public:

private:
    MainWindow* mw;

    QTableView* tvPathList;
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

    QStandardItemModel* simTable;

    /*
        �༭����
    */
    QLabel* lbPathValue;
    QLabel* lbPathNote;
    QLineEdit* lePathValue;
    QLineEdit* lePathNote;
    QHBoxLayout* hblEidit;
    QPushButton* pbSavaPath;
    QPushButton* pbCancel;

    QSettings* pathNote;
    void closeEvent(QCloseEvent *event);
};

#endif // PATHWINDOW_H
