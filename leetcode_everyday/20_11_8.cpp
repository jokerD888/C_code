//299. ²ÂÊı×ÖÓÎÏ·
#include<string>
class Solution {
public:
    string getHint(string secret, string guess) {
        int a = 0;
        int sarr[10] = { 0 };
        int garr[10] = { 0 };

        for (int i = 0; i < secret.size(); i++) {
            if (secret[i] == guess[i])
                a++;
            else {
                sarr[secret[i] - '0']++;
                garr[guess[i] - '0']++;
            }
        }
        int b = 0;
        for (int i = 0; i < 10; i++) {
            b += min(sarr[i], garr[i]);
        }
        return to_string(a) + "A" + to_string(b) + "B";
    }
};
