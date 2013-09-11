# Investigation rationale

As web applications running in the browser are limited both in terms
of performance and of functionnality (webapps do not have access to
the system in the same way as native app can), one possibility is to
run an applet as part of the webpage to potentially improve on those
two fronts.

In addition, this has the advantage of giving us access to a number of
libraries on the JVM that are not available in the browser.

However, this approach also has a number of downsides. One important
downside is that applets have been falling out of style for a number
of years now, first because of inconsistencies between different JVMs
and now at an accelerated pace because of the HTML5 standard that add
many of the functionnalities that required an applet in the
past. Other downsides include adding a requirement on the client side
(JVM), having to handle browser-applet communication, slower loading
of the webapp (JVM boot-up), etc.

This project's aim is to produce an applet from clojure code and test
it in a contect similar to the blacksmartie project. This will allow
to better appreciate how the pros and cons impact us in a very
concrete way.


# How to use this project

## Requirements

  * leiningen 2.2.0+
  * Java Development Kit (JDK) such as openjdk-6 or openjdk-7
  * bash
  * applet_server project (web server used to serve the applet)

## Building

A simple `lein uberjar` should suffice to build an applet. However,
unsigned applets do not have access to reflection which is used quite
often in dynamic languages such as clojure. An example how to sign the
applet is provided in the `build.sh` script at the root of the project.

## Status

The applet can be built and served. However, throws an exception when
loaded. Next step is to investigate the exception and resolve it.
