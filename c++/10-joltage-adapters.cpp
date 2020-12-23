#include <iostream>
#include <filesystem>
#include <fstream>
#include <list>
#include <vector>

using namespace std;
using namespace std::filesystem;

void read_adapters(list<int> &adapters, string &source_file_p)
{
    path input_file_path = absolute(path{source_file_p});
    path root_path = input_file_path.parent_path().parent_path().parent_path();
    path input_path = root_path.append("input").append("10-joltage-adapters.txt");
    ifstream input_str(input_path.u8string());
    string line;
    int line_cnt = 0;
    if (input_str.is_open())
    {
        while (getline(input_str, line))
        {
            int joltage = stoi(line);
            list<int>::iterator it = adapters.begin();
            list<int>::iterator end = adapters.end();
            bool inserted = false;
            while (it != end)
            {
                if (joltage < *it)
                {
                    adapters.insert(it, joltage);
                    inserted = true;
                    break;
                }
                it++;
            }
            if (!inserted)
            {
                adapters.push_back(joltage);
            }
            line_cnt++;
        }
        input_str.close();
    }
}

void determine_steps(list<int> &adapters)
{
    int diffs[3] = {0};
    list<int>::iterator it = adapters.begin();
    list<int>::iterator end = adapters.end();
    diffs[*it - 1]++;
    while (it != end)
    {
        int first = *it;
        it++;
        if (it == end)
        {
            break;
        }
        int second = *it;
        diffs[second - first - 1]++;
    }
    diffs[2]++;
    cout << "One diffs: " << diffs[0] << endl;
    cout << "Two diffs: " << diffs[1] << endl;
    cout << "Three diffs " << diffs[2] << endl;
    cout << "Multiplied  " << diffs[0] * diffs[2] << endl;
}

std::int64_t determine_arrangements(vector<int> &adapters, int index, int offset)
{
    const int size = adapters.size();
    const int size2 = adapters.back();
    static std::int64_t **cache = new std::int64_t *[size];
    if (!cache[0])
    {
        for (int ind = 0; ind < size; ind++)
        {
            cache[ind] = new std::int64_t[size2];
            fill_n(cache[ind], size2, -1);
        }
    }
    if (adapters.size() - 1 - index < 0)
    {
        return 0;
    }
    int oldindex = index;
    int next = adapters.at(index);
    if (next - offset > 3)
    {
        return 0;
    }
    // last element
    if (adapters.size() - 1 - index == 0)
    {
        cache[oldindex][offset] = 1;
        return 1;
    }
    index++;
    std::int64_t sum = 0;
    if (cache[index][offset] != -1)
    {
        sum += cache[index][offset];
    }
    else
    {
        sum += determine_arrangements(adapters, index, offset);
    }
    if (cache[index][next] != -1)
    {
        sum += cache[index][next];
    }
    else
    {
        sum += determine_arrangements(adapters, index, next);
    }
    if (cache[oldindex][offset] == -1)
    {
        cache[oldindex][offset] = sum;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    string script_path(argv[0]);
    list<int> adapters;
    read_adapters(adapters, script_path);
    determine_steps(adapters);
    adapters.push_front(0);
    adapters.push_back(adapters.back() + 3);
    vector<int> adapts(adapters.begin(), adapters.end());
    cout << "Number of arrangements: " << determine_arrangements(adapts, 1, 0) << endl;
}