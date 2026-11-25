#ifndef tlogRtlog_H
#define tlogRtlog_H
#define MAXFLDS 100
#define SMALL 100
#define MEDIUM 100
#define LARGE 500
#define MAX 1000
#define MAXFLDSIZE 1000
#include "paths.h"

char tlogname[256];
char tlog_date[10];
char tlog_time[5];
char Rtlogname[256];
char Org_Rtlogname[256];
char dclosename[256];
char last_four_tlogname[6];
char first_four_tlogname[6];
char LogFileName[MAXFLDS];

float calculated_discount_amt=0;
int record_count=0;
int current_line_counter=0;
char string15_2part[MAXFLDS];
int min_06=0;
int file_count=0;
int no_of_bin_digits=0;

FILE *outfile;
FILE *logfile;
FILE *dclose;
FILE *dclose1;
FILE *FileArray[10];

char transaction_line[500];
char CurrentDate[50];
char LogMode[2];
char message[1024];
char dclose_date[12];
int LineCounter[10];


char tdisc='N';
char cash_flag='N';
/* tax flags */
char a_flag='N';
char b_flag='N';
char c_flag='N';
char d_flag='N';
char manual_tax='N';
char manual_written='N';
char transaction_taxexmpt='N';
char Dclose_Done='N';
char v_00_15_head='N';
char start_dclose='N';
char sys_cash='N';
char manual_tax_bucket='N'; /*Version 2.0 : Added new tax code "RDTX4" for Manual tax*/


int file_counter=0;
int zero_counter=0;
int six_counter=0;
int tax_08_counter=0;
int twelve_counter=0;
int fourteen_counter=0;
int fifteenB_counter=0;
int seventeen_counter=0;
int total_08_tax=0;
int v_00_15_counter=0;

int number_of_fields=0;
int field_count_08=0;
int zero_fields=0;
int dclose_line_counter=0;
int head_counter=0;
int transaction_number;
int Head_net_positive=0;
int Head_net_negative=0;
int thead_no =0;
int ttail_no=0;
int transaction_item_count=0;
int total_lines_in_file=0;

struct Zero0
{
	int Header_Record_Number[10];
	char string_type[3];
	char terminal_number[5];
	char operator_number[10];
	char transaction_number[6];
	char transaction_type[3];
	char number_of_strings[5];
	char net_postive_amount[10];
	char net_negative_amount[10];
	char net_total_amount[10];
	char net_noncash_total[10];
	char operatotr_password[15];
	char date_of_transaction[10];
	char time_of_transaction[8];
	char indicat0[9];
	char indicat1[9];
	char ringtime[9];
	char tendertime[9];
	char no_sales_time[9];
	char inactive_time[10];
	char net_cash[10];
	char binindicat0[16];
} v_00,v_00_b[MAX];
struct Zero1
{
	int Header_Record_Number[10];
	char string_type[3];
	char org_terminal_number[5];
	char org_operator_number[5];
	char org_transaction_number[6];
	char org_date_of_transaction[10];
        char org_time_of_transaction[5];
} v_01;
struct Zero2
{
	int Header_Record_Number[10];
	char string_type[3];
	char item_code[25];
};


struct Zero4
{
	int Header_Record_Number[10];
	char string_type[3];
	char tender_type[4];
	char tender_amount[10];
	char tender_amount_f[10];

} v_04;
struct Zero5
{
	int Header_Record_Number[10];
	char string_type[3];
	char store_closing_date[12];
	char store_closing_time[8];
} v_05;
struct Zero6
{
	int Header_Record_Number[10];
	char DataExists;
	char string_type[3];
	char item_code[25];
	char dept_no[9];
	char item_amount[15];
	char tax_plan[9];
	char indicat0[9];
	char indicat1[9];
	char binindicat0[16];
	char bintaxplan[16];
	char GSTTax;
	int index_10;
} v_06[MAX];


struct Zero8
{
	int Header_Record_Number[10];
	char string_type[3];
	char customer_account_number[25];
	char amount[10];
	char tax_code[6];
	char indicat0[5];
	char binindicat0[16];
} v_08[MAX],v_08_tax[MAX];

struct Zero9
{
	int Header_Record_Number[10];
	char string_type[3];
	char discount[5];
	char discount_seq[11];
} v_09[MAX] = {0};

struct Zero9P
{
	int Header_Record_Number[10];
	char string_type[3];
	char overflag[5];
	char item_code[25];
	char override_price[21];
	char reason_code[9];
} v_09P[MAX]={0};

struct Zero7
{
	int Header_Record_Number[10];
	char string_type[3];
	char group[6];
	char quantity[15];
	char sale_quantity[15];
	char quantity_over[10];
	char filler[10];
	char price_over[10];
} v_07[MAX];

