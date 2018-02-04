#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"


// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i = (intal*) malloc(sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}

	//alloc 3 chars for a null-terminated string "+0".
	i->s = (char *) malloc(3 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "+0"); 
	i->n = 1;

	return i;
}

void delete_intal(intal** i){

	if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->s != NULL ) {
		free( (*i)->s );
	}

	free(*i);
	*i = NULL;
	return;
}

void read_intal(intal* i, char* str){
	int n;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	n = strlen(str);
	
	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
	 	i->s = realloc(i->s, n + 1);
		i->n = strlen(str)-1; //one extra char for null termination
		//printf("%d\n",i->n);
	 	strcpy(i->s, str);
	} else {
		//it doesn't have a sign and hence it's positive
		n++; //one extra for the + sign
		i->n = strlen(str);
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
	}
	return;
}



intal* read1_intal(intal* i, char* str){
	int n;
	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	n = strlen(str);

	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	strcpy(i->s, str);
	} else {
		//it doesn't have a sign and hence it's positive
		n++; //one extra for the + sign
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
	}
	i->n=n;
	return i;
}


void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	printf("\n");
	return;
}


void add_zeros(intal* i, int n)
{
	//printf("%s",i->s);
	int len = i->n;
	//printf("%d\n ",n);
	char *s1 = (char*)(malloc(sizeof(char)*(n+len+1)));
	s1[0] = i->s[0];
	int k = 0;
	
	for(k =1;k<=n;k++)
		s1[k] = '0';
	int j =0;
	
	while(i->s[j+1] !='\0')
	{	s1[j+k] = i->s[j+1];
		j++;
	}
	i->n = n+len-1;
	//printf("%s",s1);
	read_intal(i,s1);
	
}

void remove_zeros(intal *i)
{
	int len = i->n;
	//printf("%d",len);
	int k;
	char* str =(char*)(malloc(sizeof(char)*(len+1)));
	str[0] = i->s[0];
	int j = 1;
	for(k=1;k<=len;k++)
	{
		if(i->s[k] != '0')
			break;

	}
	//printf("\n%c",i->s[k]);
	while(i->s[k] !='\0')
	{	str[j] = i->s[k];
		j++;k++;
	}
	str[j]= '\0';
	//printf("%s",str);
	read_intal(i,str);
}

void comp9(intal *x)
{
	int i =1;
	//char *str = 
	int val;
	while(x->s[i]!= '\0')
	{	val = x->s[i]-'0';
		val = 9 - val;
		//printf("%d",val);
		val = val +'0';
		//val = itoa(val);
		//printf("%c",val);
		x->s[i] = val;
		i++;
	}
}

intal *sub1_intal(intal *x1,intal *x2)
{
	int len;
	if(x1->n > x2->n)
	{
		len = x1->n;
		add_zeros(x2,(x1->n - x2->n));
	}
	if(x2->n > x1->n)
	{
		len = x2->n;
		add_zeros(x1,(x2->n - x1->n));
	}
	if(x1->n == x2->n)
		len = x1->n;
	//print_intal(x1);
	
	//print_intal(x2);
	comp9(x2);
	//print_intal(x2);
	//printf("here");
	intal * temp = add_intal(x1,x2);
	//print_intal(temp);
	//print_intal(temp);
	if(temp->n == x1->n)
	{
		//printf("here");
		temp->s[0]='-';
		comp9(temp);
		comp9(x2);
		//print_intal(temp);
	}
	if(temp->n > x1->n)
	{
		//printf("here");
		intal *carry1 = create_intal();
		read_intal(carry1,"1");
		temp->s[1] = '0';
		temp = add_intal(temp,carry1);
	comp9(x2);
	remove_zeros(temp);
	//print_intal(temp);
	//printf("l = %d",temp->n);
	}
	return temp;
	
	
}	

intal * sub_intal(intal *x1,intal *x2)
{
	if(x1->s[0] == '-' && x2->s[0] == '+')
	{
		x2->s[0] = '-';
		intal * x = add_intal(x1,x2);
		x2->s[0] = '+';
		remove_zeros(x);
		return x;
	}
	if(x1->s[0] == '+' && x2->s[0] == '-')
	{
		x2->s[0] = '+';
		intal * x = add_intal(x1,x2);
		x2->s[0] = '-';
		remove_zeros(x);
		return x;
	}
	if(x1->s[0] == '-' && x2->s[0] == '-')
	{
		//x2->s[0] = '+';
		//x1->s[0] = '+';
		intal *x;
		if( x1->n <= x2->n)
		 x = sub1_intal(x1,x2);
		else
		 x = sub1_intal(x2,x1);
				
		remove_zeros(x);
		return x;
	}
	if(x1->s[0] == '+' && x2->s[0] == '+')
	{
		intal * x = sub1_intal(x1,x2);
		remove_zeros(x);
		return x;
	}
}
	

		

