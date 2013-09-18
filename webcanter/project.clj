(defproject webcanter "0.1.0-SNAPSHOT"
  :description "Exploration on using Incanter for displaying cytometry data in a web page."
  :url "https://github.com/handyem/sandbox"
  :license {:name "Closed Source, Property of Handyem."}
  :dependencies [[org.clojure/clojure "1.5.1"]
                 [incanter "1.5.4"]
                 [ring "1.2.0"]
                 [compojure "1.1.5"]]

  :plugins [[lein-cljsbuild "0.3.2"]]
  :source-paths ["src/clj" "src/cljs"]
  :test-paths ["test"]
  :main webcanter.main

  ;; I try to check how much data we can process, so we tell Java to
  ;; get more memory.
  :jvm-opts ["-Xmx1g" ; Maximum heap size - 1Gigabyte.
             ])
