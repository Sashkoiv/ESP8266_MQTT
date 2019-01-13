# ESP8266_MQTT
A set of firmware packs for ESP8266 modules which utilizing MQTT interface could be controlled or controll different house stuff so that to make it a kind of cheap Smart House solution.

## Used links
[![bitluni's lab](https://img.shields.io/badge/bitluni's-lab-800000.svg)](http://bitluni.net/simple-mqtt-broker-setup-on-a-raspberry-pi/)
[![knolleary](https://img.shields.io/badge/knolleary-pubsubclient-568203.svg)](https://github.com/knolleary/pubsubclient)

## Instruction

* Update packages list
    ```sh
    sudo apt-get update
    sudo apt-get install mosquitto
    ```

* Check an IP address of your device - it would be the IP of the Mosquitto server
    ```sh
    ifconfig
    ```

* To add the first user's credentials:
    ```sh
    cd /etc/mosquitto
    sudo mosquitto_passwd -c passwordfile [username]
    ```

* Append another user to the `passwordfile`
    ```sh
    sudo mosquitto_passwd -b passwordfile user password
    ```

* To remove a user from the `passwordfile`
    ```sh
    sudo mosquitto_passwd -D passwordfile user
    ```

* After the passwordfile is created it's needed to disable anonymous access and add the file path to mosquitto.conf
    ```sh
    sudo nano mosquitto.conf
    ```
    Paste follow text by pressing `Ctrl+Shift+V` or `Shift+Ins` on your PC.
    ```sh
    allow_anonymous false
    password_file /etc/mosquitto/passwordfile
    ```
    To save and exit press `Ctrl+O` => `y` => `Enter` => `Ctrl+X`

* To run the listener run (to stop is press `Crtl+C`)
    ```sh
    mosquitto_sub -v -t 'topic'
    ```
* To publish a message for test run
    ```sh
    mosquitto_pub -t 'topic' -m 'helloWorld'
    ```

* It may not be working from the first try. Then is needed to check if the server is running
    ```sh
    sudo systemctl status mosquitto.service
    ```
    or just run it in the terminal
    ```sh
    mosquitto
    ```
