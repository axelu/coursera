def find_index_low(arr, start, end, t):
    # Where to insert a value
    if end == start:
        if arr[start] > t:
            return start
        else:
            return start+1
        
    mid = int((end+start)/2)
    center = arr[mid]
    
    if t > center:
        return find_index_low(arr, mid+1, end, t)
    else:
        return find_index_low(arr, start, mid, t)




file = "algo1-programming_prob-2sum.txt"

_arr = [int(i) for i in open(file, "r").readlines()]
arr = sorted(_arr)

c = 10000
n=len(arr)-1
mySum = {}
count = 0
for x in arr:
    mySet = set()
    
    #print ("for",x, "find a num between",-c-x, c-x)
    i_low = find_index_low(arr, 0, n, -c - x)    
    i_up = find_index_low(arr, 0, n, c - x)
    
    mylist = arr[i_low:i_up]
        
    if x in mylist:
        mylist.remove(x)
    
    for m in mylist:
        mySum[x+m] = True
        
print (len(mySum.items()))
