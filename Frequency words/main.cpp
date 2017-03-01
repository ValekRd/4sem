#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <locale>
#include <vector>

std::string prepare (const std::string& s);

struct Statistics
{
    int count;
    std::string word;
};

bool compare (const Statistics& lhs, const Statistics& rhs);

int main () {
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
                map[word] = 1;
            }
            else
            {
                it->second++;
            }
        }

        std::vector<Statistics> s (map.size());
        int i = 0;
        for (auto& item : map)
        {
            s[i].word = item.first;
            s[i].count = item.second;
            i++;
        }
        std::sort (s.begin(), s.end(), compare);

        for (int j = 0; j < s.size(); ++j)
        {
            std::cout << s[j].word << std::endl;
        }

        file.close();
    }

    return 0;
}

bool compare (const Statistics& lhs, const Statistics& rhs)
{
    return lhs.count > rhs.count;
}

std::string prepare (const std::string& s)
{
    std::string result = s;
    std::transform(s.begin(), s.end(), result.begin(), ::tolower);

    if (ispunct(s.back()))
    {
        result.pop_back();
    }

    return result;
}