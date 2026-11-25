/*********************************************************************************************************/
/*	Base Program: tlog2Rtlog.c                                                                       */
/*	Program Logic: This is the main executable program which will take the ASCII file of the TLOG as */
/*	input and read each and every line and stores in the input structures basing on the string types */
/*	of the TLOG.In this program we are not considering the 15 and 16 strings as part of the conversi-*/
/*	on. We are only taking the first 15 string in order to get the store and the country of the store*/
/*	The input data structures will be framed according to the format of the RTLOG and stored in the  */
/*	out put RTLOG data structures. The formation is specific to MICHAELS as there are lot of custom  */
/*	strings which can not be handled as generalized way.                                             */


/* VER  DEVELOPER             DATE            CHANGE DESCRIPTION                                      */
/* ------------------------------------------------------------------                                 */
/* 1.0  SURYANARAYANA    24/03/2013       Initial Creation.                                           */
/* 1.1  SRINATH          11/08/2014       PRB0004116 - Handled core dump issue (RTLOGStructs.h)       */
/*                                        PRB0004115 - Handled dummy RTLOG creation (tlog2Rtlog.c)    */
/* 2.0  JAYANTHI         12/10/2015       Added new tax code "RDTX4" for Manual tax			    */
/*********************************************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "tlogRtlog.h"
#include "GetStringType.h"
#include "RTLOGStructs.h"

/* ========== THEAD Database Operations (merged from THEADDbOps.c) ========== */

/* Maximum records to batch in one insert */
#define MAX_THEAD_BATCH 500

/* Structure to hold THEAD data for database insertion */
struct THEAD_DB_Record
{
	char STORE[10];                    /* LocationNumber from FHEAD */
	char BUSINESS_DATE[8];             /* BusinessDate from FHEAD (YYYYMMDD) */
	char TRAN_DATETIME[14];            /* TransactionDate from THEAD (YYYYMMDDHHmmss) */
	char REGISTER[5];                  /* Register from THEAD */
	char TRAN_NO[10];                  /* TransactionNumber from THEAD */
	char CASHIER[10];                  /* Operator/Cashier from THEAD */
	char SALESPERSON[10];              /* SalesPerson from THEAD */
	char TRAN_TYPE[6];                 /* TransactionType from THEAD */
	char SUB_TRAN_TYPE[6];             /* SubTransactionType from THEAD */
	char ORIG_TRAN_NO[10];             /* OrigTxnNo from THEAD */
	char ORIG_REG_NO[5];               /* OrigRegNo from THEAD */
	char REF_NO1[30];                  /* ReferenceNumber1 from THEAD */
	char REF_NO2[30];                  /* ReferenceNumber2 from THEAD */
	char REF_NO3[30];                  /* ReferenceNumber3 from THEAD */
	char REF_NO4[30];                  /* ReferenceNumber4 from THEAD */
	char VALUE[20];                    /* Value from THEAD */
	char VALUE_SIGN[1];                /* Value Sign (P/N) from THEAD */
	char BANNER_NO[4];                 /* BannerId from THEAD */
	char ROUNDED_AMT[20];              /* RoundedAmount from THEAD */
	char ROUNDED_OFF_AMT[20];          /* RoundedOffAmount from THEAD */
	int  PROCESSED;                    /* 0=pending, 1=inserted, 2=failed */
	char ERROR_MSG[256];               /* Error message if failed */
};

/* Global variables for THEAD batch collection */
struct THEAD_DB_Record thead_records[MAX_THEAD_BATCH];
int thead_record_count = 0;
FILE *thead_error_log = NULL;
char thead_error_logfile[256];
FILE *thead_input_log = NULL;

/* Function prototypes for THEAD operations */
void InitializeTHEADDbOps(char *log_directory);
void CollectTHEADRecord(char *store, char *business_date, char *tran_datetime, char *register_no,
                        char *tran_no, char *cashier, char *salesperson, char *tran_type,
                        char *sub_tran_type, char *orig_tran_no, char *orig_reg_no,
                        char *ref_no1, char *ref_no2, char *ref_no3, char *ref_no4,
                        char *value, char *value_sign, char *banner_no, char *rounded_amt,
                        char *rounded_off_amt);
int GenerateTHEADInsertSQL(char *sql_filename);
int ExecuteTHEADInsert(char *sql_filename);
void LogTHEADError(char *tran_no, char *error_msg);
void CloseTHEADDbOps(void);
void LogTHEADBatchBeforeInsert(void);
static void EscapeSQLString(char *src, char *dest, int dest_size);


void FieldExtract( char *record, char *delim, char arr[][MAXFLDSIZE],int *fldcnt);
/*void substr(char *dest, char *src, int startpos, int nof_char); */
void writeRtlogHeader(int string_counter);
void writeRtlogDHeader(int string_counter);
void writeDcloseTransaction(int string_counter,FILE *dclose);
void writeRtlogTransaction();
void writeRtlog();
void DCLOSEHeadTail(int string_counter,FILE *dclose);
void DcloseFileOpen();
void time_stamp_extract(char *tm_stamp);

