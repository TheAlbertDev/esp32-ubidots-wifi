# Arduino + ESP32 + Wi-Fi + Ubidots

## Requeriments

### :computer: Board drivers

- [Arduino-ESP32](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)

> Installation instructions of ESP32 boards using the Board Manager [:link:](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)

### :books: Libraries:
 
- [UbidotsEsp32Mqtt](https://github.com/ubidots/esp32-mqtt)
- [PuSubClient](https://github.com/knolleary/pubsubclient)

> Installation instructions of Arduino libraries [:link:](https://www.arduino.cc/en/guide/libraries)

## Getting started

### :warning: Personal credentials

The code needs the Wi-Fi credentials and your Ubidots token to operate. These are sensitive data that must not be shared with anyone. For this reason, the file containing this information must not be committed.

The sensitive data must be added to a file called `private_data.h` in the root of the project. This file is in the `.gitignore` file and will not be committed.

A `private_data.template.h` file is provided with the variables to be initialized. Rename this file `private_data.h` and fill it with your personal data.

# License

This code is released under the [MIT License](./LICENSE).