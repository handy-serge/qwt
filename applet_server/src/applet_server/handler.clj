(ns applet_server.handler
  (:use compojure.core)
  (:require [compojure.handler :as handler]
            [compojure.route :as route]))

(defroutes app-routes
  (GET "/" []
       "<html>
    <head><title>Fun with applets!</title></head>
    <body>
        <applet archive=\"applet-0.1.0-SNAPSHOT-standalone.jar\"
                code=\"applet.core.class\"
                width=\"640\"
                height=\"480\"></applet>
    </body>
</html>")
  (route/resources "/")
  (route/not-found "Not Found"))

(def app
  (handler/site app-routes))
