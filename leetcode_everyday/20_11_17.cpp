
//剑指 Offer 51. 数组中的逆序对

//实际是merge归并排序的延申
//在归并过程中，需要对p1 p2所指元素进行比较，当nums[p1]>nums[p2]是符合逆序对条件，且由于左右区间在合并前已然有序，
//nums[p1]>nums[p2]时，此时[p1,mid]中所有元素都可以和p2所指元素组成逆序对，随后将p2入help,p2++,依次遍历下去
class Solution {
public:
    int mergeSort(vector<int>& nums, vector<int>& help, int L, int R) {
        //以然有序，直接返回
        if (L >= R)
            return 0;

        //取中间位置
        int mid = L + ((R - L) >> 1);//注意>>1的括号（）,因>>优先级较低，需要（）来进行优先运算
        //两边分别再归并排序
        int cnt = mergeSort(nums, help, L, mid) + mergeSort(nums, help, mid + 1, R);
        //归并
        int p1 = L, p2 = mid + 1, pos = L;
        while (p1 <= mid && p2 <= R) {
            cnt += nums[p1] > nums[p2] ? (mid-p1 + 1) : 0;
            help[pos++] = nums[p1] <= nums[p2] ? nums[p1++] : nums[p2++];
            //这里得判断<= , =不能少，若有重复相等，也必须得把p1入help,随后p1++
        }
        while (p1 <= mid) {
            help[pos++] = nums[p1++];
        }
        while (p2 <= R) {
            help[pos++] = nums[p2++];
        }
        //归并到原数组
        for (int i = L; i <= R; i++) {
            nums[i] = help[i];
        }
        
        return cnt;
    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        //帮助数组，用于归并
        vector<int> help(n);
        return mergeSort(nums, help, 0, n - 1);
    }
};

//官解
class Solution {
public:
    int mergeSort(vector<int>& nums, vector<int>& tmp, int l, int r) {
        if (l >= r) {
            return 0;
        }

        int mid = (l + r) / 2;
        int inv_count = mergeSort(nums, tmp, l, mid) + mergeSort(nums, tmp, mid + 1, r);
        int i = l, j = mid + 1, pos = l;
        while (i <= mid && j <= r) {
            if (nums[i] <= nums[j]) {
                tmp[pos] = nums[i];
                ++i;
                inv_count += (j - (mid + 1));
            }             else {
                tmp[pos] = nums[j];
                ++j;
            }
            ++pos;
        }
        for (int k = i; k <= mid; ++k) {
            tmp[pos++] = nums[k];
            inv_count += (j - (mid + 1));
        }
        for (int k = j; k <= r; ++k) {
            tmp[pos++] = nums[k];
        }
        copy(tmp.begin() + l, tmp.begin() + r + 1, nums.begin() + l);
        return inv_count;
    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> tmp(n);
        return mergeSort(nums, tmp, 0, n - 1);
    }
};
