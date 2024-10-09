#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
//int quick(int a, int n) {
//    if (n == 0) {
//        return 1;
//    }
//    if (n % 2 == 1) {
//        return quick(a, n - 1) * a;
//    }
//    else {
//        return quick(a, n / 2) * quick(a, n / 2);
//    }
//}
class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long minTime = time[0];
        for (int i : time) {
            if (i < minTime){
                minTime = i;
            }
        }
        long long leftB = minTime - 1;
        long long rightB = minTime * totalTrips;
        long long mid;
        while (leftB <= rightB) {
            mid = (leftB + rightB) >> 1;
            int sum = 0;
            for (int i : time) {
                sum += (mid / i);
            }
            if (sum == totalTrips) { break; }
            else if (sum < totalTrips) {
                leftB = mid + 1;
            }else {
                cout <<"此时时间是"<<mid<< "  此时的出行次数是" << mid << endl;
                rightB = mid;
            }
        }
        return mid;
    }
};
int main() {
    //minimumTime()
    //int a;
    //cin >> a;
    ////cout<<"2^"<<a<<" = "<<quick(2,a)<<endl;
    //int result = 2;
    //while (a > 0) {
    //    cout << a << endl;
    //    if (a & 1) {//这也就意味着是奇数了
    //        result *= 2;
    //    }
    //    else {
    //        result *= result;
    //        a >>= 1;
    //    }
    //}
    //cout << a;
    vector<int> time = { 2 }; // 测试样例的时间数组
    int totalTrips = 1; // 测试样例的总行程数
    Solution solution;
    long long result = solution.minimumTime(time, totalTrips);
    cout << "Minimum Time: " << result << endl; // 打印最小时间
    return 0;
}