/* GetStringType.h Functions 
int GetStringType(char  *SourceString);
void store_in_struct(int strng_type,char  hldarry[][MAXFLDSIZE],int no_of_flds);
void string_pad(char * src_string, size_t padlen, char * pad, char *LpadRpad);
void GetCurrentDateTime(char *DateTime,int HoldSize,char *RequiredFormat);
void number_pad(char *dest_string,int int_number,int no_of_chars);
void GetReSATransactionType(char *POSTransactionType,char *ReSA_Transaction_type);
void writeTHEAD();
void writeTITEM();
*/
char FHEAD_transaction_line[100];
int main(int argc ,char *argv[])
{
	FILE *tlogascii;
	char line[MAX],itemline[MAX];
	int field_count=0;
	char firststring[MAXFLDS];
	char item_first_string[MAXFLDS];
	char previous_transaction_type[10];
	char holdarray[MAXFLDS][MAXFLDSIZE];
	int string_type;
	char indicat0_8[4];
	char indicat0_10[4];
	int Header_Records=0;
	char *last_occurance_pointer;
	char lfile[20];
	/*char manual_tax='N';*/
	char bin_8_indicat0[16];
	char bin_10_indicat0[16]; 
	int no_of_bits=0;
	char extension[4];

	int previous_string_type;

	if (argc !=3)
	{
		printf("tlog2Rtlog <Ascii Tlog Name>\n");
		printf("Usage: tlog2Rtlog 6744TLOG201212129999.ascii N\nExiting..");

		exit(1);
	}

	/* TLOG NAME from the Argument */

	strcpy(tlogname,argv[1]);
	
	substr(last_four_tlogname,tlogname,strlen(tlogname)-10,4);
	last_occurance_pointer=strrchr(tlogname,'/');
	substr(first_four_tlogname,tlogname,last_occurance_pointer-tlogname+1,4);
	
	strcpy(LogMode,argv[2]);

	/* THEAD Database Operations - Initialize */
	char log_directory[256];
	char sql_temp_file[512];
	int db_insert_result;
	
	strcpy(log_directory, RtlogPath);
	InitializeTHEADDbOps(log_directory);

	if((tlogascii = fopen(tlogname,"r+")) == NULL)
	{
		printf("Unable to open %s file in Read Mode\nExiting..",tlogname); 
		sprintf(message,"Unable to Open %s File in READ Mode\nExiting..",tlogname);
		LOG_MESSAGE(message);
		exit(1);
	} 

	while(fgets(itemline,sizeof(itemline),tlogascii)!=0)
	{	
		int i=0;
		int j=0;
		int count_11=0;
		char string15Chk[10];
		record_count++;
		if(record_count==1) substr(string15Chk,itemline,0,8);
		substr(firststring,itemline,0,2);
		if(strcmp(string15Chk,"15|STORE") && record_count == 1)
		{
			/*printf("tlog2Rtlog.c: Missing String 15. Please Correct"); */
			sprintf(message,"Missing String 15 in File %s \n",tlogname);
			LOG_MESSAGE(message);
			exit(1);
		}
		/*printf("RecordNumber: %d\n%s",record_count,itemline); */
		/*printf("Firststring: %s\n",firststring); */
		if (strcmp(firststring,"00"))
		{
			string_type=GetStringType(firststring);	
			/*printf("Out of\n"); */
			/* Extract the data into individual fields */
			FieldExtract(itemline,"|",holdarray,&field_count);
			/*for(i=0;i<field_count;i++)
			{
				printf("\tField number: %3d==%s\n",i,holdarray[i]);  
			} */
			if (record_count==1 && string_type==15) 
			{
				fprintf(stderr, "Before store_in_struct: type=%d\n", string_type);
				store_in_struct(string_type,holdarray,record_count);
				fprintf(stderr, "After store_in_struct\n");
				if(strcmp(v_1_15.unit_number,first_four_tlogname))
				{
					printf("TLOGNAME store number and Inside Store Number Not matching\n");
					sprintf(message,"TLOG name Store:%s and inside store:%s are different:\n",first_four_tlogname,v_1_15.unit_number);
					LOG_MESSAGE(message);
					exit(1);
				}
			}
		}
		else
		{
			do
			{
				head_counter=0;
				string_type=GetStringType(firststring);	
				/*printf("In side : %s\n",itemline); */
				if(string_type==15) substr(string15_2part,itemline,4,4);
				if (string_type!=16) 
				{
					fprintf(stderr, "Before FieldExtract\n");
					FieldExtract(itemline,"|",holdarray,&field_count);
					fprintf(stderr, "After FieldExtract, fields=%d\n", field_count);

					if(string_type==10)
					{
						number_of_fields=field_count;
						/*printf("TXN : %s\tSix: %d\t10: %d\n",v_00.transaction_number,six_counter,number_of_fields);  */
					}
					if(string_type==8) field_count_08=field_count;

					/*for(i=0;i<field_count;i++)
					{
						printf("\tField number: %3d==%s\n",i,holdarray[i]); 
					}  */
					if(string_type==0) 
					{
						zero_fields=field_count;
						/*printf("Txn: %s\tNumber Of Fileds:%d\n",holdarray[3],number_of_fields]); */
					}
						
					if(Header_Records == 0 && string_type==0)
					{
						char time_stamp[10];
						
						time_stamp_extract(time_stamp);
						
						if(strlen(holdarray[11])<6) strcpy(tlog_date,holdarray[10]);
						else strcpy(tlog_date,holdarray[11]);
						/*printf("Tlog Date: %s\n",tlog_date); */
						strcpy(extension,"TMP"); 
						strcpy(Rtlogname,RtlogPath);
						strcpy(Org_Rtlogname,Rtlogname);
						strcat(Rtlogname,extension);
                                        	strcat(Rtlogname,"_"); 
						strcat(Rtlogname,"RTLOG_");
						strcat(Org_Rtlogname,"RTLOG_");
                                        	strcat(Rtlogname,v_1_15.unit_number);
                                        	strcat(Org_Rtlogname,v_1_15.unit_number);
                                        	strcat(Rtlogname,"_");
                                        	strcat(Org_Rtlogname,"_");
                                        	strcat(Rtlogname,tlog_date);
                                        	strcat(Org_Rtlogname,tlog_date);
                                        	strcat(Rtlogname,"_");
                                        	strcat(Org_Rtlogname,"_");
						strcat(Rtlogname,last_four_tlogname);
						strcat(Org_Rtlogname,last_four_tlogname);
                                        	strcat(Rtlogname,"_");
                                        	strcat(Org_Rtlogname,"_");
						strcat(Rtlogname,time_stamp);
						strcat(Org_Rtlogname,time_stamp);
                                        	strcat(Rtlogname,".dat");
                                        	strcat(Org_Rtlogname,".dat");
						sprintf(message,"tlog2Rtlog.c:Store:%s InPut:%s Output RTLOG:%s",v_1_15.unit_number,tlogname,Rtlogname);
						fprintf(stderr, "Before RTLOG path LOG_MESSAGE\n");
						LOG_MESSAGE(message);
						fprintf(stderr, "After RTLOG path LOG_MESSAGE\n");
                                        	if(( outfile = fopen(Rtlogname,"w")) == NULL)
                                        	{
                                                	/*printf("Unable to open %s file in Write Mode\nExiting..",tlogascii);*/
							sprintf(message,"tlog2Rtlog.c:%s:Unable to open %s File in WRITE Mode\nExiting..",v_1_15.unit_number,Rtlogname);
							LOG_MESSAGE(message);
                                                	exit(1);
                                        	}

                                        	/*writeRtlogHeader(0);
                                        	free(transaction_line); */
						StoreInFHEAD(0);
						fprintf(outfile,"%s\n",FHEAD_v00);
						free(FHEAD_v00);
					}
					/*printf("String:%d\n",string_type); */

				/* Storing the extracted data into Structures */
					if(string_type==0 || string_type==4 ||string_type==6 || string_type==7 || string_type==8 || string_type==9 || string_type==10 || string_type==11 || string_type==12 || string_type==14 || string_type==17 || (string_type==15 &&(!strcmp(holdarray[1],"BANKDP"))) || (string_type==9 &&(!strcmp(holdarray[1],"~"))))
					{
						/*printf("string:%d\tHead:%d\n",string_type,Header_Records); */
						if(string_type == 0 && Header_Records!=0)
						{
							writeRtlog();
						}	
					
						if(string_type==0) 
						{
							store_in_struct(string_type,holdarray,0);
							Header_Records++;
							if(atoi(v_00.transaction_type)==56 && (v_00.binindicat0[3] !=1 || v_00.binindicat0[5] !=1))
							{
								v_00_15_counter++;
								v_00_15_head='Y';
								store_in_struct(string_type,holdarray,v_00_15_counter-1);
								/*printf("txn number: %s\ttranType:%s\n",v_00_b[v_00_15_counter-1].transaction_number,v_00_b[v_00_15_counter-1].transaction_type);*/
								v_00_15_head='N';
							}
						}
						
						if(string_type==6 || string_type==7 || string_type==9 ||string_type==10 ||(string_type==9 && !strcmp(holdarray[1],"~")))				
						{
							if(string_type==6)
							{
								store_in_struct(string_type,holdarray,six_counter);
								/*printf("Txn : %s\t:%d\n",v_00.transaction_number,six_counter);    */
								six_counter++;
							}
							else if(string_type==9 && !strcmp(holdarray[1],"~"))
							{
								/*printf("Txn:%s\t%d\n",v_00.transaction_number,six_counter); */
								/*printf("%s\t%d:%d\n",v_00.transaction_number,string_type,six_counter); */ 
								store_in_struct(string_type,holdarray,six_counter);
							}
							/*else if((string_type==10 && atoi(holdarray[4])==8 ) || (string_type==10 && !strncmp(holdarray[4],"A",1))) */
							else if(string_type==10 )
							{
								hex2bin(holdarray[4],&bin_10_indicat0[0],&no_of_bits);
								if(bin_10_indicat0[3]=='1')
								{
									printf("I am in 10 TDISC :%s\n",v_00.transaction_number); 
									tdisc='Y';
									if(bin_10_indicat0[1] != '1')
									{
										calculated_discount_amt=0;
										/*printf("TDISC\n");*/
										/*printf("Hld:%s-%c\n",holdarray[2],tdisc); */
										for(int i=0;i<six_counter;i++)
										{
											store_in_struct(string_type,holdarray,i);
											/*printf("Amount: %s\n",v_10_8[i][0].discount_amount); */
										}
									}
									if(bin_10_indicat0[1] == '1')
									{
										/*printf("Void\n"); */
										for(int i=0;i<six_counter;i++)
										{
											memset(&v_10_8[i][0],0,sizeof(v_10_8[i][0]));
											v_06[i].DataExists='0';
										}

									}
									tdisc='N';
									bin_10_indicat0[0]='\0';
								}
								
								/* To handle the voided transactional discount */
								else if(atoi(v_08[six_counter-1].string_type)==8)
								{
									for(int i=six_counter-1;i>=0;i--)
									{
										/*printf("six:%s\n",v_06[i].string_type); */
										if(!strcmp(v_06[i].string_type,"06"))
										{
											store_in_struct(string_type,holdarray,i);
											v_06[i].index_10=v_06[i].index_10 + 1;
											i=-1;
										}
									}
								}
								else 
								{
									store_in_struct(string_type,holdarray,six_counter-1);
									/* 25-AUG-2013 : This is to handle the multiple discount lines for one item */

									v_06[six_counter-1].index_10=v_06[six_counter-1].index_10 + 1;

									/* 25-AUG-2013 : This is to handle the multiple discount lines for one item */
								}
							
							memset(&bin_10_indicat0,0,sizeof(bin_10_indicat0));
							}
							else if(string_type==7 || string_type==9) /* for 07 and 09 strings */ 
							{
								store_in_struct(string_type,holdarray,six_counter-1);
							}
						}
						if(string_type==8)
						{
							(field_count_08<5)?strncpy(indicat0_8,holdarray[3],4):strncpy(indicat0_8,holdarray[4],4);  
							
							/*(number_of_fields[string_type]<5)?strncpy(indicat0_8,holdarray[3],4):strncpy(indicat0_8,holdarray[4],4); */
							memset(&bin_8_indicat0,0,sizeof(bin_8_indicat0));
							hex2bin(indicat0_8,&bin_8_indicat0[0],&no_of_bits);

							/*if(atoi(indicat0_8)==880 ) */
							if(bin_8_indicat0[11]=='1' && bin_8_indicat0[7]=='1')
							{
								transaction_taxexmpt='Y';
							}
							else
							{
								/*if(atoi(indicat0_8)==20 || atoi(indicat0_8) ==120 || atoi(indicat0_8) ==220 ||atoi(indicat0_8) == 820 ||atoi(indicat0_8)==920|| atoi(indicat0_8)==40 ||atoi(indicat0_8) ==140||atoi(indicat0_8) ==240|| atoi(indicat0_8)==840 ||atoi(indicat0_8)==940) */
								if(bin_8_indicat0[5]=='1')
								{
									manual_tax='Y';
									store_in_struct(string_type,holdarray,tax_08_counter);
									tax_08_counter++;
									
								}
								
								if(bin_8_indicat0[6]=='1') manual_tax='Y';
								if(bin_8_indicat0[6]=='1' && atoi(holdarray[1])==9)
								{
									/*printf("GST TAX: Txn: %s\n",v_00.transaction_number); */
									for(int i=0;i<=six_counter;i++)
									{
										if(v_06[i].bintaxplan[0]=='1' || v_06[i].bintaxplan[1]=='1' || v_06[i].bintaxplan[2] == '1' || v_06[i].bintaxplan[3] == '1')
										{
											v_06[i].GSTTax='G';
										}
									}
								}
								if(manual_tax=='N')
								{	
									store_in_struct(string_type,holdarray,six_counter);
									six_counter++;
								}
								field_count_08=0; 
								/*number_of_fields[string_type]=0; */
								manual_tax='N';
								memset(&bin_8_indicat0,0,sizeof(bin_8_indicat0));
							}
						}
						if(string_type==11)
                                                {
                                                        store_in_struct(string_type,holdarray,twelve_counter);
                                                        twelve_counter++;

                                                }
						if(string_type==4)
						{
							store_in_struct(string_type,holdarray,twelve_counter);
							twelve_counter++;

						}
						if(string_type==12)
						{
							store_in_struct(string_type,holdarray,twelve_counter);
							twelve_counter++;
						}
						if(string_type==14)
						{
							store_in_struct(string_type,holdarray,fourteen_counter);
							fourteen_counter++;
						}
						if(string_type==15 && !strcmp(holdarray[1],"BANKDP"))
						{
							store_in_struct(string_type,holdarray,fifteenB_counter);
							/*printf("15: %d\n",fifteenB_counter);  */
							/*printf("%d - %s\t%s\n",fifteenB_counter,v_15_b[fifteenB_counter].cash_amount,v_15_b[fifteenB_counter].check_amount);*/
							fifteenB_counter++;
						}
						if(string_type==17)
						{
							store_in_struct(string_type,holdarray,seventeen_counter);
							seventeen_counter++;
						}	
						

						if(!strncmp(LogMode,"I",1)) 
						{
							sprintf(message,"tlog2Rtlog.c:%s:\tTxn:%d\tString:%d",v_1_15.unit_number,transaction_number,string_type);
							LOG_MESSAGE(message);
						}
						/*printf("Txn:%s\tCurrent String:%d\tPrevString:%d\tCurrentType:%s\tPrevType:%s\tSpl:%c\tF00:%c\tF06:%c\ttail:%c\tBank:%c\tHC:%d\n",v_00.transaction_number,string_type,previous_string_type,v_00.transaction_type,previous_transaction_type,spl_flag,first00,first06,tail_there,bank_pvoid_done,head_counter);*/
					
					}
					
				}

			/* Next Line Reading */
				fgets(itemline,sizeof(itemline),tlogascii);
				substr(firststring,itemline,0,2);
				/*printf("After loop: %s\n",firststring); */

			} while(strcmp(firststring,"05")); 

			/*printf("After loop: %s\n",firststring);*/
			if(!strcmp(firststring,"05"))
			{
				writeRtlog();
				
				StoreInFtail(0);	
				fprintf(outfile,"%s\n",FTAIL_v99);
				free(FTAIL_v99);
				start_dclose='Y';
				/*printf("Fifteen Counter:%d\n",fifteenB_counter);  */
				DcloseFileOpen();
				
				for(int i=0;i<fifteenB_counter;i++)
				{
					for(int j=0;j<file_count;j++)
					{
						if(!strcmp(v_15_b[i].dclose_date,DcloseDates[j].dclose_date))
						{
							dclose_line_counter=DcloseDates[j].LineNumber;
							DCLOSEHeadTail(i,FileArray[j]);
							DcloseDates[j].LineNumber=dclose_line_counter;
							j=file_count;
						}

					}	
				} 

				for(int i=0;i<file_count;i++)
				{
					
					dclose_line_counter=DcloseDates[i].LineNumber;

				 	writeDcloseTransaction(i,FileArray[i]);
                        		free(transaction_line);

                        		StoreInTtail(i);
                        		fprintf(FileArray[i],"%s\n",TTAIL_v00);
                        		free(TTAIL_v00);

                        		StoreInFtail(i);
                        		fprintf(FileArray[i],"%s\n",FTAIL_v99);
                        		free(FTAIL_v99);

				}
				start_dclose='N';
				for(int k=0;k<file_counter;k++)
					fclose(FileArray[k]);

				string_type=GetStringType(firststring);
				FieldExtract(itemline,"|",holdarray,&field_count);
				store_in_struct(string_type,holdarray,0); 
				/*printf("Store Closed on: %s\n",v_05.store_closing_date);*/
				/*printf("Store Closing Time: %s\n",v_05.store_closing_time);*/
			
			
			}
		}
	}
	/*printf("Header Record %d\n",Header_Records);*/
	fclose(tlogascii);
	fclose(outfile);
	fclose(logfile);
	fclose(dclose);

	rename(Rtlogname,Org_Rtlogname); 

	/* THEAD Database Operations - Execute insert */
	if (thead_record_count > 0)
	{
		sprintf(sql_temp_file, "%sTHEAD_INSERT_%s.sql", RtlogPath, last_four_tlogname);
		
		fprintf(stderr, "\n=== THEAD Database Insert ===\n");
		fprintf(stderr, "Collected %d THEAD records\n", thead_record_count);
		LogTHEADBatchBeforeInsert();
		
		if (GenerateTHEADInsertSQL(sql_temp_file) > 0)
		{
			db_insert_result = ExecuteTHEADInsert(sql_temp_file);
			
			if (db_insert_result == 0) {
				fprintf(stderr, "THEAD records inserted successfully\n");
				sprintf(message, "tlog2Rtlog.c:%s:THEAD Insert SUCCESS - %d records",
						v_1_15.unit_number, thead_record_count);
				LOG_MESSAGE(message);
			} else {
				fprintf(stderr, "ERROR: THEAD database insert failed\n");
				sprintf(message, "tlog2Rtlog.c:%s:THEAD Insert FAILED - Check logs",
						v_1_15.unit_number);
				LOG_MESSAGE(message);
			}
			
			remove(sql_temp_file);
		}
	}
	
	/* Close THEAD database operations */
	CloseTHEADDbOps();

	return(0);

}
void DcloseFileOpen()
{
	char not_found='Y';
	for(int i=0;i<fifteenB_counter;i++)
	{
		not_found='Y';
		if(i==0) 
		{
			strcpy(DcloseDates[0].dclose_date,v_15_b[0].dclose_date);
			/*printf("x:%d\t%s\n",file_count,DcloseDates[0].dclose_date); */
			file_count++;
		}
		else
		{	
			/*printf("i:%d\n",i); */
			/*for(int j=0;j<file_count;j++) */
			int j=0;
			do
			{
				/*printf("15.Dclose:%s\t Dist:%s\n",v_15_b[i].dclose_date,DcloseDates[j].dclose_date); */

				if(!strcmp(v_15_b[i].dclose_date,DcloseDates[j].dclose_date)) 
				{
					not_found='N';
					j=file_count+1;
				}
				else j++;
			} while(j<file_count);

				if(not_found == 'Y')
				{
					strcpy(DcloseDates[file_count].dclose_date,v_15_b[i].dclose_date);
					/*printf("Y:%d\t%s\n",file_count,DcloseDates[file_count].dclose_date);
					printf("j:%d-File:%d\n",j,file_count);  */
					file_count++;
				}

		}
		

	}

	for(int i=0;i<file_count;i++) 
	{
		char time_stamp[10];
		time_stamp_extract(time_stamp);
		dclose_line_counter=0;
		/*printf("Distinct Dclose Dates: %s\n",DcloseDates[i].dclose_date);  */
		strcpy(dclosename,RtlogPath);
                strcat(dclosename,"RTLOG_");
                strcat(dclosename,v_1_15.unit_number);
                strcat(dclosename,"_D_");
                strcat(dclosename,DcloseDates[i].dclose_date);
		strcat(dclosename,"_");
		strcat(dclosename,last_four_tlogname);
		strcat(dclosename,"_");
		strcat(dclosename,time_stamp);
                strcat(dclosename,".dat");
				
/****Ver 1.1 - Added the below condition to avoid dummy RTLOG creation ************************************/
                if(strlen(DcloseDates[i].dclose_date)!=0)
                {
 
                if(( FileArray[file_counter]= fopen(dclosename,"w")) == NULL)
                {
                  	sprintf(message,"tlog2Rtlog.c:%s:Unable to open %s File in WRITE Mode\nExiting..",v_1_15.unit_number,dclosename);
                        LOG_MESSAGE(message);
                        exit(1);
                }
		file_counter++;
                StoreInFHEAD(i);
                fprintf(FileArray[file_counter-1],"%s\n",FHEAD_v00);
                free(FHEAD_v00);
		DcloseDates[file_counter-1].LineNumber=dclose_line_counter;
		}

	}
}
/*void FieldExtract( char *record, char *delim, char arr[][MAXFLDSIZE],int *fldcnt) */
void FieldExtract( char *src, char *delim, char arr[][MAXFLDSIZE],int *fldcnt)
{    
/*	char*p=strtok(record,delim);    
	int fld=0;        
	while(*p)    
	{        
		strcpy(arr[fld],p);		
		strcat(arr[fld],"\0");	 
		fld++;		
		p=strtok('',delim);	
	}			
	*fldcnt=fld;
	free(p); */

        char tempstring[MAX];
        int i=0,fld=0;
        while (src && *src)
        {
                while (*src != *delim && *src)
                {
                        tempstring[i++]=*src;
                        src++;
                }
                tempstring[i]='\0';
                strcpy(arr[fld],tempstring);
                strcat(arr[fld],"\0");
                if(*src) src++;
                i=0;
                /*printf("%s\n",tempstring);
                printf("%s\n",arr[fld]); */
                memset(tempstring,'\0',sizeof(tempstring));
                fld++;
        }
        *fldcnt=fld;
}

