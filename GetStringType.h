#include "tlogRtlog.h"
#include <math.h>
int GetStringType(char  *SourceString)
{
        if (!strcmp(SourceString,"00"))
        {
                return 0;
        }
        else if (!strcmp(SourceString,"01"))
        {
                return 1;
        }
        else if(!strcmp(SourceString,"02"))
        {
                return 2;
        }
        else if(!strcmp(SourceString,"03"))
        {
                return 3;
        }
        else if(!strcmp(SourceString,"04"))
        {
                return 4;
        }
        else if(!strcmp(SourceString,"05"))
        {
                return 5;
        }
        else if(!strcmp(SourceString,"06"))
        {
                return 6;
        }
        else if(!strcmp(SourceString,"07"))
        {
                return 7;
        }
        else if(!strcmp(SourceString,"08"))
        {
                return 8;
        }
        else if(!strcmp(SourceString,"09"))
        {
                return 9;
        }
        else if(!strcmp(SourceString,"10"))
        {
                return 10;
        }
        else if(!strcmp(SourceString,"11"))
        {
                return 11;
        }
        else if(!strcmp(SourceString,"12"))
        {
                return 12;
        }
        else if(!strcmp(SourceString,"13"))
        {
                return 13;
        }
        else if(!strcmp(SourceString,"14"))
        {
                return 14;
        }
        else if(!strcmp(SourceString,"15"))
        {
                return 15;
        }
        else if(!strcmp(SourceString,"16"))
        {
                return 16;
        }
        else if(!strcmp(SourceString,"17"))
        {
                return 17;
        }
        else if(!strcmp(SourceString,"18"))
        {
                return 18;
        }
        else if(!strcmp(SourceString,"19"))
        {
                return 19;
        }
        else if(!strcmp(SourceString,"20"))
        {
                return 20;
        }
        else if(!strcmp(SourceString,"21"))
        {
                return 21;
        }
	else return -1;
}

