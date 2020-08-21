#include <header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char *Hardware_Status_file="/opt/Hardware_Status.xml";
extern char Buff[51][128];


int Hardware_xml_frame()
{
	//fprintf(stdout,"\n\nHardware xml Framing ...\n\n");
	xmlDocPtr doc = NULL;
	/* document pointer */
	xmlNodePtr node = NULL;

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");
	node = xmlNewNode(NULL,  "DeviceDetails");
	xmlDocSetRootElement(doc, node);

	xmlNewChild(node, NULL, BAD_CAST "SerialNo",BAD_CAST Buff[1]);
	xmlNewChild(node, NULL, BAD_CAST "Date_Time", BAD_CAST module.Date_time);

	xmlNewChild(node, NULL, BAD_CAST "TerminalIDExists",BAD_CAST "Found");
	xmlNewChild(node, NULL, BAD_CAST "TerminalID",BAD_CAST Buff[0]);

	xmlNewChild(node, NULL, BAD_CAST "MacidExists", BAD_CAST "Yes");

	xmlNewChild(node, NULL, BAD_CAST "Macid", BAD_CAST Buff[6]);

	xmlNewChild(node, NULL, BAD_CAST "UbootImageName", BAD_CAST Buff[43]);
	xmlNewChild(node, NULL, BAD_CAST "KernelImageName", BAD_CAST Buff[44]);
	xmlNewChild(node, NULL, BAD_CAST "RootfsImageName", BAD_CAST Buff[45]);

	if( strlen(Buff[2]) != 0 && strstr(Buff[2],"ERROR") == NULL)
	{
		xmlNewChild(node, NULL, BAD_CAST "IMEInumberExists", BAD_CAST "Yes");
		xmlNewChild(node, NULL, BAD_CAST "IMEInumber", BAD_CAST Buff[2]);
	}
	else 
	{
		xmlNewChild(node, NULL, BAD_CAST "IMEInumberExists", BAD_CAST "Error");
		xmlNewChild(node, NULL, BAD_CAST "IMEInumber", NULL);
	}
	xmlNewChild(node, NULL, BAD_CAST "UIDExists", BAD_CAST "Yes");
	xmlNewChild(node, NULL, BAD_CAST "UID", BAD_CAST Buff[5]);

	if( CONFIG.IrisRDVer_and_SNo )
	{
		if( strlen(Buff[12]) != 0 && strstr(Buff[12],"ERROR") == NULL)
		{
			xmlNewChild(node, NULL, BAD_CAST "IritechSnoExists", BAD_CAST "Found");
			xmlNewChild(node, NULL, BAD_CAST "IritechSno", BAD_CAST Buff[12]);
		}
		else 
		{
			xmlNewChild(node, NULL, BAD_CAST "IritechSnoExists", BAD_CAST "NotFound");
			xmlNewChild(node, NULL, BAD_CAST "IritechSno", NULL );
		}
	}
	if( CONFIG.PinpadSN )
	{
		if( strlen(Buff[50]) != 0 && strstr(Buff[50],"ERROR") == NULL)
		{
			xmlNewChild(node, NULL, BAD_CAST "PinpadSNExists", BAD_CAST "Found");
			xmlNewChild(node, NULL, BAD_CAST "PinpadSN", BAD_CAST Buff[50]);
		}
		else 
		{
			xmlNewChild(node, NULL, BAD_CAST "PinpadSNExists", BAD_CAST "NotFound");
			xmlNewChild(node, NULL, BAD_CAST "PinpadSN", NULL );
		}

	}
	if( CONFIG.BarcodeSno )
	{
		if( strlen(Buff[37]) != 0 && strstr(Buff[37],"ERROR") == NULL)
		{
			xmlNewChild(node, NULL, BAD_CAST "BarcodeSnoExists", BAD_CAST "Found");
			xmlNewChild(node, NULL, BAD_CAST "BarcodeSno", BAD_CAST Buff[37]);
		}
		else 
		{
			xmlNewChild(node, NULL, BAD_CAST "BarcodeSnoExists", BAD_CAST "NotFound");
			xmlNewChild(node, NULL, BAD_CAST "BarcodeSno", NULL);
		}
	}
	if( strlen(Buff[35]) != 0 && strstr(Buff[35],"ERROR") == NULL)
	{
		xmlNewChild(node, NULL, BAD_CAST "GSMVersionExists",BAD_CAST "Yes");
		xmlNewChild(node, NULL, BAD_CAST "GSMVersion",BAD_CAST Buff[35]);
	}
	else 
	{
		xmlNewChild(node, NULL, BAD_CAST "GSMVersionExists", BAD_CAST "Error");
		xmlNewChild(node, NULL, BAD_CAST "GSMVersion",NULL );
	}
	if( access("/etc/autoapn/autoapn_config.xml",F_OK) == 0 )
	{
		if( strlen(Buff[36]) != 0 && strstr(Buff[36],"ERROR") == NULL)
		{
			xmlNewChild(node, NULL, BAD_CAST "GSM_ModuleExists",BAD_CAST "Yes");
			xmlNewChild(node, NULL, BAD_CAST "GSM_Module",BAD_CAST Buff[36]);
		}
		else 
		{
			xmlNewChild(node, NULL, BAD_CAST "GSM_ModuleExists",BAD_CAST "Error");

			xmlNewChild(node, NULL, BAD_CAST "GSM_Module", NULL);
		}
	}
	if( CONFIG.WSSN)
	{
		if( strlen(Buff[14]) != 0 && strstr(Buff[14],"ERROR") == NULL)
		{
			xmlNewChild(node, NULL, BAD_CAST "WSSNExists", BAD_CAST "Found");
			xmlNewChild(node, NULL, BAD_CAST "WSSN", BAD_CAST Buff[14]);
		}
		else 
		{
			xmlNewChild(node, NULL, BAD_CAST "WSSNExists", BAD_CAST "NotFound");
			xmlNewChild(node, NULL, BAD_CAST "WSSN", NULL);
		}
	}
	/*	if( CONFIG.CamType )
		{
		xmlNewChild(node, NULL, BAD_CAST "CamTypeExists", BAD_CAST Buff[1]);
		if(strlen(module.CamTypeExists,"Found") == 0 )
		xmlNewChild(node, NULL, BAD_CAST "CamType", BAD_CAST Buff[1]);
		else 
		xmlNewChild(node, NULL, BAD_CAST "CamType", NULL);
		}*/
	if( strlen(Buff[18]) != 0 && strstr(Buff[18],"ERROR") == NULL)
	{
		xmlNewChild(node, NULL, BAD_CAST "FPScanneridExists", BAD_CAST "Yes");
		xmlNewChild(node, NULL, BAD_CAST "FPScannerid", BAD_CAST Buff[18]);
	}
	else 
	{
		xmlNewChild(node, NULL, BAD_CAST "FPScanneridExists", BAD_CAST "No");
		xmlNewChild(node, NULL, BAD_CAST "FPScannerid", NULL );
	}
	/*xmlNewChild(node, NULL, BAD_CAST "HardwareIDExists", BAD_CAST Buff[1]);
		if ( strlen(module.HardwareIDExists,"Yes") == 0 )
		xmlNewChild(node, NULL, BAD_CAST "HardwareID", BAD_CAST Buff[1]);
		else 
		xmlNewChild(node, NULL, BAD_CAST "HardwareID", NULL );
		*/
	xmlSaveFormatFileEnc(Hardware_Status_file, doc, "UTF-8", 1);

	xmlFreeDoc(doc);

	xmlCleanupParser();

	return 0;
}