void writeRtlogDHeader(int string_counter)
{
        memset(FHEAD_transaction_line,0,sizeof(FHEAD_transaction_line));
        char padding_string[MAXFLDS];
	/*printf("Transaction Line:%s\n",FHEAD_transaction_line); */
        strcpy(FHEAD_transaction_line,"FHEAD");
	/*printf("TxnType: %s\n",v_00.transaction_type);
	printf("Dclose:%d\n",dclose_line_counter);
	printf("StringCounter:%d\n",string_counter);
	printf("Bnk:%s\n",v_15_b[string_counter].type_of_15);  */
        number_pad(padding_string,dclose_line_counter,10);
	/*printf("1st:%s\n",FHEAD_transaction_line); */
        strcat(FHEAD_transaction_line,padding_string);
	strcat(FHEAD_transaction_line,"RTLG"); 
	GetCurrentDateTime(CurrentDate,25,"%Y%m%d%H%M%S");  
	/*printf("Current Date: %s\n",CurrentDate); */
	strcat(FHEAD_transaction_line,CurrentDate);
	strcat(FHEAD_transaction_line,"20"); 
        strcat(FHEAD_transaction_line,v_15_b[string_counter].dclose_date);
        strcat(FHEAD_transaction_line,v_1_15.unit_number); 	/* Store Location - (Store Number) */
        string_pad(FHEAD_transaction_line,10-strlen(v_1_15.unit_number)," ","R");  
	string_pad(FHEAD_transaction_line,30," ","R");	/* Reference Number */
        /*printf("%s-%d\n",FHEAD_transaction_line,strlen(FHEAD_transaction_line)); */
	/*strcat(FHEAD_transaction_line,"\0"); */
	/*fprintf(dclose,"%s\n",FHEAD_transaction_line);  */
}
void writeRtlogHeader(int string_counter)
{
        char padding_string[MAXFLDS];
        strcpy(transaction_line,"FHEAD");
        current_line_counter++;
        number_pad(padding_string,current_line_counter,10);
        strcat(transaction_line,padding_string);
	strcat(transaction_line,"RTLG");
	GetCurrentDateTime(CurrentDate,25,"%Y%m%d%H%M%S"); 
	/*printf("Current Date: %s\n",CurrentDate);*/
	strcat(transaction_line,CurrentDate);
	strcat(transaction_line,"20");
        strcat(transaction_line,tlog_date);    /* Business Date */
        strcat(transaction_line,v_1_15.unit_number); 	/* Store Location - (Store Number) */
        string_pad(transaction_line,10-strlen(v_1_15.unit_number)," ","R");  
	string_pad(transaction_line,30," ","R");	/* Reference Number */
        /*printf("%s-%d\n",transaction_line,strlen(transaction_line)); */
	fprintf(outfile,"%s\n",transaction_line); 
	free(transaction_line);
        memset(transaction_line,0,sizeof(transaction_line));
}

