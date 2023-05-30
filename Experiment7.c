#include "stdio.h"
#include "string.h"
//程序末尾附测试用例

/// @brief 学生人数
int Number_ = 0;
/// @brief 课程数目
int Course_ = 0;
struct students
{
	unsigned long long int id;
	char name[21];
	double score[6];
    double total;
    double average;
};
static struct students student[30];

void InputRecord();             //1     输入所有学生信息
void CaculateEveryCourses();    //2     计算每门课程的总分和平均分
void CaculateEveryStudent();    //3     计算每个学生的总分和平均分
void SortByTotal();             //4     按学生总分从高到低进行排序
void SortByNumber();            //5     按学生学号从高到低排序
void SortByDictionary();        //6     按首字母ASCII排序(词典写着太复杂了)
void SearchByNumber();          //7     按学号查找学生信息
void SearchByName();            //8     按姓名查找学生信息
void CourseStatistic();         //9     对每门课程进行成绩统计
void RecordList();              //10    输出所有学生记录信息


int main()
{
	int choice = 0;
	
	printf("1.  Input record\n"
	"2.  Caculate total and average score of every course\n"
	"3.  Caculate total and average score of every student\n"
	"4.  Sort in descending order by total score of every student\n"
	"5.  Sort in ascending order by number\n"
	"6.  Sort in dictionary order by name\n"
	"7.  Search by number\n"
	"8.  Search by name\n"
	"9.  Statistic analysis for every course\n"
	"10. List record \n"
	"0.  Exit\n");
    do
    {
        printf("Please input your choice:\n");
	    scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Input record\n");
                InputRecord();
                break;
            case 2:
                printf("Caculate total and average score of every course\n");
                CaculateEveryCourses();
                break;
            case 3:
                printf("Caculate total and average score of every student\n");
                CaculateEveryStudent();
                break;
            case 4:
                printf("Sort in descending order by total score of every student\n");
                SortByTotal();
                break;
            case 5:
                printf("Sort in ascending order by number\n");
                SortByNumber();
                break;
            case 6:
                printf("Sort in dictionary order by name\n");
                SortByDictionary();
                break;
            case 7:
                printf("Search by number\n");
                SearchByNumber();
                break;
            case 8:
                printf("Search by name\n");
                SearchByName();
                break;
            case 9:
                printf("Statistic analysis for every course\n");
                CourseStatistic();
                break;
            case 10:
                printf("List record \n");
                RecordList();
                break;
            case 0:return 0;
                break;
        }
    }while(choice != 0);
    return 0;
}

/// @brief 输入所有学生信息
void InputRecord()  //1
{
	int i = 0,j = 0;
    unsigned int temp = 0;
    printf("Please input the number of students.\n");
    scanf("%d",&Number_);
    printf("Please input the number of coures.\n");
    scanf("%d",&Course_);
	for(i = 0; i < Number_; i++)
	{
        printf("\nNo.%d student.\n",i+1);
        printf("Please input the student's id\n");
		scanf("%lld",&student[i].id);//学号 
        //这里也可以用字符串，最开始就是用的字符串但是当时还没用过strcmp()函数（后面匹配姓名没办法了才知道这个函数），就改成比对数字是否相同了，用了一个unsigned longlongint 233,不过这样好像是简单一些（就是内存用的有些奢侈）
        printf("Please input the student's name\n");
        scanf("%20s",student[i].name);//不超过20字符的姓名
        for(j = 0; j < Course_; j++)
        {
            printf("Please input No.%d coures score\n",j+1);
            scanf("%lf",student[i].score+j);
            // "指针+偏移量"访问数组元素，即student[i].score + j表示数组中第j个元素的地址。
            // 又因为student[i].score是一个数组，所以它本身就是一个指针，可以直接进行"指针+偏移量"来访问数组的某个元素。
        }
	}
	printf("\n");return;
}

/// @brief 计算每门课程的总分和平均分
void CaculateEveryCourses() //2
{
    int i,j;
    double total,average;
    for(j = 0; j < Course_; j++)
	{
        total = 0;
        average = 0;
        for(i=0; i < Number_; i++)
        {
            total += student[i].score[j];
        }
        average = total / (double)Number_;
        printf("\n");
        printf("No.%d course:\n",j+1);
        printf("\tTotal score: %.2lf.\n",total);
        printf("\tAverage score: %.2lf.\n",average);
    }
    printf("\n");return;
    
}