void store_in_struct(int strng_type,char  hldarry[][MAXFLDSIZE],int string_counter)
{
	if (strng_type == 0)
	{
                int Net_Positive=0;
                int Net_Negative=0;
                int Net_Total=0;


		if(string_counter == 0 && v_00_15_head=='N')
		{
			strcpy(v_00.string_type,hldarry[0]);
	        	strcpy(v_00.terminal_number,hldarry[1]);
        		strcpy(v_00.operator_number,hldarry[2]);
        		strcpy(v_00.transaction_number,hldarry[3]);
        		strncpy(v_00.transaction_type,hldarry[4],2);
        		strcpy(v_00.number_of_strings,hldarry[5]);
        		strcpy(v_00.net_postive_amount,hldarry[6]);
        		strcpy(v_00.net_negative_amount,hldarry[7]);
        		strcpy(v_00.net_total_amount,hldarry[8]);
        		strcpy(v_00.net_noncash_total,hldarry[9]);
        		strcpy(v_00.operatotr_password,hldarry[10]);
        		strcpy(v_00.date_of_transaction,hldarry[11]);
        		strcpy(v_00.time_of_transaction,hldarry[12]);
        		strcpy(v_00.indicat0,hldarry[13]);
        		strcpy(v_00.indicat1,hldarry[14]);
        		strcpy(v_00.ringtime,hldarry[15]);
        		strcpy(v_00.tendertime,hldarry[16]);
        		strcpy(v_00.no_sales_time,hldarry[17]);
        		strcpy(v_00.inactive_time,hldarry[18]);
        		strcpy(v_00.net_cash,hldarry[19]);
			hex2bin(v_00.indicat0,&v_00.binindicat0[0],&no_of_bin_digits);
			/*printf("Number Of Bin:%d\n",no_of_bin_digits);
			printf("Store in:\n"); 
			for (int h=0;h<16;h++)
				printf("%c",v_00.binindicat0[h]); */
                        /* To handle the POS bug gross postive + gross negative != Net Total */

                        if (abs(atoi(v_00.net_postive_amount) - atoi(v_00.net_negative_amount)) != atoi(v_00.net_total_amount))
                        {
                                Net_Positive=atoi(v_00.net_postive_amount);
                                Net_Negative=atoi(v_00.net_negative_amount);
                                Net_Total=abs(Net_Positive-Net_Negative);
                                sprintf(v_00.net_total_amount,"%d",Net_Total);
                        }

		}
		else
		{
			/*printf("I am here Get\n"); */
			strcpy(v_00_b[string_counter].string_type,hldarry[0]);
                	strcpy(v_00_b[string_counter].terminal_number,hldarry[1]);
                	strcpy(v_00_b[string_counter].operator_number,hldarry[2]);
                	strcpy(v_00_b[string_counter].transaction_number,hldarry[3]);
                	strncpy(v_00_b[string_counter].transaction_type,hldarry[4],2);
                	strcpy(v_00_b[string_counter].number_of_strings,hldarry[5]);
                	strcpy(v_00_b[string_counter].net_postive_amount,hldarry[6]);
                	strcpy(v_00_b[string_counter].net_negative_amount,hldarry[7]);
                	strcpy(v_00_b[string_counter].net_total_amount,hldarry[8]);
                	strcpy(v_00_b[string_counter].net_noncash_total,hldarry[9]);
                        strcpy(v_00_b[string_counter].operatotr_password,hldarry[10]);
                        strcpy(v_00_b[string_counter].date_of_transaction,hldarry[11]);
                        strcpy(v_00_b[string_counter].time_of_transaction,hldarry[12]);
                        strcpy(v_00_b[string_counter].indicat0,hldarry[13]);
                        strcpy(v_00_b[string_counter].indicat1,hldarry[14]);
                        strcpy(v_00_b[string_counter].ringtime,hldarry[15]);
                        strcpy(v_00_b[string_counter].tendertime,hldarry[16]);
                        strcpy(v_00_b[string_counter].no_sales_time,hldarry[17]);
                        strcpy(v_00_b[string_counter].inactive_time,hldarry[18]);
                        strcpy(v_00_b[string_counter].net_cash,hldarry[19]);
                        hex2bin(v_00_b[string_counter].indicat0,&v_00_b[string_counter].binindicat0[0],&no_of_bin_digits);
                        /* To handle the POS bug gross postive + gross negative != Net Total */

                        if (abs(atoi(v_00_b[string_counter].net_postive_amount) - atoi(v_00_b[string_counter].net_negative_amount)) != atoi(v_00_b[string_counter].net_total_amount))
                        {
                                Net_Positive=atoi(v_00_b[string_counter].net_postive_amount);
                                Net_Negative=atoi(v_00_b[string_counter].net_negative_amount);
                                Net_Total=abs(Net_Positive-Net_Negative);
                                sprintf(v_00_b[string_counter].net_total_amount,"%d",Net_Total);
                        }
	
		}
	} 
	else if (strng_type == 1)
	{
		strcpy(v_01.string_type,hldarry[0]);
		strcpy(v_01.org_terminal_number,hldarry[1]);
		strcpy(v_01.org_operator_number,hldarry[2]);
		strcpy(v_01.org_transaction_number,hldarry[3]);
		strcpy(v_01.org_date_of_transaction,hldarry[4]);
		strcpy(v_01.org_time_of_transaction,hldarry[5]);
		/*printf("v_01.org_transaction_number: %s\n",v_01.org_transaction_number);	*/
	}
	else if (string_counter == 1 &&  strng_type==15 && strcmp(hldarry[1],"BANKDP"))
	{
		strcpy(v_1_15.string_type,hldarry[0]);
		strcpy(v_1_15.unit_type,hldarry[1]);
		strcpy(v_1_15.unit_number,hldarry[2]);
		strcpy(v_1_15.unit_state,hldarry[3]);
		strcpy(v_1_15.unit_version,hldarry[4]);
		/*printf("\n%s: ",v_1_15.unit_type);*/
		/*printf("%s \t",v_1_15.unit_number);*/
		/*printf("State: %s\n",v_1_15.unit_state);*/
	}
	else if(strng_type==4)
	{
		strcpy(v_04.string_type,hldarry[0]);
		strcpy(v_04.tender_type,hldarry[1]);
		strcpy(v_04.tender_amount,hldarry[2]);
		strcpy(v_04.tender_amount_f,hldarry[3]);
	}
	else if(strng_type==5)
	{
		strcpy(v_05.string_type,hldarry[0]);
		strcpy(v_05.store_closing_date,hldarry[1]);
		strcpy(v_05.store_closing_time,hldarry[2]);
	}
	else if(strng_type==6)
	{
		/*printf("size v_06[string_counter].%d\n",sizeof(v_06[string_counter].);*/
		min_06++;
		strcpy(v_06[string_counter].string_type,hldarry[0]);
		strcpy(v_06[string_counter].item_code,hldarry[1]);	
		strcpy(v_06[string_counter].dept_no,hldarry[2]);
		/*printf("str 06 item code %s\n",v_06[string_counter].item_code); */
		strcpy(v_06[string_counter].item_amount,hldarry[3]);
		strcpy(v_06[string_counter].tax_plan,hldarry[4]);
		/*printf("str 06 item amt  %s\n",v_06[string_counter].item_amount);*/
		strcpy(v_06[string_counter].indicat0,hldarry[5]);
		strcpy(v_06[string_counter].indicat1,hldarry[6]);
		v_06[string_counter].DataExists='0';
		v_06[string_counter].GSTTax=' ';

		/*printf("ITEM AMT: %s\n",v_06[string_counter].item_amount);*/
		hex2bin(v_06[string_counter].indicat0,&v_06[string_counter].binindicat0[0],&no_of_bin_digits);
		hex2bin(v_06[string_counter].tax_plan,&v_06[string_counter].bintaxplan[0],&no_of_bin_digits);

		
	}
	else if(strng_type==9 &&(!strcmp(hldarry[1],"~")))
	{
		/*printf("size v_09p %d\n",sizeof(v_09P[string_counter].);*/
		strcpy(v_09P[string_counter].string_type,hldarry[0]);
		strcpy(v_09P[string_counter].overflag,hldarry[1]);
		strcpy(v_09P[string_counter].item_code,hldarry[2]);
		strcpy(v_09P[string_counter].override_price,hldarry[3]);
		strcpy(v_09P[string_counter].reason_code,hldarry[4]);
		/*printf("%s P-over - Price\n",v_09P[string_counter].override_price);*/
		/*printf("%s Item code\n",v_09P[string_counter].item_code);*/
	}
	else if(strng_type==7)
	{
		strcpy(v_07[string_counter].string_type,hldarry[0]);
		strcpy(v_07[string_counter].group,hldarry[1]);
		strcpy(v_07[string_counter].quantity,hldarry[2]);
		strcpy(v_07[string_counter].sale_quantity,hldarry[3]);
		strcpy(v_07[string_counter].quantity_over,hldarry[4]);
		strcpy(v_07[string_counter].filler,hldarry[5]);
		strcpy(v_07[string_counter].price_over,hldarry[6]);

		v_07[string_counter].quantity_over[strcspn(v_07[string_counter].quantity_over,"\n")]='\0';	
		/*if(strlen(v_07[string_counter].price_over) >1 )
		{
			if(atoi(v_07[string_counter].quantity_over)!=atoi(v_07[string_counter].price_over))
			{
				if(atoi(v_07[string_counter].quantity)==1)
				{
					strcpy(v_07[string_counter].quantity_over,hldarry[6]);
					v_07[string_counter].quantity_over[strcspn(v_07[string_counter].quantity_over,"\n")]='\0';	
				}
				else
				{
					int t_qty=atoi(v_07[string_counter].quantity)/100;
					int t_item_amount=t_qty*atoi(v_07[string_counter].quantity_over);
					int t_item_over=atoi(v_07[string_counter].price_over);
					if(t_item_over == t_item_amount)
					{
						strcpy(v_07[string_counter].quantity_over,hldarry[4]);
						v_07[string_counter].quantity_over[strcspn(v_07[string_counter].quantity_over,"\n")]='\0';	
					}
					else
					{
						int unit_retail=t_item_over/t_qty;
						sprintf(v_07[string_counter].quantity_over,"%d",unit_retail);
						v_07[string_counter].quantity_over[strcspn(v_07[string_counter].quantity_over,"\n")]='\0';	
					}
				}
					
			}
		}  */

/* To handle the decimal quantity introduced the strlen function - 20-AUG-13 */
		/*int t_qty=atoi(v_07[string_counter].quantity)/100; */
                double t_qty;
                if (strlen(v_07[string_counter].quantity)==2)
                {
                        t_qty=atof(v_07[string_counter].quantity);
                }
                else
                {
                        t_qty=atof(v_07[string_counter].quantity)/100;
                }
/* To handle the decimal quantity introduced the strlen function - 20-AUG-13 */

		int t_item_amount=atoi(v_06[string_counter].item_amount);
		int t_unit_retail=(int)(((double)t_item_amount/t_qty)+0.5);

		if (strlen(v_07[string_counter].quantity)==2)
		{
			t_unit_retail=(int)((float)(((float)t_item_amount/(float)t_qty)*100.0+.5));
		}
		
		if (strlen(v_07[string_counter].quantity)==2 && strlen(v_06[string_counter].item_amount)==2)
		{
			t_unit_retail=(int)((float)(((float)t_item_amount/(float)t_qty)*100.0+.5));
			printf("Txn: %s\tUnit:%d\n",v_00.transaction_number,t_unit_retail);
		}

		sprintf(v_07[string_counter].quantity_over,"%d",t_unit_retail);
		v_07[string_counter].quantity_over[strcspn(v_07[string_counter].quantity_over,"\n")]='\0';


		/*printf("%s Quantity\n",v_07[string_counter].quantity);
		printf("%s sale Quantity \n",hldarry[3]);
		printf("Over:%s\thold:%s\tLenO:%d\tLenH:%d\n",v_07[string_counter].quantity_over,hldarry[4],strlen(v_07[string_counter].quantity_over),strlen(hldarry[4])); */
	}
	else if(strng_type==8)
	{
		if(manual_tax=='N')
		{
			strcpy(v_08[string_counter].string_type,hldarry[0]);
			strcpy(v_08[string_counter].customer_account_number,hldarry[1]);
			strcpy(v_08[string_counter].amount,hldarry[2]);
			strcpy(v_08[string_counter].tax_code,hldarry[3]);
			strcpy(v_08[string_counter].indicat0,hldarry[4]);
			hex2bin(v_08[string_counter].indicat0,&v_08[string_counter].binindicat0[0],&no_of_bin_digits);
		}
		else
		{
			strcpy(v_08_tax[string_counter].string_type,hldarry[0]);
			strcpy(v_08_tax[string_counter].customer_account_number,hldarry[1]);
			strcpy(v_08_tax[string_counter].amount,hldarry[2]);
			strcpy(v_08_tax[string_counter].tax_code,hldarry[3]);
			strcpy(v_08_tax[string_counter].indicat0,hldarry[4]);
			hex2bin(v_08_tax[string_counter].indicat0,&v_08_tax[string_counter].binindicat0[0],&no_of_bin_digits);
		}

	}
	else if(strng_type==9)
	{
		strcpy(v_09[string_counter].string_type,hldarry[0]);
		strncpy(v_09[string_counter].discount,hldarry[1],4);
		strncpy(v_09[string_counter].discount_seq,hldarry[2],10);
	}
	else if(strng_type==10 && tdisc=='N')
	{
		/*printf("inside Num of Flds: %d\n",number_of_fields);
			for(int i=0;i<number_of_fields;i++)
				printf("Inside: %d\t%s\n",string_counter,hldarry[i]); */
/*This is to handle the multiple discount lines for 1 item */
		int v_index_10 = v_06[string_counter].index_10;
		/*printf("\nV_10: %d \t v_index: %d\n",v_06[string_counter].index_10,v_index_10);*/
/*This is to handle the multiple discount lines for 1 item */
	
		if(number_of_fields<=6)
		{	
			strcpy(v_10[string_counter][v_index_10].string_type,hldarry[0]);
			strcpy(v_10[string_counter][v_index_10].discount_code,hldarry[1]);
			strcpy(v_10[string_counter][v_index_10].discount_amount,hldarry[2]);
			strcpy(v_10[string_counter][v_index_10].discount_percent,hldarry[3]);
			strcpy(v_10[string_counter][v_index_10].indicat0,hldarry[4]);
			strcpy(v_10[string_counter][v_index_10].Extra,hldarry[5]);
			hex2bin(v_10[string_counter][v_index_10].indicat0,&v_10[string_counter][v_index_10].binindicat0[0],&no_of_bin_digits);
			/*printf("hld:%d-%s\tindi:%d - %s\n",strlen(hldarry[4]),hldarry[4],strlen(v_10[string_counter][0].indicat0),v_10[string_counter][0].indicat0); */

/* Special Scenario 26-AUG-2013 discount voided and discount come for the previous line item */
			if(v_index_10>=1 && v_10[string_counter][v_index_10-1].binindicat0[1]=='1')
			{
				if(v_06[string_counter].binindicat0[7]=='1')
				{
					/*printf("In side void:%d\n",string_counter); */
					memset(&v_10[string_counter][v_index_10],0,sizeof(v_10[string_counter][v_index_10]));
					/*printf("10 there: %s\n",v_10[string_counter][v_index_10].string_type);
					printf("b4:v_index:%d\n",v_index_10); */
					int spl_string_counter=string_counter-1;
					int spl_index_10=v_index_10-1;

					if(atoi(v_10[spl_string_counter][spl_index_10].string_type) == 10)
					{
						v_index_10=v_06[spl_string_counter].index_10;
					}
					else
					{
						v_06[spl_string_counter].index_10=v_index_10;
						v_index_10=v_index_10-1;
						/*printf("v_06: %d\n",v_06[spl_string_counter].index_10); */
						v_06[string_counter].index_10=v_06[string_counter].index_10-1;
					}
					/*printf("After:v_index:%d\nString:%d\nspl:%d",v_index_10,string_counter,spl_string_counter); */
					strcpy(v_10[spl_string_counter][v_index_10].string_type,hldarry[0]);
                        		strcpy(v_10[spl_string_counter][v_index_10].discount_code,hldarry[1]);
                        		strcpy(v_10[spl_string_counter][v_index_10].discount_amount,hldarry[2]);
                        		strcpy(v_10[spl_string_counter][v_index_10].discount_percent,hldarry[3]);
                        		strcpy(v_10[spl_string_counter][v_index_10].indicat0,hldarry[4]);
                        		strcpy(v_10[spl_string_counter][v_index_10].Extra,hldarry[5]);
                        		hex2bin(v_10[spl_string_counter][v_index_10].indicat0,&v_10[spl_string_counter][v_index_10].binindicat0[0],&no_of_bin_digits);

					/*for(int i=0;i<=v_index_10;i++)
					{
						printf("Txn: %s\tDiscount Code: %s\tDiscount Amount:%s\tDiscount Percent:%s\n",v_00.transaction_number,v_10[spl_string_counter][i].discount_code,v_10[spl_string_counter][i].discount_amount,v_10[spl_string_counter][i].discount_percent); 
					} */
				}
				


			}
/* Special Scenario 26-AUG-2013 discount voided and discount come for the previous line item */
			
		}
		else
		{
			/*if(atoi(hldarry[6]) == 0)
			{	
				strcpy(v_10[string_counter][v_index_10].string_type,hldarry[0]);
				strcpy(v_10[string_counter][v_index_10].discount_code,hldarry[5]);
				strcpy(v_10[string_counter][v_index_10].discount_amount,hldarry[6]);
				strcpy(v_10[string_counter][v_index_10].discount_percent,hldarry[7]);
				strcpy(v_10[string_counter][v_index_10].indicat0,hldarry[8]);
                        	hex2bin(v_10[string_counter][v_index_10].indicat0,&v_10[string_counter][v_index_10].binindicat0[0],&no_of_bin_digits);

				v_index_10 = v_index_10 + 1;
				v_06[string_counter].index_10=v_index_10;
				printf("\n2-V_10: %d \t v_index: %d\n",v_06[string_counter].index_10,v_index_10);

				strcpy(v_10[string_counter][v_index_10].string_type,hldarry[0]);
				strcpy(v_10[string_counter][v_index_10].discount_code,hldarry[9]);
				strcpy(v_10[string_counter][v_index_10].discount_amount,hldarry[10]);
				strcpy(v_10[string_counter][v_index_10].discount_amount,hldarry[2]); 
				strcpy(v_10[string_counter][v_index_10].discount_percent,hldarry[3]);
				strcpy(v_10[string_counter][v_index_10].indicat0,hldarry[4]);
                        	hex2bin(v_10[string_counter][v_index_10].indicat0,&v_10[string_counter][v_index_10].binindicat0[0],&no_of_bin_digits);

				strcpy(v_10[string_counter][v_index_10].Extra,hldarry[13]);
			}
			else
			{*/
			
			/* Modified the condition to incorporate more than 2 discounts or promos on a single item */
			int j=5;
			  int zeroflag=0;
			  float disccheck=0;
			while(j<(number_of_fields-2))
			{
				strcpy(v_10[string_counter][v_index_10].string_type,hldarry[0]);
				strcpy(v_10[string_counter][v_index_10].discount_code,hldarry[j++]);
				disccheck=disccheck+atoi(hldarry[j]);
				strcpy(v_10[string_counter][v_index_10].discount_amount,hldarry[j++]);
				strcpy(v_10[string_counter][v_index_10].discount_percent,hldarry[j++]);
				strcpy(v_10[string_counter][v_index_10].indicat0,hldarry[j++]);
                hex2bin(v_10[string_counter][v_index_10].indicat0,&v_10[string_counter][v_index_10].binindicat0[0],&no_of_bin_digits);
			if (j<(number_of_fields-2)) 
				{
 				   v_index_10 = v_index_10 + 1;
				}
			}
				
				v_06[string_counter].index_10=v_index_10;
				/*printf("\n3-V_10: %d \t v_index: %d\n",v_06[string_counter].index_10,v_index_10);		 */
				strcpy(v_10[string_counter][v_index_10].Extra,hldarry[number_of_fields-1]);
				
			
				/*strcpy(v_10[string_counter][v_index_10].string_type,hldarry[0]);
				strcpy(v_10[string_counter][v_index_10].discount_code,hldarry[5]);
				strcpy(v_10[string_counter][v_index_10].discount_amount,hldarry[6]);
				strcpy(v_10[string_counter][v_index_10].discount_percent,hldarry[7]);
				strcpy(v_10[string_counter][v_index_10].indicat0,hldarry[8]);
                        	hex2bin(v_10[string_counter][v_index_10].indicat0,&v_10[string_counter][v_index_10].binindicat0[0],&no_of_bin_digits);

				v_index_10 = v_index_10 + 1;
				v_06[string_counter].index_10=v_index_10;

				
				

				strcpy(v_10[string_counter][v_index_10].string_type,hldarry[0]);
				strcpy(v_10[string_counter][v_index_10].discount_code,hldarry[9]);
				strcpy(v_10[string_counter][v_index_10].discount_amount,hldarry[10]); 
				strcpy(v_10[string_counter][v_index_10].discount_percent,hldarry[11]);
				strcpy(v_10[string_counter][v_index_10].indicat0,hldarry[12]);
                        	hex2bin(v_10[string_counter][v_index_10].indicat0,&v_10[string_counter][v_index_10].binindicat0[0],&no_of_bin_digits);

				strcpy(v_10[string_counter][v_index_10].Extra,hldarry[13]);
				*/


				if( zeroflag == 0 && disccheck != (atoi(hldarry[2])))
				{
					strcpy(v_10[string_counter][v_index_10].discount_amount,hldarry[2]);
					for(int k=1;k<=v_index_10;k++)
					{
					strcpy(v_10[string_counter][v_index_10-k].discount_amount,0);

					}
				}	



			/*}*/
			/*printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",v_10[string_counter][0].string_type,v_10[string_counter][0].discount_code,v_10[string_counter][0].discount_amount,v_10[string_counter][0].discount_percent,v_10[string_counter][0].indicat0,v_10[string_counter][1].string_type,v_10[string_counter][1].discount_code,v_10[string_counter][1].discount_amount,v_10[string_counter][1].discount_percent,v_10[string_counter][1].indicat0,v_10[string_counter][1].Extra);*/

			for(int k=0;k<=v_index_10;k++)
			{
			v_10[string_counter][k].discount_amount[strcspn(v_10[string_counter][k].discount_amount,"\n")]='\0';
			}
		}

		/*for(int i=0;i<=v_index_10;i++)
		{
			printf("Txn: %s\tDiscount Code: %s\tDiscount Amount:%s\tDiscount Percent:%s\n",v_00.transaction_number,v_10[string_counter][i].discount_code,v_10[string_counter][i].discount_amount,v_10[string_counter][i].discount_percent); 
		} */
	}
/* Handling Transactional Level Discount string_type==10 and indicat0=8 */
	else if(strng_type==10 && tdisc=='Y')
	{

		char bin_indicat0[16];
		int no_of_bits;
		memset(&bin_indicat0,0,sizeof(bin_indicat0));
		hex2bin(hldarry[4],&bin_indicat0[0],&no_of_bits);
		if(bin_indicat0[0] == '1')
		{
			int temp_string_counter=string_counter;
			float item_amount;
			char total_discount_amt[15];
                	char discount_amt[15];
                	char real[10];
                	char decimal[3];
                	float individual_discount_amt;
                	int discount_percent=atoi(hldarry[3])/10;
                	if(v_06[temp_string_counter].binindicat0[6]=='1' && v_06[temp_string_counter].binindicat0[7]=='1')
                	{
				for(int i=temp_string_counter-1;i>=0;i--)
				{
					if(!strcmp(v_06[temp_string_counter].item_code,v_06[i].item_code) && v_06[i].binindicat0[6]!='1' && v_06[i].DataExists!='1')	
					{
						v_06[i].DataExists='1';
						v_06[temp_string_counter].DataExists='1';
						calculated_discount_amt-=(float)atoi(v_10_8[i][0].discount_amount)/100;
						memset(&v_10_8[i][0],0,sizeof(v_10_8[i][0]));
						i=-1;
						/*printf("Prev Sale:%d\tCurrent Void:%d\n",i,temp_string_counter); */
					}
				}
				if(temp_string_counter == (six_counter-1) && (v_06[six_counter-1].binindicat0[6]=='1' ))
				{
					for(int i=temp_string_counter-1;i>=0;i--)
					{
						if(v_06[i].DataExists == '0')
						{
							float final_discount_amt=0;
							float assigned_discount_amt=0;
							char t_real[10];
							char t_decimal[3];
							char t_discount_amt[15];
						
							final_discount_amt=((int)(((float)(atoi(total_discount_amt))/100-calculated_discount_amt)*100+.5)/100.0);
							/*printf("Remaining: %.2f\n",final_discount_amt); */
							assigned_discount_amt=((int)(((float)(atoi(v_10_8[i][0].discount_amount))/100)*100+.5)/100.0);
							/*printf("Existing Dis:%.2f\n",assigned_discount_amt); */
							final_discount_amt+=assigned_discount_amt;
							/*printf("Remaining: %.2f\n",final_discount_amt); */
							sprintf(t_discount_amt,"%.2f",final_discount_amt);
							substr(t_real,t_discount_amt,0,strlen(t_discount_amt)-3);
							substr(t_decimal,t_discount_amt,strlen(t_discount_amt)-2,2);
							strcpy(v_10_8[i][0].discount_amount,t_real);
							strcat(v_10_8[i][0].discount_amount,t_decimal);
							i=-1;
					
						}
					}

				}
			}
			else if(v_06[temp_string_counter].binindicat0[6]=='1')
			{
				strcpy(total_discount_amt,hldarry[2]);
				if(temp_string_counter==0)
				{
                                	/*printf("RET: X : Total Disc: %f\n",(float)(atoi(total_discount_amt))/100);
                                	printf("RET: Discount per:%d\n",discount_percent);*/

				}
				/*printf("RET: V06:%s\t Item:%s\n",(v_06[temp_string_counter].item_amount),v_06[temp_string_counter].item_code); */

				item_amount=atoi(v_06[temp_string_counter].item_amount);
				item_amount/=100;

				/*printf("RET: Item Amount %.2f\tCalculated-Di: %2f\n",item_amount,calculated_discount_amt); */

				if(((float)(atoi(total_discount_amt))/100)>calculated_discount_amt)
				{
					if(atoi(v_10[temp_string_counter][0].string_type) == 10 || atoi(v_10[temp_string_counter][1].string_type) == 10)
					{
						individual_discount_amt=((int)(((float)(item_amount-(float)atoi(v_10[temp_string_counter][0].discount_amount)/100)*discount_percent/100)*100+.5)/100.0);	
					}
					else individual_discount_amt=((int)(((float)item_amount*discount_percent/100)*100+.5)/100.0);
					/*printf("Indiv:%2f\n",individual_discount_amt); */
					
					if(temp_string_counter == (six_counter-1)) 
					{
						if(((float)(atoi(total_discount_amt))/100)>calculated_discount_amt)
							individual_discount_amt=((int)(((float)(atoi(total_discount_amt))/100-calculated_discount_amt)*100+.5)/100.0);
						else individual_discount_amt=0;
						/*printf("Return Last: Calculate:%f\t%f\n",calculated_discount_amt,(float)(atoi(total_discount_amt))/100);*/
						
					}
				}
				else
					individual_discount_amt=0;

				calculated_discount_amt+=individual_discount_amt;
				/*printf("\nRET: Y : Calculated_Discount:%f\n",calculated_discount_amt); */

				if(((float)(atoi(total_discount_amt))/100) < calculated_discount_amt)
				{
					calculated_discount_amt-=individual_discount_amt;
					/*printf("Y-1 : Calculated_Discount:%f\n",calculated_discount_amt); */
					individual_discount_amt=((float)(atoi(total_discount_amt))/100)-calculated_discount_amt;
					calculated_discount_amt+=individual_discount_amt;
					/*printf("RET Z  : Calculated_Discount:%f\n",calculated_discount_amt); */
				}
				
				if(atoi(v_06[temp_string_counter].dept_no) == 19 || atoi(v_06[temp_string_counter].dept_no) == 32 || atoi(v_08[temp_string_counter].string_type)==8)
				{
					calculated_discount_amt-=individual_discount_amt;
				}
				else
				{
					strcpy(v_10_8[temp_string_counter][0].string_type,hldarry[0]);
                			strcpy(v_10_8[temp_string_counter][0].discount_code,hldarry[1]);
					sprintf(discount_amt,"%.2f",individual_discount_amt);
				
					substr(real,discount_amt,0,strlen(discount_amt)-3);
					substr(decimal,discount_amt,strlen(discount_amt)-2,2);
					strcpy(v_10_8[temp_string_counter][0].discount_amount,real);
					strcat(v_10_8[temp_string_counter][0].discount_amount,decimal);
                			strcpy(v_10_8[temp_string_counter][0].discount_percent,hldarry[3]);
                			strcpy(v_10_8[temp_string_counter][0].indicat0,hldarry[4]);
                			strcpy(v_10_8[temp_string_counter][0].Extra,hldarry[5]);
                			hex2bin(v_10_8[temp_string_counter][0].indicat0,&v_10_8[temp_string_counter][0].binindicat0[0],&no_of_bin_digits);
					v_10_8[temp_string_counter][0].discount_amount[strcspn(v_10_8[temp_string_counter][0].discount_amount,"\n")]='\0';
				}


			}

/* If the Last item is not a RETURN item and total disc amt not equal to the calculated amt then the remaining amount should be given to the return item which comes first from the bottom - 26-AUG-2013*/
			if(((float)(atoi(total_discount_amt))/100)>calculated_discount_amt && (temp_string_counter == (six_counter-1)))
			{
				float v_10_8_disc_amt;
				/*printf("I am in New Code\n"); */
				for(int i=temp_string_counter-1;i>=0;i--)
				{
					if(v_06[i].binindicat0[6]=='1' && v_06[i].DataExists == '0' )
					{
						individual_discount_amt=((float)(atoi(total_discount_amt))/100)-calculated_discount_amt;
						v_10_8_disc_amt=((float)(atoi(v_10_8[i][0].discount_amount))/100);
						sprintf(discount_amt,"%.2f",(individual_discount_amt+v_10_8_disc_amt));
						substr(real,discount_amt,0,strlen(discount_amt)-3);
						substr(decimal,discount_amt,strlen(discount_amt)-2,2);
						strcpy(v_10_8[i][0].discount_amount,real);
						strcat(v_10_8[i][0].discount_amount,decimal);
						i=-1;
						
					}

				}
				
				

			}
			
/* If the Last item is not a RETURN item and total disc amt not equal to the calculated amt then the remaining amount should be given to the return item which comes first from the bottom - 26-AUG-2013*/

			if(v_10_8[temp_string_counter][0].binindicat0[1]=='1')
			{
				memset(&v_10_8[temp_string_counter][0],0,sizeof(v_10_8[temp_string_counter][0]));
				calculated_discount_amt=0; 
			}
	
		}
/* Transaction Level Discount proration for SALE Items */
		else
		{
			int temp_string_counter=string_counter;
			float item_amount;
			/*printf("temp:%d\tString:%d\n",temp_string_counter,string_counter);  */
			char total_discount_amt[15];
			char discount_amt[15];
			char real[10];
			char decimal[3];
			float individual_discount_amt;
			int discount_percent=atoi(hldarry[3])/10;
			if(v_06[temp_string_counter].binindicat0[6]=='1' || v_06[temp_string_counter].binindicat0[7]=='1')
			{
				/*printf("\nFound VOID : V06:%s\t Item:%s\t%d\n",(v_06[temp_string_counter].item_amount),v_06[temp_string_counter].item_code,temp_string_counter);   */

				for(int i=temp_string_counter-1;i>=0;i--)
				{
					/*printf("i:%d\t%s\t%s\t%s\ttemp:%d\tData:%c\n",i,v_06[temp_string_counter].item_code,v_06[i].item_code,v_06[i].binindicat0[6],temp_string_counter,v_06[i].DataExists);  */
					/*if(atoi(v_06[temp_string_counter].item_code)==atoi(v_06[i].item_code) && v_06[i].binindicat0[6]!='1' && v_06[i].DataExists!='1')	*/	
					if(!strcmp(v_06[temp_string_counter].item_code,v_06[i].item_code) && v_06[i].binindicat0[6]!='1' && v_06[i].DataExists!='1')	
					{
						/*printf("Before - i:%d\ttemp:%d\t%c\t%2f\n",i,temp_string_counter,v_06[i].DataExists,calculated_discount_amt);   */
						v_06[i].DataExists='1';
						v_06[temp_string_counter].DataExists='1';
						calculated_discount_amt-=(float)atoi(v_10_8[i][0].discount_amount)/100;
						memset(&v_10_8[i][0],0,sizeof(v_10_8[i][0]));
						
						/*printf("After - i:%d\ttemp:%d\tData:%c\t%2f\n",i,temp_string_counter,v_06[i].DataExists,calculated_discount_amt);  */
						i=-1;
					}
				}
				if(temp_string_counter == (six_counter-1) && (v_06[temp_string_counter].binindicat0[6]=='1' || v_06[temp_string_counter].binindicat0[7]=='1'))
				{
					for(int i=temp_string_counter-1;i>=0;i--)
					{
						
						if(v_06[i].DataExists == '0')
						{
							/*printf("v_06[%d].Data:%c\n",i,v_06[i].DataExists); */
							float final_discount_amt=0;
							float assigned_discount_amt=0;
							char t_real[10];
							char t_decimal[3];
							char t_discount_amt[15];
							/*printf("Prev Sale:%d\tCurrent:%d\tSix:%d\n",i,temp_string_counter,six_counter); */
							/*printf("Before:Data0Value: %s\n",v_10_8[i][0].discount_amount);  */
							/*printf("Calculated - Data : %f\n",calculated_discount_amt);		  */
						
							final_discount_amt=((int)(((float)(atoi(total_discount_amt))/100-calculated_discount_amt)*100+.5)/100.0);
							/*printf("Total:%s\tFinal:%f\n",total_discount_amt,final_discount_amt); */
							assigned_discount_amt=((int)(((float)(atoi(v_10_8[i][0].discount_amount))/100)*100+.5)/100.0);
							final_discount_amt+=assigned_discount_amt;
							/*printf("Final: %f\t Assigned:%f\n",final_discount_amt,assigned_discount_amt); */
							sprintf(t_discount_amt,"%.2f",final_discount_amt);
							substr(t_real,t_discount_amt,0,strlen(t_discount_amt)-3);
							substr(t_decimal,t_discount_amt,strlen(t_discount_amt)-2,2);
							strcpy(v_10_8[i][0].discount_amount,t_real);
							strcat(v_10_8[i][0].discount_amount,t_decimal);
							/*printf("After:Data0Value: %s\n",v_10_8[i][0].discount_amount);  */
							i=-1;
					
						}
					}

				}
				/*memset(&v_10_8[temp_string_counter-1][0],0,sizeof(v_10_8[temp_string_counter-1][0])); */
			}
			else
			{
				strcpy(total_discount_amt,hldarry[2]);
				if(temp_string_counter==0)
				{
					/*printf("X : Total Disc: %f\n",(float)(atoi(total_discount_amt))/100);  
					printf("Discount per:%d\n",discount_percent);  */
				}
				/*printf("V06:%s\t Item:%s\n",(v_06[temp_string_counter].item_amount),v_06[temp_string_counter].item_code);  */

				item_amount=atoi(v_06[temp_string_counter].item_amount);
				item_amount/=100;

				/*printf("Item Amount %.2f\tCalculated-Di: %2f\n",item_amount,calculated_discount_amt);    */

				if(((float)(atoi(total_discount_amt))/100)>calculated_discount_amt)
				{
					if(atoi(v_10[temp_string_counter][0].string_type) == 10 || atoi(v_10[temp_string_counter][1].string_type) == 10)
					{

						individual_discount_amt=((int)(((float)(item_amount-(float)atoi(v_10[temp_string_counter][0].discount_amount)/100)*discount_percent/100)*100+.5)/100.0);	
					}
					else individual_discount_amt=((int)(((float)item_amount*discount_percent/100)*100+.5)/100.0);


					/*printf("Indiv:%2f\n",individual_discount_amt);  */
					if(temp_string_counter == (six_counter-1)) 
					{
						/*printf("Last: Calculate:%f\t%f\n",calculated_discount_amt,(float)(atoi(total_discount_amt))/100);   */
						if(((float)(atoi(total_discount_amt))/100)>calculated_discount_amt)
						individual_discount_amt=((int)(((float)(atoi(total_discount_amt))/100-calculated_discount_amt)*100+.5)/100.0);
						else individual_discount_amt=0;
					}
				}	
				else individual_discount_amt=0;

				calculated_discount_amt+=individual_discount_amt;
				/*printf("\nY : Calculated_Discount:%f\n",calculated_discount_amt);   */

				if(((float)(atoi(total_discount_amt))/100)<calculated_discount_amt)
				{
					calculated_discount_amt-=individual_discount_amt;
					/*printf("Y-1 : Calculated_Discount:%f\n",calculated_discount_amt);  */
					individual_discount_amt=((float)(atoi(total_discount_amt))/100)-calculated_discount_amt;
					calculated_discount_amt+=individual_discount_amt;
					/*printf("\nZ : Calculate:%f\t%f\n",calculated_discount_amt,individual_discount_amt);   */
				}
				/*printf("Individual:%f\n",individual_discount_amt); 
				printf("\nCal:%.2f\n",calculated_discount_amt); */
				
				if(atoi(v_06[temp_string_counter].dept_no) == 19 || atoi(v_06[temp_string_counter].dept_no) == 32 || atoi(v_08[temp_string_counter].string_type)==8)
				{
					/*printf("%s: Cant give discount for this \n",v_1_15.unit_number);  */
					calculated_discount_amt-=individual_discount_amt;
					/*printf("A : Calculated_Discount:%f\n",calculated_discount_amt); */
				}
				else
				{
					strcpy(v_10_8[temp_string_counter][0].string_type,hldarry[0]);
                			strcpy(v_10_8[temp_string_counter][0].discount_code,hldarry[1]);
					sprintf(discount_amt,"%.2f",individual_discount_amt);
				
					substr(real,discount_amt,0,strlen(discount_amt)-3);
					substr(decimal,discount_amt,strlen(discount_amt)-2,2);
					strcpy(v_10_8[temp_string_counter][0].discount_amount,real);
					strcat(v_10_8[temp_string_counter][0].discount_amount,decimal);
                			/*strcpy(v_10_8[string_counter][0].discount_amount,hldarry[2]); */
                			strcpy(v_10_8[temp_string_counter][0].discount_percent,hldarry[3]);
                			strcpy(v_10_8[temp_string_counter][0].indicat0,hldarry[4]);
                			strcpy(v_10_8[temp_string_counter][0].Extra,hldarry[5]);
                			hex2bin(v_10_8[temp_string_counter][0].indicat0,&v_10_8[temp_string_counter][0].binindicat0[0],&no_of_bin_digits);
					/*printf("Discount Code: %s\tDiscount Amount:%s\tDiscount Percent:%s\n",v_10_8[temp_string_counter][0].discount_code,v_10_8[temp_string_counter][0].discount_amount,v_10_8[temp_string_counter][0].discount_percent);  */
					v_10_8[temp_string_counter][0].discount_amount[strcspn(v_10_8[temp_string_counter][0].discount_amount,"\n")]='\0';
				}



			}
			
/* 26-AUG-2013 - Proration in case the last item is VOID or RETURN and total is not equal to calcu */
		/*	if(((float)(atoi(total_discount_amt))/100)>calculated_discount_amt && (temp_string_counter == (six_counter-1)))
			{
				float v_10_8_disc_amt;
				for(int i=temp_string_counter-1;i>=0;i--)
				{
					if((v_06[i].binindicat0[6]=='0' && v_06[i].binindicat0[7]=='0')	&& (v_06[i].DataExists == '0'))
					{
						individual_discount_amt=((float)(atoi(total_discount_amt))/100)-calculated_discount_amt;
						v_10_8_disc_amt=((float)(atoi(v_10_8[i][0].discount_amount))/100);
						sprintf(discount_amt,"%.2f",(individual_discount_amt+v_10_8_disc_amt));
						substr(real,discount_amt,0,strlen(discount_amt)-3);
						substr(decimal,discount_amt,strlen(discount_amt)-2,2);
						strcpy(v_10_8[i][0].discount_amount,real);
						strcat(v_10_8[i][0].discount_amount,decimal);
						i=-1;
					}

				}

			} */

/* 26-AUG-2013 - Proration in case the last item is VOID or RETURN and total is not equal to calcu */
			if(v_10_8[temp_string_counter][0].binindicat0[1]=='1')
			{
				memset(&v_10_8[temp_string_counter][0],0,sizeof(v_10_8[temp_string_counter][0]));
				calculated_discount_amt=0; 
			}
		}	
	
	}
	else if(strng_type==11)
	{
		/*printf("Txn:%s\tHold:%s\n",v_00.transaction_number,hldarry[1]);*/
		strcpy(v_11[string_counter].string_type,hldarry[0]);
		strcpy(v_11[string_counter].tender,hldarry[1]);
		/*printf("Txn:%s\t11-Tender:%s\n",v_00.transaction_number,v_11[string_counter].tender); */
	}
	else if(strng_type==14)
	{
		strcpy(v_14[string_counter].string_type,hldarry[0]);
		strcpy(v_14[string_counter].tax_a,hldarry[1]);
		strcpy(v_14[string_counter].tax_b,hldarry[2]);
		strcpy(v_14[string_counter].tax_c,hldarry[3]);
		strcpy(v_14[string_counter].tax_d,hldarry[4]);
		strcpy(v_14[string_counter].indicat0,hldarry[5]);
		hex2bin(v_14[string_counter].indicat0,&v_14[string_counter].binindicat0[0],&no_of_bin_digits);

	}
	else if(strng_type==12)
	{
		/*printf("Txn:%s\tHold:%s\n",v_00.transaction_number,hldarry[2]); */
		strcpy(v_12[string_counter].string_type,hldarry[0]);
		strcpy(v_12[string_counter].tender_type,hldarry[1]);
		strcpy(v_12[string_counter].tender_amount,hldarry[2]);
		strcpy(v_12[string_counter].customer_account,hldarry[3]);
                strcpy(v_12[string_counter].customer_status,hldarry[4]);
                strcpy(v_12[string_counter].indicat0,hldarry[5]);
                strcpy(v_12[string_counter].Extra1,hldarry[6]);
                strcpy(v_12[string_counter].Extra2,hldarry[7]);
		/*printf("Txn: %s \t 12Indicat0: %s\n",v_00.transaction_number,v_12.indicat0);*/
		hex2bin(v_12[string_counter].indicat0,&v_12[string_counter].binindicat0[0],&no_of_bin_digits);
		/*printf("Txn:%s\tHold:%s\n",v_00.transaction_number,v_12[string_counter].tender_amount);*/

	}
        else if(strng_type==15 && (!(strcmp(hldarry[1],"BANKDP"))))
        {
                strcpy(v_15_b[string_counter].string_type,hldarry[0]);
                strcpy(v_15_b[string_counter].type_of_15,hldarry[1]);
                strcpy(v_15_b[string_counter].current_date,hldarry[2]);
                strcpy(v_15_b[string_counter].dclose_date,hldarry[3]);
		strcpy(dclose_date,hldarry[3]);
                strcpy(v_15_b[string_counter].cash_amount,hldarry[4]);
                strcpy(v_15_b[string_counter].check_amount,hldarry[5]);
                strcpy(v_15_b[string_counter].net_amount,hldarry[6]);
                strcpy(v_15_b[string_counter].oper_id,hldarry[7]);

		/*printf("Get:%d - %s\t%s\n",string_counter,v_15_b[string_counter].cash_amount,v_15_b[string_counter].check_amount); */
        }
	else if(strng_type==17)
	{
		strcpy(v_17[string_counter].string_type,hldarry[0]);
		strncpy(v_17[string_counter].register_number,hldarry[1],4);
		strcpy(v_17[string_counter].amount,hldarry[2]);
		strncpy(v_17[string_counter].transaction_number,hldarry[3],4);
		/*printf("Txn:%d\tHld:%d\tTxnV:%s\tHldV:%s\tSur\n",strlen(v_17[string_counter].transaction_number),strlen(hldarry[3]),v_17[string_counter].transaction_number,hldarry[3]); */
	}
	else
		printf("Please Check:GetStringType.h\n");

}