void writeDcloseTransaction(int string_counter,FILE *dclose)
{
	char padding_string[MAXFLDS];
	free(transaction_line);
	strcpy(transaction_line,"THEAD");
	dclose_line_counter++;
	number_pad(padding_string,dclose_line_counter,10);
	strcat(transaction_line,padding_string);
	strcat(transaction_line,"     ");	/* Register Number */
	strcat(transaction_line,"20");
	strcat(transaction_line,DcloseDates[string_counter].dclose_date);	/* Transaction Date */
	strcat(transaction_line,"000000");	/* Time of Transaction HHMMSS */
	strcat(transaction_line,"          ");	/* Transaction Number */
	strcat(transaction_line," ");
	string_pad(transaction_line,9," ","R");	/* Operator Number */
	string_pad(transaction_line,10," ","R"); /* Sales Person */
	strcat(transaction_line,"DCLOSE");	/* Transaction Type - 6*/
	string_pad(transaction_line,6," ","R");	/* Sub Transaction Type */
	string_pad(transaction_line,15," ","R");	/* Orig Tran and RegNo */
	string_pad(transaction_line,6," ","R");	/* Reason Code */
	string_pad(transaction_line,86," ","R");	
	strcat(transaction_line,"2");
	string_pad(transaction_line,29," ","R");	/*Reference Number 1 - 30 */
	string_pad(transaction_line,30," ","R");	/*Reference Number 2 - 30 */
	string_pad(transaction_line,30," ","R");	/*Reference Number 3 - 30 */
	string_pad(transaction_line,30," ","R");	/*Reference Number 4 - 30 */
	string_pad(transaction_line,21," ","R");	/*Value - 20 */
	strcat(transaction_line,"0001");		/* Banner Id */
	string_pad(transaction_line,44," ","R");
	
	/* 13.1 Back Porting */
	string_pad(transaction_line,42," ","R");
	fwrite(transaction_line,strlen(transaction_line),1,dclose);
	memset(transaction_line,0,sizeof(transaction_line));
	fprintf(dclose,"\n");
	free(transaction_line);
}

