#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <locale>
#include <vector>

std::string prepare(const std::string& s);

int main() {
    std::ifstream file("file.txt");

    if (file.is_open())
    {
        std::map <std::string, int> map;
        std::map <std::string, int>::iterator it;
        std::string word;
        while (!file.eof())
        {
            file >> word;
            word = prepare(word);
            it = map.find(word);
            if (it == map.end())
            {
                map.insert(std::pair <std::string, int>(word, 1));
            }
            else
            {
                map.find(word)->second++;
            }
        }

        struct Statistics
        {
            int count;
            std::string word;
        };

        struct Statistics_more : public std::binary_function<Statistics, Statistics, bool>
        {
            bool operator()(const Statistics& s1, const Statistics& s2) const
            { return s1.count > s2.count; };
        };

        std::vector<Statistics> s(map.size());
        int i = 0;
        for (auto& item : map)
        {
            s[i].word = item.first;
            s[i].count = item.second;
            i++;
        }
        std::sort(s.begin(), s.end(), Statistics_more());

        for (int j = 0; j < s.size(); ++j)
        {
            std::cout << s[j].word << std::endl;
        }

        file.close();
    }

    return 0;
}

std::string prepare(const std::string& s)
{
    std::string result = s;
    std::transform(s.begin(), s.end(), result.begin(), ::tolower);

    if (s[s.length() - 1] == '.' || s[s.length() - 1] == ',' ||
        s[s.length() - 1] == '?' || s[s.length() - 1] == '!')
    {
        result.pop_back();
    }

    return result;
}