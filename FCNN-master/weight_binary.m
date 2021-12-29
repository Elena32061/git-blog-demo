tic;
step=22;
a=0.35;
hid=30;
average=0;
%打乱训练样本
r=randperm(5000);
r=r';
Xt = [X r];
yt = [y r];
%重新排序
Xt=sortrows(Xt,401);
yt=sortrows(yt,11);
%取出训练和测试
x_train=Xt(1:4000,1:400);
x_train=x_train';
x_test=Xt(4001:5000,1:400);
x_test=x_test';
y_train=yt(1:4000,1:10);
y_train=y_train';
y_test=yt(4001:5000,1:10);
y_test=y_test';
%归一化
x_train = mapminmax(x_train,0,1);
x_test =mapminmax(x_test,0,1);
%训练
fprintf('迭代步数为%d,学习因子为%.2f,隐藏层神经元个数为%d,',step,a,hid);
for i=1:10
[w1,b1,w_h1,b_h1]=mytrain(x_train,y_train,hid,step,a);
w1(find(w1<0)) = -1;
w1(find(w1>=0)) = 1;
w_h1(find(w_h1<0)) = -1;
w_h1(find(w_h1>=0)) = 1;
%测试
result=mytest(x_test,y_test,w1,b1,w_h1,b_h1);
average=average+result;
end
average=average/10;
fprintf('正确率为%.2f/1000\n',average);
toc