#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int operator_checker(char* str, int n, float* minus, int* status,float* result, int* r);
int calc(float* result, int* r, char oper);
void error(char* str);
float calculator(char* str);

int error_flag = 0;

typedef struct {
	char a;  // 실제 연산기호 저장
	int i;  // 연산기호의 우선순위 저장
}opers;

/* 최종 계산값 도출 */
/* parameter : 계산할 문자열 */
/* return : 정상 == 계산결과, 비정상 == 프로그램 종료*/
float calculator(char* str)
{
	float result[10] = { 0 };  // 숫자 저장 스택
	int r = 0;  // result count
	opers oper[10];  // 연산기호, 괄호 저장 스택 (구조체)
	int op = 0;  // oper count		
	float minus = 1;  // 음수변환자
	float f_count = 10;  // 실수 자릿수 계산

	int n = -1;  // str count
	int c,status = 0; // c : 연산자 우선순위, status = 숫자 시작과 끝 상태; 
    int flag = 0;
	while(str[++n] != '\0')
	{
		c = operator_checker(str, n, &minus, &status,result,&r);
		
		/* '-'가 연산자가 아니라 음수표기인경우 함수에서 처리만 하고 그냥 넘김 */
		if (c == -1) {continue;};

		/* 숫자일 경우 변환해서 바로 저장 */
		if (c == 0)
		{
			if (status != 2)
			{
				result[r] = result[r] * 10.f + ((float)(str[n] - '0'));
				status = 0; 
			}
			else
			{
				result[r] = result[r] + ((float)(str[n] - '0') / f_count);
				f_count *= 10.f;
				status = 2; 
			}
			continue;
		} 
		
		/* 연산자 등장 시 */
		if (c > 0)
        {
			/* 숫자가 저장된 직후 상태인 status == 0,2일때만 r++시켜줌 */
			if (status == 0 || status == 2)
			{
				/* 첫 문자가 괄호나 연산자로 시작할 경우 r++해주면 안됨 */
				if ( ( n == 0 && (str[n] == '+' || str[n] == '-' || str[n] == '(' || str[n] == 'a') )){}
				else
				{   
					r++;
					status = 1;  // 다시 숫자 저장될 때까지는 r++ 안되게 1로 변경
					f_count = 10;  
				}
			}
			/* 첫 연산자일 경우 무조건 저장 */
			if (op == 0)
			{
				oper[op].a = str[n];  // 실제 연산자 저장
				oper[op++].i = c;  // 연산자 우선순위 저장
			}
			/* 두번째부터는 우선순위 비교 후 처리 */
			else if (op > 0)
			{
				/* 괄호 및 ^기호가 아닌 다른 기호가 나왔을 때 */
				if (c > 0 && c < 3)
				{
					/* 현재 연산자보다 우선순위가 높거나 같은 연산자는 계산 처리 */
					/* 이전 연산자가 열린괄호면 수행 중단 */
					while (op > 0 && oper[op - 1].i >= c && oper[op - 1].i != 4)
					    int a =calc(result, &r, oper[op-- - 1].a);
                        
				}
				
				/* 닫힌괄호가 나왔을 때 */
				else if (c == 5)
				{   
					/* 열린괄호가 나올때까지 계산 처리 */
					while (op > 1 && oper[op - 1].i != 4)
                        int b =calc(result, &r, oper[op-- - 1].a);
					/*열린 괄호 제거 */
					op--;
				}
			
				/* 닫힌 괄호가 아니라면 현재 연산자 저장 */
				if (c != 5)
				{
					oper[op].a = str[n];/*printf("%c",str[n]);*/
					oper[op++].i = c;
				}
			}
		}		
	}

	/* 숫자로 끝난 경우, r++이 되지 않았기 때문에 마지막으로 해줌 */
	if (status == 0 || status == 2) r++;
	/* 남은 연산자 모두 계산 */
	while (op != 0)
	{
        if(oper[op-1].i == 4) 
		{
			error("연산자가 잘못입력되어있음");
			error_flag = 1;
		}
        float c= calc(result, &r, oper[op-- - 1].a);
    }
    	/* result에는 최종 값 하나만 */
	if (r == 1)
	{
		
		return result[r - 1];
	}
	else 
	{printf("%d %d",result[0], result[1]);
		error("계산이 비정상 종료되었습니다. "); 
		error_flag = 1;
	}
	return 0;	
}

