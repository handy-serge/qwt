(defproject experiment-stats "0.1.0-SNAPSHOT"
  :description
  "# Statictics display in ClojureScript to be used by Cytodyem. #

  The project displays statistic information on a right side of the Cytodyem window.
  See the [Powerpoint on a Wiki page for more information][1].

  The statistic display should include:

  - Tabular representation of statistical data:
      - Columns contain separate statistics values
      - Lines represent plots and gates
  - Statistics is updated from Cytodyem's C++/CLI code.

  [1]: https://handyem.atlassian.net/wiki/display/SS/Alvin+release+scope
"

  :url "https://handyem.atlassian.net/wiki/display/SS/Statistics+view"

  :dependencies [[org.clojure/clojure "1.5.1"]
                 [compojure "1.1.5"]
                 [domina "1.0.2-SNAPSHOT"]
                 [hiccups "0.2.0"]]
  :plugins [[lein-ring "0.8.6"]
            [lein-cljsbuild "0.3.2"]]

  :ring {:handler experiment.handler/app})
