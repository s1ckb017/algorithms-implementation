'''
Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.

Given nums = [2, 7, 11, 15], target = 9,
Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
'''

class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        hashmap = {}
        for i in nums:
            if hashmap.get(i) is None:
                hashmap[i] = 0
            hashmap[i]+=1
        
        ret = [0, 0]
        for i in range(0,len(nums)):
            resto = target - nums[i]
            print("resto: " + str(resto) + " " + str(hashmap.get(resto)))
            if resto != nums[i] and hashmap.get(resto) is not None:
                ret[0]=i
                ret[1]=resto
                print(ret)
                break
            if resto == nums[i] and hashmap.get(resto) is not None and hashmap.get(resto) > 1:
                ret[0]=i
                ret[1]=resto
                break
        for i in range(0,len(nums)):
            if i != ret[0] and ret[1] == nums[i]:
                ret[1] = i
                break
        return ret
            
