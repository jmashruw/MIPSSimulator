/* On my honor, I have neither given nor received unauthorized aid on this assignment */

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>
#include <climits>

std::unordered_map<std::string, std::string> cat1;
std::unordered_map<std::string, int> id;
std::map<int, std::string> data;
std::vector<int> registers(32, 0);
std::map<int, std::string> addrInst;
std::ofstream simulationfile;
int cycle = 1;

void populateCat1(std::unordered_map<std::string, std::string>& cat1)
{
    cat1["010000"] = "J";
    cat1["010001"] = "JR";
    cat1["010010"] = "BEQ";
    cat1["010011"] = "BLTZ";
    cat1["010100"] = "BGTZ";
    cat1["010101"] = "BREAK";
    cat1["010110"] = "SW";
    cat1["010111"] = "LW";
    cat1["011000"] = "SLL";
    cat1["011001"] = "SRL";
    cat1["011010"] = "SRA";
    cat1["011011"] = "NOP";
    cat1["110000"] = "ADD";
    cat1["110001"] = "SUB";
    cat1["110010"] = "MUL";
    cat1["110011"] = "AND";
    cat1["110100"] = "OR";
    cat1["110101"] = "XOR";
    cat1["110110"] = "NOR";
    cat1["110111"] = "SLT";
    cat1["111000"] = "ADDI";
    cat1["111001"] = "ANDI";
    cat1["111010"] = "ORI";
    cat1["111011"] = "XORI";
}

void maintainID(std::unordered_map<std::string, int>& id)
{
    id["J"] = 1;
    id["JR"] = 2;
    id["BEQ"] = 3;
    id["BLTZ"] = 4;
    id["BGTZ"] = 5;
    id["BREAK"] = 6;
    id["SW"] = 7;
    id["LW"] = 8;
    id["SLL"] = 9;
    id["SRL"] = 10;
    id["SRA"] = 11;
    id["NOP"] = 12;
    id["ADD"] = 13;
    id["SUB"] = 14;
    id["MUL"] = 15;
    id["AND"] = 16;
    id["OR"] = 17;
    id["XOR"] = 18;
    id["NOR"] = 19;
    id["SLT"] = 20;
    id["ADDI"] = 21;
    id["ANDI"] = 22;
    id["ORI"] = 23;
    id["XORI"] = 24;
}

short binaryToDecimalWithout2Complement(std::string s)
{
    std::string::size_type sz; // alias of size_t
    int i = std::stol(s, nullptr, 2);
    return (short) i;
}

int binTwosComplementToSignedDecimal(long num)
{
    return (signed char)num;
}