void string_pad(char *src_string, size_t padlen, char *pad, char *lpadrpad)
{
	size_t lenstring = strlen(src_string);
	char *final = (char *)malloc(lenstring+padlen+1);
	strcpy(final,"");
	/*printf("string length %d\n",lenstring); */
	if (!strcmp(lpadrpad,"R"))
	{
		strcat(final,src_string);
		for (int i=0;i<padlen;i++)
		{
			strcat(final,pad);
		}
		/*strcat(final,'\0');*/
	}
	else if (!strcmp(lpadrpad ,"L"))
	{
		for(int i=0;i<padlen;i++)
			strcat(final,pad);
		strcat(final,src_string);
		/*strcat(final,'\0');*/
	}
	strcpy(src_string,final);
	memset(final,0,sizeof(*final));
	free(final);
}
void string_pad_old(char * src_string, size_t padlen, char* pad, char *LpadRpad)
{
        size_t lenstring = strlen(src_string);
        size_t lenpad = strlen(pad);
        /*char Lpad[100];*/

        /*printf ("string Len:%d\nPad Len:%d\n",lenstring,lenpad); */

        char * padded = (char*)malloc((lenpad*padlen)+lenstring);
        char * Lpad = (char*)malloc(lenstring + lenpad);
        strncpy(padded, src_string, lenstring);

/*        printf("\n: Padded: %s\n",padded); */
        if (!strcmp(LpadRpad,"R"))
        {
		/*printf("I am in R\n");*/
                padded += lenstring+1;
                for(; padlen > 0; padlen--, padded += lenpad)
                        {
                        strncpy(padded, pad, lenpad);
                        strcat(src_string,padded);
                        }
        }
        else
        {
                padded -= lenstring;
                for(; padlen > 0; padlen--)
                {
                        strcat(Lpad,pad);
                        strcat(Lpad,src_string);
                        strcpy(src_string,Lpad);
			strcpy(Lpad,"");
                }
			free(Lpad);
        }

        /*printf("Inside src_string: %s\n",src_string);*/
	free(padded);
        src_string[strlen(src_string)+1]= '\0';
}
/*void GetCurrentDateTime(char *DateTime,int HoldSize,char *RequiredFormat)
{
	time_t Now = time(0);
	strftime(DateTime,HoldSize,RequiredFormat,localtime(&Now));
}*/

