#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct Edge {
    int to;
    double distance;
    int railway_line;
    Edge(int t, double d, int r) : to(t), distance(d), railway_line(r) {}
};
using MAP = std::vector<std::vector<Edge>>;

void print_all_path(std::vector<int>* path, const std::vector<std::string> STAT_NAME_LIST){
    //std::cout<<"Printing paths"<<std::endl;
    if ((*path).size()  > 40){ //change
        std::cout<<(*path).size()<<" ";
        for (int i=0;i<(*path).size();i++){
            if (i==0){
                std::cout<<STAT_NAME_LIST[(*path)[i]];
            } else {
                std::cout<<"->"<<STAT_NAME_LIST[(*path)[i]];
            }
        }
        std::cout<<std::endl;
    }
}

void printvec(std::vector<int>* vec){
    for (int i=0;i<(*vec).size();i++){
        std::cout<<(*vec)[i]<<" ";
    }
    std::cout<<std::endl;
}

int find_all_path(MAP map, int start, int end, std::vector<int>* path, const std::vector<std::string> STAT_NAME_LIST){
    (*path).push_back(start);
    //std::cout<<"start: "<<start<<std::endl;
    //printvec(path);
    if (start==end){
        print_all_path(path, STAT_NAME_LIST);
        (*path).pop_back();
        //start=(*path)[(*path).size()-1];
    } else {
        for (int neigh=0;neigh<map[start].size();neigh++){ //neighを走査
            //std::cout<<"start: "<<start<<" neigh: "<<map[start][neigh].to<<" "<<map[start].size();
            bool exist_in_path=false;
            for (int j=0;j<(*path).size();j++){
                if (map[start][neigh].to==(*path)[j]) {
                    exist_in_path=true;
                    break;
                }
            }
            if (!exist_in_path){
                //std::cout<<"call find_all_path("<<map[start][neigh].to<<", "<<end<<")"<<std::endl;
                find_all_path(map, map[start][neigh].to, end, path, STAT_NAME_LIST);
            }
        }
        //std::cout<<std::endl;
        //std::cout<<start<<" ";
        (*path).pop_back();
    }
    
    return 0;
}

int main() {
    int STATION_NUM=46, path_count=0;
    //std::cin >> STATION_NUM;
    MAP m(STATION_NUM);
    std::vector<std::string> STATION_NAME(STATION_NUM);

    // Read railmap.txt
    std::ifstream ifs_railmap("data/West/railmap.txt");
    //std::ifstream ifs_railmap("railmap_debug.txt");
    if (!ifs_railmap){
        std::cerr<<"File railmap.txt does not exist."<<std::endl;
        exit(1);
    }

    int i=-1;
    std::string line, s, stmp;
    Edge tmp(-1, -1.0, -1);
    while (std::getline(ifs_railmap, line)){
        std::stringstream ss(line);
        if (line[0]=='#'){
            i++;
            continue;
        } else if (line.empty()){
            continue;
        }
        ss >> tmp.to >> tmp.distance >> tmp.railway_line;
        m[i].push_back(tmp);
    }
    ifs_railmap.close();

    // Read station_num.txt
    std::ifstream ifs_station_num("data/West/station_num.txt");
    i=0;
    while (std::getline(ifs_station_num, line)){
        std::stringstream ss(line);
        ss >> stmp >> s;
        STATION_NAME[i++]=s;
        //std::cout<<stmp<<" "<<s<<" ";
    }
    ifs_station_num.close();
/*
    // Check if data was read correctly
    std::cout<<"Print railway network"<<std::endl;
    for (int i=0;i<m.size();i++){
        for (int j=0;j<m[i].size();j++){
            std::cout<<m[i][j].to<<" "<<m[i][j].distance<<" "<<m[i][j].railway_line<<std::endl;
        }
    }
    std::cout<<std::endl;
*/
/*
    std::cout<<"The number of stations: "<<STATION_NAME.size()<<std::endl;
    for (int i=0;i<STATION_NAME.size();i++){
        std::cout<<i<<" "<<STATION_NAME[i]<<std::endl;
    }
    std::cout<<std::endl;
*/

    // DFS
    std::vector<int> vtmp(0, 0);
    
    //find_all_path(m, 87, 81, &vtmp, STATION_NAME);
    find_all_path(m, 28, 2, &vtmp, STATION_NAME);
    //std::cout<<"The number of paths from "<<STATION_NAME[90]<<" to "<<STATION_NAME[55]<<": "<<path_count<<std::endl;
    return 0;
}
