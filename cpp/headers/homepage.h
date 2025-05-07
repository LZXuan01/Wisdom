#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <vector>
#include <ctime>
#include <sstream>
#include <string>

struct Knowledge
{
    Rectangle dateButton;
    Rectangle timeButton;
    Rectangle editButton;
    Rectangle memoButton;
    std::string memoText;
    std::string date;
    std::string time;

    time_t GetTimestamp() const
    {
        std::tm tm = {0};
        std::istringstream dateStream(date + " " + time);

        // 解析日期（如 "25 December 03:45 PM"）
        dateStream >> tm.tm_mday;

        std::string monthStr;
        dateStream >> monthStr;

        // 将月份名称转换为数字（1-12）
        const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        for (int i = 0; i < 12; i++)
        {
            if (monthStr == months[i])
            {
                tm.tm_mon = i;
                break;
            }
        }

        // 解析时间
        int hour, minute;
        char ampm[3];
        dateStream >> hour >> minute >> ampm;

        // 转换为 24 小时制
        if (ampm[0] == 'P' && hour != 12)
            hour += 12;
        if (ampm[0] == 'A' && hour == 12)
            hour = 0;

        tm.tm_hour = hour;
        tm.tm_min = minute;

        // 假设当前年份（因为日期没有年份信息）
        time_t now = std::time(nullptr);
        tm.tm_year = localtime(&now)->tm_year;

        return mktime(&tm);
    }

    std::string Serialize() const
    {
        std::string text = memoText;
        // Replace all newlines with [new line]
        size_t pos = 0;
        while ((pos = text.find('\n', pos)) != std::string::npos)
        {
            text.replace(pos, 1, "[new line]");
            pos += 10; // length of "[new line]"
        }
        return text + "|" + date + "|" + time;
    }

    static Knowledge Deserialize(const std::string &data)
    {
        Knowledge k;
        size_t pos1 = data.find('|');
        size_t pos2 = data.find('|', pos1 + 1);

        if (pos1 != std::string::npos && pos2 != std::string::npos)
        {
            k.memoText = data.substr(0, pos1);
            // Replace all [new line] with newlines
            size_t pos = 0;
            const std::string newlineToken = "[new line]";
            while ((pos = k.memoText.find(newlineToken, pos)) != std::string::npos)
            {
                k.memoText.replace(pos, newlineToken.length(), "\n");
                pos += 1; // length of "\n"
            }

            k.date = data.substr(pos1 + 1, pos2 - pos1 - 1);
            k.time = data.substr(pos2 + 1);
        }
        return k;
    }
};


extern std::vector<Knowledge> KnowledgeGroup;
extern int currentKnowledgePage;
extern int currentEditButton;

void SortKnowledgeByTimeAscending();
void SaveKnowledgeData();
void LoadKnowledgeData();
void InitHomePage();
void UpdateHomePage();
void DrawHomePage();

#endif