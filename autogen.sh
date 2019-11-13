#!/bin/bash

echo Generando codigo objeto para servidor de notificaciones

cd ./ServidorNotificaciones
make clean 
make
echo ejecutando Servidor de Notificaciones
gnome-terminal  -e "bash -c ./servidor;bash"\

cd ../ServidorAlertas
make clean
make
echo ejecutando Servidor de ServidorAlertas
gnome-terminal -e "bash -c ./servidor;bash"\

cd ../Cliente
make clean
make
echo ejecutando Cliente
gnome-terminal -e "bash -c ./cliente;bash"\



cd ..