void number_pad(char *dest_string,int int_number,int no_of_chars)
{
	char buffer[50];
	/*printf("I am in Number Pad\n");*/
	sprintf(buffer,"%%0%dd",no_of_chars);
	sprintf(dest_string,buffer,int_number);
	/*sprintf(dest_string,"%d",int_number);
	string_pad(dest_string,10-strlen(dest_string),"0","R");*/
}

/*void GetItemStatus(char *pIndicat0,char *v_item_status) */
void GetItemStatus(char binIndicat0[],char *v_item_status)
{
	/*printf("I am in GetItemStatus\n");*/
	/*if((!strcmp(pIndicat0,"1013")) || (!strcmp(pIndicat0,"1113")) || (!strcmp(pIndicat0,"1413"))|| atoi(pIndicat0)==102 || atoi(pIndicat0)==1015 || atoi(pIndicat0)==1105 || atoi(pIndicat0)==115 || atoi(pIndicat0)==1115 || atoi(pIndicat0)==1415 || atoi(pIndicat0)== 15 || atoi(pIndicat0)==100 || atoi(pIndicat0)==1513 || atoi(pIndicat0)==1813|| atoi(pIndicat0)==113 || atoi(pIndicat0)==13 || !(strcmp(pIndicat0,"1D2")) || !(strcmp(pIndicat0,"0"))) strcpy(v_item_status,"S");
	else if((!strcmp(pIndicat0,"1893")) || (!strcmp(pIndicat0,"D2")) ||  (!strcmp(pIndicat0,"D4")) || (!strcmp(pIndicat0,"1093"))||atoi(pIndicat0)==1993 || atoi(pIndicat0)==1095 || atoi(pIndicat0)==1493 || atoi(pIndicat0)==1193 || atoi(pIndicat0)==1195 || atoi(pIndicat0)==1495 || atoi(pIndicat0)==1593 ||  atoi(pIndicat0)==1893 || atoi(pIndicat0)==1895 || atoi(pIndicat0)== 895 || atoi(pIndicat0)==1995) strcpy(v_item_status,"V");
	else if(atoi(pIndicat0)==1053 || atoi(pIndicat0)==52 || atoi(pIndicat0)==54 || atoi(pIndicat0)==152 || atoi(pIndicat0)==154) strcpy(v_item_status,"R");
	else strcpy(v_item_status,"X");
	*/

	if(binIndicat0[6]=='1') strcpy(v_item_status,"R");
	else if( binIndicat0[7]=='1') strcpy(v_item_status,"V");
	else strcpy(v_item_status,"S");

	/*if(binIndicat0[6]=='1' && binIndicat0[7]=='1') strcpy(v_item_status,"S"); */
	if(binIndicat0[6]=='1' && binIndicat0[7]=='1') strcpy(v_item_status,"V");
}