void DCLOSEHeadTail(int string_counter,FILE *dclose)
{
        /* CASH Deposit Total THEAD*/

	/*printf("HeadTail: %d\n\n",string_counter); */
	StoreInTHEAD15(string_counter);
        fprintf(dclose,"%s\n",THEAD_v00_15);
        free(THEAD_v00_15);
	sys_cash='Y';
	
	StoreInTtail(string_counter);
	fprintf(dclose,"%s\n",TTAIL_v00);
	free(TTAIL_v00);

        /* CHECK Deposit Total THEAD*/
	StoreInTHEAD15(string_counter);
        fprintf(dclose,"%s\n",THEAD_v00_15);
        free(THEAD_v00_15);

	StoreInTtail(string_counter);
	fprintf(dclose,"%s\n",TTAIL_v00);
	free(TTAIL_v00);
}


void writeRtlog()
{
	/*printf("V_00:%s\tType:%s\n",v_00.string_type,v_00.transaction_type); */
	/*if(strcmp(v_00.transaction_type,"53"))
	{*/
	if(!strcmp(v_00.transaction_type,"56") && atoi(v_15_b[fifteenB_counter-1].string_type)==15)
	{
		/*writeDCLOSE(0); */
		Dclose_Done='Y';
	}
	/*else if(strcmp(v_00.transaction_type,"56"))
	{ */
		if(atoi(v_00.transaction_type)==56 && Dclose_Done=='N') Dclose_Done='Y';
		StoreInTHEAD(0);
		fprintf(outfile,"%s\n",THEAD_v00);
		memset(THEAD_v00,0,sizeof(*THEAD_v00));
		free(THEAD_v00); 
		/*printf("Txn: %s\tSix:%d\n",v_00.transaction_number,six_counter);   */
		for(int i=0;i<six_counter;i++)
		{
			/*if(atoi(v_08[i].string_type)==8) printf("bin:%c\n",v_08[i].binindicat0[7]); */
			/*	printf("Printing 06\n"); */
			int p_index_10 = v_06[i].index_10;
			/*printf("\nP_INDEX: %d\n",p_index_10);  */
			StoreInTITEM(i);
			fprintf(outfile,"%s\n",TITEM_v06);
			memset(TITEM_v06,0,sizeof(*TITEM_v06));
			free(TITEM_v06); 
			

/* TO handle multiple lines of Discount 23-AUG-2013 */
	/* Commented 23-AUG-2013 */
			/*if((!strcmp(v_10[i][0].string_type,"10") && strcmp(v_10[i][1].string_type,"10")))
			{
				if(atoi(v_10[i][0].string_type)==10)
				{
					StoreInDisc(i,0);
					fprintf(outfile,"%s\n",IDISC_v10);
					memset(IDISC_v10,0,sizeof(*IDISC_v10));
					free(IDISC_v10); 
				}
			}
			else if((!strcmp(v_10[i][0].string_type,"10") && !strcmp(v_10[i][1].string_type,"10")))	
			{
				for(int disc_lines=0;disc_lines<=1;disc_lines++)
				{
					StoreInDisc(i,disc_lines);
					fprintf(outfile,"%s\n",IDISC_v10);
					memset(IDISC_v10,0,sizeof(*IDISC_v10));
					free(IDISC_v10); 

				}
			} */
	/* Commented 23-AUG-2013 */

			if(!strcmp(v_10[i][0].string_type,"10"))
			{
				/*printf("inside 10-0\n"); */
				for(int j=0;j<p_index_10;j++)
				{
					/*printf("10[%d][%d]\t%s\t%s\n",i,j,v_10[i][j].string_type,v_10[i][j].discount_amount);   */
					StoreInDisc(i,j);
                                        fprintf(outfile,"%s\n",IDISC_v10);
                                        memset(IDISC_v10,0,sizeof(*IDISC_v10));
                                        free(IDISC_v10);

				}
				
			}
/* TO handle multiple lines of Discount 23-AUG-2013 */
			if(atoi(v_10_8[i][0].string_type)==10 )
			{
				/*printf("Coming Here TDISC\n");  */
				
				StoreInTDisc(i,0);
				fprintf(outfile,"%s\n",TDISC_v10_8);
				memset(TDISC_v10_8,0,sizeof(*TDISC_v10_8));
				free(TDISC_v10_8);  
			}
											

		}

/** Tax Record in the transaction will be writing to the file. basing on the values in A/B/C/D buckets those many tax records will be written */
		for(int i=0;i<fourteen_counter;i++)
		{
			/*printf("Printing Tax\n"); */
			manual_tax_bucket='N'; /*Version 2.0 : Added new tax code "RDTX4" for Manual tax*/
			if(atoi(v_14[i].tax_a)>0)
			{
                        	a_flag='Y';
				StoreInTTax(i);
                                fprintf(outfile,"%s\n",TAX_v14);
                        }
                        if(atoi(v_14[i].tax_b)>0)
                        {
                        	b_flag='Y';
				StoreInTTax(i);
                                fprintf(outfile,"%s\n",TAX_v14);
                        }
                        if(atoi(v_14[i].tax_c)>0)
                        {
                        	c_flag='Y';
				StoreInTTax(i);
                                fprintf(outfile,"%s\n",TAX_v14);
                        }

                        if(atoi(v_14[i].tax_d)>0)
                        {
                         	d_flag='Y';
				if(atoi(v_08_tax[0].string_type) == 8  && v_08_tax[0].binindicat0[5]=='1')
				{
					/*printf("Txn: %s I am in 08M\n",v_00.transaction_number); */
					for (int i=0;i<tax_08_counter;i++)
					{
						/*printf("Bin:%c\n",v_08_tax[i].binindicat0[5]); */
						if(v_08_tax[i].binindicat0[5] == '1')
						{
							/*printf("Tax Amount: %s\n",v_08_tax[i].amount); */
							if(v_08_tax[i].binindicat0[8] == '1' || v_08_tax[i].binindicat0[9] == '1')
							{
								if(v_08_tax[i].binindicat0[8] == '1' && v_08_tax[i].binindicat0[9] == '1')
									total_08_tax+=atoi(v_08_tax[i].amount);
								else
									total_08_tax-=atoi(v_08_tax[i].amount);
							}
							else
							{
								total_08_tax+=atoi(v_08_tax[i].amount);
							}
						}
					}
					/*printf("08M: %d\tTotal:%d\n",tax_08_counter,total_08_tax); */
					if (abs(total_08_tax) != atoi(v_14[i].tax_d))
					{	
						StoreInTTax(0);
						fprintf(outfile,"%s\n",TAX_v14);
					}
				}
				StoreInTTax(i);
                                fprintf(outfile,"%s\n",TAX_v14);
                        }
			if(atoi(v_14[i].tax_d)==0 && atoi(v_14[i].tax_a)==0 && atoi(v_14[i].tax_b)==0 && atoi(v_14[i].tax_c)==0)
			{
				StoreInTTax(i);
				fprintf(outfile,"%s\n",TAX_v14);
			}
			memset(TAX_v14,0,sizeof(TAX_v14));
			free(TAX_v14); 
		}

/** Tender Record in the transaction will be writing to the file. For 11 and 12 string types we are writing the tender records **/

		for(int i=0;i<twelve_counter;i++)
		{
			/*printf("Printing Tender\n");*/ 
			/*printf("11 len:%d\n",strlen(v_11[i].tender)); */
			StoreInTender(i);
			fprintf(outfile,"%s\n",TENDER_v12);
			memset(TENDER_v12,0,sizeof(*TENDER_v12));
			free(TENDER_v12);
		}
		StoreInTtail(0);
		fprintf(outfile,"%s\n",TTAIL_v00);
		memset(TTAIL_v00,0,sizeof(*TTAIL_v00));
		free(TTAIL_v00);  
		CleanUpOutStructs();
		/*printf("Record Completed\n"); */
	/*} */
							/*}*/
	CleanUpInputArray();
}

