(defproject stats "0.1.0-SNAPSHOT"
  :description 
  "# Stats: Statictics display in ClojureScript to be used by Cytodyem. #

The project displays statistic information on a right side of the Cytodyem window.
See the [Powerpoint on a Wiki page for more information](https://handyem.atlassian.net/wiki/display/SS/Alvin+release+scope).

The statistic display should include:

- Tabular representation of each data
    - Columns contain separate statistics values
    - Lines represent plots and gates

- Statistics is updated from Cytodyem's C++/CLI code.
"

  :url "https://handyem.atlassian.net/wiki/display/SS/Statistics+view"
  :dependencies [[org.clojure/clojure "1.5.1"]
                 [compojure "1.1.5"]]
  :plugins [[lein-ring "0.8.5"]]
  :ring {:handler stats.handler/app}
  :profiles
  {:dev {:dependencies [[ring-mock "0.1.5"]]}})
