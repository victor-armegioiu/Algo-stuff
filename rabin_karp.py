# https://leetcode.com/problems/longest-duplicate-substring/

from functools import reduce
from math import log 

class Solution:    
    def check(self, l, a):
        mod = 2 ** 63 - 1
        max_pow = pow(26, l - 1, mod)
        
        h = reduce(lambda x, y: (x * 26 + y) % mod, a[:l], 0)
        cache = set([h])
        
        for i in range(l, len(a)):
            h = (h - a[i - l] * max_pow) % mod
            h = (h * 26 + a[i]) % mod
            
            if h in cache:
                return i - l + 1
            cache.add(h)
            
    def longestDupSubstring(self, S: str) -> str:
        a = [ord(c) - ord('a') for c in S]
        l, r = 0, len(S) - 1
        ans = ''
        
        while l < r:
            mid = (l + r + 1) // 2
            pos = self.check(mid, a)
            
            if pos:
                ans = S[pos:pos + mid]
                l = mid
            else:
                r = mid - 1
    
        return ans
                