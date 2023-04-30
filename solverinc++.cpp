#include <bits/stdc++.h>

using namespace std;

vector<string> generate_strings(vector<int> &nums, int i, int j)
{
    vector<string> res;
    if (i == j)
    {
        res.push_back(to_string(nums[i]));
        return res;
    }
    for (int k = i; k < j; k++)
    {
        vector<string> left = generate_strings(nums, i, k);
        vector<string> right = generate_strings(nums, k + 1, j);
        for (auto &l : left)
        {
            for (auto &r : right)
            {
                res.push_back("(" + l + "+" + r + ")");
                res.push_back("(" + l + "-" + r + ")");
                res.push_back("(" + l + "*" + r + ")");
                if (r != "0")
                {
                    res.push_back("(" + l + "/" + r + ")");
                }
            }
        }
    }
    return res;
}

// Function to solve mathematical operations
// Function to solve mathematical operations
float solve(float num1, float num2, char op)
{
    float result;
    if (op == '+')
        result = num1 + num2;
    else if (op == '-')
        result = num1 - num2;
    else if (op == '*')
        result = num1 * num2;
    else if (op == '/')
        result = num1 / num2;
    else
        result = 0;

    if (result<0||floor(result) != result)
    {
        // Return flag value indicating expression should be skipped
        // cout<<num1<<" "<<op<<" "<<num2<<"\n";
        return numeric_limits<float>::quiet_NaN();
    }

    return result;
}

// Function to solve brackets and mathematical operations
// Function to solve brackets and mathematical operations
float solveString(string str)
{
    int n = str.length();
    stack<float> nums;
    stack<char> ops;

    for (int i = 0; i < n; i++)
    {
        // If character is an opening bracket
        if (str[i] == '(')
        {
            ops.push(str[i]);
        }
        // If character is a number
        else if (isdigit(str[i]))
        {
            float num = 0;
            while (i < n && (isdigit(str[i]) || str[i] == '.'))
            {
                if (str[i] == '.')
                {
                    i++;
                    int decimal = 10;
                    while (i < n && isdigit(str[i]))
                    {
                        num += (str[i] - '0') / (float)decimal;
                        decimal *= 10;
                        i++;
                    }
                }
                else
                {
                    num = num * 10 + (str[i] - '0');
                    i++;
                }
            }
            i--;
            nums.push(num);
        }
        // If character is an operator
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            while (!ops.empty() && (ops.top() == '*' || ops.top() == '/') && nums.size() >= 2)
            {
                float num2 = nums.top();
                nums.pop();
                float num1 = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();
                float res = solve(num1, num2, op);
                if (isnan(res))
                {
                    // Return NaN to indicate that expression should be skipped
                    return res;
                }
                nums.push(res);
            }
            ops.push(str[i]);
        }
        // If character is a closing bracket
        else if (str[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(' && nums.size() >= 2)
            {
                float num2 = nums.top();
                nums.pop();
                float num1 = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();
                float res = solve(num1, num2, op);
                if (isnan(res))
                {
                    // Return NaN to indicate that expression should be skipped
                    return res;
                }
                nums.push(res);
            }
            ops.pop();
        }
    }

    while (!ops.empty() && nums.size() >= 2)
    {
        float num2 = nums.top();
        nums.pop();
        float num1 = nums.top();
        nums.pop();
        char op = ops.top();
        ops.pop();
        float res = solve(num1, num2, op);
        if (isnan(res))
        {
            // Return NaN to indicate that expression should be skipped
            return res;
        }
        nums.push(res);
    }

    if (nums.size() == 1)
    {
        return nums.top();
    }

    // Return NaN to indicate that expression should be skipped
    return NAN;
}

int main()
{
    vector<int> numsorg = {3, 5, 9, 13, 19, 25};
    int target = 477;
    int found = 0;
    sort(numsorg.begin(), numsorg.end()); // sort the input vector in ascending order

    vector<vector<int>> permutations; // create an empty vector of vectors

    do
    {
        permutations.push_back(numsorg);                     // push the current permutation into the vector of vectors
    } while (next_permutation(numsorg.begin(), numsorg.end())); // generate the next lexicographically greater permutation

    // print the vector of vectors
    for (auto &nums : permutations)
    {
        vector<string> res = generate_strings(nums, 0, nums.size() - 1);
        for (auto &s : res)
        {
            float result = solveString(s);
            if (result == target)
            {
                cout << s << "\n";
                found = 1;
            }
        }
    }
    if (!found)
    {
        cout << "can't get target value\n";
    }
    return 0;
}
