/* THEAD, TITEM, IDISC ReSA File type records definition and formation */


/********************************************************************************************************************************************************/
/*Change History:                                                                                                                                       */
/*Date:08-MAR-13 : Handled return transaction voided quantity and quantity sign in StoreInITEM()                                                        */
/*                 memset(&v_09P[string_counter],0,sizeof(v_09P[string_counter])                                                                        */
/*Date:14-Mar-13 : Handled 08 Misllenious string for fee transaction (4,8,80,88,400) as Non merchandise item in TITEM                                   */
/*Date:11-Aug-14 : Handled core dump issue in RTLOG conversion                                                                                          */
/*Date:10-Dec-15 - Version 2.0 : Added new tax code "RDTX4" for Manual tax                                                                              */
/*Date:15-Jan-19 : Added new tendertype 'PROMO CARD'                                                                                                    */
/*Date:30-Jan-19 : Karthikkumar TS, TCS - Added logic to populate ref_no12 in sa_tran_tender for coupon tender type                                     */
/*Date:29-SEP-22 : Added new tendertype 'PLCC'                                                                                                          */
/*Date:12-AUG-25 : Commented code for 'MPFTX'                                                                                                           */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/*                                                                                                                                                      */
/********************************************************************************************************************************************************/


/* Output Header Structure */
struct FHEAD_00
{
	char FileTypeRecord[5];
	char LineNumber[10];
	char FileTypeDef[4];
	char FileCreateDate[14];
	char BusinessDate[8];
	char LocationNumber[10];
	char ReferenceNumber[30];
} *FHEAD_v00;

struct THEAD_00
{
	char FileTypeRecord[5];
	char LineNumber[10];
	char Register[5];
	char TransactionDate[14];
	char TransactionNumber[10];
	char Cashier[10];
	char SalesPerson[10];
	char TransactionType[6];
	char SubTransactionType[6];
	char OrigTxnNo[10];
	char OrigRegNo[5];
	char ReasonCode[6];
	char VendorNumber[10];
	char VendorInvoiceNumber[30];
	char PaymentRefNumber[16];
	char ProofOfDelivery[30];
	char ReferenceNumber1[30];
	char ReferenceNumber2[30];
	char ReferenceNumber3[30];
	char ReferenceNumber4[30];
	char ValueSign[1];
	char Value[20];
	char BannerId[4];
	char CustomerOrderHead[30];
	char CustomerOrderDate[14];
/* For 13.1 Back porting */

	char RoundedAmountSign[1];
        char RoundedAmount[20];
        char RoundedOffSign[1];
        char RoundedOffAmount[20]; 

/* For 13.1 Back porting */
	char EndOfString[1];
	char NewLine[1];
} *THEAD_v00,*THEAD_v00_15;

/* Output Discount Structure */
struct IDISC_10
{
	char FileTypeRecord[5];
	char LineNumber[10];
	char RMSPromotionNumber[6];
	char DiscountNumber[10];
	char DiscountType[6];
	char CouponNumber[16];
	char CouponReferenceNumber[16];
	char QuantitySign[1];
	char Quantity[12];
	char UnitDiscountAmount[20];
	char ReferenceNumber13[30];
	char ReferenceNumber14[30];
	char ReferenceNumber15[30];
	char ReferenceNumber16[30];	
	char UomQuantity[12];
	char CatchWeightInd[1];
	char PromoComponent[10];
	char EndOfString[1];
	char NewLine[1];
} *IDISC_v10,*TDISC_v10_8;

/* Output Tax Structure */
struct TAX_14
{
	char FileTypeRecord[5];
	char LineNumber[10];
	char TaxCode[6];
	char TaxSign[1];
	char TaxAmount[20];
	char ReferenceNumber17[30];
	char ReferenceNumber18[30];
	char ReferenceNumber19[30];
	char ReferenceNumber20[30];
	char EndOfString[1];
	char NewLine[1];
} *TAX_v14;

/*Output Transaction Item Structure */
struct TITEM_06
{
	char FileTypeRecord[5];
	char LineNumber[10];
	char ItemStatus[6];
	char ItemType[6];
	char ItemNumberType[6];
	char FormatId[1];
	char Item[25];
	char ReferenceItem[25];	
	char NonMerchandiseItem[25];
	char Voucher[25];
	char Department[4];
	char Class[4];
	char SubClass[4];
	char QuantitySign[1];
	char Quantity[12];
	char SellingUnit[4];
	char UnitRetail[20];	
	char OverrideReason[6];
	char OriginalUnitRetail[20];
	char TaxableIndicator[1];
	char Pump[8];
	char ReferenceNumber5[30];
	char ReferenceNumber6[30];
	char ReferenceNumber7[30];
	char ReferenceNumber8[30];
	char ItemSwipedInd[1];
	char ReturnReasonCode[6];
	char SalesPerson[10];
	char ExpirationDate[8];
	char DropShipInd[1];
	char UomQty[12];
	char CatchWeightInd[1];
	char SellingItem[25];
	char CustOrderLine[6];
	char MediaId[10];
	char EndOfString[1];
	char NewLine[1];
} *TITEM_v06;

/* Output Tender Type Structure */
struct TENDER_12
{

	char FileTypeRecord[5];
        char LineNumber[10];
	char TenderTypeGroup[6];
	char TenderTypeId[6];
	char TenderSign[1];
	char TenderAmount[20];
	char CcNo[40];
	char CcAuthNo[16];
	char CcAuthorizationSource[6];
	char CcCardHolderVerification[6];
	char CcExpirationDate[8];
	char CcEntryMode[6];
	char CcTerminalId[5];
	char CcSpecialCondition[6];
	char VoucherNumber[25];
	char CouponNumber[16];
	char CouponReferenceNumber[16];
	char ReferenceNumber9[30];
	char ReferenceNumber10[30];
	char ReferenceNumber11[30];
	char ReferenceNumber12[30];
	char EndOfString[1];
	char NewLine[1];

} *TENDER_v12;


/* Transaction Tail Output Structure */

struct TTAIL_00
{
	char FileTypeRecord[5];
        char LineNumber[10];
	char TransactionRecordCount[10];
	char EndOfString[1];
	char NewLine[1];
} *TTAIL_v00;


/* File Tail OUTput Structure */
struct FTAIL_99
{
	char FileTypeRecord[5];
	char LineNumber[10];
	char TotalTransactionLines[10];
	char EndOfString[1];
	char NewLine[1];

} *FTAIL_v99;

void CleanUpOutStructs()
{
	/*memset(TENDER_v12,0,sizeof(*TENDER_v12)); */
}
/* Procedure to Capture all the details required to compose the Header from string types 00 */
void StoreInFHEAD(int string_counter)
{
	char padding_string[MAXFLDS];
	FHEAD_v00 = (struct FHEAD_00 *)malloc(sizeof(struct FHEAD_00));
	strcpy(FHEAD_v00->FileTypeRecord,"FHEAD");
	/*if(atoi(v_00.transaction_type) == 56 && !(strcmp(v_15_b[string_counter].type_of_15,"BANKDP")) && Dclose_Done=='N')*/
	if(start_dclose=='Y')
	{
		dclose_line_counter++;
                number_pad(padding_string,dclose_line_counter,10);
	}
        else
        {
                current_line_counter++;
                number_pad(padding_string,current_line_counter,10);
        }
	strcpy(FHEAD_v00->LineNumber,padding_string);
	strcpy(FHEAD_v00->FileTypeDef,"RTLG");
	GetCurrentDateTime(CurrentDate,25,"%Y%m%d%H%M%S");
	strcpy(FHEAD_v00->FileCreateDate,CurrentDate);
	strcpy(FHEAD_v00->BusinessDate,"20");
	/*if(atoi(v_00.transaction_type) == 56 && !(strcmp(v_15_b[string_counter].type_of_15,"BANKDP")) && Dclose_Done=='N') */
	if(start_dclose=='Y')
                strcat(FHEAD_v00->BusinessDate,DcloseDates[string_counter].dclose_date);
        else
                strcat(FHEAD_v00->BusinessDate,tlog_date);     /* Business Date */
/*	strcpy(FHEAD_v00->LocationNumber,v_1_15.unit_number);  */  /* Store Location - (Store Number) */
	sprintf(FHEAD_v00->LocationNumber,"%d",atoi(v_1_15.unit_number));
	string_pad(FHEAD_v00->LocationNumber,10-strlen(FHEAD_v00->LocationNumber)," ","R");
	string_pad(FHEAD_v00->ReferenceNumber,30," ","R");        /* Reference Number */

}
	

/* Forward declaration for CollectTHEADRecord (to avoid implicit int declaration) */
extern void CollectTHEADRecord(char *store, char *business_date, char *tran_datetime, char *register_no,
                               char *tran_no, char *cashier, char *salesperson, char *tran_type,
                               char *sub_tran_type, char *orig_tran_no, char *orig_reg_no,
                               char *ref_no1, char *ref_no2, char *ref_no3, char *ref_no4,
                               char *value, char *value_sign, char *banner_no, char *rounded_amt,
                               char *rounded_off_amt);

