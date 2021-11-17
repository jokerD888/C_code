
//��ָ Offer 51. �����е������

//ʵ����merge�鲢���������
//�ڹ鲢�����У���Ҫ��p1 p2��ָԪ�ؽ��бȽϣ���nums[p1]>nums[p2]�Ƿ�����������������������������ںϲ�ǰ��Ȼ����
//nums[p1]>nums[p2]ʱ����ʱ[p1,mid]������Ԫ�ض����Ժ�p2��ָԪ���������ԣ����p2��help,p2++,���α�����ȥ
class Solution {
public:
    int mergeSort(vector<int>& nums, vector<int>& help, int L, int R) {
        //��Ȼ����ֱ�ӷ���
        if (L >= R)
            return 0;

        //ȡ�м�λ��
        int mid = L + ((R - L) >> 1);//ע��>>1�����ţ���,��>>���ȼ��ϵͣ���Ҫ������������������
        //���߷ֱ��ٹ鲢����
        int cnt = mergeSort(nums, help, L, mid) + mergeSort(nums, help, mid + 1, R);
        //�鲢
        int p1 = L, p2 = mid + 1, pos = L;
        while (p1 <= mid && p2 <= R) {
            cnt += nums[p1] > nums[p2] ? (mid-p1 + 1) : 0;
            help[pos++] = nums[p1] <= nums[p2] ? nums[p1++] : nums[p2++];
            //������ж�<= , =�����٣������ظ���ȣ�Ҳ����ð�p1��help,���p1++
        }
        while (p1 <= mid) {
            help[pos++] = nums[p1++];
        }
        while (p2 <= R) {
            help[pos++] = nums[p2++];
        }
        //�鲢��ԭ����
        for (int i = L; i <= R; i++) {
            nums[i] = help[i];
        }
        
        return cnt;
    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        //�������飬���ڹ鲢
        vector<int> help(n);
        return mergeSort(nums, help, 0, n - 1);
    }
};

//�ٽ�
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
