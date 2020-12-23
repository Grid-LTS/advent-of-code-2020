#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
using namespace std;
using namespace std::filesystem;

void read_numbers(vector<long> &stream, vector<long> &preamble, string &source_file_p)
{
    path input_file_path = absolute(path{source_file_p});
    path root_path = input_file_path.parent_path().parent_path().parent_path();
    path input_path = root_path.append("input").append("09-xmas-cypher.txt");
    ifstream input_str(input_path.u8string());
    string line;
    int line_cnt = 0;
    if (input_str.is_open())
    {
        while (getline(input_str, line))
        {
            if (line_cnt <= 24) {
                preamble.push_back(stol(line));
            } else {
                stream.push_back(stol(line));
            }            
            line_cnt++;
        }
        input_str.close();
    }
}

bool find_pair(long number, vector<long> &preamble){
    
    for (unsigned int i = 0; i < preamble.size(); i++) {
        for (unsigned int j = i+1; j < preamble.size(); j++) {
            if (preamble.at(i) + preamble.at(j) == number) {
                return true;
            }
        }
    }
    return false;
}

long check_cypher(vector<long> &stream, vector<long> &preamble){
    int start = 0;
    int max = stream.size();
    long element = stream.at(start);
    while (find_pair(element, preamble) && start < max){
        preamble.erase(preamble.begin());
        preamble.push_back(element);
        start++;
        element = stream.at(start);
    }
    if (start < max) {
       return element;
    }
    return 0;
}

long sum(vector<long> v) {
    long total = 0;
    for (auto& n : v)
        total += n;
    return total;
}

void find_contiguous(vector<long> &stream, long violation) {
    vector<long> contiguous;
     int length = stream.size();
    contiguous.push_back(stream.at(0));
    contiguous.push_back(stream.at(1));
    int runner = 2;
    while (runner < length) {
        long total = sum(contiguous);
        if (total < violation) {
            contiguous.push_back(stream.at(runner));
            runner++;
        }
        if (total > violation) {
            contiguous.erase(contiguous.begin());
        }
        if (total == violation) {
            break;
        }
    }
    if (runner == length){
        cout << "No contiguous found" <<endl;
        return;
    }
    auto max = *max_element(contiguous.begin(), contiguous.end());
    auto min = *min_element(contiguous.begin(), contiguous.end());
    cout << "Encryption weakness: " << max + min << endl;
}

int main(int argc, char *argv[])
{
    string script_path(argv[0]);
    vector<long> preamble;
    vector<long> numbers;
    read_numbers(numbers, preamble, script_path);
    long num = check_cypher(numbers, preamble);
    cout << "Violation of cypher: " << num  << endl;
    vector<long> listn;
    listn.insert(listn.begin(), preamble.begin(), preamble.end());
    listn.insert(listn.end(), numbers.begin(), numbers.end());
    find_contiguous(listn, num);
}
