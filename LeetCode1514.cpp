class Solution{
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;
        int longest = 2;
        vector<vector<int>> dp(n, vector<int>(1002, 1));
        for (int i = 0; i < n; i++) {
            int diff = nums[i] - nums[j] + 501;
            dp[i][diff] = dp[j][diff] + 1;
            longest = max(longest, dp[i][diff])
        }
    }
}