void StoreInTHEAD(int string_counter)
{

	/*CleanUpOutStructs(); */
        /*printf("inside Store In THEAD\n");   */
	char ReSA_Transaction_type[MAXFLDS];
	char ReSA_Transaction_subtype[MAXFLDS];
	char padding_string[MAXFLDS];
	char org_txn[5];
	THEAD_v00 = (struct THEAD_00 *)malloc(sizeof(struct THEAD_00));
	thead_no=current_line_counter;
	Head_net_positive=atoi(v_00.net_postive_amount);
	Head_net_negative=atoi(v_00.net_negative_amount);
	transaction_number=atoi(v_00.transaction_number);
	strcpy(THEAD_v00->FileTypeRecord,"THEAD");
        if(atoi(v_00.transaction_type) == 56 && !(strcmp(v_15_b[string_counter].type_of_15,"BANKDP")) && Dclose_Done=='N')
                number_pad(padding_string,dclose_line_counter,10);
        else
        {
                current_line_counter++;
                thead_no=current_line_counter;
                number_pad(padding_string,current_line_counter,10);
        }
	strcpy(THEAD_v00->LineNumber,padding_string);
	/*if(strlen(v_00.terminal_number)<5) string_pad(THEAD_v00->Register,5-strlen(v_00.terminal_number),"0","R");
	strcat(THEAD_v00->Register,v_00.terminal_number); */
	strcpy(THEAD_v00->Register,v_00.terminal_number);
	string_pad(THEAD_v00->Register,5-strlen(v_00.terminal_number)," ","R");
	strcpy(THEAD_v00->TransactionDate,"20");
	strcat(THEAD_v00->TransactionDate,v_00.date_of_transaction);
	strcat(THEAD_v00->TransactionDate,v_00.time_of_transaction);
	strcat(THEAD_v00->TransactionDate,"00");
	if(strlen(v_00.transaction_number)<10)	string_pad(THEAD_v00->TransactionNumber,10-strlen(v_00.transaction_number),"0","R");
	strcat(THEAD_v00->TransactionNumber,v_00.transaction_number);
        if(atoi(v_00.transaction_type) == 56 && !(strcmp(v_15_b[string_counter].type_of_15,"BANKDP")) && Dclose_Done=='N')
        {
                /*if(dclose_line_counter==2) strcpy(THEAD_v00->TransactionNumber,"1390");
                else strcpy(THEAD_v00->TransactionNumber,"1410"); 
		strcat(THEAD_v00->TransactionNumber,v_00.transaction_number);  */
		/*if(dclose_line_counter == 2)
		{
			strcpy(THEAD_v00->TransactionNumber,v_00.transaction_number);
			string_pad(THEAD_v00->TransactionNumber,10-strlen(v_00.transaction_number),"0","L");	
		}
		else */
			string_pad(THEAD_v00->TransactionNumber,10,"0","L");  
		
		

		/*sprintf(THEAD_v00->TransactionNumber,"%d",dclose_line_counter);
		string_pad(THEAD_v00->TransactionNumber,10-strlen(THEAD_v00->TransactionNumber),"0","L"); */
		/*string_pad(THEAD_v00->TransactionNumber,10,"0","L");  */

	}

	sprintf(THEAD_v00->Cashier,"%d",atoi(v_00.operator_number));		/* Cashier ID - 10 */
	string_pad(THEAD_v00->Cashier,10-strlen(THEAD_v00->Cashier)," ","R");
	string_pad(THEAD_v00->SalesPerson,10," ","R");                /* Sales Person - 10 */
	GetReSATransactionType(v_00.transaction_type,ReSA_Transaction_type); /* Transaction Type -6 */
	strcpy(THEAD_v00->TransactionType,ReSA_Transaction_type);
	if (strlen(THEAD_v00->TransactionType) <6) string_pad(THEAD_v00->TransactionType,6-strlen(THEAD_v00->TransactionType)," ","R");
	GetReSATransactionSubType(v_00.transaction_type,ReSA_Transaction_subtype);
	strcpy(THEAD_v00->SubTransactionType,ReSA_Transaction_subtype); 
	if (strlen(THEAD_v00->SubTransactionType) <6) string_pad(THEAD_v00->SubTransactionType,6-strlen(THEAD_v00->SubTransactionType)," ","R");


	if(!strcmp(v_17[string_counter].string_type,"17"))
	{
		/*printf("Length:%d\t%s\n",strlen(v_17[string_counter].transaction_number),v_17[string_counter].transaction_number);  */
		strcpy(THEAD_v00->OrigTxnNo,v_17[string_counter].transaction_number);
		string_pad(THEAD_v00->OrigTxnNo,10-strlen(THEAD_v00->OrigTxnNo)," ","R");
		/*printf("org orign %d \t  %sSat\n",strlen(THEAD_v00->OrigTxnNo),THEAD_v00->OrigTxnNo);  */ 
		
	}
	else string_pad(THEAD_v00->OrigTxnNo,10,"0","R");   /*Orig_tran_no -10 */

	if(!strcmp(v_17[string_counter].string_type,"17"))
	{
		/*printf("123-v_17[%d]:%s\t%d\n",string_counter,v_17[string_counter].register_number,strlen(v_17[string_counter].register_number)); */
		strncpy(THEAD_v00->OrigRegNo,v_17[string_counter].register_number,4); 
		/*printf("THEAD_v00->OrigRegNo:%s\t%d\n",THEAD_v00->OrigRegNo,strlen(THEAD_v00->OrigRegNo)); */
		string_pad(THEAD_v00->OrigRegNo,5-strlen(v_17[string_counter].register_number)," ","R");
		/*printf("124\n"); */
	}
        else string_pad(THEAD_v00->OrigRegNo,5," ","R");         /*Orig_reg_no -5 */

        string_pad(THEAD_v00->ReasonCode,6," ","R");         /*Reason Code - 6 */

        string_pad(THEAD_v00->VendorNumber,10," ","R");        /* Vendor Number - 10 */
        string_pad(THEAD_v00->VendorInvoiceNumber,30," ","R");        /*Vendor Invoice Number - 30 */
        string_pad(THEAD_v00->PaymentRefNumber,16," ","R");        /* Payment Reference Number - 16 */
        string_pad(THEAD_v00->ProofOfDelivery,30," ","R");        /*Proof of Delivery Number - 30 */


        if(atoi(v_00.transaction_type) == 56 && !(strcmp(v_15_b[string_counter].type_of_15,"BANKDP")) && Dclose_Done=='N')
        {
                if(dclose_line_counter==2) strcpy(THEAD_v00->ReferenceNumber1,"1390");
                else strcpy(THEAD_v00->ReferenceNumber1,"1410");
                string_pad(THEAD_v00->ReferenceNumber1,30-strlen(THEAD_v00->ReferenceNumber1)," ","R");
        }
        else string_pad(THEAD_v00->ReferenceNumber1,30," ","R");        /*Reference Number 1- 30 */

        /*string_pad(THEAD_v00->ReferenceNumber2,30," ","R");        Reference Number 2- 30*/ 

	/*printf("Txn: %s\n",v_00.transaction_number);   */
	/*printf("After Ref1\n");  */
	/*strcpy(THEAD_v00->ReferenceNumber2,v_00.number_of_strings); */
	if(atoi(v_00.transaction_type) == 56 && !(strcmp(v_15_b[string_counter].type_of_15,"BANKDP")) && Dclose_Done=='N')
	{
		string_pad(THEAD_v00->ReferenceNumber2,30," ","R");
	}
	else
	{
		sprintf(THEAD_v00->ReferenceNumber2,"%d",atoi(v_00.number_of_strings));
		strcat(THEAD_v00->ReferenceNumber2,"|");
		strcat(THEAD_v00->ReferenceNumber2,v_00.net_postive_amount);
		strcat(THEAD_v00->ReferenceNumber2,"|");
		strcat(THEAD_v00->ReferenceNumber2,v_00.net_negative_amount);
		strcat(THEAD_v00->ReferenceNumber2,"|");

/****Ver 1.1 - Added on 11-Aug-14 to overcome core dump issue ************/
                if(strlen(v_00.net_postive_amount)+strlen(v_00.net_negative_amount) >= 14)
                {
                  sprintf(THEAD_v00->ReferenceNumber2,"%d|%d|%d|",atoi(v_00.number_of_strings),atoi(v_00.net_postive_amount),atoi(v_00.net_negative_amount));
                }
/***** ver 1.1 - change ended *********/

		char operator_password[5];
		substr(operator_password,v_00.operatotr_password,0,4);
		strcat(THEAD_v00->ReferenceNumber2,operator_password);
		strcat(THEAD_v00->ReferenceNumber2,"|");
		strcat(THEAD_v00->ReferenceNumber2,v_00.indicat0);
		string_pad(THEAD_v00->ReferenceNumber2,30-strlen(THEAD_v00->ReferenceNumber2)," ","R");
	}



	/*printf("After Ref2\n");    */
	if(atoi(v_00.transaction_type) == 56 && !(strcmp(v_15_b[string_counter].type_of_15,"BANKDP"))) 
        {
        	string_pad(THEAD_v00->ReferenceNumber3,30," ","R");        /*Reference Number 3- 30 */
	}
	else if(atoi(v_00.transaction_type) == 53 || atoi(v_00.transaction_type) == 59 || atoi(v_00.transaction_type) == 64 || atoi(v_00.transaction_type) == 91 ||(atoi(v_00.transaction_type) == 56 &&  Dclose_Done=='Y'))
	{
		char tran_type[3];
		substr(tran_type,v_00.transaction_type,0,2);
		strncpy(THEAD_v00->ReferenceNumber3,tran_type,2);
		string_pad(THEAD_v00->ReferenceNumber3,30-strlen(THEAD_v00->ReferenceNumber3)," ","R");
	}
	else
	{
		strcpy(THEAD_v00->ReferenceNumber3,v_00.indicat1);
		strcat(THEAD_v00->ReferenceNumber3,"|");
		strcat(THEAD_v00->ReferenceNumber3,v_00.ringtime);
		strcat(THEAD_v00->ReferenceNumber3,"|");
		strcat(THEAD_v00->ReferenceNumber3,v_00.tendertime);
		strcat(THEAD_v00->ReferenceNumber3,"|");
		strcat(THEAD_v00->ReferenceNumber3,v_00.no_sales_time);
		strcat(THEAD_v00->ReferenceNumber3,"|");
		strcat(THEAD_v00->ReferenceNumber3,v_00.inactive_time);
		THEAD_v00->ReferenceNumber3[strcspn(THEAD_v00->ReferenceNumber3,"\n")]='\0';
		/*char inactive_time[3];
		substr(inactive_time,v_00.inactive_time,0,2); 
		strcat(THEAD_v00->ReferenceNumber3,inactive_time); */
		string_pad(THEAD_v00->ReferenceNumber3,30-strlen(THEAD_v00->ReferenceNumber3)," ","R");
	}
	/*printf("After Ref3\n");   */

        if(atoi(v_00.transaction_type) == 56 && !(strcmp(v_15_b[string_counter].type_of_15,"BANKDP")) && Dclose_Done=='N')
        {
        	string_pad(THEAD_v00->ReferenceNumber4,30," ","R");        /*Reference Number 4- 30 */
	}
	else if(atoi(v_00.transaction_type) == 53 || atoi(v_00.transaction_type) == 59 || atoi(v_00.transaction_type) == 64 || atoi(v_00.transaction_type) == 91 || (atoi(v_00.transaction_type) == 56 && Dclose_Done=='Y'))
	{
		if(atoi(v_00.transaction_type) == 53) strcpy(THEAD_v00->ReferenceNumber4,"Register Total");
		if(atoi(v_00.transaction_type) == 56) strcpy(THEAD_v00->ReferenceNumber4,"Bank Deposit");
		if(atoi(v_00.transaction_type) == 59) strcpy(THEAD_v00->ReferenceNumber4,"User Training Transaction");
		if(atoi(v_00.transaction_type) == 64) strcpy(THEAD_v00->ReferenceNumber4,"Terminal Monitor Transaction");
		if(atoi(v_00.transaction_type) == 91) strcpy(THEAD_v00->ReferenceNumber4,"Reserved For Users");	
		string_pad(THEAD_v00->ReferenceNumber4,30-strlen(THEAD_v00->ReferenceNumber4)," ","R");
			
	}
	else
	{
		strcpy(THEAD_v00->ReferenceNumber4,v_00.net_noncash_total);
		string_pad(THEAD_v00->ReferenceNumber4,30-strlen(THEAD_v00->ReferenceNumber4)," ","R");
	}


	int net_calculate_amt=atoi(v_00.net_postive_amount) - atoi(v_00.net_negative_amount);
/*        if((v_00.net_postive_amount - v_00.net_negative_amount)>=0) strcpy(THEAD_v00->ValueSign,"P"); */
	/*printf("Net Positve: %s\n",v_00.net_postive_amount);*/
	/*printf("Net Negative: %s\n",v_00.net_negative_amount);*/
	/*printf("Net : %d\n",net_calculate_amt);*/
	if (net_calculate_amt>=0) strcpy(THEAD_v00->ValueSign,"P"); 
        else strcpy(THEAD_v00->ValueSign,"N");
	if(atoi(v_00.transaction_type) == 60)
	{
		sprintf(THEAD_v00->Value,"%d",atoi(v_17[string_counter].amount)*100);
		string_pad(THEAD_v00->Value,20-strlen(THEAD_v00->Value),"0","L");
	}
        else if(atoi(v_00.transaction_type) == 56 && !(strcmp(v_15_b[string_counter].type_of_15,"BANKDP")) && Dclose_Done=='N')
        {

                char realpart[15];
                char decimalpart[4];
                strcpy(THEAD_v00->ValueSign,"P");
                if(dclose_line_counter==2)
                {
                        substr(realpart,v_15_b[string_counter].cash_amount,0,strlen(v_15_b[string_counter].cash_amount)-3);
                        substr(decimalpart,v_15_b[string_counter].cash_amount,strlen(v_15_b[string_counter].cash_amount)-2,2);

                }
                else
                {
                        substr(realpart,v_15_b[string_counter].check_amount,0,strlen(v_15_b[string_counter].check_amount)-3);
                        substr(decimalpart,v_15_b[string_counter].check_amount,strlen(v_15_b[string_counter].check_amount)-2,2);

                }
                strcpy(THEAD_v00->Value,realpart);
                strcat(THEAD_v00->Value,decimalpart);
                strcat(THEAD_v00->Value,"00");
                string_pad(THEAD_v00->Value,20-strlen(THEAD_v00->Value),"0","L");
        }
	else
	{
        	string_pad(THEAD_v00->Value,18-strlen(v_00.net_total_amount),"0","R");
        	strcat(THEAD_v00->Value,v_00.net_total_amount);         /* VALUE - Net total Amount 20 16 Real + 4 Decimal */
        	strcat(THEAD_v00->Value,"00");
	}
        strcat(THEAD_v00->BannerId,"0001");                /*Banner Id*/
        string_pad(THEAD_v00->CustomerOrderHead,30," ","R");        /* Customer Order Head ID - 30 */
        string_pad(THEAD_v00->CustomerOrderDate,14," ","R");        /* Customer Order Head Date - 30 */

/* For 13.1 Back proting */

        if(Head_net_positive-Head_net_negative >=0) strcpy(THEAD_v00->RoundedAmountSign,"P");
        else strcpy(THEAD_v00->RoundedAmountSign,"N");

	if(atoi(v_00.transaction_type) == 60)
        {
                sprintf(THEAD_v00->RoundedAmount,"%d",atoi(v_17[string_counter].amount)*100);
                string_pad(THEAD_v00->RoundedAmount,20-strlen(THEAD_v00->RoundedAmount),"0","L");
        }
        else
        {
        	sprintf(THEAD_v00->RoundedAmount,"%d",atoi(v_00.net_total_amount)*100);
        	string_pad(THEAD_v00->RoundedAmount,20-strlen(THEAD_v00->RoundedAmount),"0","L");
	}

        strcpy(THEAD_v00->RoundedOffSign,"P");
        string_pad(THEAD_v00->RoundedOffAmount,20,"0","R");


/* For 13.1 Back proting */



	/*strcpy(THEAD_v00->EndOfString,"\0");*/

	/*strcpy(THEAD_v00->NewLine,"\n");*/
	/* memset(&v_11[string_counter],0,sizeof(v_11[string_counter])); */

	/* THEAD Database Operations - Collect record for insertion */
	{
		char value_str[20], rounded_amt_str[20], rounded_off_str[20];
		char tran_no_str[10], store_str[10];
		char business_date[10];
		int i;
		
		strcpy(value_str, THEAD_v00->Value);
		strcpy(rounded_amt_str, THEAD_v00->RoundedAmount);
		strcpy(rounded_off_str, THEAD_v00->RoundedOffAmount);
		strcpy(tran_no_str, THEAD_v00->TransactionNumber);
		strcpy(store_str, v_1_15.unit_number);
		/* Business date from transaction header (YYYYMMDD format) */
		strcpy(business_date, "20");
		strcat(business_date, v_00.date_of_transaction);
		
		/* Trim trailing spaces from transaction number */
		for(i = strlen(tran_no_str) - 1; i >= 0 && tran_no_str[i] == ' '; i--)
			tran_no_str[i] = '\0';
		
		CollectTHEADRecord(
			store_str,
			business_date,
			THEAD_v00->TransactionDate,
			THEAD_v00->Register,
			tran_no_str,
			THEAD_v00->Cashier,
			THEAD_v00->SalesPerson,
			THEAD_v00->TransactionType,
			THEAD_v00->SubTransactionType,
			THEAD_v00->OrigTxnNo,
			THEAD_v00->OrigRegNo,
			THEAD_v00->ReferenceNumber1,
			THEAD_v00->ReferenceNumber2,
			THEAD_v00->ReferenceNumber3,
			THEAD_v00->ReferenceNumber4,
			value_str,
			THEAD_v00->ValueSign,
			THEAD_v00->BannerId,
			rounded_amt_str,
			rounded_off_str
		);
	}
}
/* Procedure to compose the transaction level details from the string types 06,07,10 */
void StoreInTITEM(int string_counter)
{
	/*printf("inside Store In TITEM\n");   */
	char padding_string[MAXFLDS];
	char v_item_status[1];
	TITEM_v06 = (struct TITEM_06 *)malloc(sizeof(struct TITEM_06));
	current_line_counter++;
	number_pad(padding_string,current_line_counter,10);
	strcpy(TITEM_v06->FileTypeRecord,"TITEM");
	strcpy(TITEM_v06->LineNumber,padding_string);
	GetItemStatus(v_06[string_counter].binindicat0,v_item_status);
	strcpy(TITEM_v06->ItemStatus,v_item_status);		/* Item Status - 6 */

	if(atoi(v_08[string_counter].string_type)==8)
	{
		if(v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1')
			strcpy(TITEM_v06->ItemStatus,"S");
		if(v_08[string_counter].binindicat0[8]=='1') strcpy(TITEM_v06->ItemStatus,"R");
		if(v_08[string_counter].binindicat0[9]=='1') strcpy(TITEM_v06->ItemStatus,"V");
		/*if(v_08[string_counter].binindicat0[8]=='1' && v_08[string_counter].binindicat0[9]=='1') strcpy(TITEM_v06->ItemStatus,"S"); */
		if(v_08[string_counter].binindicat0[8]=='1' && v_08[string_counter].binindicat0[9]=='1') strcpy(TITEM_v06->ItemStatus,"V");
	}
	

	string_pad(TITEM_v06->ItemStatus,5," ","R");

	char item_06[15];
	char temp_item_06[15];
	substr(item_06,v_06[string_counter].item_code,8,14);
	sprintf(temp_item_06,"%d",atoi(item_06));
	if(atoi(v_08[string_counter].string_type)==8)
	{
		if (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1')
		strcpy(TITEM_v06->ItemType,"NMITEM");
	}
	else
	{
		if(strlen(temp_item_06)>2 && strlen(temp_item_06) <=6 )
			strcpy(TITEM_v06->ItemType,"ITEM");
		else 
			strcpy(TITEM_v06->ItemType,"REF");			/* Item Type - 6 */
		
	}

	string_pad(TITEM_v06->ItemType,6-strlen(TITEM_v06->ItemType)," ","R");

	if(strlen(temp_item_06)>2 && strlen(temp_item_06) <=6 )
		strcpy(TITEM_v06->ItemNumberType,"ITEM  ");
	else  
		strcpy(TITEM_v06->ItemNumberType,"UCC14 ");		/* Item Number Type - 6*/

	strcpy(TITEM_v06->FormatId," ");			/* Format Id - 1 */
	/*string_pad(TITEM_v06->Item,25," ","R"); */
/*	strcpy(TITEM_v06->ReferenceItem,v_06[string_counter].item_code);	 Reference Item - 25*/ 
/*	string_pad(TITEM_v06->ReferenceItem,25-strlen(TITEM_v06->ReferenceItem)," ","R");  */
	if(strlen(temp_item_06)>2 && strlen(temp_item_06) <=6 )
	{
		/* UPC NOT FOUND or SKU NOT FOUND for item number >2 and <=6 20-JUN-2013*/
		if (strlen(temp_item_06)>2 && strlen(temp_item_06) < 6) string_pad(temp_item_06,6-strlen(temp_item_06),"0","L");
		string_pad(temp_item_06,1,"10","L");
		strcpy(TITEM_v06->Item,temp_item_06);
		string_pad(TITEM_v06->Item,25-strlen(TITEM_v06->Item)," ","R");
                string_pad(TITEM_v06->ReferenceItem,25," ","R");

		/*strcpy(TITEM_v06->ReferenceItem,temp_item_06); */
	}
	else 
	{
		string_pad(TITEM_v06->Item,25," ","R");
		strcpy(TITEM_v06->ReferenceItem,item_06);
		string_pad(TITEM_v06->ReferenceItem,25-strlen(TITEM_v06->ReferenceItem)," ","R");
	}
	


	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
		string_pad(TITEM_v06->ReferenceItem,25," ","R");
	
	/*strcpy(TITEM_v06->ReferenceItem,"0"); */

	/*string_pad(TITEM_v06->ReferenceItem,25-strlen(TITEM_v06->ReferenceItem)," ","R"); */

	string_pad(TITEM_v06->NonMerchandiseItem,25," ","R");                 /* Non Merchadise Item - 25 */

/* For Handling Non Merchandise fee transactions - 08 string in TLOG - indicat0 in 4,8,80,88,400 */
	
	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
	{
		if(strlen(v_08[string_counter].customer_account_number)<=14)
		{
			strcpy(TITEM_v06->NonMerchandiseItem,v_08[string_counter].customer_account_number);
		}
		else
		{
			char item_08[15];
			substr(item_08,v_08[string_counter].customer_account_number,8,14);
			strcpy(TITEM_v06->NonMerchandiseItem,item_08);
		}
		string_pad(TITEM_v06->NonMerchandiseItem,25-strlen(TITEM_v06->NonMerchandiseItem)," ","R");

	}	
	string_pad(TITEM_v06->Voucher,25," ","R");                 /* Voucher - 25 */

	/*substr(v_06[string_counter].dept_no,v_06[string_counter].dept_no,strlen(v_06[string_counter].dept_no)-2,2);*/
	string_pad(TITEM_v06->Department,2,"0","R");
        strcat(TITEM_v06->Department,v_06[string_counter].dept_no);                  /* Department -4 */




	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
 	strcpy(TITEM_v06->Department,"0000");
	/*printf("Dept: %s-%d\n",TITEM_v06->Department,strlen(TITEM_v06->Department));	*/
        string_pad(TITEM_v06->Class,4,"0","R");                 /* Class - 4 */
        string_pad(TITEM_v06->SubClass,4,"0","R");                 /* sub-Class - 4 */

	if(atoi(v_07[string_counter].quantity) >=0 && !(strcmp(v_item_status,"S"))) strcpy(TITEM_v06->QuantitySign,"P");	 /* Quantity Sign - 1 */
	else strcpy(TITEM_v06->QuantitySign,"N");

	
	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1')) 
		strcpy(TITEM_v06->QuantitySign,"P");

	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
                strcpy(TITEM_v06->QuantitySign,"N");




	/*printf("Txn: %d\t%s\t06[%d]:%c\n",transaction_number,v_item_status,string_counter,v_06[string_counter].binindicat0[6]);     */
	/*printf("Txn: %d\t%s\t06[%d]:%d\n",transaction_number,v_item_status,string_counter,atoi(v_06[string_counter].indicat0));    */
	/* For handling quantity where 07 string is not avaialable and transaction status as Return or Voided - Defaulting quantity as 1 */
	/*if(atoi(v_07[string_counter].string_type)==0 && ((!strcmp(v_item_status,"R")||!strcmp(v_item_status,"V")))) */
	if(v_06[string_counter].binindicat0[6]=='1' || v_06[string_counter].binindicat0[7]=='1' )
	{
		/*printf("Txn: %d\t%s\t06[%d]:%c\n",transaction_number,v_item_status,string_counter,v_06[string_counter].binindicat0[6]);     */
		/* To handle return transaction voided - Quantity Sign should be P */
		if(!strcmp(v_item_status,"V")&&!strcmp(v_06[string_counter].indicat0,"D2")) strncpy(TITEM_v06->QuantitySign,"P",1); 
		if(!strcmp(v_item_status,"V")&&!strcmp(v_06[string_counter].indicat0,"D4")) strncpy(TITEM_v06->QuantitySign,"P",1); 
		if(!strcmp(v_item_status,"V")&& v_06[string_counter].binindicat0[6]=='1') strncpy(TITEM_v06->QuantitySign,"P",1);
		/*strcpy(TITEM_v06->Quantity,"1");
		string_pad(TITEM_v06->Quantity,7,"0","L");
		string_pad(TITEM_v06->Quantity,4,"0","R");*/
		sprintf(TITEM_v06->Quantity,"%d",atoi(v_07[string_counter].quantity)*100);
		string_pad(TITEM_v06->Quantity,12-strlen(TITEM_v06->Quantity),"0","L");	
	}
	else
	{
		/*string_pad(TITEM_v06->Quantity,10-strlen(v_07[string_counter].quantity),"0","R"); */
		/*strcat(TITEM_v06->Quantity,v_07[string_counter].quantity);*/			 /* Quantity - 12 (8+4)  */
		/*strcat(TITEM_v06->Quantity,"00");*/ 
		sprintf(TITEM_v06->Quantity,"%d",atoi(v_07[string_counter].quantity)*100);
		string_pad(TITEM_v06->Quantity,12-strlen(TITEM_v06->Quantity),"0","L");
		if(atoi(v_07[string_counter].string_type)==0)
		{
			strcpy(TITEM_v06->Quantity,"1");
                	string_pad(TITEM_v06->Quantity,7,"0","L");
                	string_pad(TITEM_v06->Quantity,4,"0","R");

		}
	}

	/*printf("Qty:%s\n",v_07[string_counter].quantity);  */

	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
	{
		strcpy(TITEM_v06->Quantity,"1");
		string_pad(TITEM_v06->Quantity,7,"0","L");
		string_pad(TITEM_v06->Quantity,4,"0","R");
	}

	/*printf("TXN: %d\t%s\t:%s\t%s\t%s\t%s\n",transaction_number,v_07[string_counter].string_type,v_07[string_counter].group,v_07[string_counter].quantity,v_07[string_counter].sale_quantity,v_07[string_counter].quantity_over);  */
	strcpy(TITEM_v06->SellingUnit,"EA  ");				/* Selling Unit Measure - 4 */

	
	/*if(atoi(v_07[string_counter].string_type)==0 && ((!strcmp(v_item_status,"R")||!strcmp(v_item_status,"V")))) */

	

	if(v_06[string_counter].binindicat0[6]=='1' || v_06[string_counter].binindicat0[7]=='1' )
	{
		/*string_pad(TITEM_v06->UnitRetail,18-strlen(v_06[string_counter].item_amount),"0","R");
		strcat(TITEM_v06->UnitRetail,v_06[string_counter].item_amount);			   */
	        string_pad(TITEM_v06->UnitRetail,18-strlen(v_07[string_counter].quantity_over),"0","R");
		strcat(TITEM_v06->UnitRetail,v_07[string_counter].quantity_over);	
		strcat(TITEM_v06->UnitRetail,"00");
	}
	else
	{
		/*printf("v07[%d]:%s\t Len:%d\n",string_counter,v_07[string_counter].quantity_over,strlen(v_07[string_counter].quantity_over)); */
		string_pad(TITEM_v06->UnitRetail,18-strlen(v_07[string_counter].quantity_over),"0","R");
		strcat(TITEM_v06->UnitRetail,v_07[string_counter].quantity_over);
		strcat(TITEM_v06->UnitRetail,"00");
        	if(atoi(v_07[string_counter].string_type)==0)
        	{
			strcpy(TITEM_v06->UnitRetail,v_06[string_counter].item_amount);
			string_pad(TITEM_v06->UnitRetail,18-strlen(v_06[string_counter].item_amount),"0","L");
                	strcat(TITEM_v06->UnitRetail,"00");
        	}
	}
	/*printf("Sur-1\n");   */

	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
	{
		sprintf(TITEM_v06->UnitRetail,"%d",atoi(v_08[string_counter].amount)*100);
		string_pad(TITEM_v06->UnitRetail,20-strlen(TITEM_v06->UnitRetail),"0","L");
	}
	/*printf("Sur - 2 \n");   */
	if(atoi(v_09P[string_counter].reason_code) >0) 
	{
		/*printf("Inside: %d\n",string_counter); */
		strcpy(TITEM_v06->OverrideReason,"T");
		string_pad(TITEM_v06->OverrideReason,5," ","R");
		string_pad(TITEM_v06->OriginalUnitRetail,18-strlen(v_09P[string_counter].override_price),"0","R");
		strcat(TITEM_v06->OriginalUnitRetail,v_09P[string_counter].override_price);			  /* orig Unit Retail 20 (16+4) */	
		strcat(TITEM_v06->OriginalUnitRetail,"00");
		/* After Void transaction T is coming for the next Sale transactions also - memset resolved */
		/*memset(&v_09P[string_counter],0,sizeof(v_09P[string_counter])); */
	}
	else
	{
		string_pad(TITEM_v06->OverrideReason,6," ","R");

		string_pad(TITEM_v06->OriginalUnitRetail,18-strlen(v_07[string_counter].quantity_over),"0","R");
		strcat(TITEM_v06->OriginalUnitRetail,v_07[string_counter].quantity_over);

		if(atoi(v_07[string_counter].string_type)==0)
		{
			strcpy(TITEM_v06->OriginalUnitRetail,v_06[string_counter].item_amount);
			string_pad(TITEM_v06->OriginalUnitRetail,18-strlen(v_06[string_counter].item_amount),"0","L");
		}
        	strcat(TITEM_v06->OriginalUnitRetail,"00");

	} 

	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
	{
		string_pad(TITEM_v06->OverrideReason,6," ","R");
		sprintf(TITEM_v06->OriginalUnitRetail,"%d",atoi(v_08[string_counter].amount)*100);
		string_pad(TITEM_v06->OriginalUnitRetail,20-strlen(TITEM_v06->OriginalUnitRetail),"0","L");

	}

	if(!(strncmp(v_06[string_counter].tax_plan,"0",1))) strcpy(TITEM_v06->TaxableIndicator,"N");
	else strcpy(TITEM_v06->TaxableIndicator,"Y"); 
	/*printf("Sur - 3 \n");   */

	if(atoi(v_06[string_counter].string_type)==6 && ((v_06[string_counter].binindicat0[8]=='1') || (v_06[string_counter].bintaxplan[3]=='0' && v_06[string_counter].bintaxplan[2]=='0' && v_06[string_counter].bintaxplan[1]=='0' && v_06[string_counter].bintaxplan[0]=='0') ))
		strcpy(TITEM_v06->TaxableIndicator,"N"); 
	else strcpy(TITEM_v06->TaxableIndicator,"Y"); 
	

	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
		strcpy(TITEM_v06->TaxableIndicator,"N"); 

	string_pad(TITEM_v06->Pump,8," ","L"); 
	/*printf("Taxable Indicator : %s\n",TITEM_v06->TaxableIndicator);*/

	if(atoi(v_06[string_counter].string_type)==6 && ((v_06[string_counter].binindicat0[8]=='1') || (v_06[string_counter].bintaxplan[3]=='0' && v_06[string_counter].bintaxplan[2]=='0' && v_06[string_counter].bintaxplan[1]=='0' && v_06[string_counter].bintaxplan[0]=='0') ))
		strcpy(TITEM_v06->ReferenceNumber5,"NonTax Item");
	else 
	{
		if(atoi(v_08[string_counter+1].string_type)==8 && atoi(v_08[string_counter+1].customer_account_number) ==99)
			strcpy(TITEM_v06->ReferenceNumber5,"TaxExmpted");
		else strcpy(TITEM_v06->ReferenceNumber5,"Taxable"); 
	}



	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
		strcpy(TITEM_v06->ReferenceNumber5,"NonTax Item");

	string_pad(TITEM_v06->ReferenceNumber5,30-strlen(TITEM_v06->ReferenceNumber5)," ","R");	

	
	/*string_pad(TITEM_v06->ReferenceNumber6,30," ","R");*/			 /*Reference Number 6 - 30 */

	if(atoi(v_06[string_counter].dept_no) == 19)
		strcpy(TITEM_v06->ReferenceNumber6,"CGCARD");
	
	if(atoi(v_06[string_counter].dept_no) == 32)
		strcpy(TITEM_v06->ReferenceNumber6,"OGCARD");

	if(atoi(v_06[string_counter].dept_no) == 37)
		strcpy(TITEM_v06->ReferenceNumber6,"Delivery Fee");

	if(atoi(v_08[string_counter].string_type)==8 && atoi(v_08[string_counter].customer_account_number) == 99)
		strcpy(TITEM_v06->ReferenceNumber6,"99 KEY");
	if(atoi(v_08[string_counter+1].string_type)==8 && atoi(v_08[string_counter+1].customer_account_number) ==225)
		strcpy(TITEM_v06->ReferenceNumber6,"PIF/PUF");

	if(!strcmp(v_1_15.unit_state,"CAN"))
	{
		if(v_06[string_counter].binindicat0[8]!='1')
		{
			if(v_06[string_counter].bintaxplan[3]=='1' && v_06[string_counter].bintaxplan[2]=='0' && v_06[string_counter].bintaxplan[1]=='0' && v_06[string_counter].bintaxplan[0] == '0')
			strcpy(TITEM_v06->ReferenceNumber6,"G");
		}

			
	}	

	if(v_06[string_counter].GSTTax == 'G')
		strcpy(TITEM_v06->ReferenceNumber6,"G");


	string_pad(TITEM_v06->ReferenceNumber6,30-strlen(TITEM_v06->ReferenceNumber6)," ","R");
	

	/*string_pad(TITEM_v06->ReferenceNumber7,30," ","R");			 Reference Number 7 - 30 */

	/*printf("After ref6\n");  */
	strcpy(TITEM_v06->ReferenceNumber7,v_07[string_counter].group);
	strcat(TITEM_v06->ReferenceNumber7,"|");
	strcat(TITEM_v06->ReferenceNumber7,v_07[string_counter].quantity);
	strcat(TITEM_v06->ReferenceNumber7,"|");
	strcat(TITEM_v06->ReferenceNumber7,v_07[string_counter].sale_quantity);
	strcat(TITEM_v06->ReferenceNumber7,"|");
	strcat(TITEM_v06->ReferenceNumber7,v_07[string_counter].quantity_over);
	/*strcat(TITEM_v06->ReferenceNumber7,"|");
	strcat(TITEM_v06->ReferenceNumber7,v_07[string_counter].price_over); */
	/*if(atoi(v_08[string_counter].string_type)==8 && (atoi(v_08[string_counter].indicat0)==4 || atoi(v_08[string_counter].indicat0)==8 || atoi(v_08[string_counter].indicat0)==80 || atoi(v_08[string_counter].indicat0)==88 || atoi(v_08[string_counter].indicat0)==880||atoi(v_08[string_counter].indicat0)==400)) 
	{
		switch(atoi(v_08[string_counter].indicat0))
		{
			case 4: strcpy(TITEM_v06->ReferenceNumber7,"Other Fee");
				break;
			case 8:
			case 88: strcpy(TITEM_v06->ReferenceNumber7,"Send Fee");
				break;
			case 80:
			case 880:
			case 400: strcpy(TITEM_v06->ReferenceNumber7,"No Tax");
				break;
			default: strcpy(TITEM_v06->ReferenceNumber7," ");
		}
	}
	else if(atoi(v_08[string_counter].string_type)==8 && (atoi(v_08[string_counter].indicat0)==100 || atoi(v_08[string_counter].indicat0)== 104 || atoi(v_08[string_counter].indicat0)==108||atoi(v_08[string_counter].indicat0)==204 ||atoi(v_08[string_counter].indicat0)==208||atoi(v_08[string_counter].indicat0)==200))
	{
                switch(atoi(v_08[string_counter].indicat0))
                {
                        case 204:
                        case 104: strcpy(TITEM_v06->ReferenceNumber7,"Other Fee Return / Void");
                                break;
                        case 208:
                        case 108: strcpy(TITEM_v06->ReferenceNumber7,"Send Fee Return / Void");
                                break;
                        case 200:
			case 280:
                        case 100: strcpy(TITEM_v06->ReferenceNumber7,"Return / Void");
                                break;
                        default: strcpy(TITEM_v06->ReferenceNumber7," ");
                }


        } */

if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1'))
{
	if(v_08[string_counter].binindicat0[2]=='1') strcpy(TITEM_v06->ReferenceNumber7,"Other Fee");
	else if(v_08[string_counter].binindicat0[3]=='1') strcpy(TITEM_v06->ReferenceNumber7,"Send Fee");
	else if(v_08[string_counter].binindicat0[7]=='1') strcpy(TITEM_v06->ReferenceNumber7,"No Tax");
}
/*if(v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1') 
{
	strcpy(TITEM_v06->ReferenceNumber7,"Fee Return / Void");
} */


	string_pad(TITEM_v06->ReferenceNumber7,30-strlen(TITEM_v06->ReferenceNumber7)," ","R");


	/*string_pad(TITEM_v06->ReferenceNumber8,30," ","R");			 Reference Number 8 - 30 */
	
	strcpy(TITEM_v06->ReferenceNumber8,v_06[string_counter].tax_plan);
	strcat(TITEM_v06->ReferenceNumber8,"|");
	strcat(TITEM_v06->ReferenceNumber8,v_06[string_counter].indicat0);
	strcat(TITEM_v06->ReferenceNumber8,"|");
	char indicat1_06[1];
	sprintf(indicat1_06,"%d",atoi(v_06[string_counter].indicat1));
	strcat(TITEM_v06->ReferenceNumber8,indicat1_06);
	strcat(TITEM_v06->ReferenceNumber8,"|");
	if(atoi(v_09[string_counter].string_type)>0)
	{
		strcat(TITEM_v06->ReferenceNumber8,v_09[string_counter].discount);
		strcat(TITEM_v06->ReferenceNumber8,"|");
		char dis_09[15];
		sprintf(dis_09,"%d",atoi(v_09[string_counter].discount_seq));
		strcat(TITEM_v06->ReferenceNumber8,dis_09);
	}
	TITEM_v06->ReferenceNumber8[strcspn(TITEM_v06->ReferenceNumber8,"\n")]='\0';
	/*printf("After ref8\n");  */

	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
		strcpy(TITEM_v06->ReferenceNumber8,"NMITEM");
	string_pad(TITEM_v06->ReferenceNumber8,30-strlen(TITEM_v06->ReferenceNumber8)," ","R");

	/*if (atoi(v_06[string_counter].indicat0)==1015)*/
	if(v_06[string_counter].binindicat0[2] == '1') strcpy(TITEM_v06->ItemSwipedInd,"N");
	else strcpy(TITEM_v06->ItemSwipedInd,"Y");					/* ItemSwipedInd - Y -need to decode */
	

	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
		strcpy(TITEM_v06->ItemSwipedInd,"N");

	string_pad(TITEM_v06->ReturnReasonCode,6," ","R");			/* Return Reason Code - 6 */
	string_pad(TITEM_v06->SalesPerson,10," ","R");				/* Sales Person - 10 */ 
	string_pad(TITEM_v06->ExpirationDate,8," ","R");			/* Expiration DAte - 8 */
	string_pad(TITEM_v06->DropShipInd,1,"N","R");				/* DropShipInd - 1 */

	/*string_pad(TITEM_v06->UomQty,8-strlen(v_07[string_counter].sale_quantity),"0","R");
	strcat(TITEM_v06->UomQty,v_07[string_counter].sale_quantity);
	strcat(TITEM_v06->UomQty,"0000");						 UomQty - sale quantity - 12(8+4) */

	/*if(atoi(v_07[string_counter].string_type)==0 && ((!strcmp(v_item_status,"R")||!strcmp(v_item_status,"V")))) */
	
	if(v_06[string_counter].binindicat0[6]=='1' || v_06[string_counter].binindicat0[7]=='1' || atoi(v_07[string_counter].string_type)==0)
	{
		/* To handle return transaction voided - Quantity Sign should be P */
		/*strcpy(TITEM_v06->UomQty,"1");
		string_pad(TITEM_v06->UomQty,7,"0","L");
		string_pad(TITEM_v06->UomQty,4,"0","R");*/
                sprintf(TITEM_v06->UomQty,"%d",atoi(v_07[string_counter].quantity)*100);
		string_pad(TITEM_v06->UomQty,12-strlen(TITEM_v06->UomQty),"0","L");		
	}
	else
	{
		/*string_pad(TITEM_v06->UomQty,10-strlen(v_07[string_counter].quantity),"0","R");
		strcat(TITEM_v06->UomQty,v_07[string_counter].quantity);*/			 /* Quantity - 12 (8+4)  */
		/*strcat(TITEM_v06->UomQty,"00");  */
		sprintf(TITEM_v06->UomQty,"%d",atoi(v_07[string_counter].quantity)*100);
		string_pad(TITEM_v06->UomQty,12-strlen(TITEM_v06->UomQty),"0","L");
	}

	if(atoi(v_08[string_counter].string_type)==8 && (v_08[string_counter].binindicat0[2]=='1' || v_08[string_counter].binindicat0[3]=='1' || v_08[string_counter].binindicat0[7]=='1' || v_08[string_counter].binindicat0[8]=='1' || v_08[string_counter].binindicat0[9]=='1'))
	{
		strcpy(TITEM_v06->UomQty,"1");
		string_pad(TITEM_v06->UomQty,7,"0","L");
		string_pad(TITEM_v06->UomQty,4,"0","R");
	}
	strcat(TITEM_v06->CatchWeightInd,"N");					/* CatchWeightInd - 1 */
	string_pad(TITEM_v06->SellingItem,25," ","R");					/* SellingItem - 25 */
	string_pad(TITEM_v06->CustOrderLine,6," ","R");				/* CustOrderLine - 6 */
	string_pad(TITEM_v06->MediaId,10," ","R");				/* MediaId - 10 */ 
	
	/*printf("Written Item\n");  */

}
/* Capturing the Discount level details from string type 10  and 07 */
void StoreInDisc(int string_counter,int disc_lines)
{
	/*printf("inside Store In IDISC\n");  */
        char padding_string[MAXFLDS];
        char v_item_status[1];
        IDISC_v10= (struct IDISC_10 *)malloc(sizeof(struct IDISC_10));
        current_line_counter++;
        number_pad(padding_string,current_line_counter,10);
	
        strncpy(IDISC_v10->FileTypeRecord,"IDISC",5);
        strcpy(IDISC_v10->LineNumber,padding_string);
	if(atoi(v_00.transaction_type) == 2) strcpy(IDISC_v10->RMSPromotionNumber,"1005  ");
	else strcpy(IDISC_v10->RMSPromotionNumber,"1006  ");		/* RMS Promotion Number - 6 */ 			
	substr(IDISC_v10->DiscountNumber,v_10[string_counter][disc_lines].discount_code,0,6); 	/* Discount Reference Number -10 */
	string_pad(IDISC_v10->DiscountNumber,10-strlen(IDISC_v10->DiscountNumber),"0","R");
	strcpy(IDISC_v10->DiscountType,"CSTMER");			/* Discount Type - 6 */
	string_pad(IDISC_v10->CouponNumber,16," ","R");		/* Coupon Number - 16 */	
	string_pad(IDISC_v10->CouponReferenceNumber,16," ","R");		/* Coupon Reference Number - 16 */	

	/*if(atoi(v_07[string_counter].quantity) >=0 && (atoi(v_10[string_counter][disc_lines].indicat0)!= 2) || atoi(v_10[string_counter][disc_lines].indicat0)!=6) strcpy(IDISC_v10->QuantitySign,"P");	  Quantity Sign - 1 
	else strcpy(IDISC_v10->QuantitySign,"N"); */
	
/*	if(!(strncmp(v_10[string_counter][disc_lines].indicat0,"0",1))) strcpy(IDISC_v10->QuantitySign,"P");
	else if(!(strncmp(v_10[string_counter][disc_lines].indicat0,"2",1)) || !(strncmp(v_10[string_counter][disc_lines].indicat0,"1",1)) || !(strncmp(v_10[string_counter][disc_lines].indicat0,"9",1))|| !(strncmp(v_10[string_counter][disc_lines].indicat0,"6",1))) strcpy(IDISC_v10->QuantitySign,"N");
	else strcpy(IDISC_v10->QuantitySign,"P"); */

	/*printf("DiscBin:");  */
	/*for(int o=0;o<16;o++)
		printf("%c\t",v_10[string_counter][disc_lines].binindicat0[o]);
	printf("\n"); */
	if(v_10[string_counter][disc_lines].binindicat0[0] =='1' || v_10[string_counter][disc_lines].binindicat0[1] =='1' )
	{
		/*printf("I am in Void Disc\n"); */
		if(v_10[string_counter][disc_lines].binindicat0[0] =='1' && v_10[string_counter][disc_lines].binindicat0[1] =='1')
			strcpy(IDISC_v10->QuantitySign,"P");
		else
			strcpy(IDISC_v10->QuantitySign,"N");
	}		
	else
		strcpy(IDISC_v10->QuantitySign,"P");


	/*string_pad(IDISC_v10->Quantity,10-strlen(v_07[string_counter].quantity),"0","R");
	strcat(IDISC_v10->Quantity,v_07[string_counter].quantity);			  Quantity - 12 (8+4)  
	strcat(IDISC_v10->Quantity,"00");  */

	/*if(!(strncmp(v_10[string_counter][disc_lines].indicat0,"2",1)) || !(strncmp(v_10[string_counter][disc_lines].indicat0,"1",1)) || !(strncmp(v_10[string_counter][disc_lines].indicat0,"9",1)) || !(strncmp(v_10[string_counter][disc_lines].indicat0,"6",1)))  */


/**** BAGB project discount quantity change - 07 string changed ****/ 
	/*if(v_10[string_counter][disc_lines].binindicat0[0] =='1' || v_10[string_counter][disc_lines].binindicat0[1] =='1' || atoi(v_07[string_counter].string_type)==0)
		strcpy(IDISC_v10->Quantity,"10000");
	else
		sprintf(IDISC_v10->Quantity,"%d",atoi(v_07[string_counter].sale_quantity)*10000); */

	strcpy(IDISC_v10->Quantity,"10000");
/**** BAGB project discount quantity change - 07 string changed ****/ 

	string_pad(IDISC_v10->Quantity,12-strlen(IDISC_v10->Quantity),"0","L");


	sprintf(IDISC_v10->UnitDiscountAmount,"%d",atoi(v_10[string_counter][disc_lines].discount_amount)*100);
	
	IDISC_v10->UnitDiscountAmount[strcspn(IDISC_v10->UnitDiscountAmount,"\n")]='\0';

	string_pad(IDISC_v10->UnitDiscountAmount,20-strlen(IDISC_v10->UnitDiscountAmount),"0","L");
	IDISC_v10->UnitDiscountAmount[strcspn(IDISC_v10->UnitDiscountAmount,"\n")]='\0';

	/*sprintf(IDISC_v10->ReferenceNumber13,"%d",atoi(v_10[string_counter][disc_lines].discount_percent)/10);	 Discount Percent in ReferenceNumber13 - 30 */
	
	char discount_decimal[4];
	char discount_real[4];

	substr(discount_decimal,v_10[string_counter][disc_lines].discount_percent,strlen(v_10[string_counter][disc_lines].discount_percent)-1,1);
	substr(IDISC_v10->ReferenceNumber13,v_10[string_counter][disc_lines].discount_percent,0,strlen(v_10[string_counter][disc_lines].discount_percent)-1);
	strcat(IDISC_v10->ReferenceNumber13,".");
	strcat(IDISC_v10->ReferenceNumber13,discount_decimal);

	string_pad(IDISC_v10->ReferenceNumber13,30-strlen(IDISC_v10->ReferenceNumber13)," ","R");
		
	string_pad(IDISC_v10->ReferenceNumber14,30," ","R");			/* ReferenceNumber14 - 30 */

	/*string_pad(IDISC_v10->ReferenceNumber15,30," ","R");			 ReferenceNumber15 - 30 */

	strcpy(IDISC_v10->ReferenceNumber15,v_10[string_counter][disc_lines].discount_code);
	strcat(IDISC_v10->ReferenceNumber15,"|");
	int indicat0_10;
	indicat0_10=atoi(v_10[string_counter][disc_lines].indicat0);
	char ind0_10[10];
	sprintf(ind0_10,"%d",indicat0_10);
	/*strcat(IDISC_v10->ReferenceNumber15,v_10[string_counter].indicat0);*/
	/*sprintf(IDISC_v10->ReferenceNumber15,"%d",indicat0_10);*/
	strcat(IDISC_v10->ReferenceNumber15,ind0_10);

	
	string_pad(IDISC_v10->ReferenceNumber15,30-strlen(IDISC_v10->ReferenceNumber15)," ","R");

	
	
	string_pad(IDISC_v10->ReferenceNumber16,30," ","R");			/* ReferenceNumber16 - 30 */

	if(v_10[string_counter][disc_lines].binindicat0[0] =='1' || v_10[string_counter][disc_lines].binindicat0[1] =='1' || atoi(v_07[string_counter].string_type)==0)
		strcpy(IDISC_v10->UomQuantity,"10000");
	else
		sprintf(IDISC_v10->UomQuantity,"%d",atoi(v_07[string_counter].sale_quantity)*10000);

        string_pad(IDISC_v10->UomQuantity,12-strlen(IDISC_v10->UomQuantity),"0","L");


	strcpy(IDISC_v10->CatchWeightInd,"N");				/* CatchWeightInd - 1 */

	string_pad(IDISC_v10->PromoComponent,10," ","R");			/* PromoComponent - 10 */
		

}
void StoreInTDisc(int string_counter,int disc_lines)
{
	/*printf("inside Store In TDISC\n");   */
        char padding_string[MAXFLDS];
        char v_item_status[1];
        TDISC_v10_8= (struct IDISC_10 *)malloc(sizeof(struct IDISC_10));
        current_line_counter++;
        number_pad(padding_string,current_line_counter,10);
	/*printf("inside Store In TDISC-1\n");  */
	
        strncpy(TDISC_v10_8->FileTypeRecord,"IDISC",5);
        strcpy(TDISC_v10_8->LineNumber,padding_string);
	if(atoi(v_00.transaction_type) == 2) strcpy(TDISC_v10_8->RMSPromotionNumber,"1005  ");
	else strcpy(TDISC_v10_8->RMSPromotionNumber,"1006  ");		/* RMS Promotion Number - 6 */ 			

	/*printf("XXXX\n"); */
	if(atoi(v_10_8[string_counter][0].string_type)==10 ) substr(TDISC_v10_8->DiscountNumber,v_10_8[string_counter][0].discount_code,0,6);
	string_pad(TDISC_v10_8->DiscountNumber,10-strlen(TDISC_v10_8->DiscountNumber),"0","R");
	strcpy(TDISC_v10_8->DiscountType,"CSTMER");			/* Discount Type - 6 */
	string_pad(TDISC_v10_8->CouponNumber,16," ","R");		/* Coupon Number - 16 */	
	string_pad(TDISC_v10_8->CouponReferenceNumber,16," ","R");		/* Coupon Reference Number - 16 */	

	/*printf("TDISC - 1\n");   */

/* 24-JUL-2013  In Order to handle the RETURN of transactional level discount*/
	if(atoi(v_10_8[string_counter][0].string_type)==10 && (v_10_8[string_counter][0].binindicat0[0]=='1' || v_10_8[string_counter][0].binindicat0[1]=='1')) 
	{
		if(v_10_8[string_counter][0].binindicat0[0]=='1' && v_10_8[string_counter][0].binindicat0[1]=='1')
			strcpy(TDISC_v10_8->QuantitySign,"P");
		else
			strcpy(TDISC_v10_8->QuantitySign,"N");
	}
	else
		strcpy(TDISC_v10_8->QuantitySign,"P");

/* 24-JUL-2013 */
	strcpy(TDISC_v10_8->Quantity,"10000");

	string_pad(TDISC_v10_8->Quantity,12-strlen(TDISC_v10_8->Quantity),"0","L");
	/*printf("TDISC - 2\n");  */


	v_10_8[string_counter][0].discount_amount[strcspn(v_10_8[string_counter][0].discount_amount,"\n")]='\0';
	sprintf(TDISC_v10_8->UnitDiscountAmount,"%d",atoi(v_10_8[string_counter][0].discount_amount)*100);

	TDISC_v10_8->UnitDiscountAmount[strcspn(TDISC_v10_8->UnitDiscountAmount,"\n")]='\0';
	string_pad(TDISC_v10_8->UnitDiscountAmount,20-strlen(TDISC_v10_8->UnitDiscountAmount),"0","L");
	TDISC_v10_8->UnitDiscountAmount[strcspn(TDISC_v10_8->UnitDiscountAmount,"\n")]='\0'; 

	/* if(atoi(v_10_8[string_counter][0].string_type)==10 ) sprintf(TDISC_v10_8->ReferenceNumber13,"%d",atoi(v_10_8[string_counter][0].discount_percent)/10);  */
	char discount_decimal[4];
	char discount_real[4];

	substr(discount_decimal,v_10_8[string_counter][0].discount_percent,strlen(v_10_8[string_counter][0].discount_percent)-1,1);
	substr(TDISC_v10_8->ReferenceNumber13,v_10_8[string_counter][0].discount_percent,0,strlen(v_10_8[string_counter][0].discount_percent)-1);
	strcat(TDISC_v10_8->ReferenceNumber13,".");
	strcat(TDISC_v10_8->ReferenceNumber13,discount_decimal); 


	string_pad(TDISC_v10_8->ReferenceNumber13,30-strlen(TDISC_v10_8->ReferenceNumber13)," ","R"); 

		
	string_pad(TDISC_v10_8->ReferenceNumber14,30," ","R");			/* ReferenceNumber14 - 30 */

	/*printf("TDISC - 3\n");    */

	if(atoi(v_10_8[string_counter][0].string_type)==10 ) strcpy(TDISC_v10_8->ReferenceNumber15,"TDISC");
	
	string_pad(TDISC_v10_8->ReferenceNumber15,30-strlen(TDISC_v10_8->ReferenceNumber15)," ","R");

	
	string_pad(TDISC_v10_8->ReferenceNumber16,30," ","R");			/* ReferenceNumber16 - 30 */


	if(atoi(v_10_8[string_counter][0].string_type)==10 ) strcpy(TDISC_v10_8->UomQuantity,"10000");
        string_pad(TDISC_v10_8->UomQuantity,12-strlen(TDISC_v10_8->UomQuantity),"0","L");



	strcpy(TDISC_v10_8->CatchWeightInd,"N");				/* CatchWeightInd - 1 */

	string_pad(TDISC_v10_8->PromoComponent,10," ","R");			/* PromoComponent - 10 */
		

}
/* Procedure to compose the TAX level details using string type 14 */
void StoreInTTax(int string_counter)
{
	char padding_string[MAXFLDS];
	char v_item_status[1];
	char tax_bucket[1];
	int d_bucket_tax=0;
	current_line_counter++;
	char v_indicat0[3];
	TAX_v14 = (struct TAX_14 *)malloc(sizeof(struct TAX_14));
	number_pad(padding_string,current_line_counter,10);
	strcpy(TAX_v14->FileTypeRecord,"TTAX");			/* File Type Record - 5 */
	string_pad(TAX_v14->FileTypeRecord,5-strlen(TAX_v14->FileTypeRecord)," ","R");
	strcpy(TAX_v14->LineNumber,padding_string);		/* Running Sequence Number - 10 */

	/*printf("Inside Tax\n");  */
/*Version 2.0 - Changes started for the change : Tax code "RDTX4" for Manual tax */
	if((atoi(v_14[string_counter].tax_a)>0 || atoi(v_14[string_counter].tax_b)>0 || atoi(v_14[string_counter].tax_c)>0 || atoi(v_14[string_counter].tax_d)>0) && (atoi(v_08_tax[string_counter].string_type)==8 && manual_written=='N' && v_08_tax[string_counter].binindicat0[5]=='1'))
	{
	manual_tax_bucket='Y';
	}
	if (manual_tax_bucket=='Y') strcpy(TAX_v14->TaxCode,"RDTX4");
	else
/*Version 2.0 - Changes ended for the change : Tax code "RDTX4" for Manual tax */
	if(atoi(v_14[string_counter].tax_a) > 0 && a_flag=='Y') strcpy(TAX_v14->TaxCode,"RGTX");	/* TAX Code - 6 */
	else if(atoi(v_14[string_counter].tax_b)>0 && b_flag=='Y') strcpy(TAX_v14->TaxCode,"RDTX1");
	else if(atoi(v_14[string_counter].tax_c)>0 && c_flag=='Y') strcpy(TAX_v14->TaxCode,"RDTX2");
	else if(atoi(v_14[string_counter].tax_d)>0 && d_flag=='Y') strcpy(TAX_v14->TaxCode,"RDTX3");
	else if(atoi(v_14[string_counter].tax_a)==0 && atoi(v_14[string_counter].tax_b)==0 && atoi(v_14[string_counter].tax_c)==0 && atoi(v_14[string_counter].tax_d)==0 && transaction_taxexmpt=='Y') strcpy(TAX_v14->TaxCode,"TXEXM");
	else strcpy(TAX_v14->TaxCode,"RGTX");
	char temp_tend_bin[30];
/*for(int i=0;i<twelve_counter;i++)
{
	substr(temp_tend_bin, v_12[i].customer_account,0,6);
	if ((atoi(v_12[i].tender_type)==10 || atoi(v_12[i].tender_type)==11 || atoi(v_12[i].tender_type)==12 || atoi(v_12[i].tender_type)==13 || atoi(v_12[i].tender_type)==20 || atoi(v_12[i].tender_type)==26) && (atoi(temp_tend_bin)==539186 || atoi(temp_tend_bin)==546683 || atoi(temp_tend_bin)==555370 || atoi(temp_tend_bin)==551917))  */
		/*Date:29-SEP-22 : Added new tendertype 'PLCC' */
/*	strcpy(TAX_v14->TaxCode,"MPFTX");
} */
	string_pad(TAX_v14->TaxCode,6-strlen(TAX_v14->TaxCode)," ","R");

/*	if(atoi(v_14[string_counter].indicat0) ==0 ) strcpy(TAX_v14->TaxSign,"P");	  TAX Sign - 1 
	else strcpy(TAX_v14->TaxSign,"N"); */

/*	if(!(strncmp(v_14[string_counter].indicat0,"0",1))) strcpy(TAX_v14->TaxSign,"P"); 
	else strcpy(TAX_v14->TaxSign,"N"); */

	if(a_flag=='Y')
	{
		if(v_14[string_counter].binindicat0[3]=='1') strcpy(TAX_v14->TaxSign,"N");
		else strcpy(TAX_v14->TaxSign,"P");
	}
	else if (b_flag=='Y')
	{
		if(v_14[string_counter].binindicat0[2]=='1') strcpy(TAX_v14->TaxSign,"N");
		else strcpy(TAX_v14->TaxSign,"P");
	}
	else if(c_flag=='Y')
	{
		if(v_14[string_counter].binindicat0[1]=='1' ) strcpy(TAX_v14->TaxSign,"N");
		else strcpy(TAX_v14->TaxSign,"P");
	}
	else if(d_flag=='Y')
	{

		if(v_14[string_counter].binindicat0[0]=='1' ) strcpy(TAX_v14->TaxSign,"N");
		else strcpy(TAX_v14->TaxSign,"P");
	}
	else strcpy(TAX_v14->TaxSign,"P");
	

	/*printf("Txn %d\t%s\n",transaction_number,v_14[string_counter].indicat0);	  */
	if(atoi(v_14[string_counter].tax_a)>0 && a_flag=='Y')				/* TAX amount - 20 (16+4) */ 
	{
		/*printf(" String Suri %d\n",strlen(v_14[string_counter].tax_a));*/
		if (strlen(v_14[string_counter].tax_a)>2) string_pad(TAX_v14->TaxAmount,18-strlen(v_14[string_counter].tax_a),"0","R");
		else string_pad(TAX_v14->TaxAmount,16,"0","R");
		strcat(TAX_v14->TaxAmount,v_14[string_counter].tax_a);
		strcat(TAX_v14->TaxAmount,"00");
		strcpy(tax_bucket,"A");
		a_flag='N';
	}
	else if(atoi(v_14[string_counter].tax_b)>0 && b_flag == 'Y') 
	{
		if (strlen(v_14[string_counter].tax_b)>2) string_pad(TAX_v14->TaxAmount,18-strlen(v_14[string_counter].tax_b),"0","R");
                else string_pad(TAX_v14->TaxAmount,16,"0","R");
                strcat(TAX_v14->TaxAmount,v_14[string_counter].tax_b);
		strcat(TAX_v14->TaxAmount,"00");
		strcpy(tax_bucket,"B");
		b_flag='N';
	}
	else if(atoi(v_14[string_counter].tax_c)>0 && c_flag == 'Y') 
	{
		if (strlen(v_14[string_counter].tax_c)>2) string_pad(TAX_v14->TaxAmount,18-strlen(v_14[string_counter].tax_c),"0","R");
                else string_pad(TAX_v14->TaxAmount,16,"0","R");
		strcat(TAX_v14->TaxAmount,v_14[string_counter].tax_c); 
		strcat(TAX_v14->TaxAmount,"00");
		strcpy(tax_bucket,"C");
		c_flag = 'N';
	}
	else if(atoi(v_14[string_counter].tax_d)>0 && d_flag == 'Y') 
	{
		/*printf("Txn: %d\t%d\n",transaction_number,atoi(v_14[string_counter].tax_d));*/
		if(atoi(v_08_tax[string_counter].string_type)==8 && manual_written=='N' && v_08_tax[string_counter].binindicat0[5]=='1')
		{
			if (total_08_tax >=0) strcpy(TAX_v14->TaxSign,"P");
			else strcpy(TAX_v14->TaxSign,"N");
			sprintf(TAX_v14->TaxAmount,"%d",abs(total_08_tax));
			strcat(TAX_v14->TaxAmount,"00");
			string_pad(TAX_v14->TaxAmount,20-strlen(TAX_v14->TaxAmount),"0","L");
			strcpy(tax_bucket,"M");
			manual_written='Y';
		}
		else
		{
			if (v_14[string_counter].binindicat0[0] == '1' && total_08_tax<0 )
			{
				d_bucket_tax=total_08_tax + atoi(v_14[string_counter].tax_d);
				strcpy(TAX_v14->TaxSign,"P");

			}
			else
			{
				d_bucket_tax=atoi(v_14[string_counter].tax_d) - total_08_tax;
			}
			

			sprintf(TAX_v14->TaxAmount,"%d",abs(d_bucket_tax));
			strcat(TAX_v14->TaxAmount,"00");
			string_pad(TAX_v14->TaxAmount,20-strlen(TAX_v14->TaxAmount),"0","L");
			strcpy(tax_bucket,"D");
			d_flag='N';
		}
		
	}
	else  
	{
		string_pad(TAX_v14->TaxAmount,20,"0","R");
		strcpy(tax_bucket," ");
	}

	
	strcpy(TAX_v14->ReferenceNumber17,tax_bucket);
	string_pad(TAX_v14->ReferenceNumber17,30," ","R");	/* ReferenceNumber 17 - 30 */

	
	string_pad(TAX_v14->ReferenceNumber18,30," ","R");	/* ReferenceNumber 18 - 30 */


	/*string_pad(TAX_v14->ReferenceNumber19,30," ","R");	 ReferenceNumber 19 - 30 */

	strcpy(TAX_v14->ReferenceNumber19,v_14[string_counter].tax_a);	
	strcat(TAX_v14->ReferenceNumber19,"|");
	strcat(TAX_v14->ReferenceNumber19,v_14[string_counter].tax_b);
	strcat(TAX_v14->ReferenceNumber19,"|");
	strcat(TAX_v14->ReferenceNumber19,v_14[string_counter].tax_c);
	strcat(TAX_v14->ReferenceNumber19,"|");
	strcat(TAX_v14->ReferenceNumber19,v_14[string_counter].tax_d);
	/*strcat(TAX_v14->ReferenceNumber19,"|");
	strcat(TAX_v14->ReferenceNumber19,v_14[string_counter].indicat0); */

	string_pad(TAX_v14->ReferenceNumber19,30-strlen(TAX_v14->ReferenceNumber19)," ","R");
	int indicat14=0;
	indicat14=atoi(v_14[string_counter].indicat0);

	sprintf(TAX_v14->ReferenceNumber20,"%d",indicat14);
	string_pad(TAX_v14->ReferenceNumber20,30-strlen(TAX_v14->ReferenceNumber20)," ","R");	/* ReferenceNumber 20 - 30 */
	
	/*strcpy(TAX_v14->EndOfString,"\0");	*/
/*	strcpy(TAX_v14->NewLine,"\n");*/ 
}

void StoreInTender(int string_counter)
{
	/* Added for populating ref_no12 30-Jan-19 changes - begins */
	char l_coupon_number[30];
	strcpy(l_coupon_number, "");
	/* Added for populating ref_no12 30-Jan-19 changes - ends */
	char padding_string[MAXFLDS];
        char v_item_status[1];
        current_line_counter++;
	char return_amt[20];
        TENDER_v12 = (struct TENDER_12 *)malloc(sizeof(struct TENDER_12));
        number_pad(padding_string,current_line_counter,10);
        strcpy(TENDER_v12->FileTypeRecord,"TTEND");                 /* File Type Record - 5 */
        string_pad(TENDER_v12->FileTypeRecord,5-strlen(TENDER_v12->FileTypeRecord)," ","R"); 
        strcpy(TENDER_v12->LineNumber,padding_string);             /* Running Sequence Number - 10 */
	/*printf("Txn:%s\t%s\n",v_00.transaction_number,TENDER_v12->FileTypeRecord); */
	
	/*printf("InSide Tender\n");  */
	if(atoi(v_11[string_counter].string_type)==11 ) 
	{	
		GetTenderTypeGroup(TENDER_v12->TenderTypeGroup,"15");
		string_pad(TENDER_v12->TenderTypeGroup,6-strlen(TENDER_v12->TenderTypeGroup)," ","R");
		GetTenderTypeId(TENDER_v12->TenderTypeId,"15",string_counter);
		/*printf("Txn:%s\t%s\t%s\n",v_00.transaction_number,TENDER_v12->FileTypeRecord,TENDER_v12->TenderTypeId); */
		string_pad(TENDER_v12->TenderTypeId,6-strlen(TENDER_v12->TenderTypeId)," ","R");
	}
	else if(!strcmp(v_04.string_type,"04"))
	{
		GetTenderTypeGroup(TENDER_v12->TenderTypeGroup,"15");
                string_pad(TENDER_v12->TenderTypeGroup,6-strlen(TENDER_v12->TenderTypeGroup)," ","R");
                GetTenderTypeId(TENDER_v12->TenderTypeId,"15",0);
                string_pad(TENDER_v12->TenderTypeId,6-strlen(TENDER_v12->TenderTypeId)," ","R");
	}
	else
	{
		/*printf("Txn:%s\tV_12:%s\n",v_00.transaction_number,v_12[string_counter].tender_type); */
		GetTenderTypeGroup(TENDER_v12->TenderTypeGroup,v_12[string_counter].tender_type);	/* Getting TenderTypeGroup - 6 */
		string_pad(TENDER_v12->TenderTypeGroup,6-strlen(TENDER_v12->TenderTypeGroup)," ","R"); 
		GetTenderTypeId(TENDER_v12->TenderTypeId,v_12[string_counter].tender_type,string_counter);			/* Getting TenderTypeId - 6 */
		string_pad(TENDER_v12->TenderTypeId,6-strlen(TENDER_v12->TenderTypeId)," ","R"); 
	}
	
	/*printf("Tender - 1\n"); */

/*	if(atoi(v_12[string_counter].indicat0)==400) strcpy(TENDER_v12->TenderSign,"N");*/		 /*Tender Sign - 1  */

	if(v_12[string_counter].binindicat0[10]=='1') strcpy(TENDER_v12->TenderSign,"N");
	else {strcpy(TENDER_v12->TenderSign,"P"); }

/*	string_pad(TENDER_v12->TenderAmount,18-strlen(v_12[string_counter].tender_amount),"0","R");	 Tender Amount 20 (16+4) 
	strcat(TENDER_v12->TenderAmount,v_12[string_counter].tender_amount);
	strcat(TENDER_v12->TenderAmount,"00");*/

	/*printf("Txn:%s\tString:%s\tIndicat:%s\n",v_00.transaction_number,v_12[string_counter].tender_type,v_12[string_counter].indicat0);  */
	
	if(atoi(v_11[string_counter].string_type)==11 )
	{
		strcpy(TENDER_v12->TenderSign,"P");
		/*printf("In 11 - %s \n",v_11[string_counter].tender); */
		/*sprintf(TENDER_v12->TenderAmount,"%ld",atoi(v_11[string_counter].tender)*100); */
		strcpy(TENDER_v12->TenderAmount,v_11[string_counter].tender);
		TENDER_v12->TenderAmount[strcspn ( TENDER_v12->TenderAmount,"\n")]='\0';
		strcat(TENDER_v12->TenderAmount,"00");	
		/*printf("TenderOut:%s\n",TENDER_v12->TenderAmount); */
		string_pad(TENDER_v12->TenderAmount,20-strlen(TENDER_v12->TenderAmount),"0","L");
		/*printf("Tt:%s\n",TENDER_v12->TenderAmount); */
		cash_flag='N';
	}
	else if(!strcmp(v_04.string_type,"04"))
	{
                strcpy(TENDER_v12->TenderSign,"P");
                sprintf(TENDER_v12->TenderAmount,"%d",atoi(v_04.tender_amount)*100);
                string_pad(TENDER_v12->TenderAmount,20-strlen(TENDER_v12->TenderAmount),"0","L");

	}
	else if(atoi(v_12[string_counter].tender_type)==2 || atoi(v_12[string_counter].tender_type)==14 || atoi(v_12[string_counter].tender_type)==15)
	{
		/*if(Head_net_positive-Head_net_negative<0 || atoi(v_12[string_counter].indicat0)==400)*/
		if(v_12[string_counter].binindicat0[10]=='1')  strncpy(TENDER_v12->TenderSign,"N",1);
                else strncpy(TENDER_v12->TenderSign,"P",1);
                /*sprintf(TENDER_v12->TenderAmount,"%d",atoi(v_12[string_counter].tender_amount)*100);
		printf("TenderOut:%s\n",TENDER_v12->TenderAmount); */
		strcpy(TENDER_v12->TenderAmount,v_12[string_counter].tender_amount);
		TENDER_v12->TenderAmount[strcspn ( TENDER_v12->TenderAmount,"\n")]='\0';
		strcat(TENDER_v12->TenderAmount,"00");
                string_pad(TENDER_v12->TenderAmount,20-strlen(TENDER_v12->TenderAmount),"0","L");
                strcat(TENDER_v12->TenderAmount,"\0");
	}
	else
	{
                /* Commented 0n 30-SEP-2013 in order to handle long interger (big values) 
		sprintf(TENDER_v12->TenderAmount,"%d",atoi(v_12[string_counter].tender_amount)*100);
                string_pad(TENDER_v12->TenderAmount,20-strlen(TENDER_v12->TenderAmount),"0","L"); */

		/* Added on 30-SEP-2013 --> In order to handle big values */
		strcpy(TENDER_v12->TenderAmount,v_12[string_counter].tender_amount);
                TENDER_v12->TenderAmount[strcspn ( TENDER_v12->TenderAmount,"\n")]='\0';
                strcat(TENDER_v12->TenderAmount,"00");
                string_pad(TENDER_v12->TenderAmount,20-strlen(TENDER_v12->TenderAmount),"0","L");
                strcat(TENDER_v12->TenderAmount,"\0");


	} 


	/*printf("Before Cc Number\n");   */

/*	printf("Txn:%s\tNetPos:%d\tNetNeg:%d\tSign:%s\n",v_00.transaction_number,atoi(v_00.net_postive_amount),atoi(v_00.net_negative_amount),TENDER_v12->TenderSign);*/

	if (atoi(v_12[string_counter].tender_type)==10 || atoi(v_12[string_counter].tender_type)==11 || atoi(v_12[string_counter].tender_type)==12 || atoi(v_12[string_counter].tender_type)==13 || atoi(v_12[string_counter].tender_type)==20 || atoi(v_12[string_counter].tender_type)==26)  /* Date:29-SEP-22 : Added new tendertype 'PLCC' */
	{
		if(atoi(v_12[string_counter].indicat0)==400) strncpy(TENDER_v12->TenderSign,"N",1);
                else strncpy(TENDER_v12->TenderSign,"P",1);
		strcpy(TENDER_v12->CcNo,v_12[string_counter].customer_account);
		string_pad(TENDER_v12->CcNo,40-strlen(TENDER_v12->CcNo)," ","R"); 
		strcpy(TENDER_v12->CcAuthNo,"0000");
		string_pad(TENDER_v12->CcAuthNo,12," ","R");
		strcpy(TENDER_v12->CcAuthorizationSource,"E");
		string_pad(TENDER_v12->CcAuthorizationSource,5," ","R");
		strcpy(TENDER_v12->CcCardHolderVerification,"C");
		string_pad(TENDER_v12->CcCardHolderVerification,5," ","R");
		strcpy(TENDER_v12->CcExpirationDate,"20161231");
		strcpy(TENDER_v12->CcEntryMode,"T");
		string_pad(TENDER_v12->CcEntryMode,5," ","R");
		strcpy(TENDER_v12->CcTerminalId,"1");
		string_pad(TENDER_v12->CcTerminalId,4," ","R");
		strcpy(TENDER_v12->CcSpecialCondition,"E");
		string_pad(TENDER_v12->CcSpecialCondition,5," ","R");
		string_pad(TENDER_v12->VoucherNumber,25," ","R");
	}
	else
	{
		string_pad(TENDER_v12->CcNo,40," ","R");				/* CC Number - 40 */
		string_pad(TENDER_v12->CcAuthNo,16," ","R");				/* CC Auth Number - 16 */
		string_pad(TENDER_v12->CcAuthorizationSource,6," ","R");		/* Authorization Source - 6 */
		string_pad(TENDER_v12->CcCardHolderVerification,6," ","R");		/* CardHolderVerification - 6 */
		string_pad(TENDER_v12->CcExpirationDate,8," ","R");			/* Card Expiry Date - 8 */
		string_pad(TENDER_v12->CcEntryMode,6," ","R");				/* Card Entry Mode - 6 */
		string_pad(TENDER_v12->CcTerminalId,5," ","R");				/* Terminal ID - 5 */
		string_pad(TENDER_v12->CcSpecialCondition,6," ","R");			/* Card Special Condition - 6 */
		string_pad(TENDER_v12->VoucherNumber,25," ","R");			/* VoucherNumber - 25 */

	}

	/*printf("After CC \n");   */
	if (atoi(v_12[string_counter].tender_type)==1 || atoi(v_12[string_counter].tender_type)==3 ||atoi(v_12[string_counter].tender_type)==4 || atoi(v_12[string_counter].tender_type)==18 || atoi(v_12[string_counter].tender_type)==19 || atoi(v_12[string_counter].tender_type)==21 || atoi(v_12[string_counter].tender_type)==22 || atoi(v_12[string_counter].tender_type)==23 || atoi(v_12[string_counter].tender_type)==25)  /* Date:15-Jan-19 : Added new tendertype 'PROMO CARD' */
	{
                /* Added for populating ref_no12 30-Jan-19 changes - begins */
                strcpy(l_coupon_number, v_12[string_counter].customer_account);
                /* Added for populating ref_no12 30-Jan-19 changes - ends */
                
                if (strlen(v_12[string_counter].customer_account) >6)
                        substr(TENDER_v12->CouponNumber,v_12[string_counter].customer_account,0,16);
                else
                        {
						strcpy(TENDER_v12->CouponNumber,"0");
						strcpy(l_coupon_number, "00000000000000000000");			/* Added for populating 20 '0' in ref_no12 having NULL in ASCII 30-Jan-19 */
						}
                string_pad(TENDER_v12->CouponNumber,16-strlen(TENDER_v12->CouponNumber)," ","L");			
        }
	else string_pad(TENDER_v12->CouponNumber,16," ","R");				/* Coupon Number */
	
	strcpy(TENDER_v12->CouponReferenceNumber,"1111");				/* Coupon Reference Number */
	string_pad(TENDER_v12->CouponReferenceNumber,16-strlen(TENDER_v12->CouponReferenceNumber)," ","R");


	string_pad(TENDER_v12->ReferenceNumber9,30," ","R");				/* ReferenceNumber9 - 30 */
	string_pad(TENDER_v12->ReferenceNumber10,30," ","R");				/* ReferenceNumber10 - 30 */
	/*string_pad(TENDER_v12->ReferenceNumber11,30," ","R");				 ReferenceNumber11 - 30 */
    
	strcpy(TENDER_v12->ReferenceNumber11,v_12[string_counter].indicat0);
	string_pad(TENDER_v12->ReferenceNumber11,30-strlen(TENDER_v12->ReferenceNumber11)," ","R");
	
	/* commented for 30-Jan-19 changes - begins */
	/* string_pad(TENDER_v12->ReferenceNumber12,30," ","R");			--ReferenceNumber12 - 30 */ 
	/* commented for 30-Jan-19 changes - ends */
	
	/* Added for populating ref_no12 30-Jan-19 changes - begins */
	strcpy(TENDER_v12->ReferenceNumber12, l_coupon_number);
	string_pad(TENDER_v12->ReferenceNumber12, 30 - strlen(l_coupon_number), " ", "R");  /* ReferenceNumber12 - 30 */ 
	/* Added for populating ref_no12 30-Jan-19 changes - ends */
	
/*	strcpy(TENDER_v12->EndOfString,"\0");*/
/*	strcpy(TENDER_v12->NewLine,"\n"); */
	/*printf("End - Tender \n");   */

}

/* TAIL Record for THEAD record */

void StoreInTtail(int string_counter)
{
	char padding_string[MAXFLDS];
	free(TTAIL_v00);
        char v_item_status[1];
        TTAIL_v00= (struct TTAIL_00 *)malloc(sizeof(struct TTAIL_00));
	
	/*printf("Txn Type:%s\tDclose:%c\n",v_00.transaction_type,Dclose_Done); */
	if(start_dclose=='Y')
	{
		dclose_line_counter++;
                number_pad(padding_string,dclose_line_counter,10);
	}
        else
        {
                current_line_counter++;
		ttail_no=current_line_counter;
                number_pad(padding_string,current_line_counter,10);
        }

        strcpy(TTAIL_v00->FileTypeRecord,"TTAIL");                 /* File Type Record - 5 */
        string_pad(TTAIL_v00->FileTypeRecord,5-strlen(TTAIL_v00->FileTypeRecord)," ","R");
        strcpy(TTAIL_v00->LineNumber,padding_string);             /* Running Sequence Number - 10 */

	if(start_dclose=='Y')
		transaction_item_count=0;
	else
		transaction_item_count=ttail_no-thead_no-1;
	total_lines_in_file+=transaction_item_count;
	padding_string[0]='\0';
	number_pad(padding_string,transaction_item_count,10);
	strcpy(TTAIL_v00->TransactionRecordCount,padding_string);
	
/*	strcpy(TTAIL_v00->EndOfString,"\0");*/
/*	strcpy(TTAIL_v00->NewLine,"\n");*/
	/*printf("Tail Completed\n");   */

	if(atoi(v_00.transaction_type) == 56 && Dclose_Done=='Y') Dclose_Done='N';
}

/* FTAIL Record for FHEAD record */
void StoreInFtail(int string_counter)
{
	char padding_string[MAXFLDS];
	char v_item_status[1];
	FTAIL_v99= (struct FTAIL_99 *)malloc(sizeof(struct FTAIL_99));
	if(start_dclose=='Y')
	{
		dclose_line_counter++;
                number_pad(padding_string,dclose_line_counter,10);
	}
        else
        {
                current_line_counter++;
                number_pad(padding_string,current_line_counter,10);
        }
	strcpy(FTAIL_v99->FileTypeRecord,"FTAIL");                 /* File Type Record - 5 */
	string_pad(FTAIL_v99->FileTypeRecord,5-strlen(FTAIL_v99->FileTypeRecord)," ","R");
	strcpy(FTAIL_v99->LineNumber,padding_string);             /* Running Sequence Number - 10 */

	padding_string[0]='\0';
	if(start_dclose=='Y')
		number_pad(padding_string,dclose_line_counter-2,10);
	else	
		number_pad(padding_string,current_line_counter-2,10);
	strcpy(FTAIL_v99->TotalTransactionLines,padding_string);
	
	strcpy(FTAIL_v99->EndOfString,"\0");

}
void StoreInTHEAD15(int string_counter)
{

	/*CleanUpOutStructs(); */
        /*printf("inside Store In THEAD:%d\n",string_counter);    */
	char ReSA_Transaction_type[MAXFLDS];
	char ReSA_Transaction_subtype[MAXFLDS];
	char padding_string[MAXFLDS];
	char org_txn[5];
	THEAD_v00_15 = (struct THEAD_00 *)malloc(sizeof(struct THEAD_00));
	thead_no=dclose_line_counter;
	Head_net_positive=atoi(v_00_b[string_counter].net_postive_amount);
	Head_net_negative=atoi(v_00_b[string_counter].net_negative_amount);
	transaction_number=atoi(v_00_b[string_counter].transaction_number);
	strcpy(THEAD_v00_15->FileTypeRecord,"THEAD");
	dclose_line_counter++;
        number_pad(padding_string,dclose_line_counter,10);
	strcpy(THEAD_v00_15->LineNumber,padding_string);
	strcpy(THEAD_v00_15->Register,v_00_b[string_counter].terminal_number);
	string_pad(THEAD_v00_15->Register,5-strlen(v_00_b[string_counter].terminal_number)," ","R");
	strcpy(THEAD_v00_15->TransactionDate,"20");
	strcat(THEAD_v00_15->TransactionDate,v_00_b[string_counter].date_of_transaction);
	strcat(THEAD_v00_15->TransactionDate,v_00_b[string_counter].time_of_transaction);
	strcat(THEAD_v00_15->TransactionDate,"00");
	if(strlen(v_00_b[string_counter].transaction_number)<10)	
		string_pad(THEAD_v00_15->TransactionNumber,10-strlen(v_00_b[string_counter].transaction_number),"0","R");
	strcat(THEAD_v00_15->TransactionNumber,v_00_b[string_counter].transaction_number);

	string_pad(THEAD_v00_15->TransactionNumber,10,"0","L");  

	sprintf(THEAD_v00_15->Cashier,"%d",atoi(v_00_b[string_counter].operator_number));		/* Cashier ID - 10 */
	string_pad(THEAD_v00_15->Cashier,10-strlen(THEAD_v00_15->Cashier)," ","R");
	string_pad(THEAD_v00_15->SalesPerson,10," ","R");                /* Sales Person - 10 */
	GetReSATransactionType(v_00_b[string_counter].transaction_type,ReSA_Transaction_type); /* Transaction Type -6 */
	strcpy(THEAD_v00_15->TransactionType,ReSA_Transaction_type);
	if (strlen(THEAD_v00_15->TransactionType) <6) string_pad(THEAD_v00_15->TransactionType,6-strlen(THEAD_v00_15->TransactionType)," ","R");
	GetReSATransactionSubType(v_00_b[string_counter].transaction_type,ReSA_Transaction_subtype);
	strcpy(THEAD_v00_15->SubTransactionType,ReSA_Transaction_subtype); 
	if (strlen(THEAD_v00_15->SubTransactionType) <6) 
		string_pad(THEAD_v00_15->SubTransactionType,6-strlen(THEAD_v00_15->SubTransactionType)," ","R");

	string_pad(THEAD_v00_15->OrigTxnNo,10,"0","R");   /*Orig_tran_no -10 */

        string_pad(THEAD_v00_15->OrigRegNo,5," ","R");         /*Orig_reg_no -5 */

        string_pad(THEAD_v00_15->ReasonCode,6," ","R");         /*Reason Code - 6 */

        string_pad(THEAD_v00_15->VendorNumber,10," ","R");        /* Vendor Number - 10 */
        string_pad(THEAD_v00_15->VendorInvoiceNumber,30," ","R");        /*Vendor Invoice Number - 30 */
        string_pad(THEAD_v00_15->PaymentRefNumber,16," ","R");        /* Payment Reference Number - 16 */
        string_pad(THEAD_v00_15->ProofOfDelivery,30," ","R");        /*Proof of Delivery Number - 30 */


        if(sys_cash=='N') strcpy(THEAD_v00_15->ReferenceNumber1,"1390");
        else strcpy(THEAD_v00_15->ReferenceNumber1,"1410");

        string_pad(THEAD_v00_15->ReferenceNumber1,30-strlen(THEAD_v00_15->ReferenceNumber1)," ","R");

	string_pad(THEAD_v00_15->ReferenceNumber2,30," ","R");

	/*printf("After Ref2\n");    */
        string_pad(THEAD_v00_15->ReferenceNumber3,30," ","R");        /*Reference Number 3- 30 */

	/*printf("After Ref3\n");   */

        string_pad(THEAD_v00_15->ReferenceNumber4,30," ","R");        /*Reference Number 4- 30 */

                char realpart[15];
                char decimalpart[4];
                strcpy(THEAD_v00_15->ValueSign,"P");
                if(sys_cash=='N')
                {
                        substr(realpart,v_15_b[string_counter].cash_amount,0,strlen(v_15_b[string_counter].cash_amount)-3);
                        substr(decimalpart,v_15_b[string_counter].cash_amount,strlen(v_15_b[string_counter].cash_amount)-2,2);

                }
                else
                {
                        substr(realpart,v_15_b[string_counter].check_amount,0,strlen(v_15_b[string_counter].check_amount)-3);
                        substr(decimalpart,v_15_b[string_counter].check_amount,strlen(v_15_b[string_counter].check_amount)-2,2);
			sys_cash='N';

                }
                strcpy(THEAD_v00_15->Value,realpart);
                strcat(THEAD_v00_15->Value,decimalpart);
                strcat(THEAD_v00_15->Value,"00");
                string_pad(THEAD_v00_15->Value,20-strlen(THEAD_v00_15->Value),"0","L");

        strcat(THEAD_v00_15->BannerId,"0001");                /*Banner Id*/
        string_pad(THEAD_v00_15->CustomerOrderHead,30," ","R");        /* Customer Order Head ID - 30 */
        string_pad(THEAD_v00_15->CustomerOrderDate,14," ","R");        /* Customer Order Head Date - 30 */

/* For 13.1 Back proting */

        if(Head_net_positive-Head_net_negative >=0) strcpy(THEAD_v00_15->RoundedAmountSign,"P");
        else strcpy(THEAD_v00_15->RoundedAmountSign,"N");

        	sprintf(THEAD_v00_15->RoundedAmount,"%d",atoi(v_00_b[string_counter].net_total_amount)*100);
        	string_pad(THEAD_v00_15->RoundedAmount,20-strlen(THEAD_v00_15->RoundedAmount),"0","L");

        strcpy(THEAD_v00_15->RoundedOffSign,"P");
        string_pad(THEAD_v00_15->RoundedOffAmount,20,"0","R");


/* For 13.1 Back proting */



}
