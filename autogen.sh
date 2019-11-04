#!/bin/bash

echo Generando codigo objeto para servidor de notificaciones

cd ./ServidorNotificaciones
make clean 
make
echo ejecutando Servidor de Notificaciones
mate-terminal ./servidor

cd ../ServidorAlertas
make clean
make
echo ejecutando Servidor de ServidorAlertas
mate-terminal ./servidor

cd ../Cliente
make clean
make
echo ejecutando Cliente
gnome-terminal sh cliente



cd ..
