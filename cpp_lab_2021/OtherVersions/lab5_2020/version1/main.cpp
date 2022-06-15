#include <string.h>
#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <iostream>
#include "SITE.cpp"
#include "ORGANIZATION.cpp"

using namespace std;
const char organization[33][100]={"���пƼ���ѧ����","���пƼ���ѧ�϶���","���пƼ���ѧ������","��ѧѧԺ","úȼ��ʵ����","��ݿѧ����Ԣ","�����ѧԺ","����ѧԺ","ͼ���","��һѧ��ʳ��",
"����ѧԺ","��ѧԺ","�Ƽ�¥","���깫Ԣ","�̹������","ӡˢ��","��������","���н���������","�����շ�����","������","�˺�¥","�д���","��԰","����¥","����¥","��ʮ��¥","����ѧԺ","������",
"���߲�ʿ��Ԣ","������","��ѧ����","ͼ���α����","����ͤ",};
const int location[25][2]={	{990,383},{916,376},{883,380},{867,287},{812,298},{805,270},{997,337},{971,254},{811,222},{1099,299},{976,206},{1014,209},{969,284},{931,226},{936,200},{928,278},{923,329},{877,352},{919,346},{888,220},{891,195},{858,217},{852,191},{1035,342},{1040,292},};
int eage[64][2]={{0,1},{0,6},{1,2},{1,18},{2,17},{3,4},{3,15},{3,17},{3,21},{4,5},{5,8},{6,16},{6,23},{7,10},{7,12},{8,21},{9,24},{10,11},{10,14},{12,15},{12,24},{13,14},{13,15},{13,19},{14,20},{15,16},{16,18},{17,18},{19,21},{20,22},{21,22},{23,24},};
const int locorg[25][2]={{0,-1},{1,-1},{2,-1},{3,-1},{4,-1},{5,-1},{6,7},{8,-1},{9,-1},{10,11},{12,13},{14,15},{16,17},{18,19},{20,21},{22,-1},{23,24},{25,-1},{26,-1},{27,-1},{28,-1},{29,-1},{30,-1},{31,-1},{32,-1},};

SITE site;
Organization organization_info;


class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
private:
    QPushButton *MainButton_1;
signals:
public slots:
};







int main(int argc, char *argv[])
{

//    for(int i=0;i<site.site_num;i++){
//        cout<<i<<endl;
//        cout<<site.info[i].accessible_site_num<<endl;
//        for(int j=0;site.info[i].accessible_site_num;i++){
//            cout<<endl<<site.info[i].accessible_site[j]<<site.info[i].accessible_site_distance[site.info[i].accessible_site[j]]<<endl<<endl;

//        }
//        cout<<endl;
//    }

    QApplication a(argc, argv);
    MainWindow w;


    w.show();
    return a.exec();
}
