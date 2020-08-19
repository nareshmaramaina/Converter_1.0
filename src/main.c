#include<header.h>
char Buff[51][128];
void Update_Current_Date_with_Time()
{
        struct tm *Today=NULL;
        struct timeval tv;

        memset(module.Date_time,0,sizeof(module.Date_time));

        gettimeofday (&tv,NULL);

        Today = localtime (&tv.tv_sec) ;

        sprintf(module.Date_time,"%04d-%02d-%02dT%02d:%02d:%02d",Today->tm_year+1900,Today->tm_mon+1,Today->tm_mday,Today->tm_hour,Today->tm_min,Today->tm_sec);
        fprintf(stdout,"Today Date and Time, %s \n",module.Date_time);

        return;
}

int parseStory (xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	FILE *fp;
	char *tmp[]={"TerminalID", "SerialNo", "IMEInumber", "CCIDnumber", "Sim2CCID", "UID", "Macid", "Comm", "DOT", "BatteryInfo", "IRIS", "IritechRDVer", "IritechSno", "BiomRDVer", "WSSN","FPSRDVer", "GPS",  "FingerPrint", "FPScannerid", "Bluetooth", "SAM1", "SAM2", "Ethernet", "PaperStatus", "Printer", "WIFI", "IFD1","IFD2", "RTC", "AUDIO", "Sim1Details","SimDetails", "Sim2Details", "Adapter", "Battery", "GSMVersion", "GSM_Module",  "BarcodeSno", "InternalMem-Sysuser", "InternalMem-Jffs2", "ExternalMem", "Usbdevice", "RAM", "UbootImageName", "KernelImageName", "RootfsImageName", "ApplicationType", "ApplicationVer", "FirmwarePatchVersion", "FirmwarePatchName","PinpadSN","Camera"};

	for(cur = cur->xmlChildrenNode; cur != NULL; cur = cur->next)
	{

		for( int i =0 ; i<= 51; i++)
		{
			if (!xmlStrcmp(cur->name, (const xmlChar *)tmp[i]))
			{
				key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				strcpy(Buff[i],key);
				printf("%d) Buff[%d],cur->name = %s Key = %s\n",i,i,cur->name, key);
				break;
			}
		}
	}
	xmlFree(key);

	return 0;
}

int main(int argc,char *argv[])
{
	char filename[38];
	xmlDocPtr doc;
	xmlNodePtr cur;
	short int ret=0,Change_flag =0;

	if ( argc  < 2 )
	{
		fprintf(stdout,"Give Health xml Argument\n");
		return -1;
	}
	//fprintf(stdout,"Parsing %s file\n",argv[1]);
	doc = xmlParseFile(argv[1]);
	if (doc == NULL )
	{
		fprintf(stderr,"Document not parsed successfully. \n");
		return -1;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL)
	{
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return -1;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "POSHEALTHDETAILS")) 
	{
		fprintf(stderr,"document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return -1;
	}

	Get_Config_Settings(); // Get Settings for enble or disable each Tag 
	cur = cur->xmlChildrenNode;
	memset(&module,0x00,sizeof(struct terminal_status));
	while (cur != NULL) 
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"DEVICE_DETAILS")))
		{
			parseStory (doc,cur);
		}

		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PERIPHERALS")))
		{
			parseStory (doc,cur);
		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"MEMORY")))
		{
			parseStory (doc,cur);


		}
		else if ((!xmlStrcmp(cur->name, (const xmlChar *)"IMAGES")))
		{
			parseStory (doc,cur);

		}

		cur = cur->next;
	}
	xmlFreeDoc(doc);

	remove("/opt/BootTime_Status.xml");
	remove("/opt/Hardware_Status.xml");
	remove("/opt/Health_Status.xml");
	Update_Current_Date_with_Time();
	Hardware_xml_frame();
	Update_Current_Date_with_Time();
	Health_Status_xml_frame();
	Update_Current_Date_with_Time();
	BootTime_Status_xml_frame();
	system("cat /opt/BootTime_Status.xml  /opt/Hardware_Status.xml  /opt/Health_Status.xml");
}