void time_stamp_extract(char *tm_stamp)
{
	time_t ltime;
        struct tm *Tm;
        char tm_hr[4],tm_mm[4],tm_hs[4];
        ltime=time(NULL);
        Tm=localtime(&ltime);
	sprintf(tm_hr,"%d",Tm->tm_hour);
        sprintf(tm_mm,"%d",Tm->tm_min);
        sprintf(tm_hs,"%d",Tm->tm_sec);
        if(strlen(tm_hr) <2) string_pad(tm_hr,2-strlen(tm_hr),"0","L");
        if(strlen(tm_mm) <2) string_pad(tm_mm,2-strlen(tm_mm),"0","L");
        if(strlen(tm_hs) <2) string_pad(tm_hs,2-strlen(tm_hs),"0","L");
	
        strcpy(tm_stamp,tm_hr);
        strcat(tm_stamp,tm_mm);
        strcat(tm_stamp,tm_hs);
}
static void LogTHEADField(const char *name, const char *value, size_t capacity)
{
    size_t len = strnlen(value, capacity);
    fprintf(thead_input_log, "%s[%lu]=\"%.*s\"\n",
            name, (unsigned long)len, (int)len, value);
}

static void LogTHEADBatchBeforeInsert(void)
{
    int i;

    if (thead_input_log == NULL)
        return;

    fprintf(thead_input_log, "Record count: %d\n", thead_record_count);
    fprintf(thead_input_log, "Record size: %lu bytes\n",
            (unsigned long)sizeof(thead_records[0]));
    fprintf(thead_input_log, "Batch size: %lu bytes\n\n",
            (unsigned long)(thead_record_count * sizeof(thead_records[0])));

    for (i = 0; i < thead_record_count; i++) {
        struct THEAD_DB_Record *r = &thead_records[i];

        fprintf(thead_input_log, "--- record %d ---\n", i + 1);
        LogTHEADField("STORE", r->STORE, sizeof(r->STORE));
        LogTHEADField("BUSINESS_DATE", r->BUSINESS_DATE, sizeof(r->BUSINESS_DATE));
        LogTHEADField("TRAN_DATETIME", r->TRAN_DATETIME, sizeof(r->TRAN_DATETIME));
        LogTHEADField("REGISTER", r->REGISTER, sizeof(r->REGISTER));
        LogTHEADField("TRAN_NO", r->TRAN_NO, sizeof(r->TRAN_NO));
        LogTHEADField("CASHIER", r->CASHIER, sizeof(r->CASHIER));
        LogTHEADField("SALESPERSON", r->SALESPERSON, sizeof(r->SALESPERSON));
        LogTHEADField("TRAN_TYPE", r->TRAN_TYPE, sizeof(r->TRAN_TYPE));
        LogTHEADField("SUB_TRAN_TYPE", r->SUB_TRAN_TYPE, sizeof(r->SUB_TRAN_TYPE));
        LogTHEADField("ORIG_TRAN_NO", r->ORIG_TRAN_NO, sizeof(r->ORIG_TRAN_NO));
        LogTHEADField("ORIG_REG_NO", r->ORIG_REG_NO, sizeof(r->ORIG_REG_NO));
        LogTHEADField("REF_NO1", r->REF_NO1, sizeof(r->REF_NO1));
        fprintf(thead_input_log, "REF_NO2=<redacted>\n");
        LogTHEADField("REF_NO3", r->REF_NO3, sizeof(r->REF_NO3));
        LogTHEADField("REF_NO4", r->REF_NO4, sizeof(r->REF_NO4));
        LogTHEADField("VALUE", r->VALUE, sizeof(r->VALUE));
        LogTHEADField("VALUE_SIGN", r->VALUE_SIGN, sizeof(r->VALUE_SIGN));
        LogTHEADField("BANNER_NO", r->BANNER_NO, sizeof(r->BANNER_NO));
        LogTHEADField("ROUNDED_AMT", r->ROUNDED_AMT, sizeof(r->ROUNDED_AMT));
        LogTHEADField("ROUNDED_OFF_AMT", r->ROUNDED_OFF_AMT, sizeof(r->ROUNDED_OFF_AMT));
        fputc('\n', thead_input_log);
    }

    fflush(thead_input_log);
}
/* ========== THEAD Database Operations Implementation ========== */

/**
 * Initialize THEAD database operations
 * Opens error log file for failed records
 */
void InitializeTHEADDbOps(char *log_directory)
{
	time_t now;
	struct tm *timeinfo;
	char timestamp[20];
	
	if (log_directory == NULL) {
		strcpy(log_directory, ".");
	}
	
	time(&now);
	timeinfo = localtime(&now);
	strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", timeinfo);

	char input_logfile[512];
	snprintf(input_logfile, sizeof(input_logfile),
         "%s/THEAD_INPUT_%s.log", log_directory, timestamp);
	thead_input_log = fopen(input_logfile, "w");

if (thead_input_log != NULL)
    fprintf(thead_input_log, "THEAD pre-insert input log - %s\n\n", timestamp);
	
	sprintf(thead_error_logfile, "%s/THEAD_ERROR_%s.log", log_directory, timestamp);
	
	thead_error_log = fopen(thead_error_logfile, "w");
	if (thead_error_log == NULL) {
		fprintf(stderr, "Warning: Could not open THEAD error log file: %s\n", thead_error_logfile);
	} else {
		fprintf(thead_error_log, "THEAD Database Insert Error Log - %s\n", timestamp);
		fprintf(thead_error_log, "=====================================================\n\n");
		fflush(thead_error_log);
	}
	if (thead_input_log != NULL) {
    fclose(thead_input_log);
    thead_input_log = NULL;
}
	thead_record_count = 0;
}

