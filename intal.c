#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

static char* removeZeroes(char* intal)
{
    int count = 0;
    int len = strlen(intal);
    for(int i = 0;i<len;++i)
    {
        if(intal[i] == 48)
            ++count;
        else
            break;
        
    }
    if(count==0 || len==1)
    	return intal;
    else
    {
    	char * new=(char*)malloc(sizeof(char)*(len-count+1));
    	int i=0;
    	for(int j=count;j<len;j++)
    	{
    		new[i++]=intal[j];
    	}
    	new[i]='\0';
    	free(intal);
    	return new;
    } 
}
// Returns the sum of two intals.
char* intal_add(const char* intal1, const char* intal2)
{
	int len1=strlen(intal1);
	int len2=strlen(intal2);
	int res=len1;
	if(len2>len1)
		res=len2;
	char *ret=(char *)malloc(sizeof(char)*(res+2));
	ret[res+1]='\0';
	int i=len1-1;
	int j=len2-1;
	int k=res;
	int carry=0;
	int sum;
	while (i>=0 || j>=0)
	{
		int ele1=0;
		int ele2=0;
		if(i>=0)
			ele1=intal1[i]-48;
		if(j>=0)
			ele2=intal2[j]-48;
		sum=ele1+ele2+carry;
		ret[k]=sum%10+48;
		carry=sum/10;
		i--;j--;k--;
	}
	ret[0]=carry+48;
	return removeZeroes(ret);
}

// Returns the comparison value of two intals.
// Returns 0 when both are equal.
// Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(const char* intal1, const char* intal2)
{
	int len1=strlen(intal1);
	int len2=strlen(intal2);
	if(len1==len2)
	{
		int i=0;
		while(i<len1)
		{
			if(intal1[i]>intal2[i])
				return 1;
			if(intal2[i]>intal1[i])
				return -1;
			i++;
		}
		return 0;
	}
	else if(len1>len2)
		return +1;
	return -1;
}

// Returns the difference (obviously, nonnegative) of two intals.
char* intal_diff(const char* intal1, const char* intal2)
{
	int l=intal_compare(intal1,intal2);
	if(l==0)
	{
		char * temp=(char*)malloc(sizeof(char)*2);
		temp[0]=48;
		temp[1]='\0';
		return temp;
	}
	if(l==1)
	{
		int len1=strlen(intal1);
		int len2=strlen(intal2);
		char* res=(char*)malloc(sizeof(char)*(len1+1));
		res[len1]='\0';
		int i=len1-1;
		int j=len2-1;
		int k=len1-1;
		int carry=0;
		while(i>=0)
		{
			int ele1=intal1[i]-48;
			int ele2=0;
			if(j>=0)
				ele2=intal2[j]-48;
			int ele=ele1-ele2-carry;
			if(ele<0)
			{
				ele=10+ele1-ele2-carry;
				carry=1;
			}
			else
				carry=0;
			res[k]=ele+48;
			i--;j--;k--;
		}
		return removeZeroes(res);
	}
	int len1=strlen(intal1);
	int len2=strlen(intal2);
	char *res=(char*)malloc(sizeof(char)*(len2+1));
	res[len2]='\0';
	int i=len1-1;
	int j=len2-1;
	int k=len2-1;
	int carry=0;
	while(j>=0)
	{
		int ele1=intal2[j]-48;
		int ele2=0;
		if(i>=0)
			ele2=intal1[i]-48;
		int ele=ele1-ele2-carry;
		if(ele<0)
		{
			ele=10+ele1-ele2-carry;
			carry=1;
		}
		else
			carry=0;
		res[k]=ele+48;
		i--;j--;k--;
	}
	return removeZeroes(res);
}

// Returns the product of two intals.
char* intal_multiply(const char* intal1, const char* intal2)
{
	if( intal1[0]==48 || intal2[0]==48 )
	{
		char* temp=(char*)malloc(sizeof(char)*2);
		temp[0]=48;
		temp[1]='\0';
		return temp;
	}
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    int len = len1+len2;
    int *a = (int*)calloc(len,sizeof(int)); 
    for(int i=len1-1; i > -1; i--)
        for(int j=len2-1; j > -1; j--)
            a[i+j+1] += (intal1[i]-48)*(intal2[j]-48); 
    for(int i=len-1; i > 0; i--) 
    {
        a[i-1] = a[i-1] + a[i]/10;
        a[i] =a[i] % 10;
    }
    char *res = (char*)malloc(sizeof(char)*(len+1));
    int j = 0;
    int i = 0;
    if(a[i]==0) 
    	i++;
    while(i < len)
        res[j++] = a[i++]+48;
    free(a);
    res[j] = '\0';
    return res;
}

