


echo "Stopping and removing background service"

systemctl stop pi-cnc-server-io-service.service
systemctl disable pi-cnc-server-io-service.service
