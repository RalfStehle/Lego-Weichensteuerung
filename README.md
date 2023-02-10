<h2>Lego-Weichensteuerung</h2>
Lego Weichen fernsteuern mit GeekServo und Arduino ESP32<br>
Steuerung über Bluetooth Low Energy:<br> 
0x31 (= 1) für Weiche 1<br>
0x32 (= 2) für Weiche 2<br>
<br>
<h3>Benötigte Hardware</h3>
<A HREF="https://eu.robotshop.com/de/products/geekservo-2kg-360-degrees-compatible-w-lego" target="_blank">geekservo</A><br>
<A HREF="https://www.az-delivery.de/pages/search-results-page?q=ESP-32%20Dev%20Kit%20C%20V4" target="_blank">ESP-32 Dev Kit C V4</A><br>
<br>
<h3>Arduino-Sketch</h3>
<A HREF="https://github.com/RalfStehle/Lego-Weichensteuerung/blob/main/Sketch_Ble_Remote.ino" target="_blank">Sketch_Ble_Remote.ino</A><br>
Wichtig: Um Servos mit ESP32-Board zu betreiben, benötigt man eine zusätzliche Bibliothek.<br> 
Ich benutze die <A HREF="https://github.com/RoboticsBrno/ServoESP32" target="_blank">ServoESP32 von RoboticsBrno</A><br>
Leider funktioniert diese nicht mit dem neuen Board von Seeed Xiao Esp32<br>
<br>
<h3>Aufbau der Weichensteuerung</h3>
<br>
<div>
    <img src="https://github.com/RalfStehle/Lego-Weichensteuerung/blob/main/1.png" title="" height= "300" alt="" style="margin:5px" align="left">
    <img src="https://github.com/RalfStehle/Lego-Weichensteuerung/blob/main/2.png" title="" height= "300" alt="" style="margin:5px" align="left">
</div>
<br>
<div>
    <img src="https://github.com/RalfStehle/Lego-Weichensteuerung/blob/main/3.png" title="" height= "300" alt="" style="margin:5px" align="left">
    <img src="https://github.com/RalfStehle/Lego-Weichensteuerung/blob/main/4.png" title="" height= "300" alt="" style="margin:5px" align="left">
</div>
<br>
<div>
    <img src="https://github.com/RalfStehle/Lego-Weichensteuerung/blob/main/5.png" title="" height= "300" alt="" style="margin:5px" align="left">
    <img src="https://github.com/RalfStehle/Lego-Weichensteuerung/blob/main/6.png" title="" height= "300" alt="" style="margin:5px" align="left">
</div>
<br>
<div>
    <img src="https://github.com/RalfStehle/Lego-Weichensteuerung/blob/main/7.png" title="" height= "300" alt="" style="margin:5px" align="left">
    <img src="https://github.com/RalfStehle/Lego-Weichensteuerung/blob/main/8.png" title="" height= "300" alt="" style="margin:5px" align="left">
</div>
