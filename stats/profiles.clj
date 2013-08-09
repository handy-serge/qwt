{:dev {:source-paths ["src/clj" "src/cljs"]
       :test-paths ["test"]

       :cljsbuild {:builds
                   [{;; CLJS source code path
                     :source-paths ["src/cljs"]

                     :compiler {;; Google Clojure (CLS) configuration:
                                :output-to "resources/public/js/stats.js"
                                :optimizations :whitespace
                                :pretty-print true}}]}

       :dependencies [[;; Ring testing
                       ring-mock "0.1.5"]

                      ;; Use ClojuserScript browser REPL from nREPL.
                      [com.cemerick/piggieback "0.0.5"]]

       :plugins [;; Static code analysis
                 [lein-kibit "0.0.8"]
                 [lein-bikeshed "0.1.3"]

                 ;; Source code documentation
                 [lein-marginalia "0.7.1"]]

       ;; Code documentation configuration:
       :marginalia {;; Where to look for MathJax java script to display
                    ;; LaTex formulas in generated documentation.
                    :javascript [;; Link directly from MatJax web site
                                 "http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"]}


       ;; Repl configuration:
       :repl-options {:nrepl-middleware [cemerick.piggieback/wrap-cljs-repl]}
       :injections [(require '[cljs.repl.browser :as brepl]
                             '[cemerick.piggieback :as pb])
                    (defn browser-repl []
                      (pb/cljs-repl :repl-env
                                    (doto (brepl/repl-env :port 9000)
                                      cljs.repl/-setup)))]

       ;; Custom lein commands:
       :aliases {"@check" ["do" "bikeshed" "-v," "kibit"]
                 "@doc" ["do" "marg" "-d" "target/docs/marginalia"]}}}