void GetReSATransactionType(char *POSTransactionType,char *ReSA_Transaction_type)
{

	/*if(atoi(POSTransactionType)<50 && atoi(POSTransactionType)!=0 )
	{
		if((atoi(v_00.net_postive_amount) - atoi(v_00.net_negative_amount)) >=0) strcpy(ReSA_Transaction_type,"SALE");
		else 
		{
			if(atoi(v_00.indicat0)==808 || atoi(v_00.indicat0)==848 || atoi(v_00.indicat0)==888|| atoi(v_00.indicat0)== 8 || !strcmp(v_00.indicat0,"80A")) strcpy(ReSA_Transaction_type,"VOID");
			else strcpy(ReSA_Transaction_type,"RETURN");
		}
	}
	else if(atoi(POSTransactionType)==0) strcpy(ReSA_Transaction_type,"NOSALE");
	else if(atoi(POSTransactionType)==50)  strcpy(ReSA_Transaction_type,"LOAN");
	else if(atoi(POSTransactionType)==51)  strcpy(ReSA_Transaction_type,"PULL");
	else if(atoi(POSTransactionType)==56) strcpy(ReSA_Transaction_type,"TOTAL");
	else if(atoi(POSTransactionType)==59) strcpy(ReSA_Transaction_type,"NOSALE");
	else if(atoi(POSTransactionType)==60) strcpy(ReSA_Transaction_type,"PVOID");
	else if(atoi(POSTransactionType)==53) strcpy(ReSA_Transaction_type,"NOSALE");
	else if(atoi(POSTransactionType)==91) strcpy(ReSA_Transaction_type,"NOSALE");
	else if(atoi(POSTransactionType)==93) strcpy(ReSA_Transaction_type,"NOSALE");
	else if(atoi(POSTransactionType)==64) strcpy(ReSA_Transaction_type,"NOSALE");

	if(atoi(v_00.indicat0)==808 || !strcmp(v_00.indicat0,"C08")) strcpy(ReSA_Transaction_type,"VOID"); */


	/*if(v_00.binindicat0[3] == '1') printf("\nTxn:%s is Voided\n",v_00.transaction_number);
        if(v_00.binindicat0[14] == '1') printf("\nTxn:%s is ReTurn\n",v_00.transaction_number);	
	printf("\ntxn: %s\t%d\n",v_00.transaction_number,no_of_bin_digits);
	for(int j=0;j<16;j++)
                printf("%c\t",v_00.binindicat0[j]); */

	if(atoi(POSTransactionType)<50 && atoi(POSTransactionType)!=0 )
	{
		if(v_00.binindicat0[3] == '1') strcpy(ReSA_Transaction_type,"VOID");
		else if(v_00.binindicat0[14] == '1') strcpy(ReSA_Transaction_type,"RETURN");
		else strcpy(ReSA_Transaction_type,"SALE");
	}
	else if(atoi(POSTransactionType)==60) 
	{
		if(v_00.binindicat0[3] == '1') strcpy(ReSA_Transaction_type,"VOID");
		else strcpy(ReSA_Transaction_type,"PVOID");
	}
	else if(atoi(POSTransactionType)==0 || atoi(POSTransactionType)==59 || atoi(POSTransactionType)==53 ||atoi(POSTransactionType)==64 || atoi(POSTransactionType)==91 || atoi(POSTransactionType)==93 || atoi(POSTransactionType)==52 || atoi(POSTransactionType)==54 || atoi(POSTransactionType)==55 || atoi(POSTransactionType)==57 || atoi(POSTransactionType)==58 || atoi(POSTransactionType)==61 || atoi(POSTransactionType)==63 || atoi(POSTransactionType)==65 || atoi(POSTransactionType)==66 || atoi(POSTransactionType)==94) strcpy(ReSA_Transaction_type,"NOSALE");
	else if(atoi(POSTransactionType)==50)  strcpy(ReSA_Transaction_type,"LOAN");
	else if(atoi(POSTransactionType)==51)  
	{
		if(v_00.binindicat0[3] == '1') strcpy(ReSA_Transaction_type,"VOID");
		else strcpy(ReSA_Transaction_type,"PULL");
	}
	else if(atoi(POSTransactionType)==56 ) strcpy(ReSA_Transaction_type,"TOTAL");

	if(atoi(POSTransactionType)==56  && Dclose_Done=='Y') 
	{
		strcpy(ReSA_Transaction_type,"NOSALE");
	}
}