intal* add_intal(intal *x1,intal *x2)
{
	//print_intal(x1);
	//print_intal(x2);
	//printf("%d %d " ,x1->n,x2->n);
	int len;
	int x = x1->n + 1;
	//printf("%d",x);
	if(x1->n > x2->n)
	{
		len = x1->n;
		add_zeros(x2,(x1->n - x2->n));
	}
	if(x2->n > x1->n)
	{
		len = x2->n;
		add_zeros(x1,(x2->n - x1->n));
	}
	if(x1->n == x2->n)
		len = x1->n;
	char * str = (char*)(malloc(sizeof(char)*(len+6)));
	intal * result = create_intal();
	if(x1->s[0] == '-' && x2->s[0] == '+')
	{
		x1->s[0] = '+';
		result = sub_intal(x2,x1);
		x1->s[0] = '-';
		remove_zeros(result);
		return result;
	}
	if(x1->s[0] == '+' && x2->s[0] == '-')
	{
		x2->s[0] = '+';
		result = sub_intal(x1,x2);
		x2->s[0] = '-';
		remove_zeros(result);
		return result;
	}
	else{
	if(x1->s[0] == '+' && x2->s[0] =='+')
		str[0] = '+';
	if(x1->s[0] == '-' && x2->s[0] =='-')
		str[0] = '-';
	
	//print_intal(x1);
	//print_intal(x2);
	//printf("%c\n",x2->s[len]);
	int i = len;
	int temp = 0;
	int carry = 0;
	int k =1;
	while(k!=len+2){
		str[k] = '0';k++;}
	//printf("%s",str);
	str[len+2] = '\0';
	k = len+1;
	while(i!=0)
	{
		int v1= x1->s[i] -'0';
		int v2= x2->s[i] -'0';
		temp = v1 +v2+carry;
		//printf("%d + %d +%d\n",v1,v2,carry);
		carry = 0;
		if(temp>=10)
		{
			temp = temp%10;
			carry = 1;
		}
		str[k] = temp+'0';
		//printf("carry = %d  temp = %d\n ",carry,temp);
		//printf("%c\n",str[4+k]);
		k--;
		i--;
	}
	//printf("%d\n",carry);
	//printf("%s\n",str);
	if(carry == 1)
		{str[1] = '1';}
	read_intal(result,str);
	//print_intal(result);
	//printf("%s\n",str);
	free(str);
	remove_zeros(result);
	//print_intal(result);
	//str[4] ='7';
	//printf("%s\n",result->s);
	return result;
	
	}
	
}

intal* decrement(intal *x)
{
	intal * one = create_intal();
	read_intal(one,"1");
	x = sub_intal(x,one);
	free(one);
	return x;
}


intal* append_zeros(intal* x,int n)
{
	intal *res = create_intal();
	int len = x->n;
	char *str = (char*)(malloc(sizeof(char)*(n+len+1)));
	str[0] = x->s[0];
	int i = 1;
	int k =1;
	while(k!=n+len+1){
		str[k] = '0';k++;}
	//printf("%s",str);
	while(x->s[i]!='\0')
	{	str[i] = x->s[i];
		i++;
	}
	//printf("\n%s",str);
	str[k] = '\0';
	read_intal(res,str);
	free(str);
	return res;
		


}

intal* add_for_mul(intal* a,intal* b)
{
	int l1,l2,len,i,j,r,k,c,gt;
	int *x,*y,*res;
	l1=a->n;
	l2=b->n;
	intal* new;
	new= create_intal();
	x=(int *)malloc(sizeof(int)*l1);
	y=(int *)malloc(sizeof(int)*l2);
	len=0;
	res=(int *)malloc(sizeof(int)*(l1+l2));
	
	//copying string into array
	for(i=0;i<(l1-1);i++)
	{
		x[i]=(a->s[i+1])-'0';
	}
	
	//copying string into array
	for(i=0;i<(l2-1);i++)
	{
		y[i]=(b->s[i+1])-'0';
	}
	c=0;
	for(i=l1-2,j=l2-2;(i>=0&&j>=0);i--,j--)
	{
		r=x[i]+y[j]+c;
		if(r/10!=0)
		{
			c=r/10;
			r=r%10;
		}
		else
			c=0;
		res[len++]=r;
	}
	if(i!=-1)
	{
		for(k=i;k>=0;k--)
		{
			r=x[k]+c;
 			if(r/10!=0)
			{
				c=r/10;
				r=r%10;
			}
			else
				c=0;
			res[len++]=r;
		}
	}
	if(j!=-1)
	{
		for(k=j;k>=0;k--)
		{
			r=y[k]+c;
 			if(r/10!=0)
			{
				c=r/10;
				r=r%10;
			}
			else
				c=0;
			res[len++]=r;
		}
	}
	if(c!=0)
		res[len++]=c;
	new->s=(char *)malloc(sizeof(char)*(len+2));
	new->s[0]=a->s[0];
	
	for(i=(len-1),j=1;i>=0;i--,j++)
	{
		new->s[j]=res[i]+'0';
	}
	new->s[j]='\0';
	new->n=len+1;
	//printf("\nres:%s",new->s);
	return new;
}

