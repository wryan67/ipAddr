ipAddr
-----

Display the raspberry pi's host name and ip address on an LCD1602 display

### Prerequisites

* Install the lcd1602 driver by following the instructions here:
  https://github.com/wryan67/lcd1602_rpi_lib

### Cloneing

Use your favorite github cloning tool or this command line:

    $ git clone https://github.com/wryan67/ipAddr.git

### Compling

Navigate to the cloned repository then run make:

    $ cd ipAddr
    $ make 

### Installing

Note that sudo is not required as the program will be installed for the current user only.  

    $ make install

### Running the program

You may need to log out and back in so that $HOME/bin will be in your path, or you may need to add it to your path manually by editing your .bashrc file.  To get the usage, use the -h option

    $ ipAddr -h
    usage: ipAddr [ -a hex_address ]

To determine the hex_address, you can use the built in i2c detect program like this:

    $ i2cdetect -y 1

Next add the correct address on the command line like this:

    $ ipAddr -a 0x27

### Enable boot time execution

Edit your crontab using:

    $ crontab -e

Then add the following line, but replayce the ${HOME} variables with the physical path to your home folder:

    @reboot ${HOME}/bin/ipAddr.sh -a 0x27 > ${HOME}/logs/ipAddr.log 2>&1