static char* intal_slice(char *intal,int start,int end)
{
	char* ans=(char*)malloc(sizeof(char)*(end-start+2));
    int index = 0;
    for(int i = start; i < end; ++i)
        ans[index++] = intal[i];
   
    ans[index] = '\0';
    // printf("heyy%s %s\n",ans,intal);
    return ans;    
}

// Returns intal1 mod intal2
// The mod value should be in the range [0, intal2 - 1].
// intal2 > 1
// Implement a O(log intal1) time taking algorithm.
// O(intal1 / intal2) time taking algorithm may exceed time limit.
// O(intal1 / intal2) algorithm may repeatedly subtract intal2 from intal1.
// That will take intal1/intal2 iterations.
// You need to design a O(log intal1) time taking algorithm.
// Generate your own testcases at https://www.omnicalculator.com/math/modulo
char* intal_mod(const char* intal1, const char* intal2)
{
	char * zero=(char*)malloc(sizeof(char)*2);
	zero[0]=48;
	zero[1]='\0';
	int len1 = strlen(intal1);
    int len2 = strlen(intal2);
	char *dividend = intal_add(intal1,zero);
	char * frh;
	char * toFree;
    while(intal_compare(dividend,intal2) != -1)
    {
        char * ans=intal_slice(dividend,0,len2);
		if(intal_compare(ans,intal2) == -1){
			frh=ans;
			ans=intal_slice(dividend,0, len2 + 1);
			free(frh);
		}
		int ans_length = strlen(ans);
		while(intal_compare(ans,intal2) != -1)
        {
            char *toFree = ans;
            ans = intal_diff(ans,intal2);
            free(toFree);
        }
        if(intal_compare(ans,zero) == 0)
        {	
        	frh=ans;
            ans=intal_slice(dividend,ans_length, len1);
            toFree=dividend;
            dividend=intal_add(ans,zero);
            free(toFree);
            free(frh);
            free(ans);
        }
        else
        {
            char * rem=intal_slice(dividend,ans_length, len1);
            int len1=strlen(ans);
            int len2=strlen(rem);
            int i=0;
            toFree=dividend;
            dividend=(char*)malloc(sizeof(char)*(len1+len2+1));
           	while(i<len1)
           	{
           		dividend[i]=ans[i];
           		i++;
           	}
           	int j=0;
           	while(j<len2)
           	{
           		dividend[i+j]=rem[j];
           		j++;
           	}
           	dividend[i+j]='\0';
            free(toFree);
            free(ans);
            free(rem);
        }
        
   	}
   return removeZeroes(dividend);
  }

//Returns intal1 ^ intal2.
// Let 0 ^ n = 0, where n is an intal.
// Implement a O(log n) intal multiplications algorithm.
// 2^3000 has less than 1000 decimal digits. 3000 intal multiplications may exceed time limit.
char* intal_pow(const char* intal1, unsigned int n)
{
	char* zero=(char*)malloc(sizeof(char)*2);
	zero[0]=48;
	zero[1]='\0';
	if(n==1)
	{
		char * x=intal_add(intal1,zero);
		free(zero);
		return x;
	}
	if(n==0)
	{
		zero[0]=49;
		return zero;
	}
	if(n%2)
	{
		char * x=intal_pow(intal1,n/2);
		char * tofree=x;
		x=intal_multiply(x,x);
		free(tofree);
		tofree=x;
		x=intal_multiply(x,intal1);
		free(tofree);
		free(zero);
		return x;
	}
	else
	{
		char * x=intal_pow(intal1,n/2);
		char * tofree=x;
		x=intal_multiply(x,x);
		free(tofree);
		free(zero);
		return x;
	}

}

// char* intal_pow(const char* intal1, unsigned int n)
// {
// 	if(n==0)
// 	{
// 		char* result = (char*)malloc(sizeof(char)*2);
// 		result[0] = '1';
// 		result[1] = '\0';
// 		return result;
// 	}