intal* mul_intal(intal* a,intal* b)
{	
	
	int l1,l2,len,*x,*y,*res,*res1,i,j,r,k,c,p,gt;
	l1=a->n;
	l2=b->n;
	int ct=0;
	intal* new;
	new=create_intal();

	x=(int *)malloc(sizeof(int)*(l1+l2));
	y=(int *)malloc(sizeof(int)*(l2+l1));

	res=(int *)malloc(sizeof(int)*(l1+l2));
	res1=(int *)malloc(sizeof(int)*(l1+l2));
	new->s=(char *)malloc(sizeof(char)*(l1+l2));
	
	for(i=0;i<(l1-1);i++)
	{
		x[i]=(a->s[i+1])-'0';
		//printf("\ni:%d,a[i]:%d",i,x[i]);
	}
	
	//copying string into array
	for(i=0;i<(l2-1);i++)
	{
		y[i]=(b->s[i+1])-'0';
		
	}
	read_intal(new,"0");
	for(i=l2-2;i>=0;i--)
	{	c=0;
		len=0;
		
		for(j=l1-2;j>=0;j--)
		{
			r=(x[j]*y[i])+c;
			if(r/10!=0)
			{
				c=r/10;
				r=r%10;
			}
			else
				c=0;
			res[len++]=r;
			
		}
		if(c!=0)
		{
			res[len++]=c;
		}
		for(p=(len-1),j=0;p>=0;p--,j++)
		{
			res1[j]=res[p];
			
		}
		for(k=0;k<ct;k++)
			res1[len++]=0;
		
		intal *m;
		m=create_intal();
		
		m->s=(char *)malloc(sizeof(char)*(len+2));
		m->n=len+1;
		m->s[0]='+';
		for(k=0;k<len;k++)
			{m->s[k+1]=res1[k]+'0';}

		ct=ct+1;
		new=add_for_mul(new,m);
	}
	if(a->s[0]==b->s[0])
		new->s[0]='+';
	else
		new->s[0]='-';
	return new;
}



//intal * divide_intal(intal*x1,intal*x2)
 
int compare(intal *x1,intal *x2)
{
	if(x1->n > x2->n)
	{
		add_zeros(x2,(x1->n - x2->n));
	}
	if(x2->n > x1->n)
	{
		add_zeros(x1,(x2->n - x1->n));
	}
	return(strcmp(x1->s,x2->s));
}	

intal * exp_intal(intal *x1,intal* x2)
{
	intal * p = create_intal();
	p = read1_intal(p,"0");
	intal * one = create_intal();
	one = read1_intal(one,"1");
	intal *temp = create_intal();
	read_intal(temp,x2->s);
	//temp = decrement(temp);
	intal *result = create_intal();
	result = read1_intal(result,"1");
	int i = 0;
	//print_intal(temp);
	while(compare(temp,p)>0)
	{	
		compare(temp,p);
		//print_intal(res);
		result = mul_intal(result,x1);
		//print_intal(result);
		temp = decrement(temp);
		if(temp->s[0] == '-')
			break;
		//print_intal(temp);
		//count++;
	}
	/*for(i=0;i<n;i++)
	{
		result = mul(result,x1);
	}*/
	return(result);
}	
	
intal *divide_intal(intal *x1,intal *x2)
{
	char sign;
	char s1 = x1->s[0];
	char s2 = x2->s[0];
	if(x1->s[0] == '+' && x2->s[0] =='-')
	{	sign = '-';
		x2->s[0] = '+';
	}
	if(x1->s[0] == '-' && x2->s[0] =='+')
	{	sign = '-';
		x1->s[0] = '+';
	}
	if(x1->s[0] == '-' && x2->s[0] =='-')
	{	sign = '+';
		x2->s[0] = '+';	
		x1->s[0] = '+';	
	}
	
	if(x1->s[0] == '+' && x2->s[0] =='+')
	{	sign = '+';	
	}
	
	intal *count = create_intal();
	read_intal(count,"0");
	//printf("%s\n",count->s);
	//printf("%s",x2->s);
	//printf("%d",strcmp(x2->s,count->s));

	if(strcmp(x2->s,count->s)==0)
	{	printf("zero");
		return NULL;
	}
	intal *copy = create_intal();
	intal *one = create_intal();
	read_intal(one,"1");
	read_intal(copy,x1->s);
	int flag = 0;
	//printf("%d",compare(x1,x2));
	while(copy->s[0] !='-')
	{
		flag=compare(copy,x2);
		if(flag<0)
			break;
		copy = sub_intal(copy,x2);
		//print_intal(count);
		count = add_intal(count,one);
	}
	x1->s[0] = s1;
	x2->s[0] = s1;
	remove_zeros(x1);
	remove_zeros(x2);
	if(sign == '-')
		count->s[0] = '-';
	//print_intal(count);
	delete_intal(&copy);
	delete_intal(&one);
	return count;

		
}
		

	


