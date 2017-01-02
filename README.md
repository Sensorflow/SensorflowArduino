Sensorflow
==========
Today there are a lot of types of sensors and every type works in a different way.
Sensorflow is an interface for all these sensors, like a plug&play.

You want a temperature sensor? Just plug it and fun! Don't waste time searching how
every sensor works.

Also you get some other benefits when using Sensorflow:
 * Energy save: The device goes to sleep when needed
 * Bidirectional communication: You sensor can be passive (you read the sensor when you want) and active, the sensor notifies you when something happens.
 * Device detection: Know when a sensor is plugged or unplugged (like usb). There is an extra state, ONLINE which means that the devices is plugged and ready.
 * Long range communication: thanks to rs485 you will not have distance problems. You can even reuse your "ethernet cables"
 * Easily expandable: You can build your custom commands and process it in your favourite language because the communication is done with
 protocol buffers.

How it works
============
Basically you have one arduino per sensor. The arduino acts like a proxy between the real sensor and you. But you are not limited to use only one
sensor, you can connect all sensors you want to your arduino but in your sensor network it will appears like only one sensor. A bit confusing, lets
see it with an example.

Basic example
-------------
You want to monitorize the temperature of a room. Then you get a DHT sensor and an arduino mini pro (most compact). Just wire the DHT sensor
to the arduino, upload the sensorflow sketch and it is done! Now you can read your sensor from python or whatever you want.

Complex example
---------------
You want to monitorize a solar panel, the temperature and the illuminance. In this case you can use a DHT and BH1750 sensors. Like in the basic
example, just wire the sensor to arduino and upload the sketch. Now you have merged these two sensors into one sensorflow device. Once you connect
this sensor to your network, you will be able to query to this sensor two values, the temperature and the illuminance. But rememeber, you are using
the sensorflow interface so you dont care about how to read the sensor. I an future, you could replace the DHT sensor for other type of sensor and noone will notice the change.
