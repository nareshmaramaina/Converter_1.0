#include <libxml/tree.h>
#include <libxml/parser.h>
#include <header.h>

int parse_config_file (xmlDocPtr doc, xmlNodePtr cur) 
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;


	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"DOT"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.DOT =atoi((char*)key);
			fprintf(stdout,"DOT:%d\n", CONFIG.DOT);
			xmlFree(key);
		}

		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"BatteryInfo"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.BatteryInfo =atoi((char*)key);
			fprintf(stdout,"BatteryInfo:%d\n", CONFIG.BatteryInfo);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Iris_or_Biomat"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.Iris_or_Biomat =atoi((char*)key);
			fprintf(stdout,"Iris_or_Biomat:%d\n", CONFIG.Iris_or_Biomat);
			xmlFree(key);
		}

		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"IrisRDVer_and_SNo"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.IrisRDVer_and_SNo =atoi((char*)key);
			fprintf(stdout,"IrisRDVer_and_SNo:%d\n", CONFIG.IrisRDVer_and_SNo);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"geo_location"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.geo_location =atoi((char*)key);

			fprintf(stdout,"geo_location:%d\n", CONFIG.geo_location);
			xmlFree(key);
		}


		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"CamType"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.CamType =atoi((char*)key);
			fprintf(stdout,"CamType:%d\n", CONFIG.CamType);
			xmlFree(key);
		}


		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"BiomRDVer"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.BiomRDVer =atoi((char*)key);
			fprintf(stdout,"BiomRDVer:%d\n", CONFIG.BiomRDVer);
			xmlFree(key);
		}


	/*	else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"BiomSno"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.BiomSno =atoi((char*)key);
			fprintf(stdout,"BiomSno:%d\n", CONFIG.BiomSno);
			xmlFree(key);
		} */


		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"WSSN"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.WSSN =atoi((char*)key);
			fprintf(stdout,"WSSN:%d\n", CONFIG.WSSN);
			xmlFree(key);
		}

		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Pinpad"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.Pinpad =atoi((char*)key);
			fprintf(stdout,"Pinpad:%d\n", CONFIG.Pinpad);
			xmlFree(key);
		}

		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"PinpadSN"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.PinpadSN =atoi((char*)key);
			fprintf(stdout,"PinpadSN:%d\n", CONFIG.PinpadSN);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"FPSRDVer"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.FPSRDVer =atoi((char*)key);
			fprintf(stdout,"CONFIG.FPSRDVer:%d\n", CONFIG.FPSRDVer);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"GPS"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.GPS =atoi((char*)key);
			fprintf(stdout,"GPS:%d\n", CONFIG.GPS);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"BarcodeSno"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.BarcodeSno =atoi((char*)key);
			fprintf(stdout,"BarcodeSno:%d\n", CONFIG.BarcodeSno);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Bluetooth"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.Bluetooth =atoi((char*)key);
			fprintf(stdout,"Bluetooth:%d\n", CONFIG.Bluetooth);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"SAM1"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.SAM1 =atoi((char*)key);
			fprintf(stdout,"SAM1:%d\n", CONFIG.SAM1);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"SAM2"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.SAM2 =atoi((char*)key);
			fprintf(stdout,"SAM2:%d\n", CONFIG.SAM2);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Printer"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.Printer =atoi((char*)key);
			fprintf(stdout,"Printer:%d\n", CONFIG.Printer);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"WIFI"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.WIFI =atoi((char*)key);
			fprintf(stdout,"WIFI:%d\n", CONFIG.WIFI);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"IFD1"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.IFD1 =atoi((char*)key);
			fprintf(stdout,"IFD1:%d\n", CONFIG.IFD1);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"IFD2"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.IFD2 =atoi((char*)key);
			fprintf(stdout,"IFD2:%d\n", CONFIG.IFD2);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Camera"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.Camera =atoi((char*)key);
			fprintf(stdout,"Camera:%d\n", CONFIG.Camera);
			xmlFree(key);
		}
		else  if ((!xmlStrcmp(cur->name, (const xmlChar *)"Two_Simdetails_Autoapn"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(key)	
			CONFIG.Two_Simdetails_Autoapn =atoi((char*)key);
			fprintf(stdout,"Two_Simdetails_Autoapn:%d\n", CONFIG.Two_Simdetails_Autoapn);
			xmlFree(key);
		}
		cur = cur->next;
	}

	return 0;
}
int Get_Config_Settings()
{
	char *docname="/etc/.RHMS_config.xml"; 
	xmlDocPtr doc;
	xmlNodePtr cur;

	if ( access(docname,F_OK) != 0 )
	{
		fprintf(stderr," %s settings file not found\n",docname);
		return -1;
	}

	doc = xmlParseFile(docname);


	if (doc == NULL ) {
		fprintf(stderr," %s Document not parsed successfully. \n",docname);
		return -1;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) 
	{
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return -1;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "RHMS_Settings")) {
		fprintf(stderr," %s document of the wrong type, root node != story",docname);
		xmlFreeDoc(doc);
		return -1;
	}


	parse_config_file (doc, cur);

	xmlFreeDoc(doc);
	return 0;
}

