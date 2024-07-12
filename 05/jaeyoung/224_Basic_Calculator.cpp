class Solution {
   public:
    int calculate(string s) {
        int result = 0, temp = 0, sign = 1;
        stack<int> stack({sign});

        for (char c : s) {
            if (isdigit(c))
                temp = temp * 10 + (c - '0');
            else if (c == '(')
                stack.push(sign);
            else if (c == ')')
                stack.pop();
            else if (c == '+' || c == '-') {
                result += sign * temp;
                sign = (c == '+' ? 1 : -1) * stack.top();
                temp = 0;
            }
        }
        result += sign * temp;

        return result;
    }
};