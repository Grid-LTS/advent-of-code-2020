#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <map>
using namespace std;
using namespace std::filesystem;

void read_instructions(vector<map<string, string>> &ins, string &source_file_p, vector<int> &jump_ins, vector<int> &nop_ins)
{
    path input_file_path = absolute(path{source_file_p});
    path root_path = input_file_path.parent_path().parent_path().parent_path();
    path input_path = root_path.append("input").append("08-instructions.txt");
    ifstream input_str(input_path.u8string());
    string line;
    int line_cnt = 0;
    if (input_str.is_open())
    {
        while (getline(input_str, line))
        {
            map<string, string> el;
            int pos = line.find(" ");
            string instruction = line.substr(0, pos);
            string value = line.substr(++pos);
            el["instruction"] = instruction;
            if (instruction == "jmp")
            {
                jump_ins.push_back(line_cnt);
            }
            if (instruction == "nop")
            {
                nop_ins.push_back(line_cnt);
            }

            el["value"] = value;
            ins.push_back(el);
            line_cnt++;
        }
        input_str.close();
    }
}

int run_program(vector<map<string, string>> &ins, int &accumulator)
{
    int max = ins.size();
    vector<int> executions(max, 0);
    int current_pos = 0;
    while (current_pos < max && executions[current_pos] == 0)
    {
        map<string, string> elmap = ins[current_pos];
        string instruction = elmap.at("instruction");
        int next_pos;
        int delta = stoi(elmap.at("value"));
        //cout << "position: " << current_pos << ", instruction: " << instruction << ", value: " << delta << endl;
        if (instruction == "acc")
        {
            accumulator += delta;
            next_pos = -1;
        }
        else if (instruction == "jmp")
        {
            next_pos = current_pos + delta;
        }
        else if (instruction == "nop")
        {
            next_pos = -1;
        }
        executions[current_pos]++;
        if (next_pos >= 0)
        {
            current_pos = next_pos;
        }
        else
        {
            // move to next instructions
            current_pos++;
        }
    }
    if (current_pos < max)
    {
        return 1;
    }
    return 0;
}

void run_program_mod(vector<map<string, string>> &ins, int position, string replace)
{
        int accumulator = 0;
        vector<map<string, string>> ins_mod = ins;
        map<string, string> &entry = ins_mod[position];
        entry["instruction"] = replace;
        if (run_program(ins_mod, accumulator) == 0) {
            cout << "Modify to " << replace << " at position " << position << endl;
            cout << "Program terminates with accumulator: " << endl; 
            cout << accumulator << endl;
        }   
}

void run_program_mods(vector<map<string, string>> &ins, vector<int> &positions, string replace)
{
     for (unsigned int i = 0; i < positions.size(); i++)
    {
        run_program_mod(ins, positions[i], replace);
    }
}

int main(int argc, char *argv[])
{
    string script_path(argv[0]);
    vector<map<string, string>> ins;
    vector<int> jump_ins;
    vector<int> nop_ins;
    read_instructions(ins, script_path, jump_ins, nop_ins);
    cout << "without change" << endl;
    int accumulator = 0;
    if (run_program(ins, accumulator) == 0){
        cout << accumulator << endl;
    } else {
        cout << "Endless loop reached. Accumulator: " << endl;
        cout << accumulator << endl;
    }
    cout << "Number of jmp instructions " << jump_ins.size() << endl;
    run_program_mods(ins, jump_ins, "nop");
    cout << "Number of nop instructions " << nop_ins.size() << endl;
    run_program_mods(ins, nop_ins, "jmp");
    return 0;
}