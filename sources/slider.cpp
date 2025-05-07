#include <ctime>
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "main.h"
#include "font.h"
#include "color.h"
#include "sound.h"
#include "slider.h"

#include "knowledgepage.h"

// 不要修改下面的值
float fontSize = 60 / ppi                             ; // 字体大小
float optionSpacing = 45 / ppi                        ; // 字体之间的额外空隙
float optionHeight = (fontSize + optionSpacing) / ppi ; // 每个选项的高度

float snapZone     = screenHeight / 2 - optionHeight/2;// 滑块对齐的区域
float snapThreshold= 60 / ppi                         ;// 对齐的阈值
float snapSpeed    = 0.01 / ppi                       ;// 对齐的速度

Slider Date , Hour , Minute , AmAndPm ;
std::string UserdateStr;
std::string UsertimeStr;

int GetDaysInMonth(int month, int year)
{
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    if (month == 2)
    {

        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            return 29; // 闰年的2月是29日
        }
        return 28; // 不然就是28日
    }
    return 31;
}

void InitSliders()
{
    fontSize = 60 / ppi                               ; // 字体大小
    optionSpacing = 45 / ppi                          ; // 字体之间的额外空隙
    optionHeight = (fontSize + optionSpacing) / ppi    ; // 每个选项的高度

    snapZone = screenHeight * 0.80f - optionHeight / 2; // 滑块对齐的区域
    snapThreshold = 1000.0f / ppi                     ; // 对齐的阈值
    snapSpeed = 0.01f / ppi                           ; // 对齐的速度

    time_t now = time(nullptr)                        ; // 获取当前时间
    tm *currentTime = localtime(&now)                 ; // 转换为本地时间

    int currentYear = currentTime->tm_year + 1900     ; // 当前年份
    int currentMonth = currentTime->tm_mon + 1        ; // 当前月份
    int currentDay = currentTime->tm_mday             ; // 当前日期
    int currentHour = currentTime->tm_hour % 12;
    if (currentHour == 0) currentHour = 12;
    currentHour -= 1;
    int currentMinute = currentTime->tm_min           ; // 当前分钟
    bool isPm = currentTime->tm_hour >= 12            ; // 是否是PM


    Date.type = SliderType::DATE;
    Hour.type = SliderType::HOUR;
    Minute.type = SliderType::MINUTE;
    AmAndPm.type = SliderType::AMPM;

    const char *months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; // 月份名称

    int index = 0; // 选项索引
    int indexOfToday = 0; // 用于记录“Today”的正确索引

    for (int m = 1; m <= 12; m++) 
    {
        int days = GetDaysInMonth(m, currentYear);
        for (int d = 1; d <= days; d++) 
        {
            std::string label;
            if (m == currentMonth && d == currentDay) 
            {
                label = "Today";
                indexOfToday = index; // 记录正确索引
            } 
            else 
            {
                label = std::to_string(d) + " " + months[m - 1];
            }
            index++;
        }
    }
    
    // 第二次填充数据，并设置 yPos 基于 indexOfToday
    index = 0;
    for (int m = 1; m <= 12; m++) 
    {
        int days = GetDaysInMonth(m, currentYear);
        for (int d = 1; d <= days; d++) 
        {
            std::string label;
            if (m == currentMonth && d == currentDay) 
            {
                label = "Today";
                Date.selectedIndex = index; // 正确设置选中索引
            } 
            else 
            {
                label = std::to_string(d) + " " + months[m - 1];
            }
    
            float yPos = snapZone - (index - indexOfToday) * optionHeight;
            Date.options.push_back({label, yPos});
            index++;
        }
    }

    index = 0;
    for (int h = 1; h <= 12; h++) // 遍历每个小时
    {
        std::string label = (h < 10 ? "0" : "") + std::to_string(h); // 格式化小时，如 "01", "02", ..., "12"

        float yPos = snapZone - (index - currentHour) * optionHeight; // 计算选项的 y 坐标
    
        Hour.options.push_back({label, yPos}); // 添加选项到小时滑块
        if (h == currentHour) Hour.selectedIndex = index; // 如果是当前小时，设置为选中索引

        index++; // 增加索引
    }

    index = 0;
    for (int m = 0; m < 60; m++) // 遍历每一分钟
    {
        std::string label = (m < 10 ? "0" : "") + std::to_string(m); // 格式化分钟，如 "01", "02", ..., "59"

        float yPos = snapZone - (index - currentMinute) * optionHeight; // 计算选项的 y 坐标

        Minute.options.push_back({label, yPos}); // 添加选项到分钟滑块
        if (m == currentMinute) Minute.selectedIndex = index; // 如果是当前分钟，设置为选中索引

        index++; // 增加索引
    }

    index = 0;
    AmAndPm.options.push_back({"AM", snapZone - (index) * optionHeight}); // 添加AM选项
    AmAndPm.options.push_back({"PM", snapZone - (index + 1) * optionHeight}); // 添加PM选项
    AmAndPm.selectedIndex = isPm ? 1 : 0; // 根据当前时间设置AM/PM选中状态
    AmAndPm.startY = snapZone; // 确保AM/PM滑块位于可见区域


    Date.xPosition    = screenWidth * 0.15f; // 设置滑块的 x 坐标
    Hour.xPosition    = screenWidth * 0.45f; // 设置小时滑块的 x 坐标
    Minute.xPosition  = screenWidth * 0.65f;
    AmAndPm.xPosition = screenWidth * 0.85f;

}