struct Zero10
{
	int Header_Record_Number[10];
	char string_type[3];
	char discount_code[23];
	char discount_amount[10];
	char discount_percent[5];
	char indicat0[6];
	char Extra[20];
	char binindicat0[16];
} v_10[MAX][SMALL],v_10_8[MAX][SMALL];


struct Zero11
{
	char string_type[3];
	char tender[25];

} v_11[SMALL];

struct Zero12
{
	int Header_Record_Number[10];
        char string_type[3];
	char tender_type[9];
	char tender_amount[25];
	char customer_account[22];
	char customer_status[9];
	char indicat0[9];
	char Extra1[9];
	char Extra2[15];
	char binindicat0[16];

} v_12[MEDIUM];

struct Zero14
{
	int Header_Record_Number[10];
        char string_type[3];
	char tax_a[10];
	char tax_b[10];
	char tax_c[10];
	char tax_d[10];
	char indicat0[5];
	char binindicat0[16];
} v_14[SMALL];

struct First15
{
	int Header_Record_Number[10];
	char string_type[3];
	char unit_type[11];
	char unit_number[7];
	char unit_state[5];
	char unit_version[11];
} v_1_15;

struct Zero15
{
        int Header_Record_Number[10];
        char string_type[3];
        char type_of_15[8];
        char current_date[10];
        char dclose_date[10];
        char cash_amount[20];
        char check_amount[20];
        char net_amount[20];
        char oper_id[15];
} v_15_b[MAX];

struct Dclose
{
	char dclose_date[10];
	int LineNumber;
} DcloseDates[MAX];

struct Zero17
{
	int Header_Record_Number[10];
	char string_type[3];
	char register_number[6];
	char amount[15];
	char transaction_number[5];
} v_17[MAX];


void substr(char *dest, char *src, int startpos, int nof_char)
{
        int i,j;

        memset(dest, '\0', nof_char+1);

        for(i=nof_char, j=0;i;i--,j++)
        {
                if(src[startpos + j]=='\0')
                        break;
                dest[j] = src[startpos + j];
        }
        dest[j] = '\0';
}
void GetCurrentDateTime(char *DateTime,int HoldSize,char *RequiredFormat)
{
        time_t Now = time(0);
        strftime(DateTime,HoldSize,RequiredFormat,localtime(&Now));
}


void LOG_MESSAGE(char* message)
{

	strcpy(LogFileName,LogFilePath);
	strcat(LogFileName,"TLOG2RTLOG_");
	GetCurrentDateTime(CurrentDate,25,"%d%m%Y");
	strcat(LogFileName,CurrentDate);
	strcat(LogFileName,".log");
	if((logfile = fopen(LogFileName,"a")) == NULL)
	{
		printf("Unable to Open LogFile");
	}
	fprintf(logfile,"%s\n",message);
	fclose(logfile);
}

void binnum(int num,int *arr)
{
int bit;
int dv;
int *ref=arr;
if (num == 0) {
return;
}
do
{
        dv=num >> 1;
        bit=num & 1;
        *arr=bit;
        /*printf("%d\tarr:%d\n",num,*arr); */
        arr++;
        num=dv;
}while (num!=0);
arr=ref;
}

void hex2bin(char *sh,char *arr,int *no_of_bin_digits)
{
	int number;
	int bit;
	int no_of_bits=0;
	int dv;
	strcpy(arr,"");
	char *ref=arr; 
	int ch;
	int i=0,j=0;
	number = 0;
	i =strlen(sh);
	j=0;
	while(i!=0)
	{
		ch = sh[j];
		/*printf("Ch:%d\t%d\t%d\n",ch,'7',ch-'7'); */
		if(('0' <= ch && ch <= '9'))
		{
			number = number * 16;
			/*printf("Number :%d\n",number);*/
			number = number + (ch - '0');
		}
		if(('A' <= ch && ch && ch <= 'Z'))
		{
			number = number * 16;
			/*printf("Number :%d\n",number); */
			number = number + (ch - '7');
		}
		/*printf("Number :%d\n",number); */
		i--;
		j++;
	}
/*	printf("The O/p No in Decimal is : %d\n",number);
	printf("I am in Binarr\n"); */
		char temp;
        do
        {
		temp='';
                /*printf("In side Loop\n"); */
                dv=number >> 1;
                bit=number & 1;
		temp = (char)(((int)'0')+bit);
		/*printf("number:%d\tdv:%dbit:%d\ttemp:%c\n",number,dv,bit,temp);*/
                /**arr=(char) bit;*/
		/*printf("temp:%c\n",temp); */
		*arr=temp;
		no_of_bits++;
                /*printf("%d\t%d\t%c\n",number,bit,*arr); */
                arr++;
                number=dv;
		if(number==0) 
		{
			*arr='';
		}
        }while(number!=0);
	arr=ref;
	/*printf("InSide:");
	for(int j=0;j<16;j++)
	printf("%c\t",arr[j]);
	printf("\n"); */
	*no_of_bin_digits=no_of_bits;
}

#endif
