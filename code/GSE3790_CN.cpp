#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>


using namespace std;

void read(){
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    ifstream file("GSE3790_CN.txt", ios::in);
    ofstream fout("GSE3790_input.txt", ios::out);

    if(file.is_open()){
        content.clear();

        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,'\t')){
                row.push_back(word);
            }
            content.push_back(row);
        }
    }else{
        cout<<"could not open file"<<endl;
    }
    cout<<"The number of column is: "<<content[0].size()<<endl;
    int n=content[0].size();

    vector<string> gene_symb, gene_title;
    for( int i=0; i<content.size(); i++){
        gene_symb.push_back(content[i][n-2]);
        gene_title.push_back(content[i][n-2]);
     //   fout<<gene_symb[i]<<","<<gene_title[i]<<endl;
    }
    
    cout<<gene_symb[20188].length()<<"\t"<<gene_symb[20188]<<endl;
    cout<<gene_title[20188].length()<<"\t"<<gene_title[20188]<<endl;

    for(int i=0; i<content.size();i++){
        if( content[i][n-1].length()!=0 && content[i][n-2].length()!=0 ){
            fout<<content[i][n-1];
            for(int j=1; j<content[i].size()-2; j++){
                fout<<'\t'<<content[i][j];
            }
            fout<<endl;
        }
    }

    file.close();
    fout.close();
}

void sort(){
    vector<string>row;
    string line;

    ifstream file("GSE3790_input.txt", ios::in);
    ofstream fout("GSE3790_CN_sort.txt", ios::out);
    ofstream pout("GSE3790_CN_avg.txt", ios::out);

    if(file.is_open()){
        getline(file,line);
        pout<<line<<endl;
        pout.close();

        while(getline(file,line)){
            row.push_back(line);
        }
    }
    else{
        cout<<"could not sort the file"<<endl;
    }

    sort(row.begin(),row.end());

    for(int i=0; i<row.size(); i++){
        fout<<row[i]<<endl;
    }

    file.close();
    fout.close();
}

void avg(){
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    ifstream file("GSE3790_CN_sort.txt", ios::in);
    ofstream fout("GSE3790_CN_avg.txt", ios::app);

    if(file.is_open()){
        content.clear();

        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,'\t')){
                row.push_back(word);
            }
            content.push_back(row);
        }
    }else{
        cout<<"average find could not processed"<<endl;
    }

    int n=content[0].size();
    vector<bool> visited(content.size(),false);
    for( int i=0; i<content.size(); i++){
        if(visited[i]==true)
        continue;

        int count=1;

        for( int k=i+1; k<content.size(); k++){
            if(content[i][0]==content[k][0]){
                visited[k] = true;
                count++;
            }
        }

        fout<<content[i][0];
        for( int j=1; j<n; j++){

            double sum=0;
            for(int k=0; k<count; k++){
                sum += stod(content[i+k][j]);
            }
            double avg = sum/count;
            fout<<'\t'<<avg;
        }
        fout<<endl;
    }
    file.close();
    fout.close();
}

int main(){
    
    read();
    cout<<"file open and read sucessfully"<<endl;

    sort();
    cout<<"requared file sorted sucessfully"<<endl;

    avg();
    cout<<"gene symbol average value find sucessfully"<<endl;

    return 0;
}