#!/bin/bash
if [ -z $REBUILD ] ; then 		REBUILD="no"; fi
if [ -z $IMAGENAME ] ; then 		IMAGENAME="passcalc"; fi
if [ -z $CONTAINERNAME ] ; then 	CONTAINERNAME="passcalc"; fi
if [ -z $HTTPPORT ] ; then		HTTPPORT=80; fi
if [ -z $EXTERNALLYREACHABLE ] ; then	EXTERNALLYREACHABLE="no"; fi

docker images | grep "^${IMAGENAME} " > /dev/null
IMAGEEXISTS=$?	#This will be 0 if the image exists, otherwise it will be 1 (and will be built)

if [ $REBUILD != "no" ] || [ $IMAGEEXISTS -ne 0 ] ; then
	echo -e "### Rebuilding the dockerimage. It will be named '$IMAGENAME' ###"
	echo 'FROM alpine' > Dockerfile
	echo 'RUN apk add --update --no-cache lighttpd && rm -rf /var/cache/apk/*' >> Dockerfile
	echo 'COPY hexagon.jpg index.html light.html sha512.js /var/www/localhost/htdocs/' >> Dockerfile
	echo 'CMD ["lighttpd", "-D", "-f", "/etc/lighttpd/lighttpd.conf"]' >> Dockerfile
	docker build -t $IMAGENAME .
	rm Dockerfile
	echo ""
fi

echo -e "### Starting the container. It will be named '$CONTAINERNAME' and will listen to port $HTTPPORT ###"
if [ ! $EXTERNALLYREACHABLE == "no" ] ; then INTERFACE="0.0.0.0" ; else INTERFACE="127.0.0.1"; fi
docker run -d --rm -p $INTERFACE:$HTTPPORT:80 --name $CONTAINERNAME $IMAGENAME
echo -e "\n### It runs, you can stop it with 'docker stop $CONTAINERNAME' ###"
