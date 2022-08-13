/*
 * @Copyright Copyright (C) 2020 Chris Tzatzakis
 * @license GNU/GPL http://www.gnu.org/copyleft/gpl.html
 * Company:		Chris Tzatzakis
 + Contact:		tzatzakis@ieee.org
 ^
 + Project: 		Minumum Spanning Subset of IPs
 * File Name:				MST-IPs.cpp
 ^                              ***
 * Description:  		Coding Exercise:
 * For the given set of IPv4 addresses find a minimal spanning 
 * subnet. Implementation must be efficient from CPU and memory 
 * perspective. Reasonable test coverage is a plus. 
 *                              ***
 ^ Demo Version - this is intended purely for reviewing
 *                              ***
 * */
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

#define edge pair< int , int>

vector<vector<string> > UniqueNumbers; // Vector Archive for each unique Number identifier of every imported IP

class Graph {
private:
    vector<pair<  int, edge> > G;  // graph
    vector<pair<  int, edge> > T;  // mst
    unsigned int *parent;
    int V{};  // number of vertices/nodes in graph
public:
    explicit Graph( unsigned int V);
    void AddWeightedEdge( int u,  int v, int w);
    unsigned int find_set(unsigned int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};


Graph::Graph(unsigned int V) {
    parent = new unsigned int[V];

    //parent[i] 0 1 2 3 4 5 ...
    for ( unsigned int i = 0; i < V; i++)
        parent[i] = i;

    G.clear();
    T.clear();
}
void Graph::AddWeightedEdge( int u, int v, int w) {
    G.emplace_back(w, edge(u, v));
}
unsigned int Graph::find_set(unsigned int i) {
    if (i == parent[i])
        return i;
    else
        return find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}
void Graph::kruskal() {
    unsigned int i, uRep, vRep;
    sort(G.begin(), G.end());  // increasing weight
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]);  // add to tree
            union_set(uRep, vRep);
        }
    }
}
void Graph::print() {
    int flag=0,weightSum=0;
    string target, source;
    cout << setw(30) << left << setfill(' ') << "  "  << "Edge " << setw(30) << left << setfill(' ')<< " "  << " :   Weight   " << endl;
    cout << setw(80) << left << setfill('-')<< ""  << endl;
    for (auto & i : T) {
        for (auto & UniqueNumber : UniqueNumbers){
            if (i.second.first == strtol(UniqueNumber[0].c_str(), nullptr, 10) ){
                source = UniqueNumber[1] ;
                flag++;
            }
            if (i.second.second == strtol(UniqueNumber[0].c_str(), nullptr, 10) ){
                target = UniqueNumber[1] ;
                flag++;
            }
        }
        if(flag==2) {
            cout << setw(30) << left << setfill(' ') << source << " -  " ;
            cout << setw(30) << left << setfill(' ') << target << "  " ;
            cout << setw(4) << left << setfill(' ')<< ":  " << i.first;
            cout << endl;
            flag=0;
            weightSum += i.first;
        }
    } cout << setw(28) << left << setfill(' ') << "The sum of the weights  : " << weightSum << endl;
}

bool is_number(const std::string& s)
{
    if (s[0] == '-'){
        cout << "We have s[0] == '-' : " << s << endl;
        return !s.empty() && std::find_if(s.begin()+1,
                                          s.end(), []( char c) { return !std::isdigit(c); }) == s.end();
    }
    else
        return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

uint32_t is_IP4( const string& ipv4Str )
{
    istringstream iss( ipv4Str );

    if(count(ipv4Str.begin(), ipv4Str.end(), '.')!=3)
        return 0;

    stringstream part_str;

    for( uint32_t i = 0; i < 4; ++i ) {
        uint32_t part;
        iss >> part;
        part_str << part;

        if(!is_number(part_str.str())) {
            return 0;
        }
        part_str.str(std::string());

        cout << part << " part ip4" <<endl;
        if ( iss.fail() || part > 255 ) {
            //cout << "Error::loadCSVFile - Invalid IP address - Expected [0, 255]" << endl;
            return 0;
        }
        // Check for delimiter except on last iteration
        if ( i != 3 ) {
            char delimiter;
            iss >> delimiter;
            if ( iss.fail() || delimiter != '.' ) {
                //cout << "Error::loadCSVFile - Invalid IP address - Expected '.' delimiter" << endl;
                return 0;
            }
        }

        else
            return true;
    }
}


int searchArray(vector<vector<string> > array, const string& value) {
    if (!array.empty()) {
        for (auto & i : array) {
            for (int j = 0; j < i.size(); j++) {
                if (i[1] == value )  {
                    return strtol(i[0].c_str(),nullptr,10);
                }
            }
        }
    }


    return -1;
}

vector<vector< int> > loadCSVFile(const string& FilePath){
    cout << FilePath << "LOG::loadCSVFile" << endl;
    ifstream  dataset(FilePath);
    if(dataset.fail()){
        cout << "Error::loadCSVFile - File Not Found - 404" << endl;
        return {};
    }

    int uniqueNumbersIdValue = 0;
    string line;
    vector<vector< int> > parsedCsv;

    while(getline(dataset,line))
    {
        stringstream lineStream(line);
        string cell;
        int rowFlagCount =0;
        stringstream uniqueNumbersIdValue_str;
        int searchArrayValue;
        vector<string> parsedUniqueRow;
        vector< int> parsedRow;

        while(getline(lineStream,cell,';'))
        {
            if (cell.find('.')!=string::npos)
            {
                if(is_IP4(cell)){

                    searchArrayValue = searchArray(UniqueNumbers, cell);

                    if( searchArrayValue >= 0 ) {
                        parsedRow.push_back(searchArrayValue);
                    }else {
                        uniqueNumbersIdValue_str << uniqueNumbersIdValue;
                        parsedUniqueRow.push_back(uniqueNumbersIdValue_str.str()); // Unique Numbers Array new row element
                        parsedUniqueRow.push_back(cell); // Unique Numbers Array new row complete
                        UniqueNumbers.push_back(parsedUniqueRow); //Unique Numbers
                        parsedUniqueRow={}; uniqueNumbersIdValue_str.str(std::string()); // clear variable coordinates
                        parsedRow.push_back(uniqueNumbersIdValue); // parsedCsv Array new row
                        uniqueNumbersIdValue++;
                    }
                }
                else {
                    rowFlagCount++;
                    cout << " No IP detected " << endl;
                }


            }
            else{
                //check if the weight and/or nodes are numeric

                if(is_number(cell)) {
                    cout << "POS or NEG : " << cell << " strtol(cell.c_str(),nullptr, 10) : " << strtol(cell.c_str(),nullptr, 10) << endl;
                    if (rowFlagCount==0)
                        parsedRow.push_back(strtol(cell.c_str(),nullptr, 10));
                    else{
                        parsedRow.pop_back();
                    }
                }
                else{
                    rowFlagCount++;
                    cout << " Dont know what that is but it is not a number " << endl;
                    parsedRow.pop_back();
                }

            }
        }
        if (rowFlagCount==0)
            parsedCsv.push_back(parsedRow);

    }
    dataset.close();
    return parsedCsv;
}



int main() {
    vector<vector< int> > data;
    data = loadCSVFile("testDataset.csv");

    if (data.empty()){
        return 404;
    }

    Graph g( UniqueNumbers.size() );
    for (int i = 1; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            cout << data[i][j] << " ";
            g.AddWeightedEdge(data[i][0], data[i][1], data[i][2]);
        }
        cout <<  endl;
    }

    g.kruskal();
    g.print();

    return 0;
}