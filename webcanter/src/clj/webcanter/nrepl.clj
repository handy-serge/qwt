;; # nREPL in-application server.
;;
;; nREPL integrated inside of application allows debugging and hot
;; patching the blacksmartie code directly on device.
;;
;; For details see: [nRepl](https://github.com/clojure/tools.nrepl)
;;
;; To enable nREPL server in blacksmartie, put blacksmartie in
;; advanced mode and either:
;;
;; * Use lein:
;;   `lein nrepl connect aabb19001:7888`
;; * Or, directly in emacs (It will ask for the address and port of
;;   the server to connecto to):
;;   `M-x nrepl`
;;
;; After, when in nrepl you can call any function and inspect any
;; variables, for example:
;;
;;     ;; Inspect interface 'blacksmartie.nrepl'
;;     (in-ns 'blacksmartie.nrepl)
;;     port-number ; => 7888
;;
;; For more details, see the chapter 10 or the "Clojure Programming",
;; p. 393.
;;

(ns webcanter.nrepl
  "Handles in-application nREPL server"
  (:require [clojure.tools.logging :as log]
            [clojure.tools.nrepl.server :refer [start-server stop-server default-handler]]
            [cemerick.piggieback :as pback]))

;; (require '[cljs.repl.browser :as brepl]
;;          '[cemerick.piggieback :as pb])
;; (defn browser-repl []
;;   (pb/cljs-repl :repl-env
;;                 (doto (brepl/repl-env :port 9000)
;;                   cljs.repl/-setup)))


(require 'cljs.repl.browser)

(defn browser-repl
  "Starts browser repl on  default port 9000"
  []
  (cemerick.piggieback/cljs-repl
   :repl-env (cljs.repl.browser/repl-env :port 9000)))

(def port-number
  "Default port number to be  used for in-application nRepl server connection."
  7888)

(def server
  "Connection details to running nrepl server."
  (atom nil))

(defn server-started?
  "Checks if server is already running"
  []
  (let [is-running (not (nil? @server))]
    is-running))

(defn start-nrepl-server-with-piggieback
  "Start nREPL server on a given port"
  [port]
  (let [server-info (start-server 
                     :handler (default-handler #'pback/wrap-cljs-repl) 
                     :port port-number)]
      (log/info "Started nREPL server on a port with piggieback: " port)
      server-info))

(defn start-nrepl-server
  "Start nREPL server on a given port"
  [port]
  (let [server-info (start-server :port port-number)]
      (log/info "Started nREPL server on a port: " port)
      server-info))

(defn stop-nrepl-server
  "Stop nREPL server that is currently in run."
  []
  (reset! server (stop-server @server))
  (log/info "Stopped nREPL server"))

(defn log-server-status
  "Logs debug information about the status of the nREPL server"
  []
  (log/info "nREPL server is started: " (server-started?))
  (log/info "nREPL server details:" @server))

(defn initialize
  "Starts nREPL server on a default port
   only if run in advanced mode and only if not already running.

   Returns information about running server.

   * Default port is set by `nrepl-server-port` constant.
   * Server is started only if `advanced-mode?` configuration parameter is `true`.
  "
  []
  (if (server-started?)
    @server
    (reset! server (start-nrepl-server-with-piggieback  port-number))))

