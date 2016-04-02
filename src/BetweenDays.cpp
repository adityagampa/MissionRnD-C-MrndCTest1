/*
Q4: Two dates are given in a 8 node single linked list form,where each node
has one digit only, dates 01-31, months 01-12, year 0000-9999.

Find the number of days in between those two dates .[Exclusive]

Ex : Date1:  0->1->0->1->2->0->0->4 .
     Date2 : 0->5->0->1->2->0->0->4 should return 3 .
As there are 3 days between Jan1st 2004 and Jan 5th 2004.

Ex 2 : Date1 : 3->1->1->2->2->0->1->2.
       Date2 : 0->2->0->1->2->0->1->3 should return 1 .
(There is only one day between 31st Dec 2012 and 2nd  Jan 2013 .)

Note : Consecutive Days and Same Days should return 0;
->Return -1 for NULL Inputs .
->Between Days have to be calculated by not including start and end date .
->The SLL will have 8 Nodes in all cases . Month 9 will be represented as 09.

Difficulty : Hard 
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct node{
	int data;
	struct node *next;
};


int daysInMonth[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};
int daysInMonthForLeapYear[13]= {0,31,29,31,30,31,30,31,31,30,31,30,31};
char months[13][20]= {"","January","February","March","April","May","June","July","August","September","October","November","December"};
int leapYear(int y)
{
    return (((y%4==0) && (y%100!=0)) || (y%400==0)) ? 1 : 0;
}
int v(int date,int month,int year)
{
    return leapYear(year)?(month>=1 && month<=12 && daysInMonthForLeapYear[month]>=date ? 1 : 0):
           (month>=1 && month<=12 && daysInMonth[month]>=date ? 1 : 0);
}

int valid(int adate,int amonth,int ayear,int bdate,int bmonth,int byear)
{
    return v(adate,amonth,ayear) && v(bdate,bmonth,byear) ? 1:0;
}
int between_days(struct node *dl1, struct node *dl2)
{
    if(dl1==NULL || dl2==NULL)
        return -1;
    int d1=0,d2=0,m1=0,m2=0,y1=0,y2=0,count=0,nod=0;
    while(dl1!=NULL && dl2!=NULL)
    {
        if(count>=0 && count<=1)
        {
            d1=d1*10+dl1->data;
            d2=d2*10+dl2->data;
        }
        else if(count>=2 && count<=3)
        {
            m1=m1*10+dl1->data;
            m2=m2*10+dl2->data;
        }
        else if(count>=4 && count<=7)
        {
            y1=y1*10+dl1->data;
            y2=y2*10+dl2->data;
        }
        dl1=dl1->next;
        dl2=dl2->next;
        count++;
    }
    if(valid(d1,m1,y1,d2,m2,y2)==0)
        return -1;
    if(y1!=y2)
    {
        if(leapYear(y1)==0 && leapYear(y2)==0)
        {
            nod=365*(y1-y2);
            if(nod<0)
                nod=-nod;
            if(m1<m2)
            {
                nod+=daysInMonth[m1]-d1;
                int i=m1+1;
                for(;i<m2;i++)
                {
                    nod+=daysInMonth[i];
                }
                nod+=d2;
            }
            int max=(y1>y2)?y1:y2;
            if(max>=4)
            {
                nod+=max/4;
            }
            return nod;
        }

        if(y1>y2)
        {
            int temp=y1;
            y1=y2;
            y2=temp;
            temp=m1;
            m1=m2;
            m2=temp;
            temp=d1;
            d1=d2;
            d2=temp;

        }
        else
        {
            if(1)
            {
                if(leapYear(y1)==1 && leapYear(y2)==1)
                {
                    nod=365;
                    nod+=daysInMonthForLeapYear[m1]-d1;
                    int i=m1+1;
                    for(;i<m2;i++)
                        nod+=daysInMonthForLeapYear[i];
                    nod+=d2;
                    nod+=(y2-y1)/4;
                    return nod;
                }
                else
                {

                }
            }
        }
    }
    else
    {
        if(leapYear(y1))
        {
            int max=(m1>m2)?m1:m2;
            int min=(m1<m2)?m1:m2;
            nod=daysInMonthForLeapYear[min]-d1;
            int i=min+1;
            for(;i<max;i++)
                nod+=daysInMonthForLeapYear[i];
            nod+=d2;
        }
        else
        {
            int max=(m1>m2)?m1:m2;
            int min=(m1<m2)?m1:m2;
            nod=daysInMonth[min]-d1;
            int i=min+1;
            for(;i<max;i++)
                nod+=daysInMonth[i];
            nod+=d2;
        }
    }
    return nod;
}
