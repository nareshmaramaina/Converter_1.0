#include <sys/file.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include<sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <termios.h>
#include <net/if.h>
#include<unistd.h>
#include<termios.h>
#include<errno.h>
#include <netdb.h> 
#include <resolv.h>
#include <sys/types.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <dirent.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <dlfcn.h>

#define TEST_REAL 0
#define OPTICAL 1
#define CAPACITIVE 2
#define NO_DEVICE 3
#define FIRMWARE 1
#define APPLICATION 2
struct rhms
{
	short int DOT;
	short int BatteryInfo;
	short int Iris_or_Biomat;
	short int IrisRDVer_and_SNo;
	short int geo_location;
	short int CamType;
	short int WSSN;
	short int Pinpad;
	short int PinpadSN;
	short int FPSRDVer;
	short int GPS;
	short int BarcodeSno;
	short int BiomRDVer;
	short int Bluetooth;
	short int SAM1;
	short int SAM2;
	short int Printer;
	short int WIFI;
	short int IFD1;
	short int IFD2;
	short int Camera;
	short int Two_Simdetails_Autoapn;

}CONFIG;


char DOT_FILE[64];

typedef struct Memory
{
	char Total[16];
	char Use[16];
	char Free[16];
}MEMORY;

typedef struct device 
{
	char Longitude[24];
	char Latitude[24];
	char Captured_Time[24];
}Location;
struct Device_on_time 
{
	char Date[14];
	char Slot1[12];
	char Slot2[12];
	char Slot3[12];
	char Slot4[12];
};

struct device_battery 
{
	char Date[14];
	char Day_worked_mins[12];
	char Day_adapter_mins[12];
	char Day_charged_mins[12];
	char Day_discharged_mins[12];
};
struct terminal_status
{
	char HardwareID[30];
	char HardwareIDExists[12];
	char TerminalIDExists[12];
	char MacidExists[12];
	char IMEInumberExists[12];
	char UIDExists[12];
	char IritechSnoExists[12];
	char PinpadSNExists[12];
	char BarcodeSnoExists[12];
	char GSMVersionExists[12];
	char GSM_ModuleExists[12];
	char WSSNExists[12];
	char CamTypeExists[12];
	char FPScanneridExists[12];
	char SIM1CCIDnumberExists[12];
	char SIM2CCIDnumberExists[12];
	char RHMSClientVersion[22];
	char AutoapnAppVersion[12];
	char FingerRDServiceStatus[12];

	char BarcodeSno[32];
	char CamType[20];
	char Comm[12];
	//	char GeoLocation[80];
	//char IRIS_VERSION[12];
	//	char LIB_BIO[10];
	//	char IRIS_ID[16]; 
	//	char HWChanged[12];
	char IRIS[32];
	char IritechRDVer[10];
	char IritechSno[24];
	char BiomRDVer[10];
	char WSSN[32];
	char pinpad[32];
	char PinpadSN[64];
	char FPSRDVer[10];
	char IFD1[20];
	char IFD2[20];
	char SAM1[20];
	char SAM2[20];
	char Bluetooth[15];
	char Printer[10];
	char paper[15];
	char scanner_id[40];
	char FP_TYPE[20];
	char Camera[10];
	char WIFI[10];
	char Date_time[20];
	char macid[20];
	char RTC[10];
	char Date[40];
	char GSM_Version[50];
	char Battery_status[20];
	char BatteryVoltage[10];
	char Adapter[30];
	char ethernet[20];

	char Sim2CCID[50];
	char operator1_name[20];
	char operator2_name[20];
	char Sim1_db[12];
	char Sim2_db[12];
	char SIM1SignalMode[12];
	char SIM2SignalMode[12];

	char GSM_Module[64];
	char CCID[50];
	char UsbdeviceExists[10];
	char ExternalMemExists[10];
	MEMORY	InternalMem_Sysuser;
	MEMORY	InternalMem_Jffs2;
	MEMORY	RAM;
	MEMORY	ExternalMem;
	MEMORY	Usbdevice;
	MEMORY	System_memory;
	Location GPS;
	struct Device_on_time DOT; 
	struct device_battery BatteryInfo; 

	char AUDIO[20];
	char IMEI_no[40];
	char TerminalID[50];
	char SerialNo[50];
	char Uid_no[40];
	char UbootVersion[50];
	char KernelVersion[50];
	char rootfs_details[50];
	char FirmwareVersion[10];
	char FirmwareName[128];
}module;


int Pos_Details( void );


