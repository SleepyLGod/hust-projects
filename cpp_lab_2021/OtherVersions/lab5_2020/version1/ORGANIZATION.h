#ifndef __Organization_Info_H__

#define __Organization_Info_H__


struct Organization_Info{
    char name[100];
    int site;
    int location[2]={0,};
    int accessible_location_num=0;
    int accessible_location[10]={0,};
    double accessible_location_distance[10]={0,};
};
#endif
#ifndef __Organization_H__

#define __Organization_H__
class Organization{
    public:
        const static int organization_num = 33;
        Organization_Info info[organization_num];
        Organization();
        ~Organization(){};
        int which_site(int i);
        int which_site(char name[]);

};
#endif
