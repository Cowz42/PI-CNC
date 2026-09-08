
if [[ $(/usr/bin/id -u) -ne 0 ]]; then
    echo "Not running as root"
    exit
fi

echo "Stopping and removing background service"


systemctl disable pi-cnc-service.service
systemctl stop pi-cnc-service.service


rm /etc/systemd/system/pi-cnc-service.service
rm /usr/sbin/pi-cnc-service-exec