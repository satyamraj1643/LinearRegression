#include<bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include<Eigen/Dense>

class ETL {
    std::string dataset;
    std::string delimiter;
    bool header;

public:

  ETL(std::string filename, std::string separator, bool header){
          this->dataset = filename;
          this->delimiter = separator;
          this->header = header;
  }
    std::vector<std::vector<std::string>> readCSV() {
        std::ifstream file(dataset);
        std::vector<std::vector<std::string>> result;

        std::string line;
        while (getline(file, line)) {
            std::vector<std::string> rowData;
            boost::algorithm::split(rowData, line, boost::is_any_of(delimiter));
            result.push_back(rowData);
        }

        file.close();
        return result;
    }
    Eigen::MatrixXd CSVtoEigen(std::vector<std::vector<std::string>>dataset, int rows, int cols){
        int toStart = 0;
          if(this->header == true){
        // header value is present and we do not need the value during processing
         // so we will  reduce the number of rows by 1
         toStart = 1;
         }

         Eigen::MatrixXd mat(rows,cols);

         for(int i = toStart; i<rows; i++){
            for(int j = 0; j<cols; j++){
               mat(i-toStart, j) = atof(dataset[i][j].c_str());
            }
         }

         return mat;
    }
};


int main() {
    ETL etl("wine.data", ",", false);
    std::vector<std::vector<std::string>>data = etl.readCSV();
    //  for(int i = 0; i<data.size(); i++){
    //     for(int j = 0; j<data[i].size(); j++){
    //         std::cout << data[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    //  }


    Eigen::MatrixXd  eigenData = etl.CSVtoEigen(data,data.size(), data[0].size());

    std::cout << eigenData << std::endl;



    return 0;
}