void UpdateSlider(Slider &slider)
{
    if (IsDrawSliders)
    {
        // 如果是 AmAndPm 滑块，不允许循环
        
        bool isAmAndPmSlider = (slider.type == SliderType::AMPM);

        // 如果鼠标左键按下且鼠标在滑动条区域内
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && GetMouseX() > (slider.xPosition - screenWidth * 0.05f ) && GetMouseX() < (slider.xPosition + MeasureText(slider.options[1].text.c_str(), fontSize) + screenWidth * 0.05f))
        {
            if (slider.dragging == false)
            {
                slider.dragging = true;      // 设置拖动状态 = true
                slider.startY = GetMouseY(); // 记录鼠标的初始Y位置
            }

            snapSpeed = 0.002f; // 如果正在滑动，吸附感更改

            float deltaY = GetMouseY() - slider.startY; // 计算鼠标的移动距离
            slider.startY = GetMouseY();                // 更新鼠标的Y位置
            slider.velocity = deltaY;                   // 更新滑动条的速度

            for (auto &option : slider.options)         // 更新所有选项的Y坐标
            {
                option.y += deltaY;
            }

        }
        else // 如果鼠标未按下
        {
            slider.dragging = false;            // 拖动状态 = 否
            snapSpeed = 0.5f;                   // 恢复正常速度

            for (auto &option : slider.options) // 更新所有选项的Y坐标
            {
                option.y += slider.velocity;
            }

            slider.velocity *= 0.9f; // 模拟摩擦 越大值滑动越快
  
        }


        if (!isAmAndPmSlider)
        {
            // 处理循环滚动（滑动条的选项可以在顶部和底部循环）
            float totalHeight = slider.options.size() * optionHeight;
            for (auto &option : slider.options)
            {
                if (option.y < snapZone - totalHeight / 2)
                { // 如果选项超出了上边界，则将其移动到下边界
                    option.y += totalHeight;
                }
                else if (option.y > snapZone + totalHeight / 2)
                { // 如果选项超出了下边界，则将其移动到上边界
                    option.y -= totalHeight;
                }
            }

        }

        // 查找最接近吸附点的选项
        float minDistance = screenHeight;
        float closestOffset = 0;
        int   closestIndex = 0;

        for (size_t i = 0; i < slider.options.size(); i++)
        {
            float distance = std::fabs(slider.options[i].y - snapZone); // 计算与吸附点的距离
            if (distance < minDistance)
            { // 如果当前选项更接近吸附点
                minDistance = distance;
                closestOffset = snapZone - slider.options[i].y;
                closestIndex = i;
            }
        }

        // 如果距离足够接近吸附点，则吸附到该位置
        if (std::fabs(closestOffset) < snapThreshold)
        {
            for (auto &option : slider.options)
            {
                option.y += closestOffset * snapSpeed; // 将选项移动到吸附点
            }

            slider.selectedIndex = closestIndex; // 更新选中的选项索引
        }
    }  
    
}

void DrawSlider(const Slider &slider)
{
    float totalHeight = slider.options.size() * optionHeight;

    // 如果是AM/PM滑块，只绘制一次
    if (slider.type == SliderType::AMPM)
    {
        for (size_t i = 0; i < slider.options.size(); i++)
        {
            DrawTextEx(LBRITED , slider.options[i].text.c_str(), {slider.xPosition, slider.options[i].y + 15}, fontSize, 0 ,Cream);
        }
    }
    else
    {
        // 绘制其他类型滑块的循环选项
        for (size_t i = 0; i < slider.options.size(); i++) \
        {
            float yPos = slider.options[i].y;

            // 绘制原始位置的选项
            DrawTextEx(LBRITED , slider.options[i].text.c_str(), {slider.xPosition , yPos + 15}, fontSize, 0 , Cream);

            // 绘制向上循环的选项
            float wrappedUp = yPos + totalHeight;
            DrawTextEx(LBRITED , slider.options[i].text.c_str(), {slider.xPosition , wrappedUp + 15}, fontSize, 0 , Cream);

            // 绘制向下循环的选项
            float wrappedDown = yPos - totalHeight;
            DrawTextEx(LBRITED , slider.options[i].text.c_str(), {slider.xPosition , wrappedDown + 15}, fontSize , 0 , Cream);
        }
    }

}

void UpdateSliders()
{
    UpdateSlider(Date);
    UpdateSlider(Hour);
    UpdateSlider(Minute);
    UpdateSlider(AmAndPm);
}

void DrawSliders()
{
    UserdateStr = Date.options[Date.selectedIndex].text ;
    UsertimeStr= Hour.options[Hour.selectedIndex].text + ":" + Minute.options[Minute.selectedIndex].text + " " + AmAndPm.options[AmAndPm.selectedIndex].text;

    if (IsDrawSliders)
    {
        DrawRectangleRounded({screenWidth * 0.04f , screenHeight * 0.65f , screenWidth * 0.92f , screenHeight * 0.33f }, 0.09f , 38 , HomeButtonColor);
        BeginScissorMode( 0 , screenHeight * 0.712f , screenWidth , screenHeight * 0.1725f);
        DrawRectangleRoundedLinesEx({screenWidth * 0.05f , snapZone , screenWidth * 0.90f , screenHeight * 0.04f} , 0.5f , 38 , 3 / ppi , Cream);
        DrawSlider(Date);
        DrawSlider(Hour);
        DrawSlider(Minute);
        DrawSlider(AmAndPm);
    
        EndScissorMode();
    }
}
