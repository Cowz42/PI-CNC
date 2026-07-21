


echo "Installing background service"
echo "Needs sudo and I forgot how to check"


cp ./service/pi-cnc-server-io-service.service /etc/systemd/system/pi-cnc-server-io-service.service
cp ./build/pi-cnc-service-exec /usr/bin/pi-cnc-service-exec

systemctl daemon-reload

systemctl start pi-cnc-server-io-service.service
systemctl enable pi-cnc-server-io-service.service
