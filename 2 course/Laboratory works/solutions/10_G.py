import sys
 
sc = open("euler.in", "r")
pr = open("euler.out", "w")
 
#sc = open("input.txt", "r")
#pr = open("output.txt", "w")
 
n = int(sc.readline())
g=[]
g.append([0] * 1002)
cnt_odd = 0
start = 1
 
cnt = []
for i in range(1002):
    cnt.append([0] * 1002)
 
for i in range(n) :
    line = sc.readline()
    g.append(list(map(int, line.split())))
    g[i + 1].pop(0)
    if (len(g[i + 1]) % 2 != 0): 
        cnt_odd = cnt_odd + 1
        start = i + 1
    for to in g[i + 1]:
        cnt[min(i + 1, to)][max(i + 1, to)] += 1
         
 
if (cnt_odd >= 3) :
    pr.write("-1")
else:
    path = []
    #dfs(start)
    stack = []
    stack.append(start)
    while len(stack) != 0:
        v = stack[-1]
        to = v 
        while (len(g[v]) > 0) and (cnt[min(v, to)][max(v, to)] < 2):
            to = g[v].pop()
        if (cnt[min(v, to)][max(v, to)] < 2):
            path.append(v)
            stack.pop()
        else:
            stack.append(to)
            cnt[min(v, to)][max(v, to)] -= 2
    pr.write("%d\n" % (len(path) - 1))
    for v in path:
        pr.write("%d " %  v)
 
sc.close();
pr.close();
