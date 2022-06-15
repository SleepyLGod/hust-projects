#include <string.h>
#include <math.h>
#include <iostream>
#include "ORGANIZATION.h"
#include "SITE.h"
extern SITE site;
extern const char organization[33][100];
extern const int location[25][2];
extern int eage[64][2];
extern const int locorg[25][2];

Organization::Organization(){
    for(int i=0;i<organization_num;i++){
        strcpy(info[i].name,organization[i]);
        for(int j=0;j<site.site_num;j++){
            if(!strcmp(info[i].name,site.info[j].organization[0])||!strcmp(info[i].name,site.info[j].organization[1])){
                info[i].site = j;
                info[i].location[0] = site.info[j].location[0];
                info[i].location[1] = site.info[j].location[1];
//                info[i].accessible_location_num = site.info[j].accessible_location_num;
//                for(int k=0;k<site.info[j].accessible_location_num;k++){
//                    info[i].accessible_location[k] = site.info[j].accessible_location[k];
//                }
                break;
            }
        }
    }
//    for(int i=0;i<organization_num;i++){
//        for(int j=0;j<info[i].accessible_location_num;j++){
//            info[i].accessible_location_distance[j] = sqrt(pow((info[i].location[0]-info[j].location[0]),2)+pow((info[i].location[1]-info[j].location[1]),2));
//        }
//    }
//    for(int i=0;i<site.site_num;i++){
//        std::cout<<"第"<<i<<"个地点"<<std::endl;
//        int temp[site.site_num] = {0,};
//        std::cout<<"有"<<site.info[i].accessible_location_num<<"建筑"<<std::endl;
//        for(int j=0;j<site.info[i].accessible_location_num;j++){
//            std::cout<<site.info[i].accessible_location[j];
//            int p = which_site(site.info[i].accessible_location[j]);
//            std::cout<<p;
//            std::cout<<temp[p];
//            if(!temp[p]){
//                temp[p]++;
//                site.info[i].accseeible_site[site.info[i].accessible_site_num++] = p;
//                site.info[i].accseeible_site_distance[p] = sqrt(pow((site.info[i].location[0]-site.info[p].location[0]),2)+pow((site.info[i].location[1]-site.info[p].location[1]),2));
//            }
//        }
//     }

};

int Organization::which_site(int i){
    return info[i].site;
};

int Organization::which_site(char name[]){
    for(int i=0;i<organization_num;i++){
        if(!strcmp(name,info[i].name)){
            return info[i].site;
        }
    }
}