void GetReSATransactionSubType(char *POSTransactionType,char *ReSA_Transaction_subtype)
{
	/*if(atoi(POSTransactionType)<50 && atoi(POSTransactionType)!=0 && atoi(v_00.indicat0)!=808 && atoi(POSTransactionType)!=2 )
	{
		if((atoi(v_00.net_postive_amount) - atoi(v_00.net_negative_amount)) >=0) strcpy(ReSA_Transaction_subtype,"SALE");
		else 
		{
			if(atoi(v_00.indicat0)==808 || atoi(v_00.indicat0)==848 || atoi(v_00.indicat0)==888 ||atoi(v_00.indicat0)== 8 || !strcmp(v_00.indicat0,"80A")) strcpy(ReSA_Transaction_subtype,"VOID");
			else strcpy(ReSA_Transaction_subtype,"RETURN");
		}
	} */
	if(atoi(POSTransactionType)<50 && atoi(POSTransactionType)!=0 && atoi(POSTransactionType)!=2 )
	{
                if(v_00.binindicat0[3] == '1') strcpy(ReSA_Transaction_subtype,"VOID");
                else if(v_00.binindicat0[14] == '1') strcpy(ReSA_Transaction_subtype,"RETURN");
                else strcpy(ReSA_Transaction_subtype,"SALE");
	}
	else if(atoi(POSTransactionType)==0 || atoi(POSTransactionType)==59 || atoi(POSTransactionType)==53 ||atoi(POSTransactionType)==64 || atoi(POSTransactionType)==91 || atoi(POSTransactionType)==93  || atoi(POSTransactionType)==61) strcpy(ReSA_Transaction_subtype,"NOSALE");
	else if(atoi(POSTransactionType)==50)  strcpy(ReSA_Transaction_subtype,"      ");
	else if(atoi(POSTransactionType)==51)  
	{
		if(v_00.binindicat0[3] == '1') strcpy(ReSA_Transaction_subtype,"VOID");
		else strcpy(ReSA_Transaction_subtype,"      ");
	}
	else if(atoi(POSTransactionType)==56) strcpy(ReSA_Transaction_subtype,"    ");
	else if(atoi(POSTransactionType)==60) strcpy(ReSA_Transaction_subtype,"    ");
	else if(atoi(POSTransactionType)==53) strcpy(ReSA_Transaction_subtype,"CREG");

	if(atoi(v_00.indicat0)==808 || !strcmp(v_00.indicat0,"C08")) strcpy(ReSA_Transaction_subtype,"VOID");
	if(atoi(POSTransactionType)==2) strcpy(ReSA_Transaction_subtype,"EMP");


}