/**
 * Collect a THEAD record for batch insertion
 * Returns 1 if successful, 0 if batch is full
 */
void CollectTHEADRecord(char *store, char *business_date, char *tran_datetime, char *register_no,
                        char *tran_no, char *cashier, char *salesperson, char *tran_type,
                        char *sub_tran_type, char *orig_tran_no, char *orig_reg_no,
                        char *ref_no1, char *ref_no2, char *ref_no3, char *ref_no4,
                        char *value, char *value_sign, char *banner_no, char *rounded_amt,
                        char *rounded_off_amt)
{
	if (thead_record_count >= MAX_THEAD_BATCH) {
		fprintf(stderr, "THEAD batch is full (%d records). Execute insert before adding more.\n", 
		        MAX_THEAD_BATCH);
		return;
	}
	
	/* Copy data with safe string handling */
	memset(&thead_records[thead_record_count], 0, sizeof(struct THEAD_DB_Record));
	
	strncpy(thead_records[thead_record_count].STORE, store, sizeof(thead_records[thead_record_count].STORE) - 1);
	strncpy(thead_records[thead_record_count].BUSINESS_DATE, business_date, 
	        sizeof(thead_records[thead_record_count].BUSINESS_DATE) - 1);
	strncpy(thead_records[thead_record_count].TRAN_DATETIME, tran_datetime, 
	        sizeof(thead_records[thead_record_count].TRAN_DATETIME) - 1);
	strncpy(thead_records[thead_record_count].REGISTER, register_no, 
	        sizeof(thead_records[thead_record_count].REGISTER) - 1);
	strncpy(thead_records[thead_record_count].TRAN_NO, tran_no, 
	        sizeof(thead_records[thead_record_count].TRAN_NO) - 1);
	strncpy(thead_records[thead_record_count].CASHIER, cashier, 
	        sizeof(thead_records[thead_record_count].CASHIER) - 1);
	strncpy(thead_records[thead_record_count].SALESPERSON, salesperson, 
	        sizeof(thead_records[thead_record_count].SALESPERSON) - 1);
	strncpy(thead_records[thead_record_count].TRAN_TYPE, tran_type, 
	        sizeof(thead_records[thead_record_count].TRAN_TYPE) - 1);
	strncpy(thead_records[thead_record_count].SUB_TRAN_TYPE, sub_tran_type, 
	        sizeof(thead_records[thead_record_count].SUB_TRAN_TYPE) - 1);
	strncpy(thead_records[thead_record_count].ORIG_TRAN_NO, orig_tran_no, 
	        sizeof(thead_records[thead_record_count].ORIG_TRAN_NO) - 1);
	strncpy(thead_records[thead_record_count].ORIG_REG_NO, orig_reg_no, 
	        sizeof(thead_records[thead_record_count].ORIG_REG_NO) - 1);
	strncpy(thead_records[thead_record_count].REF_NO1, ref_no1, 
	        sizeof(thead_records[thead_record_count].REF_NO1) - 1);
	strncpy(thead_records[thead_record_count].REF_NO2, ref_no2, 
	        sizeof(thead_records[thead_record_count].REF_NO2) - 1);
	strncpy(thead_records[thead_record_count].REF_NO3, ref_no3, 
	        sizeof(thead_records[thead_record_count].REF_NO3) - 1);
	strncpy(thead_records[thead_record_count].REF_NO4, ref_no4, 
	        sizeof(thead_records[thead_record_count].REF_NO4) - 1);
	strncpy(thead_records[thead_record_count].VALUE, value, 
	        sizeof(thead_records[thead_record_count].VALUE) - 1);
	strncpy(thead_records[thead_record_count].VALUE_SIGN, value_sign, 
	        sizeof(thead_records[thead_record_count].VALUE_SIGN) - 1);
	strncpy(thead_records[thead_record_count].BANNER_NO, banner_no, 
	        sizeof(thead_records[thead_record_count].BANNER_NO) - 1);
	strncpy(thead_records[thead_record_count].ROUNDED_AMT, rounded_amt, 
	        sizeof(thead_records[thead_record_count].ROUNDED_AMT) - 1);
	strncpy(thead_records[thead_record_count].ROUNDED_OFF_AMT, rounded_off_amt, 
	        sizeof(thead_records[thead_record_count].ROUNDED_OFF_AMT) - 1);
	
	thead_records[thead_record_count].PROCESSED = 0;
	memset(thead_records[thead_record_count].ERROR_MSG, 0, sizeof(thead_records[thead_record_count].ERROR_MSG));
	
	thead_record_count++;
}

/**
 * Escape single quotes in string for SQL
 */
static void EscapeSQLString(char *src, char *dest, int dest_size)
{
	int src_idx = 0, dest_idx = 0;
	
	if (src == NULL) {
		dest[0] = '\0';
		return;
	}
	
	while (src[src_idx] != '\0' && dest_idx < dest_size - 2) {
		if (src[src_idx] == '\'') {
			if (dest_idx < dest_size - 3) {
				dest[dest_idx++] = '\'';
				dest[dest_idx++] = '\'';
			}
		} else {
			dest[dest_idx++] = src[src_idx];
		}
		src_idx++;
	}
	dest[dest_idx] = '\0';
}

/**
 * Generate SQL INSERT statements for collected THEAD records
 * Returns number of records processed, -1 on error
 */
