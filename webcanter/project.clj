(defproject webcanter "0.1.0-SNAPSHOT"
  :description "Exploration on using Incanter for displaying cytometry data in a web page."
  :url "https://github.com/handyem/sandbox"
  :license {:name "Closed Source, Property of Handyem."}
  :dependencies [[org.clojure/clojure "1.5.1"]
                 [incanter "1.5.4"]
                 [ring "1.2.0"]
                 [compojure "1.1.5"]]
  :main webcanter.main)
