(defproject applet "0.1.0-SNAPSHOT"
  :description "FIXME: write description"
  :url "http://example.com/FIXME"
  :license {:name "Eclipse Public License"
            :url "http://www.eclipse.org/legal/epl-v10.html"}
  :omit-source true
  :aot :all
  :dependencies [[org.clojure/clojure "1.5.1"]
                 [seesaw "1.4.3"]]
  :global-vars {*warn-on-reflection* true})