int GenerateTHEADInsertSQL(char *sql_filename)
{
	FILE *sql_file;
	int i;
	char escaped_value[256];
	char timestamp[20];
	time_t now;
	struct tm *timeinfo;
	
	if (thead_record_count == 0) {
		fprintf(stderr, "No THEAD records to insert.\n");
		return 0;
	}
	
	sql_file = fopen(sql_filename, "w");
	if (sql_file == NULL) {
		fprintf(stderr, "Error: Could not open SQL file for writing: %s\n", sql_filename);
		return -1;
	}
	
	/* Write SQL header */
	fprintf(sql_file, "-- THEAD Batch Insert SQL\n");
	fprintf(sql_file, "-- Generated for %d records\n", thead_record_count);
	fprintf(sql_file, "-- Table: mik.mik_sa_head_stg_in\n");
	fprintf(sql_file, "SET ECHO OFF;\n");
	fprintf(sql_file, "SET FEEDBACK OFF;\n");
	fprintf(sql_file, "WHENEVER SQLERROR EXIT SQL.SQLCODE;\n\n");
	
	/* Generate INSERT statements */
	for (i = 0; i < thead_record_count; i++) {
		/* Build INSERT statement with sequence number and default values */
		fprintf(sql_file, "INSERT INTO mik.mik_sa_head_stg_in (\n");
		fprintf(sql_file, "    STG_ID, STORE, BUSINESS_DATE, TRAN_DATETIME, REGISTER, TRAN_NO,\n");
		fprintf(sql_file, "    CASHIER, SALESPERSON, TRAN_TYPE, SUB_TRAN_TYPE, ORIG_TRAN_NO,\n");
		fprintf(sql_file, "    ORIG_TRAN_TYPE, ORIG_REG_NO, RECEIPT_BARCODE, REF_NO1, REF_NO2,\n");
		fprintf(sql_file, "    REF_NO3, REF_NO4, REASON_CODE, VENDOR_NO, VENDOR_INVC_NO,\n");
		fprintf(sql_file, "    PAYMENT_REF_NO, PROOF_OF_DELIVERY_NO, STATUS, VALUE, BANNER_NO,\n");
		fprintf(sql_file, "    CUST_ORDER_NO, CUST_ORDER_DATE, ROUNDED_AMT, ROUNDED_OFF_AMT,\n");
		fprintf(sql_file, "    BEGIN_DATETIME, LOYALTY_ID, SYSTEM_CODE, STG_STATUS_IND,\n");
		fprintf(sql_file, "    UPDATE_DATETIME, CREATE_DATETIME, TENDER_CONTROL, TOTAL_TAX_AMT\n");
		fprintf(sql_file, ")\n");
		fprintf(sql_file, "VALUES (\n");
		fprintf(sql_file, "    MIK.MIK_SA_HEAD_IN_STG_ID_SEQUENCE.NEXTVAL,\n");
		fprintf(sql_file, "    %s,\n", thead_records[i].STORE);
		fprintf(sql_file, "    TO_DATE('%s', 'YYYYMMDD'),\n", thead_records[i].BUSINESS_DATE);
		fprintf(sql_file, "    TO_DATE('%s', 'YYYYMMDDHH24MISS'),\n", thead_records[i].TRAN_DATETIME);
		fprintf(sql_file, "    '%s',\n", thead_records[i].REGISTER);
		fprintf(sql_file, "    %s,\n", thead_records[i].TRAN_NO);
		fprintf(sql_file, "    '%s',\n", thead_records[i].CASHIER);
		fprintf(sql_file, "    '%s',\n", thead_records[i].SALESPERSON);
		fprintf(sql_file, "    '%s',\n", thead_records[i].TRAN_TYPE);
		fprintf(sql_file, "    '%s',\n", thead_records[i].SUB_TRAN_TYPE);
		fprintf(sql_file, "    %s,\n", thead_records[i].ORIG_TRAN_NO);
		fprintf(sql_file, "    NULL,\n");  /* ORIG_TRAN_TYPE */
		fprintf(sql_file, "    '%s',\n", thead_records[i].ORIG_REG_NO);
		fprintf(sql_file, "    NULL,\n");  /* RECEIPT_BARCODE */
		fprintf(sql_file, "    '%s',\n", thead_records[i].REF_NO1);
		fprintf(sql_file, "    '%s',\n", thead_records[i].REF_NO2);
		fprintf(sql_file, "    '%s',\n", thead_records[i].REF_NO3);
		fprintf(sql_file, "    '%s',\n", thead_records[i].REF_NO4);
		fprintf(sql_file, "    NULL,\n");  /* REASON_CODE */
		fprintf(sql_file, "    NULL,\n");  /* VENDOR_NO */
		fprintf(sql_file, "    NULL,\n");  /* VENDOR_INVC_NO */
		fprintf(sql_file, "    NULL,\n");  /* PAYMENT_REF_NO */
		fprintf(sql_file, "    NULL,\n");  /* PROOF_OF_DELIVERY_NO */
		fprintf(sql_file, "    NULL,\n");  /* STATUS */
		fprintf(sql_file, "    %s,\n", thead_records[i].VALUE);
		fprintf(sql_file, "    %s,\n", thead_records[i].BANNER_NO);
		fprintf(sql_file, "    NULL,\n");  /* CUST_ORDER_NO */
		fprintf(sql_file, "    NULL,\n");  /* CUST_ORDER_DATE */
		fprintf(sql_file, "    %s,\n", thead_records[i].ROUNDED_AMT);
		fprintf(sql_file, "    %s,\n", thead_records[i].ROUNDED_OFF_AMT);
		fprintf(sql_file, "    NULL,\n");  /* BEGIN_DATETIME */
		fprintf(sql_file, "    NULL,\n");  /* LOYALTY_ID */
		fprintf(sql_file, "    'LEGACY',\n");  /* SYSTEM_CODE */
		fprintf(sql_file, "    'N',\n");  /* STG_STATUS_IND */
		fprintf(sql_file, "    SYSDATE,\n");  /* UPDATE_DATETIME */
		fprintf(sql_file, "    SYSDATE,\n");  /* CREATE_DATETIME */
		fprintf(sql_file, "    NULL,\n");  /* TENDER_CONTROL */
		fprintf(sql_file, "    NULL\n");  /* TOTAL_TAX_AMT */
		fprintf(sql_file, ");\n\n");
	}
	
	fprintf(sql_file, "COMMIT;\n");
	fprintf(sql_file, "QUIT;\n");
	
	fclose(sql_file);
	
	fprintf(stderr, "Generated SQL file: %s with %d insert statements\n", sql_filename, thead_record_count);
	return thead_record_count;
}

/**
 * Execute the generated SQL via SQLPlus
 * Uses $UP environment variable (already set in environment)
 * Shell expands $UP automatically - no need to read it in C
 * Returns 0 on success, -1 on error
 */
int ExecuteTHEADInsert(char *sql_filename)
{
	char command[1024];
	char output_file[512];
	int result;
	FILE *output;
	char line[512];
	
	if (sql_filename == NULL) {
		fprintf(stderr, "Error: sql_filename is NULL\n");
		return -1;
	}
	
	sprintf(output_file, "%s.log", sql_filename);
	
	/* Build SQLPlus command - shell will expand $UP automatically */
	sprintf(command, "sqlplus -S $UP @%s > %s 2>&1", sql_filename, output_file);
	
	fprintf(stderr, "Executing SQLPlus command (using $UP from environment)...\n");
	
	result = system(command);
	
	if (result != 0) {
		fprintf(stderr, "Error: SQLPlus execution failed with return code: %d\n", result);
		
		/* Log the error */
		output = fopen(output_file, "r");
		if (output != NULL) {
			fprintf(stderr, "\nSQLPlus output:\n");
			while (fgets(line, sizeof(line), output) != NULL) {
				fprintf(stderr, "%s", line);
				if (thead_error_log != NULL) {
					fprintf(thead_error_log, "%s", line);
				}
			}
			fclose(output);
		}
		return -1;
	}
	
	fprintf(stderr, "SQLPlus execution completed successfully\n");
	
	/* Check output for errors */
	output = fopen(output_file, "r");
	if (output != NULL) {
		int has_error = 0;
		while (fgets(line, sizeof(line), output) != NULL) {
			if (strstr(line, "ORA-") != NULL || strstr(line, "ERROR") != NULL) {
				has_error = 1;
				if (thead_error_log != NULL) {
					fprintf(thead_error_log, "DB Error: %s", line);
				}
			}
		}
		fclose(output);
		
		if (has_error) {
			return -1;
		}
	}
	
	return 0;
}

/**
 * Log error for a failed THEAD record
 */
void LogTHEADError(char *tran_no, char *error_msg)
{
	time_t now;
	struct tm *timeinfo;
	char timestamp[20];
	
	if (thead_error_log == NULL) {
		return;
	}
	
	time(&now);
	timeinfo = localtime(&now);
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
	
	fprintf(thead_error_log, "[%s] Transaction: %s\n", timestamp, tran_no);
	fprintf(thead_error_log, "Error: %s\n", error_msg);
	fprintf(thead_error_log, "---\n");
	fflush(thead_error_log);
}

/**
 * Close and finalize THEAD database operations
 */
void CloseTHEADDbOps(void)
{
	if (thead_error_log != NULL) {
		fprintf(thead_error_log, "\nLog closed at: ");
		time_t now = time(NULL);
		fprintf(thead_error_log, "%s", ctime(&now));
		fclose(thead_error_log);
		fprintf(stderr, "THEAD error log written to: %s\n", thead_error_logfile);
	}
	
	thead_record_count = 0;
}
