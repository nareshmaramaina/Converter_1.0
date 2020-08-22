if test $1
then
	if [ ! -d $1 ]
	then
		echo "$1 Directory Not Found"
		exit 1
	fi
	cd  $1

else 
	echo give Project path
	exit 0
fi

sed '/#Health/d' * -i > /dev/null 2>&1
sed '/#END/d' * -i > /dev/null 2>&1
i=0
j=0
k=0
l=0
for line in $(ls )
do
	if [ -d $line ]
	then
		echo "Skipping Because Direcory"
		continue	
	fi

	Converter_BootHardwareHealthxml $line 
	if [ -f /opt/Hardware_Status.xml ]
	then

		curl  --cacert /vision/curl-ca-bundle.crt  -XPOST -H "content-type: application/xml" https://rhms2.callippus.co.uk/api/HardwareStatus -d @/opt/Hardware_Status.xml > /opt/Hardware_response.xml 2>&1
		grep "<Units>" /opt/Hardware_response.xml -q
		if [ $? -ne 0 ]
		then 
			Fail=$Fail,$line
			tput bold ; tput setaf 1;
			echo "$line request 1 failure"
			tput sgr0
		else 
			i=$(expr $i + 1)
			echo "$line request 1 Success"
		fi	

	else echo " $line /opt/Hardware_Status.xml file not found"

	fi
	if [ -f /opt/BootTime_Status.xml ]
	then
		curl --cacert /vision/curl-ca-bundle.crt https://rhms2.callippus.co.uk/api/ApplicationStatus?serialNo=$line  > /opt/Application_response.xml
		curl --cacert /vision/curl-ca-bundle.crt https://rhms2.callippus.co.uk/api/FirmwareStatus?serialNo=$line  > /opt/Firmware_response.xml
		sed -i '/\/BootStatus/d' /opt/BootTime_Status.xml
		AppsData=$(xmllint --format /opt/Application_response.xml  | sed 's:ApplicationStatusResponse:Application:g' | sed '/ApplicationURL/d' | sed '/ProjectName/d' |  sed 's:ArrayOfApplication:ArrayOfApplications:g' | sed '/xml/d')
		Running_AppsData=$(echo "<ArrayOfApplications>\n$AppsData" | sed 's:ArrayOfApplications:ArrayOfRunningApplications:g')
		FirmwareData=$(xmllint  --format /opt/Firmware_response.xml  | egrep "FirmwareName|Version" | head -2 | sed 's:Version:FirmwareVersion:g')
		echo "<ArrayOfApplications>\n$AppsData\n$Running_AppsData\n$FirmwareData\n</BootStatus>"	>> /opt/BootTime_Status.xml	
		curl --cacert /vision/curl-ca-bundle.crt -XPOST -H "content-type: application/xml" https://rhms2.callippus.co.uk/api/BootTimeStatus -d @/opt/BootTime_Status.xml > /opt/BootTime_response.xml 2>&1
		grep "<Units>" /opt/BootTime_response.xml -q
		if [ $? -ne 0 ]
		then 
			tput bold ; tput setaf 1;
			echo "$line request 2 failure"
			tput sgr0
		else 
			j=$(expr $j + 1)
			echo "$line request 2 Success"
		fi	
	else echo "$line /opt/BootTime_Status.xml  file not found"
	fi
	if [ -f /opt/Health_Status.xml ]
	then
		curl  --cacert /vision/curl-ca-bundle.crt -XPOST -H "content-type: application/xml" https://rhms2.callippus.co.uk/api/HealthStatus -d @/opt/Health_Status.xml > /opt/Health_response.xml	2>&1
		grep "<Units>" /opt/Health_response.xml -q
		if [ $? -ne 0 ]
		then 
			tput bold ; tput setaf 1;
			echo "$line request 3 failure"
			tput sgr0
		else 
			k=$(expr $k + 1)
			echo "$line request 3 Success"
		fi	
	else echo "$line /opt/Health_Status.xml file not found"
	fi
	l=$(expr $l + 1)
	echo "Device Run count = $l"
done
echo "Fail Devices = $Fail"
echo "Total Devices count = $l"
echo "Total Hardware request Success run count = $i"
echo "Total BootTime request Success run count = $j"
echo "Total Health   request Success run count = $k"
echo "Total Hardware request Fail run count = $(expr $l - $i)"
echo "Total BootTime request Fail run count = $(expr $l - $j)"
echo "Total Health   request Fail run count = $(expr $l - $k)"