// 	if(n%2==0)
// 	{	
// 		char* temp = intal_pow(intal1,n/2);
// 		char* result = intal_multiply(temp,temp);
// 		free(temp);
// 		return result;
// 	}
// 	else
// 	{
// 		char * x=intal_pow(intal1,n/2);
// 		char * tofree=x;
// 		x=intal_multiply(x,x);
// 		free(tofree);
// 		tofree=x;
// 		x=intal_multiply(x,intal1);
// 		free(tofree);
// 		return x;
// 	}
// }



// Returns Greatest Common Devisor of intal1 and intal2.
// Let GCD be "0" if both intal1 and intal2 are "0" even though it is undefined, mathematically.
// Use Euclid's theorem to not exceed the time limit.
char* intal_gcd(const char* intal1, const char* intal2)
{
	char* zero=(char*)malloc(sizeof(char)*2);
	zero[0]=48;
	zero[1]='\0';
	int t=intal_compare(intal1,intal2);
	if(t==1)
	{
		char* temp1=intal_add(intal1,zero);
		char* temp2=intal_add(intal2,zero);
		char* temp3;
		char* tofree;
		while(intal_compare(temp2,zero)==1)
		{
			temp3=intal_mod(temp1,temp2);
			tofree=temp1;
			temp1=temp2;
			temp2=temp3;
			free(tofree);
		}
		return temp1;
	}
	else
	{
		char* temp2=intal_add(intal1,zero);
		char* temp1=intal_add(intal2,zero);
	
		char* temp3;
		char* tofree;
		while(intal_compare(temp2,zero)==1)
		{
			temp3=intal_mod(temp1,temp2);
			tofree=temp1;
			temp1=temp2;
			temp2=temp3;
			free(tofree);
		}
		return temp1;
	}
}

// Returns nth fibonacci number.
// intal_fibonacci(0) = intal "0".
// intal_fibonacci(1) = intal "1".
char* intal_fibonacci(unsigned int n)
{
	char* result;
	char* num0 = (char*)malloc(sizeof(char)*2);
	char* num1 = (char*)malloc(sizeof(char)*2);
	num0[0] = 48;
	num0[1] = '\0';
	num1[0] = 49;
	num1[1] = '\0';
	if(n==0)
		return num0;
	if(n==1)
		return num1;
	char* temp;
	for(int i = 2; i<=n ; i++)
	{	
		temp = num0;
		result = intal_add(num0,num1);
		num0 = num1;
		num1 = result;
		free(temp);
	}
	free(num0);
	return result;
}

// Returns the factorial of n.
char* intal_factorial(unsigned int n)
{
	if(n==0)
	{
		char* temp=(char*)malloc(sizeof(char)*2);
		temp[0]=49;
		temp[1]='\0';
		return temp;
	}
	if(n==1)
	{
		char* temp=(char*)malloc(sizeof(char)*2);
		temp[0]=49;
		temp[1]='\0';
		return temp;
	}
	char* s=(char*)malloc(sizeof(char)*32);
	char* temp=(char*)malloc(sizeof(char)*2);
	temp[0]=49;
	temp[1]='\0';
	int i=2;
	char* prev;
	while(i<=n)
	{
		sprintf(s,"%d", i);
		prev=temp;
		temp=intal_multiply(temp,s);
		free(prev);
		i++;
	}
	free(s);
	return temp;
}

// Returns the Binomial Coefficient C(n,k).
// 0 <= k <= n
// C(n,k) < 10^1000 because the returning value is expected to be less than 10^1000.
// Use the Pascal's identity C(n,k) = C(n-1,k) + C(n-1,k-1)
// Make sure the intermediate intal values do not cross C(n,k).
// Use Dynamic Programming. Use extra space of not more than O(k) number of intals. Do not allocate the whole O(nk) DP table.
// Don't let C(1000,900) take more time than C(1000,500). Time limit may exceed otherwise.
char* intal_bincoeff(unsigned int n, unsigned int k)
{
	char** arr=(char**)malloc(sizeof(char*)*(k+1));
	for(int i=0;i<=k;i++)
	{
		arr[i] = (char*)malloc(sizeof(char)*2);
		arr[i][0]=48;
		arr[i][1]='\0';
	}

	arr[0][0]=49;
	arr[0][1]='\0';
	char* temp;
	char * toFree;
	char * zero=(char*)malloc(sizeof(char)*2);
	zero[0]=48;
	zero[1]='\0';
	for(int i=1;i<=n;i++)
	{
		int t = k;
		if(i<k)
			t = i;
		for(int j=t;j>0;--j)
		{
			temp = intal_add(arr[j],arr[j-1]);
			toFree=arr[j];
			arr[j]=intal_add(temp,zero);
			free(toFree);
		}
	}
	char* result =intal_add(arr[k],zero);
	for(int i=0;i<=k;i++)
		free(arr[i]);
	free(arr);
	free(zero);
	return result;

}

