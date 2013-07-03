Bugfree-OBST!
=============

    procedure OBST(P,Q,n)
        //给定n个标识符a1＜a2＜…＜an。已知成功检索的概率P(i),不成功检索概率Q(i),    0≤i≤n。算法对于标识符ai+1,…,aj计算最优二分检索树Tij的成本C(i,j)、根 R(i,j)、权W(i,j) //
        real P(1:n),Q(1:n),C(0:n,0:n),W(0:n,0:n);integer R(0:n,0:n)
        for i←0 to n-1 do
            (W(i,i), R(i,i), C(i,i))←(Q(i),0,0)  //置初值//
            (W(i,i+1), R(i,i+1), C(i,i+1))←(Q(i)+Q(i+1)+P(i+1),i+1, Q(i)+Q(i+1)+P(i+1))  
        repeat //含有一个结点的最优树//
        (W(n,n), R(n,n), C(n,n))←(Q(n),0,0) 
        for m←2 to n do
            for i←0 to n-m do
                j←i+m
                W(i,j) ←W(i,j-1)+P(j)+Q(j)
                k←区间[R(i,j-1), R(i+1,j)]中使{C(i,l-1)+C(l,j)}取最小值的l值  //Knuth结论//
                C(i,j) ←W(i,j)+C(i,k-1)+C(k,j)
                R(i,j)←k
            repeat
        repeat
    end OBST
