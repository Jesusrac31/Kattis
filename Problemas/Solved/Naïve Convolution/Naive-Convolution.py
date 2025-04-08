line = input().split(" ")
n = int(line[0])
m = int (line[1])
line = input().split(" ")
pol1 = []
for i in line:
    pol1.append(int(i))

line = input().split(" ")
pol2 = []
for i in line:
    pol2.append(int(i))
    
polsol = []
for i in pol2:
    polsol.append(i*pol1[0])

for i in range(1, len(pol1)):
    for j in range(len(pol2)-1):
        polsol[len(polsol)-m+j+1]+=pol1[i]*pol2[j]
    polsol.append(pol1[i]*pol2[-1])

while(polsol[0] == 0 and len(polsol)>1):
    polsol.pop(0)
for i in polsol:
    print(i, end=" ")
print()