/// @brief 计算每个学生的总分和平均分
void CaculateEveryStudent() //3
{
    int i,j;
    double total,average;
    for(i = 0; i < Number_; i++)
	{
        total = 0;
        average = 0;
        for(j = 0; j < Course_; j++)
        {
            total += student[i].score[j];
        }
        average =  total / (double)Course_;
        student[i].average = average;
        student[i].total = total;
        printf("\n");
        printf("No.%d student:\n",i+1);
        printf("%lld  %s\n",student[i].id,student[i].name);
        for(j = 0; j < Course_; j++)
        {
            printf("\tScore of No.%d coures score is %lf.\n",
                                j+1,    student[i].score[j]);
        }
        printf("\tTotal score: %.2lf.\n",total);
        printf("\tAverage score: %.2lf.\n",average);
    }
    printf("\n");return;
    
}

/// @brief 按学生总分从高到低进行排序
void SortByTotal()  //4
{
    int i = 0, j = 0, maxIndex = 0, temp = 0;
    int arr[30]={0};  // 存放学生结构体在排序后的序列
    // 初始化arr数组为0 ~ Number_-1
    for(i = 0; i < Number_; i++)
    {
        arr[i] = i;     
    }
    // 高到低排斥
    for(i = 0; i < Number_; i++)
    {
        maxIndex = i;
        for(j = i + 1; j < Number_; j++)
        {
            // 逐个找出最大值的序号
            if(student[j].total > student[maxIndex].total)
            {
                maxIndex = j;   
            }
        }
        // 将当前未排序序列的最大值交换到已排序的末尾
        temp = arr[i];
        arr[i] = arr[maxIndex];
        arr[maxIndex] = temp;
    }
    printf("Sort by total score in descending order:\n");  // 输出按总分排序后的结果
    for(i = 0; i < Number_; i++)
    {
        printf("%lld\t%s\n\ttotal score: %.2lf\n", 
               student[arr[i]].id, student[arr[i]].name, 
               student[arr[i]].total);
    }
    printf("\n");return;
}

