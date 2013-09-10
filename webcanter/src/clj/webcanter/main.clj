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
            [incanter.charts :as charts])
  (:import (java.io ByteArrayOutputStream
                    ByteArrayInputStream)))


(defn html-doc
  [title & body]
  (html
   (doctype :html5)
   [:html
    [:head
     [:title title]]
    [:body
     [:div
      [:h2
       [:a {:href "/"}
        "Generate a normal sample"]]]
     body]]))


(def sample-form
  (html-doc "Dissplay an Incanter plot in a web page."
            (form-to [:get "/sample-normal"]
                     "sample size: " (text-field {:size 4} :size)
                     (submit-button "view"))))


(defn gen-samp-hist-png
  [request size-str mean-str sd-str]
  (let [;; Parse request parameters.
        size (if (nil? size-str)
               1000
               (Integer/parseInt size-str))

        ;; Create sample data
        sample-x (stats/sample-poisson size
                                       :lambda 8000)

        sample-y (stats/sample-poisson size
                                       :lambda 8000)

        ;; Create the scatter-plot chart
        chart (doto (charts/scatter-plot
                     sample-x sample-y
                     :title "Poisson on Poisson"
                     :density? true)
                (charts/set-x-range 7500 9000)
                (charts/set-y-range 7500 9000))

        ;; Serialize the chart as .PNG image
        out-stream (ByteArrayOutputStream.)
        in-stream (do
                    (incanter/save chart 
                                   out-stream
                                   :width 300
                                   :height 300)                    
                    (ByteArrayInputStream.
                     (.toByteArray out-stream)))

        ;; Made HTTP responce to be send to web page.
        responce {:status 200
                  :headers {"Content-Type" "image/png"}
                  :body in-stream}]
    responce))


;; Set URL mapping for webservice.
(defroutes webservice
  (GET "/" []
       sample-form)
  (wrap-params (GET "/sample-normal" [request size mean sd]
                    (gen-samp-hist-png request size mean sd))))


;; Run webservice.
(defn -main [& args]
  (run-jetty #'webservice 
             {:port 8080
              :join? false}))
