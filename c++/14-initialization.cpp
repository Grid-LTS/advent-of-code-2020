#include <iostream>
#include <filesystem>
#include <fstream>
#include <list>
#include <vector>
#include <bitset>
#include <map>

using namespace std;
using namespace std::filesystem;

unsigned long apply_bitmask_to_value(string &bitmask, int &value)
{
    std::string binary = std::bitset<36>(value).to_string();
    for (string::size_type i = 0; i < binary.size(); i++)
    {
        if (bitmask[i] != 'X')
        {
            binary[i] = bitmask[i];
        }
    }
    return std::bitset<36>(binary).to_ulong();
}

void multiply_floating_bits(string binary, int index, int &value, map<unsigned long, int> &memory)
{
    if (index < binary.size())
    {
        for (string::size_type i = index; i < binary.size(); i++)
        {
            if (binary[i] == 'X')
            {
                std::string binary_alt = binary;
                binary[i] = '0';
                binary_alt[i] = '1';
                int new_index = ++i;
                multiply_floating_bits(binary, new_index, value, memory);
                multiply_floating_bits(binary_alt, new_index, value, memory);
                return;
            }
        }
    }
    memory[std::bitset<36>(binary).to_ulong()] = value;
}

void apply_bitmask_to_memlocation(string &bitmask, int &value, int &mem_location, map<unsigned long, int> &memory)
{
    std::string binary = std::bitset<36>(mem_location).to_string();
    for (string::size_type i = 0; i < binary.size(); i++)
    {
        if (bitmask[i] == '0')
        {
            continue;
        }
        binary[i] = bitmask[i];
    }
    multiply_floating_bits(binary, 0, value, memory);
}

void read_input(list<int> &adapters, string &source_file_p)
{
    path input_file_path = absolute(path{source_file_p});
    path root_path = input_file_path.parent_path().parent_path().parent_path();
    path input_path = root_path.append("input").append("14-initialization.txt");
    ifstream input_str(input_path.u8string());
    string line;
    int line_cnt = 0;
    string bitmask;
    map<int, unsigned long> memory_1;
    map<unsigned long, int> memory_2;
    if (input_str.is_open())
    {
        while (getline(input_str, line))
        {
            int pos = line.find("mask = ");
            if (pos == 0)
            {
                bitmask = line.substr(7);
                continue;
            }
            int pos_end = line.find("] = ");
            int mem_location = stoi(line.substr(4, pos_end));
            int no = stoi(line.substr(pos_end + 4));
            memory_1[mem_location] = apply_bitmask_to_value(bitmask, no);
            apply_bitmask_to_memlocation(bitmask, no, mem_location, memory_2);
        }
        input_str.close();
        unsigned long sum1 = 0;
        for (auto const &[key, val] : memory_1)
        {
            /*
            std::cout << "PART 1: location: "
                      << key
                      << ','
                      << "value: "
                      << val
                      << std::endl; */
            sum1 += val;
        }
        cout << "PART 1: " << sum1 << endl;

        unsigned long sum2 = 0;
        for (auto const &[key, val] : memory_2)
        {
            /* For debugging
            std::cout << "PART 2: location: "
                      << key
                      << ','
                      << "value: "
                      << val
                      << std::endl;
            sum2 += val;*/
        }
        cout << "PART 2: " << sum2 << endl;
    }
}

int main(int argc, char *argv[])
{
    string script_path(argv[0]);
    list<int> adapters;
    read_input(adapters, script_path);
}