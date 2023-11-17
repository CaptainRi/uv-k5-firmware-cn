#include "bits/stdc++.h"

using namespace std;
ifstream file("../name.txt"); // 替换成你的文件名或路径
ofstream outFile("../name_tmp.txt");
string names[1000];
unsigned char chinese[1000][2];
unsigned char english[1000];
bool en_flag[256] = {false};

int init_file() {
    int lines = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // 对读取的每一行执行操作，例如打印到控制台
            names[lines] = line;
            lines++;

        }

        file.close();
    } else {
        cout << "无法打开文件" << endl;
    }
    return lines;

}

bool sortByValue(const pair<array<unsigned char, 2>, int> &a, const pair<array<unsigned char, 2>, int> &b) {
    return a.second < b.second;
}

map<array<unsigned char, 2>, unsigned char> map_str;
map<array<unsigned char, 2>, unsigned char > all_code;

bool isGBKChineseCharacter(const string &str, size_t index) {
    // 检查GBK编码的字符是否为汉字
    if (index < str.size() - 1) {
        unsigned char firstByte = static_cast<unsigned char>(str[index]);
        unsigned char secondByte = static_cast<unsigned char>(str[index + 1]);
        if (firstByte >= 0x81 && firstByte <= 0xFE &&
            ((secondByte >= 0x40 && secondByte <= 0x7E) || (secondByte >= 0x80 && secondByte <= 0xFE))) {
            return true;
        }
    }
    return false;
}
void removeNullStrings(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream input(inputFile, std::ios::binary);
    std::ofstream output(outputFile, std::ios::binary);

    if (!input.is_open()) {
        std::cerr << "Unable to open input file" << std::endl;
        return;
    }

    if (!output.is_open()) {
        std::cerr << "Unable to open output file" << std::endl;
        return;
    }

    std::string buffer;
    while (getline(input, buffer)) {
        size_t found = buffer.find("\\x00");
        while (found != std::string::npos) {
            buffer.erase(found, 4); // Erase 4 characters starting from found position
            found = buffer.find("\\x00", found);
        }
        output << buffer << std::endl;
    }

    input.close();
    output.close();
}

int main() {
    int num_names = init_file();
   // cout << num_names << endl;

    int num_chinese = 0;
    int num_english = 0;
    if (!outFile.is_open()) {
        return -5;
    }
    // 写入内容到文件


//        // 关闭文件流
//    outFile << "Hello, this is some text.\n";
//    outFile << "This is a new line.";

    for (int i = 0; i < num_names; i++) {


        for (size_t j = 0; j < names[i].size(); ++j) {
            if (isGBKChineseCharacter(names[i], j)) {

                array<unsigned char, 2> tmp = {0};
                tmp[0] = names[i][j];
                tmp[1] = names[i][j + 1];

                if (map_str.find(tmp) != map_str.end()) {
                } else {
                    // 如果不在映射中，添加新的键并设置出现次数为1
                    map_str[tmp] = num_chinese;
                    //   cout<<num_chinese<<":"<<tmp[0]<< tmp[1]<<endl;

                    chinese[num_chinese][0] = tmp[0];
                    chinese[num_chinese][0] = tmp[1];
                    //   outFile <<"\\x"<< hex << setw(2) << setfill('0') << uppercase <<  num_chinese << endl;

                    num_chinese++;
                }
                j++; // 跳过下一个字节，因为汉字占两个字节

            } else {

                if (en_flag[names[i][j]]) {

                } else {
                    //         如果不在映射中，添加新的键并设置出现次数为1
                    en_flag[names[i][j]] = true;
                    english[num_english] = names[i][j];
                    num_english++;
                }
            }
        }
    }




    // outFile <<"\\x"<< hex << setw(2) << setfill('0') << uppercase <<   map_str[tmp] << endl;



    vector<pair<array<unsigned char, 2>, int>> vec(map_str.begin(), map_str.end());

    // 使用自定义的比较函数按值排序
    sort(vec.begin(), vec.end(), sortByValue);
    en_flag['\n']= true;

    for(int i='!';i<='~';i++)
{
    en_flag[i]= true;
}
    // 输出排序后的键值对
    int now_code = 1;
    for (const auto &pair: vec) {
        //cout << "{" << static_cast<int>(pair.first[0]) << ", " << static_cast<int>(pair.first[1]) << "} : " << pair.second << endl;
        array<unsigned char, 2> tmp = {0};
        tmp[0] = pair.first[0];
        tmp[1] = pair.first[1];
        map_str[tmp] = now_code;
        while (en_flag[map_str[tmp]]) {
            cout << (char)map_str[tmp] << ":"<<(int)map_str[tmp] << endl;
            array<unsigned char, 2> tmp1;
            tmp1[0]=5;
            tmp1[1]=map_str[tmp];
            all_code[tmp1]=map_str[tmp];
            map_str[tmp] += 1;
            now_code++;
        }
        array<unsigned char, 2> tmp1;
        tmp1[0]=tmp[0];
        tmp1[1]=tmp[1];
        all_code[tmp1]=map_str[tmp];

        now_code++;
        cout << tmp[0] << tmp[1] <<  ":"<<(int)map_str[tmp] << endl;
    }
    for (int i = 0; i < num_names; i++) {
        for (size_t j = 0; j < names[i].size(); ++j) {
            if (isGBKChineseCharacter(names[i], j)) {

                array<unsigned char, 2> tmp = {0};
                tmp[0] = names[i][j];
                tmp[1] = names[i][j + 1];
                outFile <<"\\x"<< hex << setw(2) << setfill('0') << uppercase << (int)  all_code[tmp] ;

            }else
            {
                array<unsigned char, 2> tmp = {0};
                tmp[0] = 5;
                tmp[1] = names[i][j ];
                outFile <<"\\x"<< hex << setw(2) << setfill('0') << uppercase << (int) all_code[tmp] ;
            }

        }

        outFile<<endl;
    }
    cout<<"code ok"<<endl;
    outFile.close();

    std::string inputFile = "../name_tmp.txt"; // Replace with your input file name
    std::string outputFile = "../name_out.txt"; // Replace with your output file name

    removeNullStrings(inputFile, outputFile);

    std::cout << "Null strings removed from the file." << std::endl;
//int sum=0;
//    for (const auto &pair: vec) {
//        array<unsigned char, 2> tmp = {0};
//        tmp[0] = pair.first[0];
//        tmp[1] = pair.first[1];
//        if (tmp[0]==5)
//        {
//
//      sum+= ( all_code[tmp]-tmp[1]);
//        }else
//        {
//            sum+= (int )(all_code[tmp]-map_str[tmp]);
//
//        }
//    }
//    cout<<sum<<endl;
    cout << num_chinese << endl;
    cout << num_english << endl;
}