/// @brief 按学生学号从高到低排序
void SortByNumber() //5
{
    int i = 0, j = 0, temp = 0;
    int arr[30]={0};
    //初始化arr数组为0 ~ Number_-1
    for(i = 0; i < Number_; i++)
    {
        arr[i] = i;     
    }
    //对arr数组进行排序 //经过排序后arr[i]的值是对应结构体第i个元素的排名   //后续遍历时只需输出结构体中的第arr[i++]个元素就是正确的序了
    for(i = 0; i < Number_; i++)
    {
        for(j = i+1; j < Number_; j++)
        {
            if(student[i].id < student[j].id)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("Sort by number in descending order:\n");
    //遍历
    for(i = 0; i < Number_; i++)
    {
        printf("%lld\t%s\n", 
               student[arr[i]].id, student[arr[i]].name);
        for(j = 0; j < Course_; j++)
        {
            printf("\tScore of No.%d coures score is %lf.\n",
                                j+1,    student[arr[i]].score[j]);
        }
        printf("\ttotal score: %.2lf\n\taverage score: %.2lf\n", 
               student[arr[i]].total, student[arr[i]].average);
    }
    printf("\n");return;
}

/// @brief 按首字母ASCII排序(词典写着太复杂了)
void SortByDictionary()  //6
{
    int i = 0, j = 0;
    char arr[30]={0};// 存放学生结构体在排序后的序列
    char temp = 0;
    //初始化arr数组为0 ~ Number_-1
    for(i = 0; i < Number_; i++)
    {
        arr[i] = i;     
    }
    //对arr数组进行排序 //经过排序后arr[i]的值是对应结构体第i个元素的排名   //后续遍历时只需输出结构体中的第arr[i++]个元素就是正确的序了
    for(i = 0; i < Number_; i++)
    {
        for(j = i+1; j < Number_; j++)
        {
            if(student[i].name[0] < student[j].name[0])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("Sort by number in descending order:\n");
    //遍历
    for(i = 0; i < Number_; i++)
    {
        printf("%s\t%lld\n", 
                student[arr[i]].name, student[arr[i]].id);
        for(j = 0; j < Course_; j++)
        {
            printf("\tScore of No.%d coures score is %lf.\n",
                                j+1,    student[arr[i]].score[j]);
        }
        printf("\ttotal score: %.2lf\n\taverage score: %.2lf\n", 
               student[arr[i]].total, student[arr[i]].average);
    }
    printf("\n");return;
}

/// @brief 按学号查找学生信息
void SearchByNumber()   //7
{
    int i = 0, j = 0;
    unsigned long long int ID;
    printf("Please input the number you want to search: ");
    scanf("%lld",&ID);
    for(i = 0; i < Number_; i++)
    {
        if(ID == student[i].id)
        {
            printf("%lld  %s", 
               student[i].id, student[i].name);
        
            for(j = 0; j < Course_; j++)
            {
                printf("  Score of No.%d coures score is %lf.\n",j+1,student[i].score[j]);
            }
            printf("  \ntotal score: %.2lf  average score: %.2lf\n", 
                            student[i].total,  student[i].average);
            return;
        }
        else
        {
            printf("ERROR\n");
            printf("The number of the search was not found in the record.\n");
        }
    }
    return;
}

/// @brief 按姓名查找学生信息
void SearchByName() //8
{
    int i = 0, j = 0;
    char name[21];
    printf("Please input the name you want to search: ");
    scanf("%20s",name);//输入不超过20字符的姓名
    for(i = 0; i < Number_; i++)
    {
        if(strcmp(name,student[i].name) == 0)
        {
            break;
        }
    }
    if(strcmp(name,student[i].name) != 0)
    {
        printf("ERROR\n");
        printf("The name of the search was not found in the record.\n");
    }
    else
    {
        printf("Name: %s\n", student[i].name);
        for(j = 0; j < Course_; j++)
        {
            printf("  Score of No.%d coures score is %lf.\n",j+1,student[i].score[j]);
        }
        printf("  \ntotal score: %.2lf  average score: %.2lf\n", 
                        student[i].total,  student[i].average);
    }
    
}

/// @brief 对每门课程进行成绩统计
void CourseStatistic()  //9
{
    int i = 0, j = 0;
    double score[30][6] = {0};
    double (*p)[6] = score; // 定义指向数组 score 的指针
    for(i = 0; i < Number_; i++)
    {
        for(j = 0; j < Course_; j++)
        {
            *(p[i]+j) = student[i].score[j]; // 使用指针访问二维数组 score，并将其赋值
        }
    }
    for(j = 0; j < Course_; j++)// 遍历每门课程
    {
        int excellent = 0, good = 0, medium = 0, pass = 0, fail = 0;// 存储各个类别的人数
        double total = Number_;
        for(i = 0; i < Number_; i++)// 遍历每个学生的某一门课程成绩
        {
            if(score[i][j] >= 90)
            {
                excellent++;
            }
            else if(score[i][j] >= 80 && score[i][j] < 90)
            {
                good++;
            }
            else if(score[i][j] >= 70 && score[i][j] < 80)
            {
                medium++;
            }
            else if(score[i][j] >= 60 && score[i][j] < 70)
            {
                pass++;
            }
            else
            {
                fail++;
            }
        }
        printf("For course%d, there are %d students (accounting for %.2lf%%) with excellent score,\n", j+1, excellent, excellent/total*100);
        printf("%d students (accounting for %.2lf%%) with good score,\n", good, good/total*100);
        printf("%d students (accounting for %.2lf%%) with medium score,\n", medium, medium/total*100);
        printf("%d students (accounting for %.2lf%%) with pass score,\n", pass, pass/total*100);
        printf("%d students (accounting for %.2lf%%) with fail score.\n\n", fail, fail/total*100);
    }
}

/*
void RecordList()   //直接用结构体访问的版本
{
    int i = 0, j = 0;
    for(i = 0; i < Number_; i++)
    {
        printf("No.%d student:\n",i+1);
        printf("%lld  %s", 
               student[i].id, student[i].name);
        for(j = 0; j < Course_; j++)
        {
            printf("  Score of No.%d coures score is %lf.\n",j+1,student[i].score[j]);
        }
        printf("  \ntotal score: %.2lf  average score: %.2lf\n", 
                        student[i].total,  student[i].average);
    }
}
*/
/// @brief 输出所有学生记录信息
void RecordList()   //10   //使用指针访问结构体
{
    int i = 0, j = 0;
    struct students *p = student;
    for(i = 0; i < Number_; i++, p++)
    {
        printf("No.%d student:\n",i+1);
        printf("%lld  %s\n", 
               p->id, p->name);
        for(j = 0; j < Course_; j++)
        {
            printf("  Score of No.%d coures score is %lf.\n",j+1,p->score[j]);
        }
        printf("  \ntotal score: %.2lf  average score: %.2lf\n", 
                        p->total,  p->average);
    }
}
/*测试用例
1
4
3
202232182319
Aname
100
60
80
202032182319
Cname
60
100
55.6
202332182319
Bname
90
67
86
202132182319
Dname
90
75
84
2
3
4
5
6
7
202232182319
8
Bname
9
10
0

*/
