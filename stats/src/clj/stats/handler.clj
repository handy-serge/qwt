(ns stats.handler
  (:use compojure.core)
  (:require [compojure.handler :as handler]
            [compojure.route :as route]))

(defroutes app-routes
  (GET "/" [] "Hello World")
  (route/resources "/")
  (route/not-found "Not Found"))

(def app
  (handler/site app-routes))

;; This is just a function to test if kibit reports the problems.
(defn foo []
  (if (= 1 1)
    (println "work")
  nil))
