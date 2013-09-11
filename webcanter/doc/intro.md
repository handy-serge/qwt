# Introduction to Webcanter

So far, this tutorial follows the
[tutorial from data-sorcery.org](http://data-sorcery.org/2009/11/29/incanter-webapp/).

The changes include updating it for the current version of Compojure,
Hiccup and Ring.

Next step would be playing with it via REPL.

## Make the tutorial build.
Initial tutorial was written for the really old version of Compojure.
Compojure was split into several pieces and the syntax of the route
definition was changed.

Key peaces are the dependencies definitions in the project:

```clojure
(defproject webcanter "0.1.0-SNAPSHOT"
  :dependencies [[org.clojure/clojure "1.5.1"]
                 [incanter "1.5.4"]
                 [ring "1.2.0"]
                 [compojure "1.1.5"]]
  :main webcanter.main)
```

Then we do proper imports:

```clojure
(ns webcanter.main
  (:use compojure.core)
  (:require [compojure.handler :as handler]
            [compojure.route :as route]
            [ring.adapter.jetty :refer [run-jetty]]
            [hiccup.core :refer [html]]
            [hiccup.form :refer [form-to submit-button text-field]]
            [hiccup.page :refer [doctype]]
            [ring.middleware.params :refer [wrap-params]]
            [incanter.core :as incanter]
            [incanter.stats :as stats]
            [incanter.charts :as charts]
            [clojure.tools.logging :as log]
            [clj-logging-config.log4j :refer [set-logger!]]
            [webcanter.nrepl :as nrepl])
  (:import (java.io ByteArrayOutputStream
                    ByteArrayInputStream)))
```

Routes are defined differently:

```clojure
;; Set URL mapping for webservice.
(defroutes webservice
  (GET "/" []
       sample-form)
  (route/resources "/")
  (wrap-params (GET "/sample-normal" [request size mean sd]
                    (gen-samp-hist-png request size mean sd))))
```

And then jetty needs to be run as a part of main function:

```clojure
;; Run webservice.
(defn -main [& args]
  (set-logger!)
  (try
    (log/info "Initializing repl")
    (nrepl/initialize)
    (nrepl/log-server-status)
    (catch Throwable t
      (log/error t "Failed to start nREPL server")))
  (run-jetty #'webservice
             {:port 8080
              :join? false}))
```

## How to run the server

- From the `webcanter` folder, run the following command: `lein run`.
  This will start the server on localhost on a port 8080.
- Then in a Chrome open the page `localhost:8080`
  The page will display the form to input the number of points to
  display in the plot. Input some number, for example: `100`
- Press the button `view`
- It will display new page with the URL like this:
  `http://localhost:8080/sample-normal?size=100`
  The plot will show the image of the scatter plot rendered as PNG.

In a future, for experiments, it is possible to change the parameter
in the URL and refresh the page to see results updated.

## Preliminary performance results
To get rough idea of the performance, it is possible to use Chrome
developer tools to calculate how long it is take to get data on the
screen:

- Open Chrome Developer tools (For example, by pressing
  `Ctrl-Shift-J`)
- In a Chrome Developer tools pick `Network` tab
- Refresh the page. Chrome will show how much time request to the
  webserver took.

The screen will look somewhat like this:

![How to see the duration of HTTP request in Chrome](images/measure-operation-time-with-chrome.png)

Using this crude tool as a rough metric, we could have the rough idea
of the performance:

| Number of points |      Duration   |
|-----------------:|----------------:|
|              100 |        50-60 ms |
|             1000 |        50-60 ms |
|            10000 |      200-250 ms |
|           100000 |             3 s |
|           500000 |            49 s |
|           540000 |            57 s |
|          1000000 | 3.1 min = 181 s |

We see the big jump in duration between 100000 and 500000.

Our operation is quite complex:

- Generate data
- Calculate the scatter plot
- Transform scannter plot to PNG
- Send data via HTTP


Which part takes the time?
Could it run faster?
Need to run some more specific benchmarks.