int patch(void);
int get_machineid(char *);
void get_device_serialnumber(void);
void update_macid_details(void);
int get_app_details(void);
int battery_status(void);
int Ethernet_status(void);
int paper_status(void);
void printer_status(void);
int sam_status(int);
int Wifi_Status(void);
int dev_details(void);
int OS_Details(void);
int FirmwareDetails(void);
int patch_name(void);
int internal_memory_status(void);
int update_sdcard_info(void);
int update_usb_info(void);
int update_ram_info(void);
int gprs_details(void);
int xml_frame(void);
int remote_server_update();
int Parsing_ACK_from_Server(void);
int battery_status(void);
int gl11_gsm_operator_name(char *);
int gl11_gsm_firmware_version(char *);
int run_io_health_status(void);
void optical_scanner_id(void);
void capacitive_scanner_id(void);
int server_updation(void);
int sim_operator_name(void);
int read_revision_operator_details(char *,char*);
int retrieve_signal_details(char *,char *);
void Check_and_Set_Operator_name(char *);
int create_xml_file(void);
int is_rhms_details_updated(void);
int update_date_status_file(void);
int usb_device_presence(char *,char *);
int update_pendrive_details(void);
int Get_Wifi_Status(void);
int check_status();
int camera_status(void);
int ifd_status(int);
int Send_to_Server( void );
int  get_project_details(char *server_ip, char *port_num, char *Project_name);
int audio_test(void);
int fp_type(void);
int bluetooth_status(void);
int opt_scanner_id(char *);
int cap_scanner_id(char *);
int Check_Physical_Existence(void);
int update_fp_scanner_info(void);
int Send_Hardware_status_to_server (void);
int copy_file (char *dest,char *src);
int update_internal_memory_info(void);
int Get_Ethernet_Status(void);
void update_fpfile_info(void);
int  check_presence(int times);
int fp_detect_type(void);
int iris_status(void);
void library_check(void);
void pinpad_status(void);
void Iris_version(void);
void Iris_Scanner_Id(void);
void attendence_record(void);
int  Device_work_records(void);
void weighing_serialid_details(void);
void FPS_RD_version();
void get_bluetooth_macid(char *);
int  GPS_info(char *);
int PINPAD_ModemOpen(char * );
int  (*PINPAD_Modemclose) (void);
int (*handshake)(void);
int (*Get_Pinpad_Serial_No)(unsigned char *);
int (*print_error_resp) (int );
int   PinpadSerialNo_info_by_dev_name(char *);
void Camera_info(void);
int parse_remote_staus_xml ();
void Uid_info(void);
int get_logname(char *file);
int retrieve_sim_details(char *ccid_buff,char *imei_buff);
int mkdir_p(char *dirname);
void Hardware_changed_info();
int Is_Hardware_changed(char *docname);
void Get_autoapn_wrote_details();
int Get_Two_Simdetails_info(void);
int read_two_revision_operator_details(char *operator1,char *operator2,char *revision_buff);
int retrieve_two_signal_details(char *SIM1,char *SIM2);
int retrieve_two_sim_details(char *ccid_buff,char *imei_buff,char *ccid1_buff);
void	POS_HEALTH_DETAILS(void);
void 	IMAGES(void);
int  PERIPHERALS(void);
void 	DEVICE_DETAILS();
int parse_config_file (xmlDocPtr doc, xmlNodePtr cur) ;
int Get_Config_Settings();
void check_net_connection();
int Check_internet_by_hostname(char *host,char *);
int Autoapn_xmlparse(char *);
int is_RHMS_multiple_run();
int RTC_info_and_Check_RHMS_run();
int get_Usb_device_serialno(char *Vendorid,char *ProductId,char *serialno);
void  barcode_SerialNo();
void xml_type_Autoapn_details();
void Non_xml_type_Autoapn_details();
int gl11_bluetooth_control_dlopen(int arg);
void Update_Comm_media(char *ip);
int Get_interface_name(char *interface,char *);
int Check_internet_by_hostname(char *host,char *ip);
void Biomatiques_RD_version();
int  GeoLocation_info(char *file);
void FPS_Id_and_version();
int  Location_info();
void SerialNo_and_Version_Based_Tags();
void Periodic_tags(void);
void Second_Time_Health_Info_sending_for_GPS();
void reboot_device(char last_digit); 
int  Get_Server_Addr(char *Server_Addr);
int 	create_Hardware_status_xml_file();
int 	create_BootTime_Status_xml_file();
int create_Health_Status_xml_file();
int Is_Hardware_Status_changed();
int Applications_Details();
int Update_Simdb_and_Signalmode();
int Get_Device_Applications_Count();
int server_BootTime_updation();
int  server_Hardware_Status_updation();
int  server_Periodic_Health_updation();
void update_Periodic_Health_status_date_file();
void update_BootTime_status_date_file();
void update_Hardware_status_date_file();
void RTC_info();
void Update_Current_Date_with_Time();
void Get_Current_Date(char *Date);
int rhms_lock();
int Update_request(int request); // arg 1 For Hardware request,arg 2 For BootTime request, arg 3 For Periodic Health request
int parseDoc(char *docname) ;

int  Update_Configured_Server_Addr();
int Send_BootTime_status_to_server (void);
int Send_Periodic_Health_status_to_server (void);
int Get_Sim_num();
void Check_and_Set_Operator_name(char *operator_buff);
int Check_RHMS_All_requests_run(int *Hardware_run,int *BootTime_run,int *Periodic_run);
int Can_i_reboot();
void FingerRDServiceStatus();
void AutoapnAppVersionDetails();
int Get_Total_Server_Apps();
int Device_App_info_Details(char *Device_Application_release_file,char *DeviceApplicationType,char *DeviceApplicationName,float *DeviceApplicationVersion );
int Check_apps(const char *file);
void Running_Apps_Details(int Total_Device_Running_Apps, xmlNodePtr Runningchildnode);
int Get_Total_Device_Apps();
void HardwareID_Details();
int Get_Tokens_of_FirmwarePatchfile(char *file,char *FirmwareName,float *Version);
int Get_Tokens_of_ApplicationPatchfile(char *file,char *ApplicationType,char *ApplicationName,float *Version);

int Downloaded_DateAndTime_Version_Details(char *DownloadCompletedFile,float *DownloadedVersion,char *Downloaded_DateAndTime);
int Get_Total_Downloaded_Updates(int type);
int FirmwareDownloadsDetails(int TotalFirmwareDownloads,xmlNodePtr childnode);
int ApplicationDownloadsDetails(int TotalApplicationDownloads,xmlNodePtr childnode);
void RHMSAppVersionDetails();
int Hardware_xml_frame();
int BootTime_Status_xml_frame();
int Health_Status_xml_frame();