// Returns the offset of the largest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_max(char **arr, int n)
{
	int max=0;
	for(int i=1;i<n;i++)
	{
		int k=intal_compare(arr[max],arr[i]);
		if(k==-1)
			max=i;
	}
	return max;
}

// Returns the offset of the smallest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_min(char **arr, int n)
{
	int min=0;
	for(int i=1;i<n;i++)
	{
		int k=intal_compare(arr[min],arr[i]);
		if(k==1)
			min=i;
	}
	return min;
}

// Returns the offset of the first occurrence of the key intal in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
int intal_search(char **arr, int n, const char* key)
{
	int t=-1;
	for(int i=0;i<n;i++)
	{
		int k=intal_compare(arr[i],key);
		if(k==0)
			return i;
	}
	return t;
}

// Returns the offset of the first occurrence of the key intal in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
// The implementation should be a O(log n) algorithm.
int intal_binsearch(char **arr, int n, const char* key)
{
	int start=0;
	int end=n-1;
	int mid=(start+end)/2;
	while(start<=end)
	{
		int k=intal_compare(arr[mid],key);
		if(k==0){
			if(mid>start)
			{
				if(intal_compare(arr[mid-1],key)==0)
					end=mid-1;
				else
					return mid;
			}
			else
				return mid;
		}
		else if(k==-1)
		{
			start=mid+1;
		}
		else
			end=mid-1;
		mid=(start+end)/2;
	}
	return -1;
}

static void heapify(char** arr,int n,int i)
{
int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l<n && intal_compare(arr[l],arr[largest])==1)
        largest = l;

    if(r<n && intal_compare(arr[r],arr[largest])==1)
        largest = r;

    if(largest!=i)
    {
        char* temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;
	heapify(arr,n,largest);
    }
}


// Sorts the array of n intals.
// 1 <= n <= 1000
// The implementation should be a O(n log n) algorithm.
void intal_sort(char **arr, int n)
{
for(int i=(n/2-1);i>=0;i--)
    heapify(arr,n,i);
   
    for(int i=n-1;i>0;i--)
    {
        char* temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr,i,0);
    }
}

// Coin-Row Problem - Dynamic Programming Solution
// There is a row of n coins whose values are some positive integers C[0..n-1].
// The goal is to pick up the maximum amount of money subject to the constraint that
// no two coins adjacent in the initial row can be picked up.
// 1 <= n <= 1000
// The implementation should be O(n) time and O(1) extra space even though the DP table may be of O(n) size.
// Eg: Coins = [10, 2, 4, 6, 3, 9, 5] returns 25
char* coin_row_problem(char **arr, int n)
{
	char* result;
	if(n==0)
	{
		result = (char*)malloc(sizeof(char)*2);
		result[0] = '0';
		result[1] = '\0';
	}
	char * prev;
	prev = (char*)malloc(sizeof(char)*2);
	prev[0] = '0';
	prev[1] = '\0';
	char* zero = (char*)malloc(sizeof(char)*2);
	zero[0] = '0';
	zero[1] = '\0';
	char * cur=intal_add(arr[0],prev);
	char* next;
	char* sub;
	char * tofree;
	for(int i=1 ; i<n ; i++)
	{
		sub = intal_add(prev,arr[i]);
		if(intal_compare(sub,cur)==1)
			next = sub;
		else{
			next = intal_add(cur,zero);
			free(sub);
		}

		tofree=prev;
		prev=cur;
		cur = next;
		free(tofree);
	}
	free(prev);
	return cur;
}