std::string compute(std::string s, int addr, std::map<int, std::string>& data)
{
    std::string opcode = s.substr(0, 6);
    std::string instr = cat1[opcode];
    int switch_case = id[instr];
    std::string res = s + '\t' + std::to_string(addr) + '\t';
    int break_found = 1;

    switch (switch_case) {
        case 1:
            if (break_found == 1) {
                res += "J #" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 26)) << 2);
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 2:
            if (break_found == 1) {
                res += "JR R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 3:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                res += "BEQ " + rs + ", " + rt + ", #" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 16)) << 2);
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 4:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                res += "BLTZ " + rs + ", #" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 16)) << 2);
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 5:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                res += "BGTZ " + rs + ", #" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 16)) << 2);
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 6:
            if (break_found == 1) {
                break_found = 0;
                res += "BREAK";
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 7:
            if (break_found == 1) {
                std::string base = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string offset = std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 16)));
                res += "SW " + rt + ", " + offset + "(" + base + ")";
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 8:
            if (break_found == 1) {
                std::string base = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string offset = std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 16)));
                res += "LW " + rt + ", " + offset + "(" + base + ")";
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 9:
            if (break_found == 1) {
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                std::string sa = std::to_string(binaryToDecimalWithout2Complement(s.substr(21, 5)));
                res += "SLL " + rd + ", " + rt + ", #" + sa;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 10:
            if (break_found == 1) {
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                std::string sa = std::to_string(binaryToDecimalWithout2Complement(s.substr(21, 5)));
                res += "SRL " + rd + ", " + rt + ", #" + sa;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 11:
            if (break_found == 1) {
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                std::string sa = std::to_string(binaryToDecimalWithout2Complement(s.substr(21, 5)));
                res += "SRA " + rd + ", " + rt + ", #" + sa;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 12:
            if (break_found == 1) {
                res += "NOP";
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 13:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                res += "ADD " + rd + ", " + rs + ", " + rt;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 14:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                res += "SUB " + rd + ", " + rs + ", " + rt;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 15:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                res += "MUL " + rd + ", " + rs + ", " + rt;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 16:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                res += "AND " + rd + ", " + rs + ", " + rt;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 17:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                res += "OR " + rd + ", " + rs + ", " + rt;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 18:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                res += "XOR " + rd + ", " + rs + ", " + rt;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 19:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                res += "NOR " + rd + ", " + rs + ", " + rt;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 20:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string rd = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(16, 5)));
                res += "SLT " + rd + ", " + rs + ", " + rt;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 21:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string immediate = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s.substr(16, 16))));
                res += "ADDI " + rt + ", " + rs + ", #" + immediate;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 22:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string immediate = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s.substr(16, 16))));
                res += "ANDI " + rt + ", " + rs + ", #" + immediate;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 23:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string immediate = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s.substr(16, 16))));
                res += "ORI " + rt + ", " + rs + ", #" + immediate;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        case 24:
            if (break_found == 1) {
                std::string rs = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(6, 5)));
                std::string rt = "R" + std::to_string(binaryToDecimalWithout2Complement(s.substr(11, 5)));
                std::string immediate = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s.substr(16, 16))));
                res += "XORI " + rt + ", " + rs + ", #" + immediate;
            }
            else {
                auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
                res += r;
                data[addr] = r;
            }
            break;
        default:
            auto r = std::to_string(binTwosComplementToSignedDecimal(binaryToDecimalWithout2Complement(s)));
            res += r;
            data[addr] = r;
    }
    return res;
}

void readFile(std::string fileName)
{
    std::fstream f(fileName, std::fstream::in);
    std::ofstream disassemblyfile;
    disassemblyfile.open("disassembly.txt");
    std::string s;
    int addr = 256;
    int cycle = 1;
    while (f.good()) {
        std::getline(f, s);
        if (!(s.empty())) {
            std::string res = compute(s, addr, data);
            disassemblyfile << res << "\n";
            addr += 4;
            cycle++;
        }
    }
    disassemblyfile.close();

    f.close();
}

std::vector<std::string> split(const std::string& text, std::string sep)
{
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        if (end != start) {
            tokens.push_back(text.substr(start, end - start));
        }
        start = end + sep.length();
    }
    if (end != start) {
        tokens.push_back(text.substr(start));
    }
    return tokens;
}

void populateAddressInstr(std::string fileName, std::map<int, std::string>& addrInst)
{
    std::fstream f(fileName, std::fstream::in);
    std::string s;
    int break_found = 0;
    std::string::size_type sz; // alias of size_t
    while (f.good()) {
        std::getline(f, s);
        if (!(s.empty())) {
            if (break_found == 0) {
                std::vector<std::string> vec = split(s, "\t");
                int addr = std::stoi(vec[1], &sz);
                std::string instr = vec[2];
                addrInst[addr] = instr;
                if (instr == "BREAK") {
                    break_found = 1;
                }
            }
        }
    }
    f.close();
}

//writes data to simulation file
void writeSimulationFile(std::string s, int adr, std::map<int, std::string>& data, std::vector<int>& registers)
{
    std::string sim;
    std::string addr = std::to_string(adr);
    std::string instr = s;
    sim = "--------------------\nCycle:" + std::to_string(cycle) + '\t' + addr + '\t' + instr + "\n\nRegisters\n";
    //registers
    for (int i = 0; i < registers.size(); i++) {
        if (i % 8 == 0) {
            sim += "R" + ((i < 9) ? "0" + std::to_string(i) : std::to_string(i)) + ":\t";
        }
        sim += std::to_string(registers[i]) + ((i + 1) % 8 != 0 ? '\t' : '\n');
    }
    //Data
    sim += "\nData\n";
    int j = 0;
    for (auto& itr : data) {
        if (j % 8 == 0) {
            sim += std::to_string(itr.first) + ":\t";
        }
        sim += itr.second + ((j + 1) % 8 != 0 ? '\t' : '\n');
        j++;
    }

    if (instr == "BREAK") {
        simulationfile << sim;
        return;
    }

    simulationfile << sim << '\n';
    cycle++;
}

