#ifndef __Site_Imfo_H__
#define __Site_Imfo_H__
struct Site_Imfo{
    char organization[2][100]={};
    int location[2]={0,};
    int organization_num=0;
    int organization_no[2];
//    int accessible_location_num=0;
//    int accessible_location[10]={0,};
//    double accessible_location_distance[10]={0,};
    int accessible_site_num = 0;
    int accessible_site[10] ={0,};
    double accessible_site_distance[25] = {0,};

};
#endif
#ifndef __SITE_H__
#define __SITE_H__
class SITE{
    public:
        const static int site_num = 25;
        Site_Imfo info[site_num];
        SITE();
        ~SITE(){};
};
#endif
