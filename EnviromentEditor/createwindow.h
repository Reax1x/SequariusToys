#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H
#include <QWidget>
#include<QLineEdit>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QHBoxLayout>
#include<QCheckBox>
#include<mainwindow.h>
#include <QCloseEvent>
class CreateWindow : public QWidget
{
    Q_OBJECT
public:
    friend class MainWindow;
    explicit CreateWindow(QWidget *parent = 0,MainWindow* obj=0);

signals:
public slots:
    void slotShowAddSetting(bool b);//��ʾ���Path��ϸ����
    void slotPathAdded();//��������������ӵ�Path��ǩ�������
    void slotSaveChange();//�����޸�


private:
//    MainWindow* obj;
    //����
    QVBoxLayout* cwLayout;//������������
    QHBoxLayout* row1;
    QHBoxLayout* row2;
    QHBoxLayout* row3;
    QHBoxLayout* row4;
    QHBoxLayout* row5;


    //��ǩ
    QLabel* lbName;
    QLabel* lbValue;
    QLabel* lbNote;
    QLabel* lbToPath;
    //�༭����
    QLineEdit* leName;//���Ʊ༭
    QLineEdit* leValue;//ֵ�༭
    QLineEdit* leNote;//��ע�༭
    QLineEdit* leToPath;//path����

    QCheckBox* cbAdd2Path;//��ӵ�Path��ѡ��
     //��ť
    QPushButton* pbConfirm;//ȷ�ϰ�ť
    QPushButton* pbCancel;//ȡ����ť

    MainWindow* mw;
    bool bCheckBox;
    void closeEvent(QCloseEvent *event);
};

#endif // CREATEWINDOW_H
