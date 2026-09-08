

if [[ $(/usr/bin/id -u) -ne 0 ]]; then
    echo "Not running as root"
    exit
fi


echo "Installing background service"


systemctl disable pi-cnc-service.service
systemctl stop pi-cnc-service.service



cp ./build/pi-cnc-service-exec /usr/local/sbin/pi-cnc-service-exec
cp ./service/pi-cnc-service.service /etc/systemd/system/pi-cnc-service.service



systemctl daemon-reload

systemctl start pi-cnc-service.service
systemctl enable pi-cnc-service.service