void GetTenderTypeGroup(char *OutTenderType, char *InTenderType)
{
	if (atoi(InTenderType)==0 || atoi(InTenderType)==17) strcpy(OutTenderType,"CHECK");
	else if (atoi(InTenderType)==1 || atoi(InTenderType)==3 || atoi(InTenderType)==4 || atoi(InTenderType)==6 || atoi(InTenderType)==18 || atoi(InTenderType)==19 || atoi(InTenderType)==20 || atoi(InTenderType)==21 || atoi(InTenderType)==22 || atoi(InTenderType)==23 || atoi(InTenderType)==99 || atoi(InTenderType)==25) strcpy(OutTenderType,"COUPON"); /* Date:15-Jan-19 : Added new tendertype 'PROMO CARD' */
	else if (atoi(InTenderType)==2 || atoi(InTenderType)==15 || atoi(InTenderType)==14 || atoi(InTenderType)==24) strcpy(OutTenderType,"CASH");
	else if (atoi(InTenderType)==10 || atoi(InTenderType)==11 || atoi(InTenderType)==12 || atoi(InTenderType)==26) strcpy(OutTenderType,"CCARD");
	else if (atoi(InTenderType)==13) strcpy(OutTenderType,"DCARD");

	/*printf("OutTender: %s\n",OutTenderType); */

/*                     00,
                    'CHECK',                                          -- CHECK
                    01,
                    'COUPON',                                     -- GIFT CERT
                    02,
                    'CASH',                                     -- US CURRENCY
                    03,
                    'COUPON',                                   -- MICH COUPON
                    04,
                    'COUPON',                                   -- VEND COUPON
                    06,
                    'COUPON',                                       -- INST CG
                    10,
                    'CCARD',                                    -- VISA/ US MC
                    11,
                    'CCARD',                                    -- DISC/CAN MC
                    12,
                    'CCARD',                                           -- AMEX
                    13,
                    'DCARD',                                     -- DEBIT CARD
                    14,
                    'CASH',                                  -- CDN CONVERSION
                    15,
                    'CASH',                                            -- CASH
                    17,
                    'CHECK',                                -- TRAVELERS CHECK
                    18,
                    'COUPON',                                    -- MDSE ISSUE
                    19,
                    'COUPON',                                   -- MDSE REDEEM
                    20,
                    'COUPON',                                 -- CARD OVERRIDE
                    21,
                    'COUPON',                                    -- SVC REDEEM
                    22,
                    'COUPON',                               -- MDSE CARD ISSUE
                    23,
                    'COUPON',                              -- MDSE CARD REDEEM
                    99,
                    'COUPON'                                     -- INV TENDER
*/

}

