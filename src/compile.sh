gcc -I ../include create_BootTime_Status_xml.c  create_Hardware_status_xml.c  create_Health_status_xml.c  main.c  parse_rhms_config.c -lxml2 -o Converter_BootHardwareHealthxml

