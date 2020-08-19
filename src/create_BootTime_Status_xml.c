#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

extern char Buff[51][128];
char *BootTime_Status_file="/opt/BootTime_Status.xml";


int BootTime_Status_xml_frame()
{
	int Total_Server_Apps=0,Total_Running_apps=0;
	fprintf(stdout,"\n\n BootTime_Status.xml Framing ...\n\n");
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr root_node = NULL, childnode = NULL, Runningchildnode = NULL;/* node pointers */
	char *ptr=NULL,Buffer[128]="";
	int i;

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL,  "BootStatus");
	xmlDocSetRootElement(doc, root_node);

	struct Device
	{
		int Total_Solt1_secs;
		int Total_Solt2_secs;
		int Total_Solt3_secs;
		int Total_Solt4_secs;
		int Total_work_secs;
		int Total_adapter_secs;
		int Total_charging_secs;
		int Total_discharging_secs;
	}Day;
	memset(&Day,0x00,sizeof(Day));

	xmlNewChild(root_node, NULL, BAD_CAST "SerialNo",BAD_CAST Buff[1]);
	xmlNewChild(root_node, NULL, BAD_CAST "Date_Time", BAD_CAST module.Date_time);

	if( CONFIG.DOT && strlen(Buff[8]) != 0 && strstr(Buff[8],"ERROR") == NULL)
	{

		int File_day=0,File_month=0,File_year=0;
		sscanf(Buff[8],"%02d%02d%04d/%d/%d/%d/%d",&File_day,&File_month,&File_year,&Day.Total_Solt1_secs,&Day.Total_Solt2_secs,&Day.Total_Solt3_secs,&Day.Total_Solt4_secs);
		sprintf(module.DOT.Date,"%04d-%02d-%02d",File_year,File_month,File_day);
		printf("module.DOT.Date = %s\n",module.DOT.Date);
		sprintf(module.DOT.Slot1,"%d",Day.Total_Solt1_secs);
		sprintf(module.DOT.Slot2,"%d",Day.Total_Solt2_secs);
		sprintf(module.DOT.Slot3,"%d",Day.Total_Solt3_secs);
		sprintf(module.DOT.Slot4,"%d",Day.Total_Solt4_secs);

		if( CONFIG.BatteryInfo )
		{
			sscanf(Buff[9],"%02d%02d%04d/%d/%d/%d/%d",&File_day,&File_month,&File_year,&Day.Total_work_secs,&Day.Total_adapter_secs,&Day.Total_charging_secs,&Day.Total_discharging_secs);
			sprintf(module.BatteryInfo.Date,"%04d-%02d-%02d",File_year,File_month,File_day);
			printf("module.BatteryInfo.Date = %s\n",module.BatteryInfo.Date);
			sprintf(module.BatteryInfo.Day_worked_mins,"%d",Day.Total_work_secs);
			sprintf(module.BatteryInfo.Day_adapter_mins,"%d",Day.Total_adapter_secs);
			sprintf(module.BatteryInfo.Day_charged_mins,"%d",Day.Total_charging_secs);
			sprintf(module.BatteryInfo.Day_discharged_mins,"%d",Day.Total_discharging_secs);
		}

		childnode = xmlNewChild(root_node, NULL, BAD_CAST "DOT",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Date", BAD_CAST module.DOT.Date);
		xmlNewChild(childnode, NULL, BAD_CAST "Slot1", BAD_CAST module.DOT.Slot1);
		xmlNewChild(childnode, NULL, BAD_CAST "Slot2", BAD_CAST module.DOT.Slot2);
		xmlNewChild(childnode, NULL, BAD_CAST "Slot3", BAD_CAST module.DOT.Slot3);
		xmlNewChild(childnode, NULL, BAD_CAST "Slot4", BAD_CAST module.DOT.Slot4);
	}


	if( CONFIG.Pinpad )
		xmlNewChild(root_node, NULL, BAD_CAST "Pinpad", BAD_CAST module.pinpad);
	if ( strstr(Buff[22],"Alive") != NULL )
		xmlNewChild(root_node, NULL, BAD_CAST "Ethernet", BAD_CAST "Connected");
	else 
		xmlNewChild(root_node, NULL, BAD_CAST "Ethernet", BAD_CAST "NotConnected");

	if (  strlen(Buff[17]) != 0 && strstr(Buff[17],"Capacitive") != NULL)
		xmlNewChild(root_node, NULL, BAD_CAST "FingerPrint", BAD_CAST "Capacitive");
	else if (  strlen(Buff[17]) != 0 && strstr(Buff[17],"Optical") != NULL)
		xmlNewChild(root_node, NULL, BAD_CAST "FingerPrint", BAD_CAST "Optical");
	else xmlNewChild(root_node, NULL, BAD_CAST "FingerPrint", BAD_CAST "Not-Detected");

	if( CONFIG.SAM1 )
	{
		if (  strlen(Buff[20]) != 0 && strstr(Buff[20],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "SAM1", BAD_CAST "Inserted");
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "SAM1", BAD_CAST "NotInserted");
	}
	if( CONFIG.SAM2 )
	{
		if (  strlen(Buff[21]) != 0 && strstr(Buff[21],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "SAM2", BAD_CAST "Inserted");
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "SAM2", BAD_CAST "NotInserted");
	}

	if( CONFIG.IFD1 )
	{
		if (  strlen(Buff[26]) != 0 && strstr(Buff[26],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "IFD1", BAD_CAST "Inserted");
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "IFD1", BAD_CAST "NotInserted");
	}

	if( CONFIG.IFD2 )
	{
		if (  strlen(Buff[27]) != 0 && strstr(Buff[27],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "IFD2", BAD_CAST "Inserted");
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "IFD2", BAD_CAST "NotInserted");
	}


	if( CONFIG.Printer )
	{
		if (  strlen(Buff[24]) != 0 && strstr(Buff[24],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "Printer", BAD_CAST "Yes");
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "Printer", BAD_CAST "No");
	}

	if( CONFIG.Bluetooth )
	{
		if (  strlen(Buff[19]) != 0 && strstr(Buff[19],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "Bluetooth", BAD_CAST "Yes");
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "Bluetooth", BAD_CAST "No");
	}

	if( CONFIG.WIFI )
	{
		if (  strlen(Buff[25]) != 0 && strstr(Buff[25],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "WIFI", BAD_CAST "Yes");
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "WIFI", BAD_CAST "No");
	}
	if( CONFIG.Camera )
	{
		if (  strlen(Buff[51]) != 0 && strstr(Buff[51],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "Camera", BAD_CAST "Yes");
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "Camera", BAD_CAST "No");
	}
	if( strlen(Buff[29]) != 0 && strstr(Buff[29],"ERROR") == NULL)
		xmlNewChild(root_node, NULL, BAD_CAST "Audio", BAD_CAST "Success");
	else xmlNewChild(root_node, NULL, BAD_CAST "Audio", BAD_CAST "Failure");

	if( CONFIG.BatteryInfo && strlen(module.BatteryInfo.Date) > 5 ) 
	{
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "BatteryInfo",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Date", BAD_CAST module.BatteryInfo.Date);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_worked_mins", BAD_CAST module.BatteryInfo.Day_worked_mins);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_adapter_mins", BAD_CAST module.BatteryInfo.Day_adapter_mins);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_charged_mins", BAD_CAST module.BatteryInfo.Day_charged_mins);
		xmlNewChild(childnode, NULL, BAD_CAST "Day_discharged_mins", BAD_CAST module.BatteryInfo.Day_discharged_mins);
	}

	childnode = xmlNewChild(root_node, NULL, BAD_CAST "ArrayofApplications",NULL);


	//Total_Server_Apps = Get_Total_Server_Apps();

	//fprintf(stdout," Total Server Apps = %d\n",Total_Server_Apps);

	//if ( Total_Server_Apps > 0 )
	//	Applications_Details(Total_Server_Apps,childnode);

	Runningchildnode = xmlNewChild(root_node, NULL, BAD_CAST "ArrayofRunningApplications",NULL);
	//Total_Running_apps = Get_Total_Device_Apps();

	//fprintf(stdout," Total_Running_apps = %d\n",Total_Running_apps);

	//if ( Total_Running_apps > 0 )
	//	Running_Apps_Details(Total_Running_apps,Runningchildnode);

	xmlNewChild(root_node, NULL, BAD_CAST "FirmwareName", BAD_CAST module.FirmwareName);

	xmlNewChild(root_node, NULL, BAD_CAST "FirmwareVersion", BAD_CAST module.FirmwareVersion);

	if( CONFIG.IrisRDVer_and_SNo  )
	{
		if (  strlen(Buff[11]) != 0 && strstr(Buff[11],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "IritechRDVer", BAD_CAST Buff[11]);
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "IritechRDVer", BAD_CAST "NotFound");
	}

	if( CONFIG.BiomRDVer )
	{
		if (  strlen(Buff[13]) != 0 && strstr(Buff[13],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "BiomRDVer", BAD_CAST Buff[13]);
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "BiomRDVer", BAD_CAST "NotFound");
	}
	if( CONFIG.FPSRDVer )
	{
		if (  strlen(Buff[15]) != 0 && strstr(Buff[15],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "FPSRDVer", BAD_CAST Buff[15]);
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "FPSRDVer", BAD_CAST "NotFound");
	}

	if ( strlen(Buff[40]) > 0 && strstr(Buff[40],"Not")==NULL )
	{
		xmlNewChild(root_node, NULL, BAD_CAST "ExternalMemExists", BAD_CAST "Yes");
		memset(Buffer,0,sizeof(Buffer));
		strcpy(Buffer,Buff[40]);
		ptr = strtok(Buffer, "/");
		if(ptr!=NULL)
		{
			strcpy(module.ExternalMem.Total,ptr);

			for( i=0; ( ( ptr = strtok(NULL, "/") ) != NULL );i++)
			{
				if( i == 0)
					strcpy(module.ExternalMem.Use,ptr);
				else if( i == 1)
				{
					strcpy(module.ExternalMem.Free,ptr);
					break;
				}
			}
		}
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "ExternalMem",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.ExternalMem.Total);
		xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.ExternalMem.Use);
		xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.ExternalMem.Free);
	}
	else 
		xmlNewChild(root_node, NULL, BAD_CAST "ExternalMemExists", BAD_CAST "No");

	if ( strlen(Buff[41]) > 0 && strstr(Buff[41],"Not")==NULL )
	{       
		xmlNewChild(root_node, NULL, BAD_CAST "UsbdeviceExists", BAD_CAST "Yes"); 
		memset(Buffer,0,sizeof(Buffer));
		strcpy(Buffer,Buff[41]);
		ptr = strtok(Buffer, "/");
		if(ptr!=NULL)
		{
			strcpy(module.Usbdevice.Total,ptr);

			for( i=0; ( ( ptr = strtok(NULL, "/") ) != NULL );i++)
			{       
				if( i == 0) 
					strcpy(module.Usbdevice.Use,ptr);
				else if( i == 1) 
				{       
					strcpy(module.Usbdevice.Free,ptr);
					break;  
				}
			}       
		}
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "Usbdevice",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.Usbdevice.Total);
		xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.Usbdevice.Use);
		xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.Usbdevice.Free);
	}       
	else    
		xmlNewChild(root_node, NULL, BAD_CAST "UsbdeviceExists", BAD_CAST "No"); 
	if ( strlen(module.operator2_name) == 0 )
		strcpy(module.operator2_name,"NotFound");
	if ( strlen(module.operator1_name) == 0 )
		strcpy(module.operator1_name,"NotFound");

	if( CONFIG.Two_Simdetails_Autoapn )
	{
		if( strlen(Buff[3]) != 0 && (strstr(Buff[3],"ERROR") == NULL && strstr(Buff[3],"NO_SIM") == NULL) )
		{
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumberExists", BAD_CAST "Yes");
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumber", BAD_CAST Buff[3]);
		}
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumberExists", BAD_CAST "NO_SIM");
		if( strlen(Buff[4]) != 0 && (strstr(Buff[4],"ERROR") == NULL && strstr(Buff[4],"NO_SIM") == NULL) )
		{
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumberExists", BAD_CAST "Yes");
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumber", BAD_CAST Buff[4]);
		}
		else 
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumberExists", BAD_CAST "NO_SIM");
				
		xmlNewChild(root_node, NULL, BAD_CAST "SIM1Operator", BAD_CAST module.operator1_name);
		xmlNewChild(root_node, NULL, BAD_CAST "SIM2Operator", BAD_CAST module.operator2_name);
	}
	else 
	{
		if ( strcmp(module.SIM2CCIDnumberExists,"Yes") == 0 )
		{
			if( strlen(Buff[4]) != 0 && (strstr(Buff[4],"ERROR") == NULL && strstr(Buff[4],"NO_SIM") == NULL) )
			{
				xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumberExists", BAD_CAST "Yes");
				xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumber", BAD_CAST Buff[4]);
			}
			else 
				xmlNewChild(root_node, NULL, BAD_CAST "SIM2CCIDnumberExists", BAD_CAST "NO_SIM");
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2Operator", BAD_CAST module.operator2_name);

		}	
		else 
		{
			if( strlen(Buff[3]) != 0 && (strstr(Buff[3],"ERROR") == NULL && strstr(Buff[3],"NO_SIM") == NULL) )
			{
				xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumberExists", BAD_CAST "Yes");
				xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumber", BAD_CAST Buff[3]);
			}
			else 
				xmlNewChild(root_node, NULL, BAD_CAST "SIM1CCIDnumberExists", BAD_CAST "NO_SIM");
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1Operator", BAD_CAST module.operator1_name);

		}

	}
	xmlNewChild(root_node, NULL, BAD_CAST "RHMSClientVersion", BAD_CAST "1.1.1");
	xmlNewChild(root_node, NULL, BAD_CAST "AutoapnAppVersion", BAD_CAST "NotFound");



	xmlSaveFormatFileEnc(BootTime_Status_file,doc, "UTF-8", 1);

	xmlFreeDoc(doc);

	xmlCleanupParser();

	return 0;

}
