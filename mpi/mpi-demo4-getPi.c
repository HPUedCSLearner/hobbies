#include<stdio.h>
#include<mpi.h>
int main(int argc,char *argv[])
{
    int myid,np,i,j;
    int tag=666;
    double pi=0.0; 
    double fVal;//fVal代表取Xi所对应的函数值   4/(1+x^2) 即每个矩形的高度
    int n=1000000000;
    MPI_Status status;
    double h=(double)1/n; //每个矩形的宽度
    double local=0.0;//每个进程计算的面积和 
    double start,end;
    double xi;
    MPI_Init(&argc,&argv);//启动并行程序    
    MPI_Comm_size(MPI_COMM_WORLD,&np);//获取进程总数
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);//获取当前进程号
    start=MPI_Wtime();//记录开始时间
    for(i=myid;i<n;i+=np) //利用np个进程同时计算各部分矩形面积
    {
            xi=(i+0.5)*h;
            fVal=4.0/(1.0+xi*xi);//得到f(xi) 
            local+=fVal ; 
    }
    local=local*h;//得到该进程所计算的面积 
 
    //进程号！=0的进程计算的结果发送到进程0上面 
    if(myid!=0)
   {   
        MPI_Send(&local,1,MPI_DOUBLE,0,myid,MPI_COMM_WORLD); 
    }
    if(myid==0) //进程号为0就累加每个进程的计算结果 
    {
        pi=local;//得到进程0的值 后面接收就会覆盖这个值 
        for(j=1;j<np;j++)
           {
                MPI_Recv(&local,1,MPI_DOUBLE,j,j,MPI_COMM_WORLD,&status); //把其他进程的结果发送到local中 
                pi+=local;//得到所有的面积和 
           }
    }
    end=MPI_Wtime();//结束计算时间 
    if(myid==0)
        {
          printf("PI = %.15f\n",pi);
          printf("Time = %lf\n",end-start); 
          }
    MPI_Finalize();
    return 0;
} 


// https://blog.csdn.net/m0_53700832/article/details/123706960