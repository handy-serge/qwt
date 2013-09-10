#!/bin/bash

## Create applet jar

keytool -genkey -alias mycert -dname "cn=handyem, c=en"
keytool -selfcert -alias mycert -dname "cn=handyem, c=en"

rm target/*standalone.jar

lein uberjar

JAR=`ls target/*standalone.jar`

jarsigner $JAR mycert

cp $JAR ../applet_server/resources/public