int operator_checker(char* str, int n, float* minus, int* status,float* result, int* r)
{
	static char operators[] = "+-*/^()a";
	static int operator_order[] = { 1,1,2,2,3,4,5,2 };
	static int pre_str = 0;	// 한칸 전 값을 저장하고 있음
	/* 첫 문자가 +, -, ( 가 아니라면 에러처리 */
	if (n == 0 && (str[n] == '*' || str[n] == '/' || 
							str[n] == '^' || str[n] == ')'))
	{
		error("첫 문자가 잘못되었습니다.");
		error_flag = 1;
	}
	/* 해당 문자열이 숫자라면 0값 리턴 */
	if (str[n] >= '0' && str[n] <= '9')
	{
		pre_str = 0;
		return 0;
	}
	
	/* 소숫점이라면 status 상태값 바꾸고 -1값 리턴 */
	if (str[n] == '.')
	{
		*status = 2;
		return -1;
	}

	/* 연산기호라면 연산자 우선순위 번호 리턴 */
	for (int w = 0; w < 7; ++w)	
	{
		if (str[n] == operators[w])
		{
			/* 연산기호가 아니라 음수기호일 경우 */
			/* 첫번째에 '-'기호일 때 음수 처리 */
			/* str[i] == '-'이면서 str[i-1]이 연산자, 열린괄호일 경우 음수 처리 */
			if (str[n] == '-' && ((n == 0) || 
					(n > 0 && pre_str > 0 && pre_str < 5)))
			{
				pre_str = operator_order[w];
                result[(*r)] = -1.0f;
                (*r)++;
                *status = 1;
                str[n] = 'a';
				return 2;
			}
			/* 괄호나 '-'가 아닌데 앞이 기호라면 기호 중복이므로 에러 처리 */
			else if (n > 0 && str[n] != '-' && str[n] != '(' &&
						str[n] != ')' && pre_str > 0 && pre_str < 5)
			{
				error("기호가 중복으로 입력되었습니다.");
				error_flag = 1;
			}
			/* 음수기호가 아닌 그냥 연산자일 경우 */
			pre_str = operator_order[w];
			return operator_order[w];
		}
	}
	/* 숫자, 연산자, 괄호 외 문자가 입력돼있으면 프로그램 종료 */
	error("수식에 잘못된 문자가 포함되었습니다.");
	error_flag = 1;
	return 0;  
}

int calc(float* result, int* r, char oper)
{
	/* 연산자가 있는데 result에 값이 하나라면 비정상 처리 */
	if (*r < 2)
	{
			error("연산자가 잘못 입력되었습니다.");
			error_flag = 1;
	}

	else if (oper == '+')
	{  
		result[*r - 2] += result[*r - 1];
		result[(*r)-- - 1] = 0;
	}
	else if (oper == '-')
	{
		result[*r - 2] -= result[*r - 1];
		result[(*r)-- - 1] = 0;
	}
	else if (oper == '*' || oper == 'a')
	{
        result[(*r) - 2] *= result[*r - 1];
		result[(*r)-- - 1] = 0;
	}
	else if (oper == '/')
	{
		result[(*r) - 2] /= result[*r - 1];
		result[(*r)-- - 1] = 0;
	}
	else if (oper == '^')
	{
		float temp = 1;
		for (int i = 0; i < result[*r - 1]; ++i)
			temp *= result[*r - 2];
		result[*r - 1] = 0;
		result[(*r)-- - 2] = temp;		
	}
    return result[*r - 1];
}

void error(char* str)
{
	printf("%s\n", str);
}