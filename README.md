# Smart-Door-Bell





Recently my home doorbell stopped working so I decided to fix it and make the doorbell smarter. This project  takes advantage of the represented state transfer (REST) architecture using PHP, python, HTML, MYSQL database,Linux, and  REST application programing interface (API)s available on the Arduino Yun. Basically, an app on the user mobile smart phone constantly ping the server on the Arduino Yun and check if the button is press via a javascript object notation table (JSON ) . If the JSON table returns a 1 it will send a notification to the phone telling the user if some are at the front or back door. Also, the Arduino microcontroller will play a sound doorbell sound off an SD card using an amplifier to let the user know someone rang the doorbell. I also  used a radio FM transmitter and a receiver to allow the server to be mobile independent of the speaker. This project is still being developed.
