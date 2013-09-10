(defproject experiment-stats "0.1.0-SNAPSHOT"
  :description
  ""
  :dependencies [[org.clojure/clojure "1.5.1"]
                 [compojure "1.1.5"]
                 [domina "1.0.2-SNAPSHOT"]
                 [hiccups "0.2.0"]]
  :plugins [[lein-ring "0.8.6"]
            [lein-cljsbuild "0.3.2"]]

  :ring {:handler experiment.handler/app})