void GetTenderTypeId(char *OutTenderType, char *InTenderType,int string_counter)
{
	char temp_string[30];
	if (atoi(InTenderType)==0) strcpy(OutTenderType,"2000");
	else if (atoi(InTenderType)==1) strcpy(OutTenderType,"5020");
	else if (atoi(InTenderType)==2) strcpy(OutTenderType,"1000");
	else if (atoi(InTenderType)==3) strcpy(OutTenderType,"5000");
	else if (atoi(InTenderType)==4) strcpy(OutTenderType,"5010");
	else if (atoi(InTenderType)==6) strcpy(OutTenderType,"5030");
	else if (atoi(InTenderType)==10) 
	{
		substr(temp_string, v_12[string_counter].customer_account,0,4);
		if(atoi(temp_string)>=5100 && atoi(temp_string)<=5599) strcpy(OutTenderType,"3010");
		else strcpy(OutTenderType,"3000");
	}	
	else if(atoi(InTenderType)==11) 
	{
		substr(temp_string, v_12[string_counter].customer_account,0,4);
		if(atoi(temp_string)>=5100 && atoi(temp_string)<=5599) strcpy(OutTenderType,"3010");
		else strcpy(OutTenderType,"3030");
		/*printf("Txn:%s\ttemp :%s\tTwel:%d\tIn:%s\tOutTenderType:%s\n",v_00.transaction_number,temp_string,string_counter,InTenderType,OutTenderType);*/
	}
	else if(atoi(InTenderType)==12) strcpy(OutTenderType,"3020");	
	else if(atoi(InTenderType)==13) strcpy(OutTenderType,"8000");	
	else if(atoi(InTenderType)==14) strcpy(OutTenderType,"1010");	
	else if(atoi(InTenderType)==15) strcpy(OutTenderType,"1000");	
	else if(atoi(InTenderType)==17) strcpy(OutTenderType,"2020");	
	else if(atoi(InTenderType)==18) strcpy(OutTenderType,"5040");	
	else if(atoi(InTenderType)==19) strcpy(OutTenderType,"5050");	
	else if(atoi(InTenderType)==20) strcpy(OutTenderType,"3000");	
	else if(atoi(InTenderType)==21) strcpy(OutTenderType,"5090");	
	else if(atoi(InTenderType)==22) strcpy(OutTenderType,"5060");	
	else if(atoi(InTenderType)==23) strcpy(OutTenderType,"5070");	
	else if(atoi(InTenderType)==24) strcpy(OutTenderType,"1020");
	else if(atoi(InTenderType)==99) strcpy(OutTenderType,"5080");	
	else if(atoi(InTenderType)==25) strcpy(OutTenderType,"5100");     /* Date:15-Jan-19 : Added new tendertype 'PROMO CARD' */
	else if(atoi(InTenderType)==26) strcpy(OutTenderType,"8040");     /* Date:29-SEP-22 : Added new tendertype 'PLCC' */
/*	     00,
               2000,                                         -- PERSONAL CHECK
               01,
               5020,                                  -- GCN: Gift Certificate
               02,
               1000,                                                   -- CASH
               03,
               5000,                                   -- MANUFACTURERS COUPON
               04,
               5010,                                            -- VEND COUPON
               06,
               5030,                                                -- INST CG
               10,
               CASE
                  WHEN SUBSTR ( (TRIM (LEADING 0 FROM account_no)), 0, 4) >=
                          5100
                       AND SUBSTR ( (TRIM (LEADING 0 FROM account_no)), 0, 4) <=
                             5599
                  THEN
                     3010
                  ELSE
                     3000
               END,                                                    -- VISA
               11,
               CASE
                  WHEN SUBSTR ( (TRIM (LEADING 0 FROM account_no)), 0, 4) >=
                          5100
                       AND SUBSTR ( (TRIM (LEADING 0 FROM account_no)), 0, 4) <=
                             5599
                  THEN
                     3010
                  ELSE
               		3030                                               
		END,							-- DISCOVER
               12,
               3020,                                                   -- AMEX
               13,
               8000,                                                  -- DEBIT
               14,
               1010,                                         -- ALTERNATE CASH
               15,
               1000,                                                   -- CASH
               17,
               2020,                                        -- TRAVELERS CHECK
               18,
               5040,                                             -- MDSE ISSUE
               19,
               5050,                                            -- MDSE REDEEM
               20,
               3000,                                                   -- VISA
               21,
               5090,                                             -- SVC REDEEM
               22,
               5060,                                        -- MDSE CARD ISSUE
               23,
               5070,                                       -- MDSE CARD REDEEM
               99,
               5080                                              -- INV TENDER  
*/


}

void CleanUpInputArray()
{

	memset(&v_04,0,sizeof(v_04));
	memset(&v_06,0,sizeof(v_06));
	memset(&v_07,0,sizeof(v_07));
	memset(&v_08,0,sizeof(v_08));
	memset(&v_08_tax,0,sizeof(v_08));
	memset(&v_09,0,sizeof(v_09));
	memset(&v_09P,0,sizeof(v_09P));
	memset(&v_10,0,sizeof(v_10)); 
	memset(&v_10_8,0,sizeof(v_10_8)); 
	memset(&v_11,0,sizeof(v_11)); 
	memset(&v_12,0,sizeof(v_12));
	memset(&v_14,0,sizeof(v_14));
	memset(&v_17,0,sizeof(v_17));
	memset(&v_00,0,sizeof(v_00)); 
	number_of_fields=0;
	six_counter=0;
	twelve_counter=0;
	fourteen_counter=0;
	seventeen_counter=0;
	tax_08_counter=0;
	total_08_tax=0;
	no_of_bin_digits=0;
	calculated_discount_amt=0;
	transaction_taxexmpt='N';
	manual_tax='N';
	manual_written='N';
}

void writeTHEAD()
{
	char padding_string[MAXFLDS];
	char ReSA_Transaction_type[MAXFLDS];
	current_line_counter++;
	strcpy(transaction_line,"THEAD");			/* THEAD -5 */
	number_pad(padding_string,current_line_counter,10);	/*Running Line Number - 10 */	
	strcat(transaction_line,padding_string);	
	strcat(transaction_line,"0");
	strcat(transaction_line,v_00.terminal_number);		/* Register Number  - 5 */
	strcat(transaction_line,"20");
	strcat(transaction_line,v_00.date_of_transaction);	/* Transaction Date YYYYMMDD */
	strcat(transaction_line,v_00.time_of_transaction);
	strcat(transaction_line,"00");				/*Transaction Date,time in sec - 14 */
	string_pad(transaction_line,10-strlen(v_00.transaction_number),"0","R");
	strcat(transaction_line,v_00.transaction_number)	/* POS Transaction Number  - 10 */;
	string_pad(transaction_line,10-strlen(v_00.operator_number),"0","R");
	strcat(transaction_line,v_00.operator_number);		/* Cashier - 10 */
	string_pad(transaction_line,10," ","R");		/* Sales Person - 10 */
	/*strcpy(ReSA_Transaction_type,"SALE");	*/
	GetReSATransactionType(v_00.transaction_type,ReSA_Transaction_type);
	strcat(transaction_line,ReSA_Transaction_type);
	/*string_pad(transaction_line,6-strlen(ReSA_Transaction_type)," ","R")*/;
	strcat(transaction_line,"SALE");   /* Sub Transaction_type - 6 */
	string_pad(transaction_line,2," ","R");
	string_pad(transaction_line,10," ","R");   /*Orig_tran_no -10 */
	string_pad(transaction_line,5," ","R");		/*Orig_reg_no -5 */
	string_pad(transaction_line,6," ","R");		/*Reason Code - 6 */
	string_pad(transaction_line,10," ","R");	/* Vendor Number - 10 */
	string_pad(transaction_line,30," ","R");	/*Vendor Invoice Number - 30 */
	string_pad(transaction_line,16," ","R");	/* Payment Reference Number - 16 */
	string_pad(transaction_line,30," ","R");	/*Proof of Delivery Number - 30 */
	string_pad(transaction_line,30," ","R");	/*Reference Number 1- 30 */
	string_pad(transaction_line,30," ","R");	/*Reference Number 2- 30 */
	string_pad(transaction_line,30," ","R");	/*Reference Number 3- 30 */
	string_pad(transaction_line,30," ","R");	/*Reference Number 4- 30 */
	if(v_00.net_total_amount >=0) strcat(transaction_line,"P");
	else strcat(transaction_line,"N");
	string_pad(transaction_line,20-strlen(v_00.net_total_amount)-2,"0","R");
	strcat(transaction_line,v_00.net_total_amount);		/*Net total Amount 20 16 Real + 4 Decimal */
	strcat(transaction_line,"00");
	strcat(transaction_line,"0001");		/*Banner Id*/
	string_pad(transaction_line,30," ","R");	/* Customer Order Head ID - 30 */
	string_pad(transaction_line,14," ","R");	/* Customer Order Head Date - 30 */
	/*printf("Length: %d\n",strlen(transaction_line));*/
	transaction_line[strlen(transaction_line)+1]='\n';
	fwrite(transaction_line,strlen(transaction_line),current_line_counter,outfile);
	memset(transaction_line,0,sizeof(transaction_line));
	free(transaction_line);
}


void writeTITEM(int string_counter)
{ 
	
	char padding_string[MAXFLDS];
	char v_item_status[1];
	current_line_counter++;
	strcpy(transaction_line,"TITEM");		/* TITEM - 5 */
	number_pad(padding_string,current_line_counter,10);     /*Running Line Number - 10 */
        strcat(transaction_line,padding_string);
	GetItemStatus(v_06[string_counter].indicat0,v_item_status);
	strcat(transaction_line,v_item_status);			/* Item Status - 6 */
	string_pad(transaction_line,5," ","R");
	strcat(transaction_line,"REF");				/* Item Type - 6 */
	string_pad(transaction_line,3," ","R");
	strcat(transaction_line,"UCC14");			/* Item Number Type - 6*/
	string_pad(transaction_line,2," ","R");			/* Format ID + Item Number Type Space - 1+1*/
	string_pad(transaction_line,15," ","R");		 /*Item - 15 */
	string_pad(transaction_line,10," ","R");		 /*Item - 10 */
	strcat(transaction_line,v_06[string_counter].item_code);		/* Reference Item - 25 */
	string_pad(transaction_line,25-strlen(v_06[string_counter].item_code)," ","R");
	string_pad(transaction_line,25," ","R");		 /* Non Merchadise Item - 25 */
	string_pad(transaction_line,25," ","R");		 /* Voucher - 25 */
	strcat(transaction_line,v_06[string_counter].dept_no);			/* Department -4 */
	string_pad(transaction_line,4-strlen(v_06[string_counter].dept_no),"0","R");
	string_pad(transaction_line,4,"0","R");			/* Class - 4 */	
	string_pad(transaction_line,4,"0","R");			/* sub-Class - 4 */	
	/*printf("Length: %d\n",strlen(transaction_line));*/
        transaction_line[strlen(transaction_line)+1]='\n';
        fwrite(transaction_line,strlen(transaction_line),current_line_counter,outfile);
        memset(transaction_line,0,sizeof(transaction_line));
        free(transaction_line);

}



