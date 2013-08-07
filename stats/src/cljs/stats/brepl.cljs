(ns experiment.stats.brepl
  "Connection to the brower REPL server."
  (:require [clojure.browser.repl :as repl]))

;; By default, the port 9000 is used.
(repl/connect "http://localhost:9000/repl")
