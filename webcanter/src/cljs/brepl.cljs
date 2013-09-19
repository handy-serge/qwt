(ns webcanter.brepl
  "Connection to the brower REPL server."
  (:require [clojure.browser.repl :as repl]))

(defn connect-repl 
  " Connects to the server side component of ClojureScript browser REPL.

  It is assumed that REPL runs on a default port 9000"
  [] 
  (repl/connect "http://localhost:9000/repl"))


;; We connect to the REPL as soon as window loaded.
;;
;; I discovered, that browser REPL does not work if the compiled
;; JavaScript with REPL is included in the `<head>` instead of being
;; included in the `<body>`.
;;
;; To mitigate this behavior, we connect to the REPL from `onload`
;; event. This may be non-ideal if we would like to use REPL for
;; debugging code that runs before page fully loaded. If it will
;; become important, we could compile REPL code into separate
;; ClojureScript file and include it before the rest of JavaScript.
(set! (.-onload js/window) connect-repl)

