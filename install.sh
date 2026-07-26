


echo "Installing background service"
echo "Needs sudo and I forgot how to check"

systemctl disable pi-cnc-service.service
systemctl stop pi-cnc-service.service



cp ./build/pi-cnc-service-exec /usr/bin/pi-cnc-service-exec
cp ./service/pi-cnc-service.service /etc/systemd/system/pi-cnc-service.service



systemctl daemon-reload

systemctl start pi-cnc-service.service
systemctl enable pi-cnc-service.service
