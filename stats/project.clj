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

  :source-paths ["src/clj" "src/cljs"]
  :test-paths ["test"]

  :dependencies [[org.clojure/clojure "1.5.1"]
                 [compojure "1.1.5"]
                 [domina "1.0.2-SNAPSHOT"]]
  :plugins [[lein-ring "0.8.6"]
            [lein-cljsbuild "0.3.2"]]

  :ring {:handler stats.handler/app}

  :cljsbuild {:builds
              [{;; CLJS source code path
                :source-paths ["src/cljs"]

                :compiler {;; Google Clojure (CLS) configuration:
                           :output-to "resources/public/js/stats.js"
                           :optimizations :whitespace
                           :pretty-print true}}]}
  :profiles
  {:dev {:dependencies [[;; Ring testing
                         ring-mock "0.1.5"]
                        [com.cemerick/piggieback "0.0.5"]]

         :plugins [;; Static code analysis
                   [lein-kibit "0.0.8"]
                   [lein-bikeshed "0.1.3"]

                   ;; Source code documentation
                   [lein-marginalia "0.7.1"]]

         :marginalia {;; Where to look for MathJax java script to display
                      ;; LaTex formulas in generated documentation.
                      :javascript [;; Link directly from MatJax web site
                                   "http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"]}

         :repl-options {:nrepl-middleware [cemerick.piggieback/wrap-cljs-repl]}
         :injections [(require '[cljs.repl.browser :as brepl]
                               '[cemerick.piggieback :as pb])
                      (defn browser-repl []
                        (pb/cljs-repl :repl-env
                                      (doto (brepl/repl-env :port 9000)
                                        cljs.repl/-setup)))]

         :aliases {"@check" ["do" "bikeshed" "-v," "kibit"]
                   "@doc" ["do" "marg" "-d" "target/docs/marginalia"]}}})
