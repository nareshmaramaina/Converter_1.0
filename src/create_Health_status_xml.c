#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char *Health_Status_file="/opt/Health_Status.xml";

extern char Buff[51][128];

int Health_Status_xml_frame();


int Health_Status_xml_frame()
{
	char *ptr=NULL,Buffer[128]="";
	int i;	
	int sim_num =0;
	int Apps_Downloads=0,Firmware_Downloads=0;

	fprintf(stdout,"\n\n Health_Status.xml Framing ...\n\n");
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr root_node = NULL, childnode = NULL;/* node pointers */

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL,  "HealthStatus");
	xmlDocSetRootElement(doc, root_node);


	
	xmlNewChild(root_node, NULL, BAD_CAST "SerialNo",BAD_CAST Buff[1]);
	xmlNewChild(root_node, NULL, BAD_CAST "Date_Time", BAD_CAST module.Date_time);

	if( (CONFIG.GPS || CONFIG.geo_location ) && (strstr(Buff[16],"Error") == NULL ) )
	{
		int File_day=0,File_month=0,File_year=0,File_Hr=0,File_Min=0;
		
		strcpy(Buffer,Buff[16]);
		ptr = strtok(Buffer, ",");
		if(ptr!=NULL)
		{
			strcpy(module.GPS.Latitude,ptr);

			for( i=0; ( ( ptr = strtok(NULL, ",") ) != NULL );i++)
			{
				if( i == 0)
					strcpy(module.GPS.Longitude,ptr);
				else if ( i== 1 )
				{
					strcpy(Buffer,ptr);
					break;
				}
			}
		}

		sscanf(Buffer,"%02d/%02d/%04d-%02d:%02d",&File_day,&File_month,&File_year,&File_Hr,&File_Min);
		sprintf(module.GPS.Captured_Time,"%04d-%02d-%02dT%02d:%02d:00",File_year,File_month,File_day,File_Hr,File_Min);
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "GPS",NULL);
		xmlNewChild(childnode, NULL, BAD_CAST "Latitude", BAD_CAST module.GPS.Latitude);
		xmlNewChild(childnode, NULL, BAD_CAST "Longitude", BAD_CAST module.GPS.Longitude);
		if ( strstr(module.GPS.Captured_Time,"0000-00-00") != NULL )
			fprintf(stdout,"Date Not found, module.GPS.Captured_Time = %s\n",module.GPS.Captured_Time);
		else 
			xmlNewChild(childnode, NULL, BAD_CAST "Captured_Time", BAD_CAST module.GPS.Captured_Time);
	}
	//Firmware_Downloads = Get_Total_Downloaded_Updates(FIRMWARE);
	if ( Firmware_Downloads > 0 )
	{
		fprintf(stdout,"%d Firmware Downloads are Found \n",Firmware_Downloads);
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "ArrayofFirmwareDownloads",NULL);
		//	FirmwareDownloadsDetails(Firmware_Downloads,childnode);		
	}
	else
	{
		fprintf(stdout,"No Firmware Downloads Found\n");
	}
	//Apps_Downloads = Get_Total_Downloaded_Updates(APPLICATION);
	if ( Apps_Downloads > 0 )
	{
		fprintf(stdout,"%d Application Downloads are Found \n",Apps_Downloads);
		childnode = xmlNewChild(root_node, NULL, BAD_CAST "ArrayofApplicationDownloads",NULL);
		//ApplicationDownloadsDetails(Apps_Downloads,childnode);

	}
	else
		fprintf(stdout,"No Application Downloads Found\n");

	if( CONFIG.Iris_or_Biomat )
	{
		if( strlen(Buff[10]) != 0 && strstr(Buff[12],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "IRIS", BAD_CAST Buff[10]);
		else 	
			xmlNewChild(root_node, NULL, BAD_CAST "IRIS", BAD_CAST "NotConnected");
	}
	if( CONFIG.Printer )
	{
		if( strlen(Buff[23]) != 0 && strstr(Buff[23],"ERROR") == NULL)
			xmlNewChild(root_node, NULL, BAD_CAST "PaperStatus", BAD_CAST "Yes");
		else 	
			xmlNewChild(root_node, NULL, BAD_CAST "PaperStatus", BAD_CAST "No");
	}

	if( strlen(Buff[28]) != 0 && strstr(Buff[28],"ERROR") == NULL)
		xmlNewChild(root_node, NULL, BAD_CAST "RTC", BAD_CAST "Success");
	else xmlNewChild(root_node, NULL, BAD_CAST "RTC", BAD_CAST "Failure");

	if( strlen(Buff[33]) != 0 && strstr(Buff[33],"ERROR") == NULL)
		xmlNewChild(root_node, NULL, BAD_CAST "Adapter", BAD_CAST "NotConnected");
	else 
		xmlNewChild(root_node, NULL, BAD_CAST "Adapter", BAD_CAST "Connected");


	if( strlen(Buff[34]) != 0 && strstr(Buff[34],"0.00V") == NULL)
	{
		memset(Buffer,0,sizeof(Buffer));
		strcpy(Buffer,Buff[34]);
		ptr = strtok(Buffer, "/");
		if(ptr!=NULL)
		{
			strcpy(module.BatteryVoltage,ptr);

			for( i=0; ( ( ptr = strtok(NULL, "/") ) != NULL );i++)
			{
				if( i == 0)
				{
					strcpy(module.Battery_status,ptr);
					break;
				}
			}
		}
		xmlNewChild(root_node, NULL, BAD_CAST "Battery", BAD_CAST module.Battery_status);
		xmlNewChild(root_node, NULL, BAD_CAST "BatteryVoltage", BAD_CAST module.BatteryVoltage);
	}
	else 
	{
		xmlNewChild(root_node, NULL, BAD_CAST "Battery", BAD_CAST "NotConnected");
		xmlNewChild(root_node, NULL, BAD_CAST "BatteryVoltage", BAD_CAST "0.00V");
	}
	xmlNewChild(root_node, NULL, BAD_CAST "Comm", BAD_CAST Buff[7]);

	if( strcmp(Buff[7],"GSM") == 0 )
	{
		sim_num = Update_Simdb_and_Signalmode();	
		if ( sim_num == 1)
		{
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1db", BAD_CAST module.Sim1_db);
			xmlNewChild(root_node, NULL, BAD_CAST "SIM1SignalMode", BAD_CAST module.SIM1SignalMode);
		}
		else if ( sim_num == 2)
		{
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2db", BAD_CAST module.Sim2_db);
			xmlNewChild(root_node, NULL, BAD_CAST "SIM2SignalMode", BAD_CAST module.SIM2SignalMode);
		}
	}

	xmlNewChild(root_node, NULL, BAD_CAST "FingerRDServiceStatus", BAD_CAST "Green");
	/*
	childnode = xmlNewChild(root_node, NULL, BAD_CAST "System_memory",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.System_memory.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.System_memory.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.System_memory.Free);
	*/
	if ( strlen(Buff[38]) > 0 )
	{	
		memset(Buffer,0,sizeof(Buffer));
		strcpy(Buffer,Buff[38]);
		ptr = strtok(Buffer, "/");
		if(ptr!=NULL)
		{
			strcpy(module.InternalMem_Sysuser.Total,ptr);

			for( i=0; ( ( ptr = strtok(NULL, "/") ) != NULL );i++)
			{
				if( i == 0)
					strcpy(module.InternalMem_Sysuser.Use,ptr);
				else if( i == 1)
				{
					strcpy(module.InternalMem_Sysuser.Free,ptr);
					break;
				}
			}
		}
	}

	childnode = xmlNewChild(root_node, NULL, BAD_CAST "InternalMem_Sysuser",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.InternalMem_Sysuser.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.InternalMem_Sysuser.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.InternalMem_Sysuser.Free);
	if ( strlen(Buff[39]) > 0 )
        {       
                memset(Buffer,0,sizeof(Buffer));
                strcpy(Buffer,Buff[39]);
                ptr = strtok(Buffer, "/");
                if(ptr!=NULL)
                {
                        strcpy(module.InternalMem_Jffs2.Total,ptr);

                        for( i=0; ( ( ptr = strtok(NULL, "/") ) != NULL );i++)
                        {
                                if( i == 0)
                                        strcpy(module.InternalMem_Jffs2.Use,ptr);
                                else if( i == 1) 
                                {
                                        strcpy(module.InternalMem_Jffs2.Free,ptr);
                                        break;
                                }
                        }
                }
        }
	
	childnode = xmlNewChild(root_node, NULL, BAD_CAST "InternalMem_Jffs2",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.InternalMem_Jffs2.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.InternalMem_Jffs2.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.InternalMem_Jffs2.Free);
	 if ( strlen(Buff[42]) > 0 )
        {
                memset(Buffer,0,sizeof(Buffer));
                strcpy(Buffer,Buff[42]);
                ptr = strtok(Buffer, "/");
                if(ptr!=NULL)
                {
                        strcpy(module.RAM.Total,ptr);

                        for( i=0; ( ( ptr = strtok(NULL, "/") ) != NULL );i++)
                        {
                                if( i == 0)
                                        strcpy(module.RAM.Use,ptr);
                                else if( i == 1)
                                {
                                        strcpy(module.RAM.Free,ptr);
                                        break;
                                }
                        }
                }
        }


	childnode = xmlNewChild(root_node, NULL, BAD_CAST "RAM",NULL);
	xmlNewChild(childnode, NULL, BAD_CAST "Total", BAD_CAST module.RAM.Total);
	xmlNewChild(childnode, NULL, BAD_CAST "Use", BAD_CAST module.RAM.Use);
	xmlNewChild(childnode, NULL, BAD_CAST "Free", BAD_CAST module.RAM.Free);



	xmlSaveFormatFileEnc(Health_Status_file,doc, "UTF-8", 1);

	xmlFreeDoc(doc);

	xmlCleanupParser();

	return 0;

}
int Update_Simdb_and_Signalmode()
{
	char *ptr=NULL,Buffer[128]="";
        int i;
	int Sig_Strength=0, sim_num=0;
	memset(module.SIM1SignalMode,0,sizeof(module.SIM1SignalMode));
	memset(module.SIM2SignalMode,0,sizeof(module.SIM2SignalMode));

	if (  strlen(Buff[30]) > 0 && strstr(Buff[30],"ERROR")==NULL )
	{
		memset(Buffer,0,sizeof(Buffer));
		strcpy(Buffer,Buff[30]);
		ptr = strtok(Buffer, "/");
		if(ptr!=NULL)
		{
			for( i=0; ( ( ptr = strtok(NULL, "/") ) != NULL );i++)
			{
				if( i == 0)
					strcpy(module.Sim1_db,ptr);
				if( i == 1)
					strcpy(module.operator1_name,ptr);
				else if( i == 2)
				{
					strcpy(module.SIM1SignalMode,ptr);
					break;
				}
			}
		}
	}
	else if (  strlen(Buff[31]) > 0 && strstr(Buff[31],"ERROR")==NULL )
        {
                memset(Buffer,0,sizeof(Buffer));
                strcpy(Buffer,Buff[31]);
                ptr = strtok(Buffer, "/");
                if(ptr!=NULL)
                {
                        for( i=0; ( ( ptr = strtok(NULL, "/") ) != NULL );i++)
                        {
                                if( i == 0)
                                        strcpy(module.Sim1_db,ptr);
                                if( i == 1)
                                        strcpy(module.operator1_name,ptr);
                                else if( i == 2)
                                {
                                        strcpy(module.SIM1SignalMode,ptr);
                                        break;
                                }
                        }
                }
        }
	
	 if (  strlen(Buff[32]) > 0 && strstr(Buff[32],"ERROR")==NULL )
        {
                memset(Buffer,0,sizeof(Buffer));
                strcpy(Buffer,Buff[32]);
                ptr = strtok(Buffer, "/");
                if(ptr!=NULL)
                {
			fprintf(stdout,"Ptr = %s\n",ptr);
                        for( i=0; ( ( ptr = strtok(NULL, "/") ) != NULL );i++)
                        {
			fprintf(stdout,"Ptr = %s\n",ptr);
                                if( i == 0)
                                        strcpy(module.Sim2_db,ptr);
                                if( i == 1)
                                        strcpy(module.operator2_name,ptr);
                                else if( i == 2)
                                {
                                        strcpy(module.SIM2SignalMode,ptr);
                                        break;
                                }
                        }
                }
        }


	if(strlen(module.Sim1_db) == 0 )
		strcpy(module.Sim1_db,"NotFound");
	else
	{
		Sig_Strength=atoi(module.Sim1_db);
		Sig_Strength = (Sig_Strength*2)-113;
		sprintf(module.Sim1_db,"%d",Sig_Strength);
	}

	if(strlen(module.Sim2_db) == 0 )
		strcpy(module.Sim2_db,"NotFound");
	else
	{
		Sig_Strength=atoi(module.Sim2_db);
		Sig_Strength = (Sig_Strength*2)-113;
		sprintf(module.Sim2_db,"%d",Sig_Strength);
	}
	

	if ( strlen( module.SIM1SignalMode ) <= 0 || strcmp(module.SIM1SignalMode,"G") == 0 )
		sim_num=2;
	else sim_num=1;
	fprintf(stdout,"module.Sim1_db = %s,module.SIM1SignalMode, = %s, module.Sim2_db = %s,module.SIM2SignalMode, = %s\n",module.Sim1_db,module.SIM1SignalMode,module.Sim2_db,module.SIM2SignalMode);
	return sim_num;
}
