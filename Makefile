
LIBS=-lwiringPi -lwiringPiDev -lwiringPiLCD101rpi

all: ipAddr

ipAddr: ipAddr.c
	@gcc ${LIBS} ipAddr.c -o ipAddr
	@echo "ipAddr compiled successfully"

install: ipAddr
	@mkdir -p ${HOME}/bin
	@mkdir -p ${HOME}/logs
	@cp ipAddr    ${HOME}/bin	
	@cp ipAddr.sh ${HOME}/bin	
	@echo "ipAddr installed in ${HOME}/bin"
	@echo "see crontab.readme for suggested crontab setup"
	@echo "Add this line to your crontab for boot execution,"
	@echo "where XX is the address of your LCD1602:"
	@echo "@reboot ${HOME}/bin/ipAddr.sh -a XX > ${HOME}/logs/ipAddr.log 2>&1"
        

remove: 
	@rm -f ${HOME}/bin/ipAddr 
	@rm -f ${HOME}/bin/ipAddr.sh
	@echo "ipAddr removed from ${HOME}/bin"
	@echo "Don't forget to update crontab"

clean:
	@rm -f ipAddr
