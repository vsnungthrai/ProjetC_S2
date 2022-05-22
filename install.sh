#/bin/bash

RES=$(dpkg -l | egrep '^ii +libsdl2-dev')
if [ ! -z "$RES" ]; then
    echo""
    echo "Le paquet libsdl2-dev est installé"

    RES=$(dpkg -l | egrep '^ii +libsdl2-ttf-dev')
    if [ ! -z "$RES" ]; then
        echo "Le paquet libsdl2-ttf-dev est installé"

        RES=$(dpkg -l | egrep '^ii +libsdl2-image-dev')
        if [ ! -z "$RES" ]; then
            echo "Le paquet libsdl2-image-dev est installé"
            
            RES=$(dpkg -l | egrep '^ii +libsdl2-mixer-dev')
            if [ ! -z "$RES" ]; then
                echo "Le paquet libsdl2-mixer-dev est installé"
                echo ""
                echo -e "\e[31mVous pouvez maintenant lancer le programme : \e[1m./run\e[0m"
                chmod 777 run
                echo""
                exit 0
            fi

        fi

    fi

fi

echo "Installation en cours ..."
sudo apt-get install libsdl2-dev -y >/dev/null
sudo apt-get install libsdl2-ttf-dev -y >/dev/null
sudo apt-get install libsdl2-image-dev -y >/dev/null
sudo apt-get install libsdl2-mixer-dev -y >/dev/null
echo ""
echo "Installation effctuée"
echo ""
echo -e "\e[31m Vous pouvez maintenant lancer le programme : ./run\e[0m"
exit 0
