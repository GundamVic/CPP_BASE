#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        int n = ratings.size();
        int sum = 0;
        vector<int> candies(n, 1);
        for (int i = 1; i < n; i++)
        {
            if (ratings[i] > ratings[i - 1])
            {
                candies[i] = candies[i - 1] + 1;
            }
        }
        sum += candies[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
            {
                candies[i] = max(candies[i + 1] + 1, candies[i]);
            }
            sum += candies[i];
        }
        return sum;
    }

    // int trap(vector<int> &height)
    // {
    //     int n = height.size();
    //     int sum_rain = 0;
    //     for (int i = 1; i < n - 1; i++)
    //     {
    //         int right_max = 0;
    //         int left_max = 0;
    //         for (int j = i + 1; j < n; j++)
    //         {
    //             right_max = max(height[j], right_max);
    //         }
    //         for (int j = i - 1; j >= 0; j--)
    //         {
    //             left_max = max(height[j], left_max);
    //         }
    //         sum_rain += max((min(left_max, right_max) - height[i]), 0);
    //     }
    //     return sum_rain;
    // }

    int trap(vector<int> &height)
    {
        int n = height.size();
        int sum_rain = 0;

        vector<int> left_max(n);
        vector<int> right_max(n);

        for (int i = 1; i < n - 1; i++)
        {
            left_max[i] = max(left_max[i - 1], height[i - 1]);
        }

        for (int i = n - 2; i > 0; i--)
        {
            right_max[i] = max(right_max[i + 1], height[i + 1]);
        }

        for (int i = 1; i < n - 1; i++)
        {
            sum_rain += max(min(left_max[i], right_max[i]) - height[i], 0);
        }

        return sum_rain;
    }

    int romanToInt(string s)
    {
        unordered_map<char, int> roman_int_map = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}};

        int sum = 0;

        for (int i = 0; i < s.size(); i++)
        {

            if ((i < s.size() - 1) && (roman_int_map[s[i]] < roman_int_map[s[i + 1]]))
            {
                sum += (roman_int_map[s[i + 1]] - roman_int_map[s[i]]);
                i++;
            }
            else
            {
                sum += roman_int_map[s[i]];
            }
        }
    }

    string intToRoman(int num)
    {
        vector<pair<int, string>> valueSymbols = {
            {1000, "M"},
            {900, "CM"},
            {500, "D"},
            {400, "CD"},
            {100, "C"},
            {90, "XC"},
            {50, "L"},
            {40, "XL"},
            {10, "X"},
            {9, "IX"},
            {5, "V"},
            {4, "IV"},
            {1, "I"}};
        string roman = "";
        for (const auto &[value, symbol] : valueSymbols)
        {
            while (value <= num)
            {
                roman += symbol;
                num -= value;
                if (num == 0)
                {
                    break;
                }
            }
        }

        return roman;
    }

    int lengthOfLastWord(string s)
    {
        int length = 0;
        int i = s.length() - 1;
        while (i >= 0 && s[i] == ' ')
        {
            i--;
        }
        while (i >= 0 && s[i] != ' ')
        {
            length++;
            i--;
        }
        return length;
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.empty())
        {
            return "";
        }
        for (int i = 0; i < strs[0].length(); i++)
        {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); j++)
            {
                if (i >= strs[j].length() || c != strs[j][i])
                {
                    return strs[0].substr(0, i);
                }
            }
        }
        return strs[0];
    }

    string s = "A man, a plan, a canal: Panama";

    bool isPalindrome(string s)
    {
        // 预处理字符串
        string filtered;
        for (char c : s)
        {
            if (isalnum(c))
            {
                filtered += tolower(c);
            }
        }
        if (filtered.length() == 0)
        {
            return false;
        }
        int left = 0;
        int right = filtered.length() - 1;
        while (left < right)
        {
            if (filtered[left] != filtered[right])
            {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    bool isSubsequence(string s, string t)
    {
        int s_p = 0;
        int t_p = 0;
        if (s.length() == 0)
        {
            return true;
        }
        while (t_p < t.length())
        {
            if (t[t_p] == s[s_p])
            {
                s_p++;
                if (s_p == s.length())
                {
                    return true;
                }
            }
            t_p++;
        }
        return false;
    }

    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right)
        {
            if (numbers[left] + numbers[right] == target)
            {
                return {left + 1, right + 1};
            }
            else if (numbers[left] + numbers[right] > target)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
    }
};

int main()
{
    vector<int> ratings = {1, 0, 2};
    string s = "MCMXCIV";
    int num = 3749;
    Solution sol;
    std::cout << sol.candy(ratings) << std::endl;
    std::cout << sol.romanToInt(s) << std::endl;
    std::cout << sol.intToRoman(num) << std::endl;
    return 0;
}