void performOperation(std::string s, std::map<int, std::string>& data, std::vector<int>& registers, int addr)
{
    int spacePos = s.find_first_of(" ");
    std::string type = s.substr(0, spacePos);
    int switch_case = id[type];
    switch (switch_case) {
        case 1: {
            //J target
            std::string ins = s.substr(spacePos + 1);
            std::string::size_type sz; // alias of size_t
            int offset = std::stoi(ins.substr(1), &sz);
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[offset], data, registers, offset);
        } break;
        case 2: {
            //J rs
            std::string ins = s.substr(spacePos + 1);
            std::string::size_type sz; // alias of size_t
            int rs = std::stoi(ins.substr(1), &sz);
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[registers[rs]], data, registers, registers[rs]);
        } break;
        case 3: {
            // res += BEQ rs, rt, offset
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rsPos = std::stoi(vec[0].substr(1), &sz);
            int rtPos = std::stoi(vec[1].substr(1), &sz);
            int offset = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            int b = registers[rtPos];
            writeSimulationFile(s, addr, data, registers);
            if (a != b) {
                performOperation(addrInst[addr + 4], data, registers, addr + 4);
            }
            else {
                performOperation(addrInst[addr + 4 + offset], data, registers, addr + 4 + offset);
            }
        } break;
        case 4: {
            //BLTZ rs, offset
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rsPos = std::stoi(vec[0].substr(1), &sz);
            int offset = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            writeSimulationFile(s, addr, data, registers);
            if (a < 0) {
                performOperation(addrInst[addr + 4 + offset], data, registers, addr + 4 + offset);
            }
            else {
                performOperation(addrInst[addr + 4], data, registers, addr + 4);
            }
        } break;
        case 5: {
            //BGTZ rs, offset
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rsPos = std::stoi(vec[0].substr(1), &sz);
            int offset = std::stoi(vec[1].substr(1), &sz);
            int a = registers[rsPos];
            writeSimulationFile(s, addr, data, registers);
            if (a > 0) {
                performOperation(addrInst[addr + 4 + offset], data, registers, addr + 4 + offset);
            }
            else {
                performOperation(addrInst[addr + 4], data, registers, addr + 4);
            }
        } break;

        case 6:
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
            simulationfile.close();
            break;
        case 7: {
            //SW rt, offset(base)
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rtPos = std::stoi(vec[0].substr(1), &sz);
            int offset = std::stoi(vec[1].substr(0, (vec[1].find_first_of('('))), &sz);
            std::string bs = vec[1].substr(vec[1].find_first_of('(') + 1, (vec[1].find_first_of(')') - vec[1].find_first_of('(') - 1));
            int base = std::stoi(bs.substr(1), &sz);
            int a = registers[base];
            data[a + offset] = std::to_string(registers[rtPos]);
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 8: {
            //LW rt, offset(base)
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rtPos = std::stoi(vec[0].substr(1), &sz);
            int offset = std::stoi(vec[1].substr(0, (vec[1].find_first_of('('))), &sz);
            std::string bs = vec[1].substr(vec[1].find_first_of('(') + 1, (vec[1].find_first_of(')') - vec[1].find_first_of('(') - 1));
            int base = std::stoi(bs.substr(1), &sz);
            int a = registers[base];
            int b = std::stoi(data[offset + a], &sz);
            registers[rtPos] = b;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 9: {
            //SLL rd, rt, sa
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int sa = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            registers[rdPos] = a << sa;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 10: {
            //SRL rd, rt, sa
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int sa = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            registers[rdPos] = (unsigned)a >> sa;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 11: {
            //SRA rd, rt, sa
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int sa = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            registers[rdPos] = (a < 0 && sa > 0) ? a >> sa | ~(~0U >> sa) : a >> sa;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 12:
            writeSimulationFile(s, addr, data, registers);
            break;
        case 13: {
            // res += "ADD "+rd+", "+rs+", "+rt;
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int rtPos = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            int b = registers[rtPos];
            long long c;
            c = (long long)a + b;
            if (c < INT_MIN || c > INT_MAX)
                break;
            registers[rdPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 14: {
            // res += "SUB "+rd+", "+rs+", "+rt;
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int rtPos = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            int b = registers[rtPos];
            long long c;
            c = (long long)a - b;
            if (c < INT_MIN || c > INT_MAX)
                break;
            registers[rdPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 15: {
            //verify multiplication overflow
            // res += "MUL "+rd+", "+rs+", "+rt;
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int rtPos = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            int b = registers[rtPos];
            long long c;
            c = (long long)a * b;
            if (c < INT_MIN || c > INT_MAX)
                break;
            registers[rdPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 16: {
            //AND rd, rs, rt
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int rtPos = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            int b = registers[rtPos];
            auto c = a & b;
            registers[rdPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 17: {
            //OR rd, rs, rt
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int rtPos = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            int b = registers[rtPos];
            auto c = a | b;
            registers[rdPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 18: {
            //XOR rd, rs, rt
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int rtPos = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            int b = registers[rtPos];
            auto c = a ^ b;
            registers[rdPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 19: {
            //NOR rd, rs, rt
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int rtPos = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            int b = registers[rtPos];
            auto c = !(a | b);
            registers[rdPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 20: {
            //SLT rd, rs, rt
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rdPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int rtPos = std::stoi(vec[2].substr(1), &sz);
            int a = registers[rsPos];
            int b = registers[rtPos];
            auto c = (a < b) ? 1 : 0;
            registers[rdPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 21: {
            //res += "ADDI "+rt+", "+rs+", #"+immediate;
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rtPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int a = registers[rsPos];
            int b = std::stoi(vec[2].substr(1), &sz);
            long long c;
            c = (long long)a + b;
            if (c < INT_MIN || c > INT_MAX)
                break;
            registers[rtPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 22: {
            //res += "ANDI "+rt+", "+rs+", #"+immediate;
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rtPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int a = registers[rsPos];
            int b = std::stoi(vec[2].substr(1), &sz);
            auto c = a & b;
            registers[rtPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 23: {
            //res += "ORI "+rt+", "+rs+", #"+immediate;
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rtPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int a = registers[rsPos];
            int b = std::stoi(vec[2].substr(1), &sz);
            auto c = a | b;
            registers[rtPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        case 24: {
            //res += "XORI "+rt+", "+rs+", #"+immediate;
            std::string ins = s.substr(spacePos + 1);
            std::vector<std::string> vec = split(ins, ", ");
            std::string::size_type sz; // alias of size_t
            int rtPos = std::stoi(vec[0].substr(1), &sz);
            int rsPos = std::stoi(vec[1].substr(1), &sz);
            int a = registers[rsPos];
            int b = std::stoi(vec[2].substr(1), &sz);
            auto c = a ^ b;
            registers[rtPos] = c;
            writeSimulationFile(s, addr, data, registers);
            performOperation(addrInst[addr + 4], data, registers, addr + 4);
        } break;
        default:
            return;
    }
}

void callRecursively(int addr, std::map<int, std::string>& addrInst)
{
    performOperation(addrInst[addr], data, registers, addr);
}

int main(int argc, char* argv[])
{
    populateCat1(cat1);
    maintainID(id);
    std::string input_file;
    if (argc > 1) {
        input_file = argv[1];
    }
    readFile(input_file); //"/Users/Jiya/Documents/UF/SEM3-Fall_2017/CAP/project/sample.txt"
    populateAddressInstr("disassembly.txt", addrInst);
    simulationfile.open("simulation.txt");
    callRecursively(256, addrInst);
    simulationfile.close();
    return 0;
}
